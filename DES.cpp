#include <iostream>
#include <string>
#include <math.h>
#ifdef __GNUC__
# define __rdtsc __builtin_ia32_rdtsc
#else
# include<intrin.h>
#endif
using namespace std;
typedef unsigned long long u64;

int initial_perm_arr[64] = { 58, 50, 42, 34, 26, 18, 10, 2,
                                60, 52, 44, 36, 28, 20, 12, 4,
                                62, 54, 46, 38, 30, 22, 14, 6,
                                64, 56, 48, 40, 32, 24, 16, 8,
                                57, 49, 41, 33, 25, 17, 9, 1,
                                59, 51, 43, 35, 27, 19, 11, 3,
                                61, 53, 45, 37, 29, 21, 13, 5,
                                63, 55, 47, 39, 31, 23, 15, 7 };

int expansion_perm_arr[48] = { 32, 1, 2, 3, 4, 5, 4, 5,
                            6, 7, 8, 9, 8, 9, 10, 11,
                            12, 13, 12, 13, 14, 15, 16, 17,
                            16, 17, 18, 19, 20, 21, 20, 21,
                            22, 23, 24, 25, 24, 25, 26, 27,
                            28, 29, 28, 29, 30, 31, 32, 1 };

int p_perm_arr[32] = { 16, 7, 20, 21,
                          29, 12, 28, 17,
                          1, 15, 23, 26,
                          5, 18, 31, 10,
                          2, 8, 24, 14,
                          32, 27, 3, 9,
                          19, 13, 30, 6,
                          22, 11, 4, 25 };

int pc1_arr[56] = {
        57, 49, 41, 33, 25, 17, 9,
        1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29,
        21, 13, 5, 28, 20, 12, 4 };

int pc2_arr[48] = {
        14, 17, 11, 24, 1, 5,
        3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8,
        16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32 };

int final_perm_arr[64] = { 40, 8, 48, 16, 56, 24, 64, 32,
                          39, 7, 47, 15, 55, 23, 63, 31,
                          38, 6, 46, 14, 54, 22, 62, 30,
                          37, 5, 45, 13, 53, 21, 61, 29,
                          36, 4, 44, 12, 52, 20, 60, 28,
                          35, 3, 43, 11, 51, 19, 59, 27,
                          34, 2, 42, 10, 50, 18, 58, 26,
                          33, 1, 41, 9, 49, 17, 57, 25 };

u64 s_boxes_arr[] =
{
    14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
    0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
    4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
    15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13,
    15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
    3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
    0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
    13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9,
    10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
    13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
    13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
    1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,
    7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
    13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
    10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
    3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14,
    2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
    14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
    4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
    11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3,
    12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
    10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
    9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
    4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13,
    4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
    13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
    1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
    6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12,
    13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
    1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
    7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
    2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
};


u64 read_u64_hex(const char* data)
{
    u64 ret = 0;
    for (;; ++data)//read left
    {
        unsigned char dec = *data - '0';
        if
            (dec < 10)
            ret = ret << 4 | dec;
        else {
            unsigned  char upper = (*data & 0xDF) - 'A';
            if (upper > 5)
                break;
            ret = ret << 4 | upper + 10;
        }
    }
    return ret;
}


u64 hex_to_bin(const char* data)
{
    //assert(strlen(data) == 16);
    u64 value = 0;
    for (int i = 0; i < 16; ++i)
    {
        char c = data[i];
        if (c >= '0' && c <= '9')
            value |= (u64)(c - '0') << ((15 - i) << 2);
        else if (c >= 'A' && c <= 'F')
            value |= (u64)(c - 'A' + 10) << ((15 - i) << 2);
        else if (c >= 'a' && c <= 'f')
            value |= (u64)(c - 'a' + 10) << ((15 - i) << 2);
    }
    return value;
}

