#define USE_BACKLIGHT

#include "backlight.h"

//#define dgb_backlight


void PCA9634_WriteReg(unsigned int areg, unsigned int adata){
   i2c_start();
   #if defined(dgb_backlight) && defined(USE_RS232)
   printf("1=%u\r\n", i2c_write(I2C_PCA9634<<1));               
   printf("2=%u\r\n", i2c_write(areg));                    
   printf("3=%u\r\n", i2c_write(adata));
   #else
   i2c_write(I2C_PCA9634<<1);
   i2c_write(areg);                    
   i2c_write(adata);
   #endif
   i2c_stop();
   delay_ms(1);
}


void PCA9634_SoftReset(){
  #if defined(dgb_backlight) && defined(USE_RS232)
  printf("Soft reset...\r\n");
  #endif
  i2c_start();
  
  #if defined(dgb_backlight) && defined(USE_RS232)
  printf("R1=%u\r\n", i2c_write(I2C_PCA9634_RST<<1));
  printf("R2=%u\r\n", i2c_write(0xA5));                    
  printf("R3=%u\r\n", i2c_write(0x5A));
  #else
  i2c_write(I2C_PCA9634_RST<<1);
  i2c_write(0xA5);                    
  i2c_write(0x5A);
  #endif
    
  i2c_stop();
  
  #if defined(dgb_backlight) && defined(USE_RS232)
  printf("Soft reset done.\r\n");
  #endif
}  

void backlight_group(unsigned char r, unsigned char b, unsigned char g){
  //update local WS2812
  /*ws2812_colors(r, b, g);
  #ifndef USE_RS232
  send_leds();
  delay_ms(1);
  send_leds();
  #endif*/
    
  //update PCA9634
  PCA9634_WriteReg(PCA9634_REG_GRPPWM, g>>2); 
  
  //General call with rbg values
  i2c_start();
  i2c_write(I2C_BACKLIGHT);
  i2c_write(PCA9634_REG_GRPPWM);
  i2c_write(r>>2);
  i2c_write(b>>2);
  i2c_write(g>>2);
  i2c_stop();
    
  #if defined(dgb_backlight) && defined(USE_RS232)
  printf("backlight group set to %u,%u,%u\r\n", r,b,g);
  #endif
}



// *********************************************************************
unsigned int8 panel_Backlight_init(){
  #if defined(dgb_backlight) && defined(USE_RS232)
  printf("Backlight init...\r\n");
  #endif
  
  prev_backlightColor.r = 0;
  prev_backlightColor.b = 0;
  prev_backlightColor.g = 20;
  
  PCA9634_SoftReset();
  
  PCA9634_WriteReg(PCA9634_REG_LEDOUT0,PCA9634_ALL_LED_TO_GRPPWM);
  PCA9634_WriteReg(PCA9634_REG_LEDOUT1,PCA9634_ALL_LED_TO_GRPPWM);
  
  //set output to totem-pole structure
  //PCA9634_WriteReg(PCA9634_REG_MODE2,0b00000101);
  //set output to open-drain structure
  PCA9634_WriteReg(PCA9634_REG_MODE2,0b00000001);  
  
  backlight_group(prev_backlightColor.r, prev_backlightColor.b, prev_backlightColor.g);
  
  // set normal mode
  PCA9634_WriteReg(PCA9634_REG_MODE1,0b0000001); 

  //delay to avoid led flash
  delay_ms(5);
  
  //individual PWM to 0xFF, dimming will be done using group
  for (int i=0;i<8;i++){
    PCA9634_WriteReg(PCA9634_REG_PWM0+i,0xFF);
  }
  
  panel_Backlight.i2c_connected = 1;
  
  #if defined(dgb_backlight) && defined(USE_RS232)
  printf("Backlight init done\r\n");
  #endif
  
  return 0;
}


void backlight_group_up(){
  prev_backlightColor.g+=10;
  if(prev_backlightColor.g > 200){
      prev_backlightColor.g = 200;
  }
  backlight_group(prev_backlightColor.r, prev_backlightColor.b, prev_backlightColor.g);
}


void backlight_group_dwn(){
  if(prev_backlightColor.g >= 10){
      prev_backlightColor.g-=10;
  }
  backlight_group(prev_backlightColor.r, prev_backlightColor.b, prev_backlightColor.g);
}


unsigned int8 panel_Backlight_show(unsigned int8 cde){
    if (cde==I2C_BACKLIGHT) {
        usb_get_packet(USB_EP_COMMAND, &backlightColor, sizeof(backlightColor));
        
        if(backlightColor.val != prev_backlightColor.val){ 
            #if defined(dgb_backlight) && defined(USE_RS232)
            printf("backlight new val to %u,%u,%u\r\n", backlightColor.r,backlightColor.b,backlightColor.g);
            #endif
            prev_backlightColor.val = backlightColor.val;
            backlight_group(prev_backlightColor.r, prev_backlightColor.b, prev_backlightColor.g);
        }
             
        return 1;
    }else
        return 0;
}


void panel_Backlight_report(T_report_idx *report_idx){
}

