#pragma once
#include  <Arduino.h>

#define NB_BYTES_ICP (1 + 1)        //addr + []

#define ICP_NB_BITS 32
#define ICP_NB_AXIS 4

typedef union{
   uint8_t data[NB_BYTES_ICP];
   
   struct{
       uint8_t i2c_addr;
       
       struct {
          uint8_t Bootloader:1;
       };
   };
} T_icp_master2panel;


typedef union {
    uint8_t data8[MAX(NB_BYTES_ICP, NB_BYTES_BCK_LIGHT)];
   
    T_icp_master2panel icp;
         
    T_backlight_master2panel backlight;
}T_icp_bcklight_Master2panel;


typedef union {
    uint8_t data[4+8];
    
    struct{
        uint32_t sw_32;
        uint16_t tw[ICP_NB_AXIS];
    };
    
    struct {
        uint8_t sw_8[4];
        word tw_word[ICP_NB_AXIS];
    };

    struct{
        uint8_t SimICPCom1:1;       //0
        uint8_t SimICPAA:1;         //1
        uint8_t SimICPTHREE:1;      //2
        uint8_t SimICPMark:1;       //3
        uint8_t SimICPEnter:1;      //4
        uint8_t SimDriftCOOn:1;     //5
        uint8_t SimICPCom2:1;       //6
        uint8_t SimICPAG:1;         //7

        uint8_t SimICPStpt:1;       //8
        uint8_t SimICPEIGHT:1;      //9
        uint8_t SimICPCLEAR:1;      //10
        uint8_t SimWarnReset:1;     //11
        uint8_t SimICPIFF:1;        //12
        uint8_t SimICPTILS:1;       //13
        uint8_t SimICPCrus:1;       //14
        uint8_t SimICPNINE:1;       //15

        uint8_t SimICPNext:1;       //16
        uint8_t SimFlirLevelDown:1; //17
        uint8_t SimICPLIST:1;       //18
        uint8_t SimICPALOW:1;       //19
        uint8_t SimICPSIX:1;        //20
        uint8_t SimICPZERO:1;       //21
        uint8_t SimICPPrevious:1;   //22 
        uint8_t SimFlirLevelUp:1;   //23
               
        uint8_t SimICPDEDUP:1;      //24
        uint8_t SimICPDEDDOWN:1;    //25
        uint8_t SimICPDEDSEQ:1;     //26
        uint8_t SimICPResetDED:1;   //27
        uint8_t SimHUDOn:1;         //28  SimICPFlirGain not used in BMS, override with SimHUDOn
        uint8_t SimHUDOff:1;        //29  SimICPFlirAutonot used in BMS, override with SimHUDOff
        uint8_t SimSetWX:1;         //30                  
        uint8_t SimDriftCOOff:1;    //31  !(SimDriftCOOn || SimWarnReset)
    };
}T_icp_panel2master;

/*
//int8 SimICPNav:1;

int8 SimDriftCO:1;


int8 SimBrtWheelUp
int8 SimBrtWheelDn
int8 SimSymWheelUp
int8 SimSymWheelDn
int8 SimHUDPower
int8 SimHUDOn
int8 SimHUDPOff
int8 SimRetUp
int8 SimRetDown*/
