// src/main.cpp
#include <Arduino.h>
#include <USB.h>
#include <USBCDC.h>     // Pour Serial0 over USB
#include <USBHID.h>     // Inclut USBHID et USBHIDDevice

// Inclut la déclaration de nos nouvelles classes HID spécifiques
#include "Esp32CockpitHID.h"


void setup() {
    Serial0.begin(115200);
    while (!Serial0 ); // Attendre que le port série soit prêt (optionnel)
    Serial0.println("Démarrage de l'ESP32-S3 avec périphériques HID composites...");

    // --- DÉFINITION DES PROPRES ID ---
    USB.VID(0x6104);
    USB.PID(0x5501);
    USB.manufacturerName("Nicolas C");
    USB.productName("CockpitHID");
    USB.serialNumber("0001"); // un numéro de série

    init_hidDevices();
}

void loop() {
    // Démonstration de l'envoi de rapports pour chaque interface HID
    static uint32_t loop_counter = 0;
    send_reports(loop_counter);

    loop_counter++;
    delay(50);
}
