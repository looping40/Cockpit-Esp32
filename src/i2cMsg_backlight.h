#pragma once
#include  <Arduino.h>

#define MAX(x,y) x > y ? x : y

#define NB_BYTES_BCK_LIGHT (1+1+3)  //addr + cde_backlight + rgb

typedef union {
    uint8_t data[NB_BYTES_BCK_LIGHT];

   struct{
      uint8_t i2c_addr;

      uint8_t cde_bcklight;
      uint8_t lightR; 
      uint8_t lightB; 
      uint8_t lightG;
   };
}T_backlight_master2panel; 

#define BCKLIGHT_NB_BITS 0
#define BCKLIGHT_NB_AXIS 0


