// src/Esp32CockpitHID.cpp
#include "Esp32CockpitHID.h"
//#include <string.h>

// --- Report Descriptor for Vendor Defined Device ---
const uint8_t vendor_hid_report_descriptor[38] = {
    0x06, 0x00, 0xFF,              // Usage Page (Vendor Defined Page 1)
    0x09, 0x01,                    // Usage (Vendor Usage 1)
    0xA1, 0x01,                    // Collection (Application)

    // Input Report (ESP32-S3 to PC) - Report ID 1
    0x85, 0x01,                    //   Report ID (1)
    0x09, 0x02,                    //   Usage (Vendor Usage 2)
    0x15, 0x00,                    //   Logical Minimum (0)
    0x26, 0xFF, 0x00,              //   Logical Maximum (255)
    0x75, 0x08,                    //   Report Size (8 bits)
    0x95, 0x40,                    //   Report Count (64)
    0x81, 0x02,                    //   Input (Data, Var, Abs)

    // Output Report (PC to ESP32-S3) - Report ID 2
    0x85, 0x02,                    //   Report ID (2)
    0x09, 0x03,                    //   Usage (Vendor Usage 3)
    0x15, 0x00,                    //   Logical Minimum (0)
    0x26, 0xFF, 0x00,              //   Logical Maximum (255)
    0x75, 0x08,                    //   Report Size (8 bits)
    0x95, 0x40,                    //   Report Count (64)
    0x91, 0x02,                    //   Output (Data, Var, Abs)
    0xC0                           // End Collection
};

uint16_t VendorDefinedHID::_onGetDescriptor(uint8_t *buffer) {
    memcpy(buffer, vendor_hid_report_descriptor, sizeof(vendor_hid_report_descriptor));
    return sizeof(vendor_hid_report_descriptor);
}
void VendorDefinedHID::_onOutput(uint8_t report_id, const uint8_t *buffer, uint16_t len) {
    CustomHIDDevice::_onOutput(report_id, buffer, len);
    if (report_id == 2) { // Output Report for Vendor Defined (ID 2)
        Serial0.println("  -> Specific handling for Vendor Defined Output Report.");
        // Traitez les 64 octets du rapport de sortie Vendor Defined ici
    }
}


// --- Report Descriptor for Full Joystick (8 Axes + 512 Buttons) - Report ID 3 ---
const uint8_t full_joystick_hid_report_descriptor_ID3[] = {
    0x05, 0x01,                    // Usage Page (Generic Desktop)
    0x09, 0x04,                    // Usage (Joystick)
    0xA1, 0x01,                    // Collection (Application)
    0x85, 0x03,                    // Report ID (3)

    // Axes (8 axes, 16 bits each)
    0x05, 0x01,                    //   Usage Page (Generic Desktop)
    0x09, 0x30,                    //   Usage (X)
    0x09, 0x31,                    //   Usage (Y)
    0x09, 0x32,                    //   Usage (Z)
    0x09, 0x33,                    //   Usage (Rx)
    0x09, 0x34,                    //   Usage (Ry)
    0x09, 0x35,                    //   Usage (Rz)
    0x09, 0x36,                    //   Usage (Slider)
    0x09, 0x37,                    //   Usage (Dial)
    0x16, 0x00, 0x80,              //   Logical Minimum (-32768)
    0x26, 0xFF, 0x7F,              //   Logical Maximum (32767)
    0x75, 0x10,                    //   Report Size (16 bits)
    0x95, 0x08,                    //   Report Count (8 axes)
    0x81, 0x02,                    //   Input (Data, Var, Abs)

    // Buttons (512 buttons, 1 bit each)
    0x05, 0x09,                    //   Usage Page (Button)
    0x19, 0x01,                    //   Usage Minimum (Button 1)
    0x29, 0x80,                    //   Usage Maximum (Button 128)
    0x15, 0x00,                    //   Logical Minimum (0)
    0x25, 0x01,                    //   Logical Maximum (1)
    0x75, 0x01,                    //   Report Size (1 bit)
    0x95, 0x80,                    //   Report Count (128)
    0x81, 0x02,                    //   Input (Data, Var, Abs)
    0xC0                           // End Collection
};
static_assert(sizeof(full_joystick_hid_report_descriptor_ID3) == 55, "full_joystick_hid_report_descriptor_ID3 size mismatch"); // <<-- Changez 39 en 55 ici

// Implémentation pour FullJoystickHID_ID3
uint16_t FullJoystickHID_ID3::_onGetDescriptor(uint8_t *buffer) {
    memcpy(buffer, full_joystick_hid_report_descriptor_ID3, sizeof(full_joystick_hid_report_descriptor_ID3));
    return sizeof(full_joystick_hid_report_descriptor_ID3);
}

