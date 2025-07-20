// src/Esp32CockpitHID.cpp
#include "Esp32CockpitHID.h"
#include <USB.h>


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


// Crée une instance pour chaque périphérique HID avec son Report ID unique
// VendorDefinedHID gère ses propres Report IDs (1 et 2) dans son descripteur.
VendorDefinedHID myVendorDevice;
// Utilisez les nouvelles classes spécifiques à chaque Report ID
FullJoystickHID_ID3 myFullJoystick1; // Instance 1 du joystick complet (Report ID 3 dans son descripteur)
FullJoystickHID_ID5 myFullJoystick2; // Instance 2 du joystick complet (Report ID 5 dans son descripteur)
ButtonsOnlyJoystickHID_ID4 myButtonsJoystick1; // Instance 1 du joystick boutons uniquement (Report ID 4 dans son descripteur)
ButtonsOnlyJoystickHID_ID6 myButtonsJoystick2; // Instance 2 du joystick boutons uniquement (Report ID 6 dans son descripteur)

// Crée une instance de l'objet USBHID global
USBHID hid_main_interface; // Utilise le constructeur par défaut

HIDDeviceInfo MyHidDevices[] = {
    {&myVendorDevice, vendor_hid_report_descriptor, sizeof(vendor_hid_report_descriptor)},
    {&myFullJoystick1, full_joystick_hid_report_descriptor_ID3, sizeof(full_joystick_hid_report_descriptor_ID3)},
    {&myFullJoystick2, full_joystick_hid_report_descriptor_ID5, sizeof(full_joystick_hid_report_descriptor_ID5)},
    {&myButtonsJoystick1, buttons_only_joystick_hid_report_descriptor_ID4, sizeof(buttons_only_joystick_hid_report_descriptor_ID4)},
    {&myButtonsJoystick2, buttons_only_joystick_hid_report_descriptor_ID6, sizeof(buttons_only_joystick_hid_report_descriptor_ID6)}
};


void init_hidDevices(){
    // Initialisation des périphériques HID via la boucle
    for (size_t i = 0; i < sizeof(MyHidDevices) / sizeof(MyHidDevices[0]); ++i) {
        if (!USBHID::addDevice(MyHidDevices[i].HidDevice, MyHidDevices[i].HidDescriptor_size)) {
            Serial0.printf("Échec de l'ajout du périphérique HID %zu! Arrêt.\r\n", i);
            while(1);
        } else {
            Serial0.printf("Périphérique HID %zu ajouté avec succès. size=%u\r\n", i, MyHidDevices[i].HidDescriptor_size);
        }
    }

    // Démarre le stack USB
    USB.begin();
    Serial0.println("USB initialisé. L'ESP32-S3 devrait maintenant apparaître comme un périphérique HID composite.");

    hid_main_interface.begin(); // Démarre l'interface HID
}


