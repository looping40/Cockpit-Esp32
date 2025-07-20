#pragma once

#include <Arduino.h>
#include <USBHID.h> // Contient la déclaration de USBHIDDevice

extern USBHID hid_main_interface; 

extern const uint8_t vendor_hid_report_descriptor[38];
extern const uint8_t full_joystick_hid_report_descriptor_ID3[55];
extern const uint8_t full_joystick_hid_report_descriptor_ID5[55]; 
extern const uint8_t buttons_only_joystick_hid_report_descriptor_ID4[25];
extern const uint8_t buttons_only_joystick_hid_report_descriptor_ID6[25];

class CustomHIDDevice;
typedef struct {
    CustomHIDDevice* HidDevice;
    const uint8_t* HidDescriptor;
    uint8_t HidDescriptor_size;
} HIDDeviceInfo;

extern HIDDeviceInfo MyHidDevices[5];

// Classe de base pour les périphériques HID spécifiques
class CustomHIDDevice : public USBHIDDevice {
public:
    virtual uint16_t _onGetDescriptor(uint8_t *buffer) override = 0; // Pure virtual

    virtual void _onOutput(uint8_t report_id, const uint8_t *buffer, uint16_t len) override {
        Serial.print("Received Output Report (ID ");
        Serial.print(report_id);
        Serial.print(", Len ");
        Serial.print(len);
        Serial.print("): ");
        for (int i = 0; i < len; i++) {
            Serial.printf("%02X ", buffer[i]);
        }
        Serial.println();
    }
};

// --- Classe pour l'interface Vendor Defined (Report IDs 1 et 2) ---
class VendorDefinedHID : public CustomHIDDevice {
public:
    VendorDefinedHID() {}
    uint16_t _onGetDescriptor(uint8_t *buffer) override;
    void _onOutput(uint8_t report_id, const uint8_t *buffer, uint16_t len) override;
};


// Classe pour Joystick Complet avec Report ID 3
class FullJoystickHID_ID3 : public CustomHIDDevice {
public:
    uint16_t _onGetDescriptor(uint8_t *buffer) override;
};

// Classe pour Joystick Complet avec Report ID 5
class FullJoystickHID_ID5 : public CustomHIDDevice {
public:
    uint16_t _onGetDescriptor(uint8_t *buffer) override;
};

// Classe pour Joystick Boutons Uniquement avec Report ID 4
class ButtonsOnlyJoystickHID_ID4 : public CustomHIDDevice {
public:
    uint16_t _onGetDescriptor(uint8_t *buffer) override;
};

// Classe pour Joystick Boutons Uniquement avec Report ID 6
class ButtonsOnlyJoystickHID_ID6 : public CustomHIDDevice {
public:
    uint16_t _onGetDescriptor(uint8_t *buffer) override;
};


void send_reports(uint32_t loop_counter);
void init_hidDevices();