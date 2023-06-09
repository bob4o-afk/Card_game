#include <stdio.h>
#include <stdint.h>
#include <string.h>


// Blowfish encryption
void blowfish_encrypt(uint32_t* xl, uint32_t* xr, const uint32_t* P, const uint32_t (*S)[256]) {
    uint32_t Xl = *xl;
    uint32_t Xr = *xr;
    uint32_t temp;
    size_t i;

    for (i = 0; i < 16; ++i) {
        Xl ^= P[i];
        Xr ^= F(Xl, S);
        temp = Xl;
        Xl = Xr;
        Xr = temp;
    }

    temp = Xl;
    Xl = Xr;
    Xr = temp;
    Xr ^= P[16];
    Xl ^= P[17];

    *xl = Xl;
    *xr = Xr;
}


// Blowfish key schedule (needs to be finished)
void blowfish_key_schedule(uint32_t* P, uint32_t* S, const uint8_t* key, size_t key_len) {
    size_t i, j;
    uint32_t data, datal, datar;
    static const uint32_t Pinit[18] = {
        0x243F6A88, 0x85A308D3, 0x13198A2E, 0x03707344,
        0xA4093822, 0x299F31D0, 0x082EFA98, 0xEC4E6C89,
        0x452821E6, 0x38D01377, 0xBE5466CF, 0x34E90C6C,
        0xC0AC29B7, 0xC97C50DD, 0x3F84D5B5, 0xB5470917,
        0x9216D5D9, 0x8979FB1B
    };
    static const uint32_t Sinit[4][256] = {
        { // S1
            0xD1310BA6, 0x98DFB5AC, 0x2FFD72DB, 0xD01ADFB7,
            // ...
        },
        // S2, S3, S4
    };

    memcpy(P, Pinit, sizeof(Pinit));
    memcpy(S, Sinit, sizeof(Sinit));

    j = 0;
    for (i = 0; i < 18; ++i) {
        data = 0x00000000;
        for (size_t k = 0; k < 4; ++k) {
            data = (data << 8) | key[j];
            j = (j + 1) % key_len;
        }
        P[i] ^= data;
    }

    datal = 0x00000000;
    datar = 0x00000000;

    for (i = 0; i < 18; i += 2) {
        blowfish_encrypt(&datal, &datar, P, S);

        P[i] = datal;
        P[i + 1] = datar;
    }

    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 256; j += 2) {
            blowfish_encrypt(&datal, &datar, P, S);

            S[i][j] = datal;
            S[i][j + 1] = datar;
        }
    }
}



// Blowfish Feistel function
uint32_t F(uint32_t x, const uint32_t (*S)[256]) {
    uint8_t a, b, c, d;
    uint32_t y;

    d = x & 0x00FF;
    x >>= 8;
    c = x & 0x00FF;
    x >>= 8;
    b = x & 0x00FF;
    x >>= 8;
    a = x & 0x00FF;

    y = S[0][a] + S[1][b];
    y ^= S[2][c];
    y += S[3][d];

    return y;
}

// Encrypt the cards file using Blowfish algorithm
void encrypt_file(const char* input_file, const char* output_file, const char* key) {
    uint32_t P[18];
    uint32_t S[4][256];
    uint8_t key_bytes[8];
    uint8_t buf[8];
    FILE* input;
    FILE* output;
    size_t bytes_read;

    // Convert the key to bytes
    size_t key_len = strlen(key);
    for (size_t i = 0; i < 8; ++i) {
        key_bytes[i] = key[i % key_len];
    }

    // Initialize Blowfish key schedule
    blowfish_key_schedule(P, S, key_bytes, 8);

    // Open input and output files
    input = fopen(input_file, "rb");
    output = fopen(output_file, "wb");

    if (input == NULL || output == NULL) {
        printf("Failed to open input or output file\n");
        return;
    }

    // Encrypt the input file block by block
    while ((bytes_read = fread(buf, sizeof(uint8_t), sizeof(buf), input)) > 0) {
        uint32_t* data = (uint32_t*)buf;

        // Encrypt the block
        blowfish_encrypt(&data[0], &data[1], P, S);

        // Write the encrypted block to the output file
        fwrite(buf, sizeof(uint8_t), bytes_read, output);
    }

    // Close input and output files
    fclose(input);
    fclose(output);

    printf("Encryption completed. Output file: %s\n", output_file);
}

//main
int main() {
    const char* input_file = "kartipartibelot (1).txt";
    const char* output_file = "output.txt";
    const char* key = "7Hs9@*eFpXq#2v";

    encrypt_file(input_file, output_file, key);

    return 0;
}
