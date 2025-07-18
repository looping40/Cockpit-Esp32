// src/main.cpp
#include <Arduino.h>
#include <USB.h>
#include <USBCDC.h>     // Pour Serial0 over USB
#include <USBHID.h>     // Inclut USBHID et USBHIDDevice

// Inclut la déclaration de nos nouvelles classes HID spécifiques
#include "Esp32CockpitHID.h"


extern const uint8_t vendor_hid_report_descriptor[38];
extern const uint8_t full_joystick_hid_report_descriptor_ID3[55];
extern const uint8_t full_joystick_hid_report_descriptor_ID5[55]; 
extern const uint8_t buttons_only_joystick_hid_report_descriptor_ID4[25];
extern const uint8_t buttons_only_joystick_hid_report_descriptor_ID6[25];

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

void setup() {
    Serial0.begin(115200);
    while (!Serial0 ); // Attendre que le port série soit prêt (optionnel)
    Serial0.println("Démarrage de l'ESP32-S3 avec périphériques HID composites...");

    // --- DÉFINITION DES PROPRES ---
    USB.VID(0x6104); // Remplacez 0xAAAA par votre Vendor ID désiré
    USB.PID(0x5501); // Remplacez 0xBBBB par votre Product ID désiré
    USB.manufacturerName("Nicolas C");
    USB.productName("CockpitHID");
    USB.serialNumber("0001"); // Ou un numéro de série dynamique


    // 1. Ajoute chaque périphérique HID individuellement au stack USBHID
    // Pour VendorDefinedHID, le Report ID est déjà dans son descripteur
    if (!USBHID::addDevice(&myVendorDevice, sizeof(vendor_hid_report_descriptor))) {
        Serial0.println("Échec de l'ajout du périphérique Vendor Defined ! Arrêt.");
        while(1);
    } else {
        Serial0.printf("Périphérique Vendor Defined ajouté avec succès. size=%u\r\n", sizeof(vendor_hid_report_descriptor));
    }

    // Pour les joysticks, les Report IDs sont définis dans leurs descripteurs respectifs
    if (!USBHID::addDevice(&myFullJoystick1, sizeof(full_joystick_hid_report_descriptor_ID3))) {
        Serial0.println("Échec de l'ajout du Joystick Full 1 ! Arrêt.");
        while(1);
    }else {
        Serial0.printf("Périphérique Joystick Full 1 ajouté avec succès. size=%u\r\n", sizeof(full_joystick_hid_report_descriptor_ID3));
    }

    if (!USBHID::addDevice(&myFullJoystick2, sizeof(full_joystick_hid_report_descriptor_ID5))) {
        Serial0.println("Échec de l'ajout du Joystick Full 2 ! Arrêt.");
        while(1);
    }else {
        Serial0.printf("Périphérique Joystick Full 2 ajouté avec succès. size=%u\r\n", sizeof(full_joystick_hid_report_descriptor_ID5));
    }

    if (!USBHID::addDevice(&myButtonsJoystick1, sizeof(buttons_only_joystick_hid_report_descriptor_ID4))) {
        Serial0.println("Échec de l'ajout du Joystick Buttons 1 ! Arrêt.");
        while(1);
    }else{
        Serial0.printf("Périphérique Joystick Buttons 1 ajouté avec succès. size=%u\r\n", sizeof(buttons_only_joystick_hid_report_descriptor_ID4));
    }

    if (!USBHID::addDevice(&myButtonsJoystick2,  sizeof(buttons_only_joystick_hid_report_descriptor_ID6))) {
        Serial0.println("Échec de l'ajout du Joystick Buttons 2 ! Arrêt.");
        while(1);
    }else{
        Serial0.printf("Périphérique Joystick Buttons 2 ajouté avec succès. size=%u\r\n", sizeof(buttons_only_joystick_hid_report_descriptor_ID6));
    }

    Serial0.println("Tous les périphériques HID ont été ajoutés avec succès.");

    // 2. Démarre le stack USB
    USB.begin();
    Serial0.println("USB initialisé. L'ESP32-S3 devrait maintenant apparaître comme un périphérique HID composite.");

    hid_main_interface.begin(); // Démarre l'interface HID
    // AJOUT: Un petit délai pour laisser l'USB s'initialiser complètement
    /*delay(500); // Délai de 500 ms

    // AJOUT: Attendre que l'interface HID soit prête avant de continuer
    Serial0.println("Attente de la disponibilité des interfaces USB HID...");
    unsigned long start_wait_time = millis();
    // La méthode ready() de USBHID vérifie si le périphérique USB est connecté et configuré.
    while (!hid_main_interface.ready()) {
        delay(10);
        if (millis() - start_wait_time > 5000) { // Timeout de 5 secondes
            Serial0.println("Timeout: Les interfaces USB HID ne sont pas devenues prêtes.");
            break;
        }
    }

    if (hid_main_interface.ready()) {
        Serial0.println("Interfaces USB HID prêtes !");
        delay(100);
    }*/
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

    loop_counter++;
    delay(50);
}