u64 shift_left(u64 key, int n)
{
    u64 leftShifted;
    int x = n == 1 ? 1 : 11;
    leftShifted = ((key << n) & ~(x << 28)) | (key >> (28 - n));
    return leftShifted;
}

u64 permute(u64 in, int* permutation, int out_size, int in_size)
{
    u64 out = 0;
    for (int i = 0; i < out_size; ++i)
        out |= (in >> (in_size - permutation[out_size - 1 - i]) & 1) << i;
    return out;
}

u64 initial_perm(u64 value)
{
    return permute(value, initial_perm_arr, 64, 64);
}

u64 expansion_perm(u64 value)
{
    return permute(value, expansion_perm_arr, 48, 32);
}

u64 p_perm(u64 value)
{
    return permute(value, p_perm_arr, 32, 32);
}

u64 p1_perm(u64 value)
{
    return permute(value, pc1_arr, 56, 64);
}

u64 p2_perm(u64 value)
{
    return permute(value, pc2_arr, 48, 56);
}

u64 final_perm(u64 value)
{
    return permute(value, final_perm_arr, 64, 64);
}

u64 s_Box(u64 value)
{
    u64* box;
    int index;
    u64 result = 0;
    for (int i = 0; i < 8; i++)
    {
        box = s_boxes_arr + i * 64;
        index = value >> (7 - i) * 6 & 0x3F;
        index = index >> 1 & 15 | (index & 1) << 4 | index & 0x20;
        result |= (box[index]) << (7 - i) * 4;
    }
    return result;
}

u64 Xor(u64 x ,u64 y)
{
    u64 result = x ^ y;
    return result;
}

void generate_Key(const char* input, u64* keys)
{
    u64 key = read_u64_hex(input);
    key = p1_perm(key);

    u64 left = key >> 28, right = key & (0xFFFFFFF);
    for (int i = 0; i < 16; i++)
    {
        if (i == 0 || i == 1 || i == 8 || i == 15)
        {
            left = shift_left(left, 1);
            right = shift_left(right, 1);
        }
        else
        {
            left = shift_left(left, 2);
            right = shift_left(right, 2);
        }
        keys[i] = p2_perm(((left << 28) | right));
    }
}
u64 Encryption(const char* plaintextinput, u64* keys)
{
    u64 temp;
    u64 plaintext = read_u64_hex(plaintextinput);
    plaintext = initial_perm(plaintext);
    u64 left = plaintext >> 32, right = plaintext & (0xFFFFFFFF);

    for (int i = 0; i < 16; i++)
    {
        temp = expansion_perm(right);
        temp = Xor(temp, keys[i]);
        temp = s_Box(temp);
        temp = p_perm(temp);
        temp = Xor(temp, left);
        left = right;
        right = temp;
    }
    swap(left, right);
    u64 result = left << 32 | right;
    result = final_perm(result);
    return result;
}

u64 Decryption(const char* plaintext, u64* keys)
{
    int start = 0, end = 15;
    u64 temp;
    while (start < end)
    {
        temp = keys[end];
        keys[end] = keys[start];
        keys[start] = temp;
        start++;
        end--;
    }
    return Encryption(plaintext, keys);
}

int main(int argc, char* argv[])
{
    string op = argv[1];
    char* key = argv[3];
    u64 generated_keys[16];
    generate_Key(key, generated_keys);

    if (op == "encrypt")
    {

        char* plain_text = argv[2];
        long long t1 = __rdtsc();
        u64 cipher_text = Encryption(plain_text, generated_keys);
        long long t2 = __rdtsc();
        printf("cipher: %016llX\n", cipher_text);
        printf("Cycles: %lld\n", t2 - t1);

    }

    else if (op == "decrypt")
    {
        char* cipher_text = argv[2];
        long long t1 = __rdtsc();
        u64 plain_text = Decryption(cipher_text, generated_keys);
        long long t2 = __rdtsc();
        printf("plain: %016llX\n", plain_text);
        printf("Cycles: %lld\n", t2 - t1);
    }
}
