#pragma once

#include <Arduino.h>
#include "Esp32CockpitHID.h"
#include "panels.h"
#include "icp.h"

void init_panels();


enum PanelEnum{
    #ifdef USE_BACKLIGHT
        Backlight,     
    #endif
    #ifdef USE_ICP_PANEL
        Icp,           
    #endif
    #ifdef USE_WRN_PANEL
        , Warning       
    #endif
    #ifdef USE_FRONT_PANEL
         , Front         
    #endif
    #ifdef USE_TWPTWA_PANEL
        , TwpTwa        
    #endif
    #ifdef USE_DEDUINO_PANEL
       , Ded           
    #endif
    #ifdef USE_GAUGE_PANEL
        , Gauge         
    #endif
    #ifdef USE_LG_PANEL
        , Gear          
    #endif
    #ifdef USE_FUELSEL_INSTR
       , FuelSelInstr  
    #endif
    #ifdef USE_TRIM_PANEL
        , Trim          
        #endif
    #ifdef USE_MISC_PANEL
        , Misc          
    #endif 
    #ifdef USE_FUELQTY_PANEL
       , FuelQty       
    #endif
    #ifdef USE_CMDS_PANEL
        , Cmds          
    #endif 
    #ifdef USE_AUXCOMM_PANEL
        , Auxcomm       
    #endif
    #ifdef USE_UHF_PANEL
        , Uhf           
    #endif
    #ifdef USE_AUDIO_PANEL
        , Audio         
    #endif
    #ifdef USE_FLTCTRL_PANEL
        , fltCtrl
    #endif
    #ifdef USE_ENGSTART_PANEL
        , engStart
    #endif
    #ifdef USE_INTLIGHT_PANEL
        , intLight
    #endif
    #ifdef USE_EXTLIGHT_PANEL
        , extLight
    #endif
    #ifdef USE_AVIONICPWR_PANEL
        , avionicPwr
    #endif
    #ifdef USE_VIBES_PANEL
        , vibes
    #endif
    
    NB_PANELS
};


CockpitPanel* panels[NB_PANELS] = { 
    #ifdef USE_BACKLIGHT
        &panel_Backlight,    
    #endif
    #ifdef USE_ICP_PANEL
        &panel_Icp,
    #endif
    #ifdef USE_WRN_PANEL
        &Panel_Warning,
    #endif
    #ifdef USE_FRONT_PANEL
        &Panel_Front,
    #endif
    #ifdef USE_TWPTWA_PANEL
        &panel_TwpTwa
    #endif
    #ifdef USE_DEDUINO_PANEL
        &panel_Ded,
    #endif
    #ifdef USE_GAUGE_PANEL
        &panel_Gauge,
    #endif
    #ifdef USE_LG_PANEL
        &panel_Gear,
    #endif
    #ifdef USE_FUELSEL_INSTR
        &panel_FuelSelInstr,
    #endif
    #ifdef USE_TRIM_PANEL
        &panel_Trim,
    #endif
    #ifdef USE_MISC_PANEL
        &panel_Misc,
    #endif
    #ifdef USE_FUELQTY_PANEL
        &panel_FuelQty
    #endif
    #ifdef USE_CMDS_PANEL
        &panel_Cmds,
    #endif
    #ifdef USE_AUXCOMM_PANEL
        &panel_Auxcomm,
    #endif
    #ifdef USE_UHF_PANEL
        &panel_Uhf,
    #endif
    #ifdef USE_AUDIO_PANEL
        &panel_Audio,
    #endif
    #ifdef USE_FLTCTRL_PANEL
        &panel_FltCtrl,
    #endif
    #ifdef USE_ENGSTART_PANEL
        &panel_EngStart,
    #endif
    #ifdef USE_INTLIGHT_PANEL
        &panel_IntLight,
    #endif
    #ifdef USE_EXTLIGHT_PANEL
        &panel_ExtLight,
    #endif
    #ifdef USE_AVIONICPWR_PANEL
        &panel_AvionicPwr,
    #endif
    #ifdef USE_VIBES_PANEL
        &panel_Vibes,
    #endif
};

