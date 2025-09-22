#include <stdio.h>
#include <stdint.h>

#define ARRAY_SIZE 9

int32_t get_unique_num(int32_t *array, size_t len)
{	
	int32_t res = 0;

    for (size_t i = 0; i < len; i++) 
    {
        res ^= array[i];
    }

    return res;	
}

int main() 
{
    int32_t array[ARRAY_SIZE] = {1, 2, 3, 4, 5, 4, 3, 2, 1};
    printf("Unique number: %d\r\n", get_unique_num(array, ARRAY_SIZE));
    return 0;
}