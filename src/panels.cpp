#include <Arduino.h>
#include "panels.h"


String CockpitPanel::GetName() const { 
    return String(Name); 
}


uint8_t CockpitPanel::GetNbBits() {
    return NbBits;
};


uint8_t CockpitPanel::GetNbAxis() {
    return NbAxis;
};


void CockpitPanel::Bit_set(uint32_t* var, uint8_t bit) {
    *var |= (1 << bit);
};


void CockpitPanel::Bit_set(uint8_t* var, uint8_t bit) {
    *var |= (1 << bit);
}


void CockpitPanel::Bit_clear(uint32_t* var, uint8_t bit) {
    *var &= ~(1 << bit);
};


bool CockpitPanel::Bit_test(uint32_t var, uint8_t bit){
    return (var & (1 << bit)) != 0;
};

void CockpitPanel::update_report_bits(uint16_t idx_bit, uint32_t* pBits) {
#ifdef nico
    uint8_t nb_bits = GetNbBits();  //aPanel->reports_size.nb_bits;
    uint16_t src_bit, src_report;
    uint16_t report_bit, report_idx;
    //uint32_t prev_vals[_NB_HID_REPORT_][4];
    bool isDirt;

    printf("Prev %LX, %LX %LX, %LX\r\n",HID_Reports.joy1.buttons, HID_Reports.joy2.buttons, HID_Reports.joy3.buttons, HID_Reports.joy4.buttons);
    
    /*for (uint8_t i=1; i<_NB_HID_REPORT_; i++){
        //memcpy(prev_vals[i], HID_reports[i]->bits, 16);
        
        //printf("1-HID[%u]  %LX, %LX %LX, %LX\r\n", i, HID_reports[i]->bits[0], HID_reports[i]->bits[1], HID_reports[i]->bits[2], HID_reports[i]->bits[3]);
    }*/
    
    //printf("curBit=%lu, nb_bits=%u mod=%lu\r\n", idx_bit, nb_bits, idx_bit % NB_BITS_PER_HID_REPORT);
    
    for (uint8_t curBit=0; curBit<nb_bits; curBit++){
        src_bit  = curBit % 32;
        src_report = curBit / 32;
        report_bit  = idx_bit % NB_BITS_PER_HID_REPORT;
        report_idx = idx_bit / NB_BITS_PER_HID_REPORT;
        //report_idx += 1; //report 0 is for master2panel only
        if (report_idx < _NB_HID_REPORT_ ){
            //printf("%u ", bit_test(aPanel->bits[src_report], src_bit));
            if (bit_test(pBits, src_bit)){
                bit_set(pBits[report_bit/32], (report_bit % 32));
                //printf("report[%lu] bit_set: %lu bits[%lu][%lu]\r\n", report_idx, report_bit, (report_bit/32), (report_bit % 32));
            }else{
                bit_clear(HID_reports[report_idx]->bits[report_bit/32], (report_bit % 32));
                //printf("report[%lu] bit_clear: %lu bits[%lu][%lu]\r\n", report_idx, report_bit, (report_bit/32), (report_bit % 32));
            }
        }        
        idx_bit++;
    }
    
    for (uint8_t j=1; j < _NB_HID_REPORT_; j++){
        //isDirt = (prev_vals[j][0] != (*HID_reports[j]).bits[0]) || (prev_vals[j][1] != (*HID_reports[j]).bits[1]);
        isDirt = memcmp(prev_vals[j], HID_reports[j]->bits, 16);
        HID_reports[j]->isDirty = isDirt;
        //   debug
        /*if ( HID_reports[j]->isDirty ){
            printf("Report[%u] is dirty, addr=%LX\r\n", j, HID_reports[j]); 
            printf("2-Prev[%u] %LX, %LX %LX, %LX\r\n", j, prev_vals[j][0], prev_vals[j][1], prev_vals[j][2], prev_vals[j][3]);
            printf("2-HID[%u]  %LX, %LX %LX, %LX\r\n", j, HID_reports[j]->bits[0], HID_reports[j]->bits[1], HID_reports[j]->bits[2], HID_reports[j]->bits[3]);
        }*/
    }
    
    //printf("\r\n");
#endif
}


void CockpitPanel::update_report_axis(uint8_t idx_axis, uint16_t* pAxis) {
#ifdef nico
    int8 nb_axis = aPanel->reports_size.nb_axis;
    unsigned char idx_report;
    unsigned char axis_report;
    
    for (int8 curAxis=0; curAxis<nb_axis; curAxis++){
        axis_report  = idx_axis % 8;
        idx_report = 1 + idx_axis / 8;  //starting at 1 because 0 is for usb command
        
        if (HID_reports[idx_report]->size == SIZE_HID_REPORT_WITH_AXIS) {
            int16 prev = HID_reports[idx_report]->axis[axis_report];
            //if (idx_report == 1 )
            //  printf("HID_reports[%u].axis[%u] old=%lu ", idx_report, axis_report, prev);
            HID_reports[idx_report]->isDirty |= (prev != aPanel->axis[curAxis]);
            HID_reports[idx_report]->axis[axis_report] = aPanel->axis[curAxis];
            
            //if (idx_report == 1 )
            //  printf("axis[%u]=%lu dirty=%u\r\n", axis_report, HID_reports[idx_report]->axis[axis_report], HID_reports[idx_report]->isDirty);
        }

        idx_axis++;
    }
    //if (idx_report == 1 )
    //  printf("\r\n");
#endif //nico
}