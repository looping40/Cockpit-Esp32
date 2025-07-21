#pragma once
#include  <Arduino.h>
#define USE_ICP_PANEL

#include "panels.h"

#include "i2cMsg_backlight.h"
#include "i2cMsg_Icp.h"


class PanelICP : public CockpitPanel {
public:
    PanelICP();
    uint8_t Init(void) override;
    uint8_t Show(uint8_t cde) override;
    void Report(T_report_idx *report_idx) override;
};


extern PanelICP panel_Icp;

/*
rom char ICP_NAME[] = "ICP";

int16 icp_axis[ICP_NB_AXIS] = {0, 0, 0, 0};

static T_panel_ctrl panel_Icp = {
    {
     panel_Icp_init,
     panel_Icp_show,
     panel_Icp_report
   },
    /*panel_name* /             &ICP_NAME,
    /*reports_size.nb_bits=* /  {ICP_NB_BITS,
    /*reports_size.nb_axis=* /   ICP_NB_AXIS},
    /*bits[2] * /               {0,0},
    /* *axis  * /               &icp_axis
};



unsigned int8 tempo_icp = 200;

T_Icp_master2panel icp_cde;
*/
