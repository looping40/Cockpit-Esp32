#pragma once
#include <Arduino.h>

#include "I2C_adresses.h"
#include "Esp32CockpitHID.h"

#define NB_BITS_PER_HID_REPORT 128


typedef struct {
    uint16_t idx_bit;
    uint8_t idx_axis;
} T_report_idx;


class CockpitPanel {
public:
    virtual uint8_t Init(void) = 0;
    virtual uint8_t Show(uint8_t cde) = 0;
    virtual void Report(T_report_idx *report_idx) = 0;
    String GetName() const;
    uint8_t GetNbBits();
    uint8_t GetNbAxis();
protected:
    bool i2c_connected = false;
    uint8_t tempo = 0;
    const char* Name;
    uint8_t NbBits = 0;
    uint8_t NbAxis = 0;
     uint32_t* pBits;
     uint16_t* pAxis;

    void Bit_set(uint32_t* var, uint8_t bit);
    void Bit_set(uint8_t* var, uint8_t bit);
    void Bit_clear(uint32_t* var, uint8_t bit);
    bool Bit_test(uint32_t var, uint8_t bit);
    void update_report_bits(uint16_t idx_bit, uint32_t* pBits);
    void update_report_axis(uint8_t idx_axis, uint16_t* pAxis);
};



