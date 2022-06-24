#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// 1

// as 9/5 =  1.8
// it's better to simplify things

#define C_TO_F(c) (float)(c * 1.8 + 32)

// 2

//    The type was returning  8 bits
//    what may cause a overflow, e.g.
//    the worser case would be
//
//    *x = 255 // all 8 bits setted, thus
//    *x * *x = 65025
//
//     Thus we changed for a 16 bits (uint16_t)
//     return type what accomodate even the worser
//     case.



uint16_t computerSquareADC(volatile uint8_t *x) {

  uint16_t retval = *x * *x;
  return retval;
}


// 3

void swapBits(uint8_t *b) {

  // get first nibble
  unsigned int nibble_1 = (*b >> 3) & ((1U << 2) - 1);

  // get second nibble
  unsigned int nibble_2 = (*b >> 7) & ((1U << 2) - 1);

  // mask
  unsigned int Xor = (nibble_1 ^ nibble_1);
  Xor = (Xor << 3) | (Xor << 7);

  // apply it
  unsigned int result = *b ^ Xor;
}


typedef enum { IDLE, READY, VENDING, FAULT } state_E;

typedef enum {
  COIN,
  COIN_RETURN,
  BUTTON,
  VEND_COMPLETE,
  GENERIC_FAULT
} input_E;

// Always start on IDLE as specified

state_E state = IDLE;

state_E stateMachine(input_E input) {
  state_E output = state;

  switch (input) {
  case GENERIC_FAULT:
    output = FAULT;
    ;
    state = output;
    break;
  case COIN:
    if (state = IDLE) {
      output = READY;
      state = output;
    }
    break;
  case COIN_RETURN:
    if (state = READY) {
      output = IDLE;
      state = output;
    }
  case BUTTON:
    if (state = READY) {
      output = VENDING;
      state = output;
    }
    break;
  case VEND_COMPLETE:
    if (state == VENDING) {
      output = IDLE;
      state = output;
    }
    break;
  default:
    break;
  }

  return output;
}



#define ARR_SIZE 5
#define LAST_X ARR_SIZE - 1
#define BEGIN 0

// get from Bresenham’s Line Generation Algorithm
// at online generator

float arrX[ARR_SIZE] = { 0, 1.5, 3,     5.6,  100 };
float arrY[ARR_SIZE] = { 0, 8,   16.89,  53.5, 99 };

float interpolation(float val) {

  // In case val is not in the range
  // previously mentioned : 0 <= i < n

  float interpolated_value = -1;

  if ((val >= arrX[LAST_X]) || ((val < arrX[BEGIN]))) {
    return interpolated_value;
  }

  for (int i = 0; i < ARR_SIZE; i++) {

    if (val >= arrX[i]) {

      // optimization in case val
      // has the same value of a already
      // known arrX element
      if (val == arrX[i]) {
        return arrY[i];
      } else {

        //  interpolation formula to get val:
        //
        //  y = y1 +   (y2 - y1) / (x2 - x1)  * (x - x1)
        //

        interpolated_value = arrY[i] + ((float)(arrY[i + 1] - arrY[i]) / (arrX[i + 1] - arrX[i])) * (val - arrX[i]);
      }
    }
  }

  return interpolated_value;
}



int main() {

  
  // float a = C_TO_F(1.567);
  // printf("%f\n", a);  

  printf("celsius to fareinheit\n");  
  ( ( C_TO_F(1.567) ) == 34.820599f )? printf("pass\n") : printf("fail\n") ; 

  //uint16_t result = computerSquareADC(&x);
  //printf("%d\n", result);
  
  printf("root square\n");
  uint8_t x = 255;
  ( computerSquareADC(&x) == 65025)? printf("pass\n") : printf("fail\n") ;

  
  uint8_t b = 0x88;
  
  // swapBits(&b);
  //printf("%d\n", b);

  printf("bit swap\n");
  swapBits(&b);
  ( b == 0x88) ? printf("pass\n") : printf("fail\n") ;   

 

 printf("Interpolation\n");
 float val = 1.6;
 
 //printf("%f\n",  interpolation(val));
 
 ( interpolation(val) == 8.592667f) ? printf("pass\n") : printf("fail\n") ;   








  

  
}