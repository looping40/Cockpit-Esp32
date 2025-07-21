
#include "icp.h"
#include <Wire.h>

//#define dgb_icp

PanelICP panel_Icp;

T_icp_panel2master receipt_icp, prevReceipt_icp;


PanelICP::PanelICP(){
    Name = "ICP";
    NbBits = ICP_NB_BITS;
    NbAxis = ICP_NB_AXIS;
}


uint8_t PanelICP::Init(void) {  
    receipt_icp.sw_32 = 0;
    prevReceipt_icp.sw_32 = 0;
    
    #if defined(dgb_icp) && defined(USE_RS232)
    printf("ICP init ...\r\n"),
    #endif
    
    Wire.beginTransmission(I2C_ICP<<1);
    i2c_connected = Wire.endTransmission() ^ 1;
    
    
    #if defined(dgb_icp) && defined(USE_RS232)
    if (!panel_Icp.i2c_connected){ 
        printf("ICP panel NOT connected\r\n");
    } else {  
        printf("1:%u\r\n", panel_Icp.i2c_connected);
    }
    printf("ICP init done.\r\n");
    #endif
    
    tempo = 200;
    
    return I2C_ICP;
}


 void PanelICP::Report( T_report_idx* report_idx) {    
    uint8_t res;
    
    if ( i2c_connected && (!tempo-- )){        
        Wire.beginTransmission((I2C_ICP<<1)+1);
        for(uint8_t i=0; i<sizeof(receipt_icp); i++){
          receipt_icp.data[i] = Wire.read();
          /*if (i == sizeof(receipt_icp)-1)
            receipt_icp.data[i] = Wire.read(0);
          else
            receipt_icp.data[i] = i2c_read(1);*/
        }
        Wire.endTransmission();
        
        //panel_Icp.bits[0] = receipt_icp.sw_32;
        res = (prevReceipt_icp.sw_32 ^ receipt_icp.sw_32) != 0;
      
        if (res){
            #if defined(dgb_icp) && defined(USE_RS232)
            printf("receipt_icp.sw: 0x%LX\r\n", panel_Icp.bits[0]);
            #endif
            
            //update report switches
            update_report_bits(report_idx->idx_bit, &receipt_icp.sw_32); 
        }
        
        //update report analog axis
        //for (uint8_t i=0;i<4;i++){
        //    panel_Icp.axis[i] = receipt_icp.tw[i];
        //}
        #if defined(dgb_icp) && defined(USE_RS232)
        //printf("receipt_icp.tw: %Lu %Lu %Lu %Lu\r\n", receipt_icp.tw[0], receipt_icp.tw[1], receipt_icp.tw[2], receipt_icp.tw[3]);
        #endif
        update_report_axis(report_idx->idx_axis, &receipt_icp.tw[0]);
        
        prevReceipt_icp.sw_32 = receipt_icp.sw_32;
        tempo = 200;
    }
    
    report_idx->idx_bit += GetNbBits();//panel_Icp.reports_size.nb_bits;
    report_idx->idx_axis += GetNbAxis();//panel_Icp.reports_size.nb_axis;
}


uint8_t PanelICP::Show(uint8_t cde) {
#ifdef nico
    int i;
    
    if ( i2c_connected && (cde==(I2C_ICP))) {
        usb_get_packet(USB_EP_COMMAND, &icp_cde.data[0], sizeof(icp_cde));
   
        i2c_start();
        #if defined(dgb_icp) && defined(USE_RS232)
        printf("\r\naddr=%X:%u\r\n", I2C_ICP, i2c_write((I2C_ICP<<1)));
        for (i=1;i<sizeof(icp_cde.data);++i){
            printf(" %x:%u ", icp_cde.data[i], i2c_write( icp_cde.data[i] ));
            //printf(" %x", lg_cde[i]);
        }
        printf("\r\n");
        #else
        i2c_write((I2C_ICP<<1));
        for (i=1;i<sizeof(icp_cde);++i){
            i2c_write( icp_cde.data[i] );
        }
        #endif

        i2c_stop();
        
        return 1;
    }else
        return 0;
#endif
return 0;
}

