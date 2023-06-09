#include <stdint.h>
#include <stdio.h>

void blowfish_encrypt(uint32_t *xl, uint32_t *xr,  uint32_t *P, uint32_t (*S)[256]);
void blowfish_key_schedule(uint32_t *P, uint32_t *S, const uint8_t *key,size_t key_len);
uint32_t Feistel(uint32_t x, const uint32_t (*S)[256]);
void encrypt_file(const char *input_file, const char *output_file, const char *key);