void send_reports(uint32_t loop_counter){
    if (!hid_main_interface.ready()) {
        delay(100); // Attendre un peu avant de réessayer
        Serial0.println("hid_main_interface not ready");
        return;
    }

#ifdef nico
    // --- Envoi du rapport pour l'interface Vendor Defined (Input Report ID 1) ---
    uint8_t vendorInputData[64];
    for (int i = 0; i < 64; i++) {
        vendorInputData[i] = (loop_counter + i) % 256;
    }
    if (hid_main_interface.SendReport(1, vendorInputData, sizeof(vendorInputData))) {
        // Serial0.print("Vendor Defined (ID 1) Input Report sent. Counter: ");
        // Serial0.println(loop_counter);
    } else {
        Serial0.println("Échec de l'envoi du rapport Vendor Defined (ID 1).");
    }
#endif

    // --- Envoi du rapport pour le Joystick Full Instance 1 (Input Report ID 3) ---
    struct FullJoystickReport {
        int16_t axes[8];
        uint8_t buttons[16];
    } joystickFullData1;

    double time_in_seconds = millis() / 1000.0;
    joystickFullData1.axes[0] = (int16_t)(sin(time_in_seconds) * 32767.0);
    joystickFullData1.axes[1] = (int16_t)(sin(time_in_seconds + PI / 2.0) * 32767.0); // Décalage pour l'axe Y
    for(int i = 2; i < 8; i++) joystickFullData1.axes[i] = 0;
    
    memset(joystickFullData1.buttons, 0, sizeof(joystickFullData1.buttons));
    if (loop_counter % 20 == 0) {
        joystickFullData1.buttons[0] |= (1 << 0); // Active le bouton 1
    } else {
        joystickFullData1.buttons[0] &= ~(1 << 0); // Désactive le bouton 1
    }

    if (hid_main_interface.SendReport(3, (uint8_t*)&joystickFullData1, sizeof(joystickFullData1))) {
        // Serial0.print("Joystick Full 1 (ID 3) Input Report sent. X-axis: ");
        // Serial0.println(joystickFullData1.axes[0]);
    } else {
        Serial0.println("Échec de l'envoi du rapport Joystick Full 1 (ID 3).");
    }

    // --- Envoi du rapport pour le Joystick Full Instance 2 (Input Report ID 5) ---
    struct FullJoystickReport joystickFullData2;
    joystickFullData2.axes[0] = (int16_t)(sin(time_in_seconds) * 32767.0);
    joystickFullData2.axes[1] = (int16_t)(sin(time_in_seconds + PI / 2.0) * 32767.0); // Décalage pour l'axe Y
    for(int i = 2; i < 8; i++) joystickFullData2.axes[i] = 0;
    memset(joystickFullData2.buttons, 0, sizeof(joystickFullData2.buttons));
    if (loop_counter % 20 == 0) {
        joystickFullData2.buttons[1] |= (1 << 0); // Active le bouton 1
    } else {
        joystickFullData2.buttons[1] &= ~(1 << 0); // Désactive le bouton 1
    }

    if (hid_main_interface.SendReport(5, (uint8_t*)&joystickFullData2, sizeof(joystickFullData2))) {
        // Serial0.print("Joystick Full 2 (ID 5) Input Report sent. X-axis: ");
        // Serial0.println(joystickFullData2.axes[0]);
    } else {
        Serial0.println("Échec de l'envoi du rapport Joystick Full 2 (ID 5).");
    }

    // --- Envoi du rapport pour le Joystick Buttons-Only Instance 1 (Input Report ID 4) ---
    uint8_t joystickButtonsData1[16];
    memset(joystickButtonsData1, 0, sizeof(joystickButtonsData1));
    if (loop_counter % 20 == 0) {
        joystickButtonsData1[2] |= (1 << 0); // Active le bouton 1
    } else {
        joystickButtonsData1[2] &= ~(1 << 0); // Désactive le bouton 1
    }
    if (hid_main_interface.SendReport(4, joystickButtonsData1, sizeof(joystickButtonsData1))) {
        // Serial0.print("Joystick Buttons 1 (ID 4) Input Report sent. Button 8 state: ");
        // Serial0.println((joystickButtonsData1[0] >> 7) & 1);
    } else {
        Serial0.println("Échec de l'envoi du rapport Joystick Buttons 1 (ID 4).");
    }
    
    // --- Envoi du rapport pour le Joystick Buttons-Only Instance 2 (Input Report ID 6) ---
    uint8_t joystickButtonsData2[16];
    memset(joystickButtonsData2, 0, sizeof(joystickButtonsData2));
    if (loop_counter % 20 == 0) {
        joystickButtonsData2[3] |= (1 << 0); // Active le bouton 1
    } else {
        joystickButtonsData2[3] &= ~(1 << 0); // Désactive le bouton 1
    }
    if (hid_main_interface.SendReport(6, joystickButtonsData2, sizeof(joystickButtonsData2))) {
        // Serial0.print("Joystick Buttons 2 (ID 6) Input Report sent. Button 9 state: ");
        // Serial0.println((joystickButtonsData2[1] >> 0) & 1);
    } else {
        Serial0.println("Échec de l'envoi du rapport Joystick Buttons 2 (ID 6).");
    }
}