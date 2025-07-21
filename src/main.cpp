// src/main.cpp
#include <Arduino.h>
#include <USB.h>
#include <USBCDC.h>     // Pour Serial0 over USB
#include <USBHID.h>     // Inclut USBHID et USBHIDDevice
#include <Wire.h>

#include "main.h"

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

    Wire.begin();

    //init panels
    init_panels();
}


void loop() {
    static uint32_t loop_counter = 0;
    send_reports(loop_counter);

    loop_counter++;
    delay(50);
}


void init_panels(){
    for(uint8_t i=0;i<NB_PANELS;i++){   
        uint8_t addr = panels[i]->Init();
        #if defined(USE_RS232)
        if (panels[i]->i2c_connected)
            printf("\033[32;40m(0x%x) panel %s connected\033[37;40m\r\n", addr, panels[i]->name);
        else
            printf("\033[31;40m(0x%x) panel %s NOT connected\033[37;40m\r\n", addr, panels[i]->name);
        #endif
        //delay_ms(5);
    }
}
