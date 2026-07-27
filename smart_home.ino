#include <Arduino.h>

// Define the physical GPIO pins where your LEDs are connected
#define LIVING_RELAY   18
#define BEDROOM_RELAY  19
#define KITCHEN_RELAY  21
#define STUDY_RELAY    22

// Function declarations
void handleButton(uint16_t vp, uint16_t value);
void allOn();
void allOff();

void setup()
{
    // Initialize HardwareSerial 0 for debugging via USB Serial Monitor
    Serial.begin(115200);
    
    // Initialize HardwareSerial 2 for the DWIN Screen
    // DWIN TX connects to ESP32 Pin 16 (RX2)
    // DWIN RX connects to ESP32 Pin 17 (TX2)
    Serial2.begin(115200, SERIAL_8N1, 16, 17);

    // Configure LED pins as outputs
    pinMode(LIVING_RELAY, OUTPUT);
    pinMode(BEDROOM_RELAY, OUTPUT);
    pinMode(KITCHEN_RELAY, OUTPUT);
    pinMode(STUDY_RELAY, OUTPUT);

    // Default state: Turn everything off at boot
    allOff();
    
    Serial.println("=========================================");
    Serial.println("   ESP32 Smart Home System Initialized   ");
    Serial.println("        Awaiting DWIN Commands...        ");
    Serial.println("=========================================");
}

void loop()
{
    // A standard DWIN VP data frame payload is typically 9 bytes:
    // Frame Header (2B: 0x5A 0xA5) + Len (1B) + Cmd (1B) + VP (2B) + Data Len (1B) + Data Value (2B)
    if (Serial2.available() >= 9) 
    {
        // Search for the 0x5A 0xA5 header to align with the start of a transmission packet
        if (Serial2.read() == 0x5A) 
        {
            if (Serial2.read() == 0xA5) 
            {
                uint8_t len = Serial2.read();      // Number of remaining bytes in the packet
                uint8_t command = Serial2.read();  // Command type (usually 0x83)
                
                // Read VP Address (2 Bytes)
                uint8_t vpHigh = Serial2.read();
                uint8_t vpLow = Serial2.read();
                uint16_t VP = (vpHigh << 8) | vpLow;
                
                // Read Data Word Count
                uint8_t dataLen = Serial2.read();
                
                // Read the actual control Value (2 Bytes)
                uint8_t valHigh = Serial2.read();
                uint8_t valLow = Serial2.read();
                uint16_t value = (valHigh << 8) | valLow;
                
                // Print tracking data directly to your PC Serial Monitor
                Serial.print("[DWIN] Received -> VP: 0x");
                Serial.print(VP, HEX);
                Serial.print(" | Value: 0x");
                Serial.println(value, HEX);

                // Pass the extracted information to execute the hardware changes
                handleButton(VP, value);
            }
        }
    }
}

void handleButton(uint16_t vp, uint16_t value)
{
    switch(vp)
    {
        case 0x5000: // Living Room
            if (value == 1) {
                digitalWrite(LIVING_RELAY, HIGH);
                Serial.println("Living Room LED -> ON");
            }
            else if (value == 0) {
                digitalWrite(LIVING_RELAY, LOW);
                Serial.println("Living Room LED -> OFF");
            }
            break;

        case 0x5002: // Bedroom
            if (value == 1) {
                digitalWrite(BEDROOM_RELAY, HIGH);
                Serial.println("Bedroom LED -> ON");
            }
            else if (value == 0) {
                digitalWrite(BEDROOM_RELAY, LOW);
                Serial.println("Bedroom LED -> OFF");
            }
            break;

        case 0x5004: // Kitchen
            if (value == 1) {
                digitalWrite(KITCHEN_RELAY, HIGH);
                Serial.println("Kitchen LED -> ON");
            }
            else if (value == 0) {
                digitalWrite(KITCHEN_RELAY, LOW);
                Serial.println("Kitchen LED -> OFF");
            }
            break;

        case 0x5006: // Study Room
            if (value == 1) {
                digitalWrite(STUDY_RELAY, HIGH);
                Serial.println("Study Room LED -> ON");
            }
            else if (value == 0) {
                digitalWrite(STUDY_RELAY, LOW);
                Serial.println("Study Room LED -> OFF");
            }
            break;

        case 0x5010: // Global Master Controls
            if (value == 0x000A) {      // Configured UI Value for ALL ON
                allOn();
            } 
            else if (value == 0x000F) { // Configured UI Value for ALL OFF
                allOff();
            }
            break;
            
        default:
            Serial.print("Unknown VP Address caught: 0x");
            Serial.println(vp, HEX);
            break;
    }
}

void allOn()
{
    digitalWrite(LIVING_RELAY, HIGH);
    digitalWrite(BEDROOM_RELAY, HIGH);
    digitalWrite(KITCHEN_RELAY, HIGH);
    digitalWrite(STUDY_RELAY, HIGH);
    Serial.println("Action Triggered: ALL LEDs turned ON");
}

void allOff()
{
    digitalWrite(LIVING_RELAY, LOW);
    digitalWrite(BEDROOM_RELAY, LOW);
    digitalWrite(KITCHEN_RELAY, LOW);
    digitalWrite(STUDY_RELAY, LOW);
    Serial.println("Action Triggered: ALL LEDs turned OFF");
}