// --- Report Descriptor for Full Joystick (8 Axes + 512 Buttons) - Report ID 5 ---
const uint8_t full_joystick_hid_report_descriptor_ID5[] = {
    0x05, 0x01,                    // Usage Page (Generic Desktop)
    0x09, 0x04,                    // Usage (Joystick)
    0xA1, 0x01,                    // Collection (Application)
    0x85, 0x05,                    // Report ID (5)

    // Axes (8 axes, 16 bits each)
    0x05, 0x01,                    //   Usage Page (Generic Desktop)
    0x09, 0x30,                    //   Usage (X)
    0x09, 0x31,                    //   Usage (Y)
    0x09, 0x32,                    //   Usage (Z)
    0x09, 0x33,                    //   Usage (Rx)
    0x09, 0x34,                    //   Usage (Ry)
    0x09, 0x35,                    //   Usage (Rz)
    0x09, 0x36,                    //   Usage (Slider)
    0x09, 0x37,                    //   Usage (Dial)
    0x16, 0x00, 0x80,              //   Logical Minimum (-32768)
    0x26, 0xFF, 0x7F,              //   Logical Maximum (32767)
    0x75, 0x10,                    //   Report Size (16 bits)
    0x95, 0x08,                    //   Report Count (8)
    0x81, 0x02,                    //   Input (Data, Var, Abs)

    // Buttons (512 buttons, 1 bit each)
    0x05, 0x09,                    //   Usage Page (Button)
    0x19, 0x01,                    //   Usage Minimum (Button 1)
    0x29, 0x80,                    //   Usage Maximum (Button 128)
    0x15, 0x00,                    //   Logical Minimum (0)
    0x25, 0x01,                    //   Logical Maximum (1)
    0x75, 0x01,                    //   Report Size (1 bit)
    0x95, 0x80,                    //   Report Count (128)
    0x81, 0x02,                    //   Input (Data, Var, Abs)
    0xC0                           // End Collection
};
static_assert(sizeof(full_joystick_hid_report_descriptor_ID5) == 55, "full_joystick_hid_report_descriptor_ID5 size match");

// Implémentation pour FullJoystickHID_ID5
uint16_t FullJoystickHID_ID5::_onGetDescriptor(uint8_t *buffer) {
    memcpy(buffer, full_joystick_hid_report_descriptor_ID5, sizeof(full_joystick_hid_report_descriptor_ID5));
    return sizeof(full_joystick_hid_report_descriptor_ID5);
}


// --- Report Descriptor for Buttons-Only Joystick - Report ID 4 ---
const uint8_t buttons_only_joystick_hid_report_descriptor_ID4[] = {
    0x05, 0x01,                    // Usage Page (Generic Desktop)
    0x09, 0x04,                    // Usage (Joystick)
    0xA1, 0x01,                    // Collection (Application)
    0x85, 0x04,                    //   Report ID (4)

    // Buttons (512 buttons, 1 bit each)
    0x05, 0x09,                    //   Usage Page (Button)
    0x19, 0x01,                    //   Usage Minimum (Button 1)
    0x29, 0x80,                    //   Usage Maximum (Button 128)
    0x15, 0x00,                    //   Logical Minimum (0)
    0x25, 0x01,                    //   Logical Maximum (1)
    0x75, 0x01,                    //   Report Size (1 bit)
    0x95, 0x80,                    //   Report Count (128)
    0x81, 0x02,                    //   Input (Data, Var, Abs)
    0xC0                           // End Collection
};
static_assert(sizeof(buttons_only_joystick_hid_report_descriptor_ID4) == 25, "full_joystick_hid_report_descriptor_ID5 size match");

// Implémentation pour ButtonsOnlyJoystickHID_ID4
uint16_t ButtonsOnlyJoystickHID_ID4::_onGetDescriptor(uint8_t *buffer) {
    memcpy(buffer, buttons_only_joystick_hid_report_descriptor_ID4, sizeof(buttons_only_joystick_hid_report_descriptor_ID4));
    return sizeof(buttons_only_joystick_hid_report_descriptor_ID4);
}

// --- Report Descriptor for Buttons-Only Joystick - Report ID 6 ---
const uint8_t buttons_only_joystick_hid_report_descriptor_ID6[25] = {
    0x05, 0x01,                    // Usage Page (Generic Desktop)
    0x09, 0x04,                    // Usage (Joystick)
    0xA1, 0x01,                    // Collection (Application)
    0x85, 0x06,                    //   Report ID (6)

    // Buttons (512 buttons, 1 bit each)
    0x05, 0x09,                    //   Usage Page (Button)
    0x19, 0x01,                    //   Usage Minimum (Button 1)
    0x29, 0x80,                    //   Usage Maximum (Button 512)
    0x15, 0x00,                    //   Logical Minimum (0)
    0x25, 0x01,                    //   Logical Maximum (1)
    0x75, 0x01,                    //   Report Size (1 bit)
    0x95, 0x80,                    //   Report Count (512)
    0x81, 0x02,                    //   Input (Data, Var, Abs)
    0xC0                           // End Collection
};
static_assert(sizeof(buttons_only_joystick_hid_report_descriptor_ID6) == 25, "buttons_only_joystick_hid_report_descriptor_ID6 size match");


// Implémentation pour ButtonsOnlyJoystickHID_ID6
uint16_t ButtonsOnlyJoystickHID_ID6::_onGetDescriptor(uint8_t *buffer) {
    memcpy(buffer, buttons_only_joystick_hid_report_descriptor_ID6, sizeof(buttons_only_joystick_hid_report_descriptor_ID6));
    return sizeof(buttons_only_joystick_hid_report_descriptor_ID6);
}