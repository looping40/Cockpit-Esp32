unsigned int8 panel_Backlight_init(void);
unsigned int8 panel_Backlight_show(unsigned int8 cde);
void panel_Backlight_report(T_report_idx *report_idx);


#include "..\..\..\..\common\firmware\i2c\i2cMsg_backlight.h"

rom char BCKLIGHT_NAME[] = "Backlight";

static T_panel_ctrl panel_Backlight = {
    {
      panel_Backlight_init,
      panel_Backlight_show,
      panel_Backlight_report
    },
    /*panel_name*/   &BCKLIGHT_NAME,
    /*reports_size.nb_bits=*/    {BCKLIGHT_NB_BITS, 
    /*reports_size.nb_axis=*/     BCKLIGHT_NB_AXIS},
    /*bits*/                     {0, 0}
};


#include "pca9634.h"


union{
  struct{
    unsigned char id;
    unsigned char r;// = 0;
    unsigned char g;// = 0;
    unsigned char b;// = 0x05;
  };
  int32 val;
}backlightColor, prev_backlightColor;
