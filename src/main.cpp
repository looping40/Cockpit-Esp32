// src/main.cpp
#include <Arduino.h>
#include <USB.h>
#include <USBCDC.h>     // Pour Serial0 over USB
#include <USBHID.h>     // Inclut USBHID et USBHIDDevice

// Inclut la déclaration de nos nouvelles classes HID spécifiques
#include "Esp32CockpitHID.h"


extern HIDDeviceInfo MyHidDevices[5];

void setup() {
    Serial0.begin(115200);
    while (!Serial0 ); // Attendre que le port série soit prêt (optionnel)
    Serial0.println("Démarrage de l'ESP32-S3 avec périphériques HID composites...");

    // --- DÉFINITION DES PROPRES ID ---
    USB.VID(0x6104);
    USB.PID(0x5501);
    USB.manufacturerName("Nicolas C");
    USB.productName("CockpitHID");
    USB.serialNumber("0001"); // Ou un numéro de série dynamique

    init_hidDevices();
}


void loop() {
    // Démonstration de l'envoi de rapports pour chaque interface HID
    static uint32_t loop_counter = 0;


#ifdef nico
    // S'assurer que l'interface est prête avant d'envoyer des rapports
    if (!hid_main_interface.ready()) {
        delay(100); // Attendre un peu avant de réessayer
        return;
    }

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

    send_reports(loop_counter);
    loop_counter++;
    delay(50);
}
