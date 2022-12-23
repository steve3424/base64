#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "base64.c"

int main() {
    char* bytes = "abcdefg";
    printf("Input: %s\n", bytes);
    PrintBits(bytes, strlen(bytes));

    char* res = Base64Encode(bytes, strlen(bytes));
    printf("Output: %s\n", res);
    PrintBits(res, strlen(res));

    uint64_t dec_len = 0;
    uint8_t* dec = Base64Decode(res, &dec_len);
    char* s = malloc(dec_len + 1);
    memcpy(s, dec, dec_len);
    s[dec_len] = '\0';
    printf("Decode: %s\n", s);
    PrintBits(dec, dec_len);

    return 0;
}
