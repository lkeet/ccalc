#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#define MAX_RESOLUTION 16

// Struct for storing an array as well as the array's resolution
typedef struct
{
    uint8_t resolution;
    int array[MAX_RESOLUTION];
} base10_array_t;

// Struct for storing a binary value as well as if it is signed
typedef struct
{
    bool signed_bit;
    char binary[MAX_RESOLUTION];
} binary_t;

// Returns a base10_array containing powers of 2
base10_array_t array_fill(uint8_t resolution) 
{
    base10_array_t bin_arr;
    bin_arr.resolution = resolution;
    uint8_t base = resolution - 1;
    for (uint8_t i = 0; i < resolution; i++)
    {
        bin_arr.array[i] = pow(2, base);
        base -= 1;
    }
    return bin_arr;
}

// Returns the integer sum of a filled base10_array
uint32_t array_sum(base10_array_t bin_arr) 
{
    uint64_t sum = 0;
    for (uint8_t i = 0; i < bin_arr.resolution; i++)
    {
        sum += bin_arr.array[i];
    }
    return sum;
}

// Returns the maximum base-10 value of a given resolution
int max_val(uint8_t resolution) 
{
    return array_sum(array_fill(resolution));
}

// Returns the minimum resolution of a base-10 value
uint8_t calc_resolution(int base10) 
{
    uint8_t resolution = 1;
    while (abs(base10) > max_val(resolution))
    {
        resolution += 1;
    }
    return resolution;
}

// Returns True/False depending on whether the string parameter is valid binary
bool is_valid(binary_t binary) 
{
    for (uint8_t i = 0; i < strlen(binary.binary); i++)
    {
        if (!(binary.binary[i] == '1' || binary.binary[i] == '0'))
        {
            return false;
        }
    }
    return true;
}

// Returns a truncated binary type (removes 0's from front of string)
binary_t truncate(binary_t binary)
{
    binary_t return_struct;
    bool full_zero = true;
    for (uint8_t i = 0; i < strlen(binary.binary); i++) // For loop for checking the string contains a 1 to truncate to
    {
        if (binary.binary[i] == '1')
        {
            full_zero = false;
        }
    }
    if (is_valid(binary) && !full_zero)
    {
        strcpy(return_struct.binary, memchr(binary.binary, '1', strlen(binary.binary)));
    }
    return return_struct;
}

// Returns the binary equivalent of a base-10 integer as a binary type
binary_t convert(int base10)
{
    binary_t return_struct; strcpy(return_struct.binary, "");
    uint8_t resolution = calc_resolution(base10);
    for (uint8_t i = 0; i < resolution; i++)
    {
        if (base10 - array_fill(resolution).array[i] >= 0)
        {
            strcat(return_struct.binary, "1");
            base10 -= array_fill(resolution).array[i];
        }
        else
        {
            strcat(return_struct.binary, "0");
        }
    }
    return return_struct;
}

// Returns an integer value from a binary type of any resolution
int base10(binary_t binary)
{
    if (is_valid(binary))
    {
        int result = 0;
        for (uint8_t i = 0; i < strlen(binary.binary); i++)
        {
            if (binary.binary[i] == '1')
            {
                result += array_fill(strlen(binary.binary)).array[i];
            }
        }
        return result;
    }
    else
    {
        return -1;
    }
}

// Returns the binary sum of two binary type
binary_t binary_add(binary_t binary1, binary_t binary2)
{
    return convert(base10(binary1) + base10(binary2));
}

// Returns the one's complement of a binary type
binary_t complement(binary_t binary)
{
    binary_t return_struct; strcpy(return_struct.binary, "");
    if (is_valid(binary))
    {
        for (uint8_t i = 0; i < strlen(binary.binary); i++)
        {
            if (binary.binary[i] == '1')
            {
                strcat(return_struct.binary, "0");
            }
            else
            {
                strcat(return_struct.binary, "1");
            }
        }
    return return_struct;
    }
}

// Returns the two's complement of a binary type
binary_t twos_complement(binary_t binary)
{
    return convert(base10(complement(binary)) + 1);
}

void print_binary(binary_t binary)
{
    printf("%s", binary.binary);
}
