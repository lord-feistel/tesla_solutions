#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

// 1
// as 9/2 = 1.8
// it's better to simplify things

#define C_TO_F(c)   c * 1.8 + 32 ;


// 2
// The type returning was wrong with just 8 bits
// what would cause a overflow

uint16_t computerSquareADC(volatile uint8_t *x)
{

    // fixed it was a 8 bits variable
    // what is not enough to hold de square of
    // a 8 bits, since in the worser case the result is
    // 65025 ( 255 ^ 2)
    // the 

    uint16_t retval = *x * *x;
    return retval;
}
 


void swapBits(uint8_t* b)
{

    unsigned int set1 = (*b >> 3) & ((1U << 2) - 1);
    unsigned int set2 = (*b >> 7) & ((1U << 2) - 1);
    unsigned int Xor = (set1 ^ set2);
    Xor = (Xor << 3) | (Xor << 7);
    unsigned int result = *b ^ Xor;

}


int main()
{

    float a = C_TO_F(89.8);
    printf("%f\n", a); 

    uint8_t x = 255;
    uint16_t result =  computerSquareADC(&x);
     printf("%d\n", result);

    uint8_t b = 0x88;
    swapBits(&b);
    printf("%d\n", b);


}