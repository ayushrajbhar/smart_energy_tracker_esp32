#include <stdio.h>
#include <time.h>

#include "EmonLib.h"
#include <EEPROM.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <HTTPClient.h>

String URL = "http://192.168.135.253/electricity_consumption/test.php";

// Constants for calibration
const float vCalibration = 265;
const float currCalibration = 0.90;

// Blynk and WiFi credentials
const char auth[] = "wWC4ruJYKN-N__6JlpOY9HmQa0hYV354";
const char ssid[] = "realme 9i";
const char pass[] = "24863179";

unsigned long sendDataPrevMills = 0;
bool signupOK = false;

// EnergyMonitor instance
EnergyMonitor emon;
// Timer for regular updates
BlynkTimer timer;

// Variables for energy calculation
float kWh = 0.0;
unsigned long lastMillis = millis();
float previousCurrent = 0.0;

// EEPROM addresses for each variable
const int addrVrms = 0;
const int addrIrms = 0;
const int addrPower = 0;
const int addrKWh = 0;

// Function prototypes
void sendEnergyDataToBlynk();
void readEnergyDataFromEEPROM();
void saveEnergyDataToEEPROM();

void setup()
{
    Serial.begin(115200);

    connectwifi();

    // Initialize EEPROM with the size of the data to be stored
    EEPROM.begin(32); // Allocate 32 bytes for float values (4 bytes each) and some extra space
    Blynk.begin(auth, ssid, pass);

    // Read the stored energy data from EEPROM
    readEnergyDataFromEEPROM();

    // Setup voltage and current inputs
    emon.voltage(34, vCalibration, 1.7); // Voltage: input pin, calibration, phase_shift
    emon.current(35, currCalibration);   // Current: input pin, calibration

    // Setup a timer for sending data every 5 seconds
    timer.setInterval(1000L, sendEnergyDataToBlynk);

    // A small delay for the system to stabilize
    delay(1000);
}

void connectwifi()
{
    WiFi.mode(WIFI_OFF);
    delay(1000);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    Serial.print("Connecting to wifi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.println("Connected to: ");
    Serial.println(ssid);
    Serial.println("IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
}

void loop()
{
    Blynk.run();
    timer.run();
    if (WiFi.status() != WL_CONNECTED)
    {
        connectwifi();
    }

    // Read voltage, current, and power from EnergyMonitor
    emon.calcVI(20, 2000); // Calculate all. No.of half wavelengths (crossings), time-out

    // Calculate energy consumed in kWh
    unsigned long currentMillis = millis();
    kWh += emon.apparentPower * (currentMillis - lastMillis) / 3600000000.0;
    lastMillis = currentMillis;
    
    if (emon.Vrms < 50)
    {
        emon.Vrms = 0;
    }
    emon.Irms = emon.Irms * 1000;
    if (emon.Irms < 75)
    {
        emon.Irms = 0;
    }
    if (emon.apparentPower < 2)
    {
        emon.apparentPower = 0;
    }

    float voltage = emon.Vrms;
    float current = emon.Irms;
    float power = emon.apparentPower;

    // Prepare the data to be sent
    String postData = "voltage=" + String(voltage) + "&current=" + String(current) + "&power=" + String(power);

    // Start HTTP client
    HTTPClient http;
    http.begin(URL);

    // Set content type
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Check if the difference between the current and previous current readings is greater than 50.000mA
    if (abs(current - previousCurrent) > 50.000)
    {
        // Send POST request with data
        int httpCode = http.POST(postData);

        // Check the response
        // if (httpCode > 0)
        // {
        //     // if (httpCode == HTTP_CODE_OK)
        //     // {
        //     //     Serial.println("Data sent successfully");
        //     // }
        //     // else
        //     // {
        //     //     Serial.println("HTTP error: " + String(httpCode));
        //     // }
        // }
        // else
        // {
        //     Serial.println("HTTP request failed");
        // }
    }

    // End HTTP client
    http.end();

    // Update previous current reading
    previousCurrent = current;

    // Delay before next loop iteration
    delay(1000); // Send data every 5 seconds
}

void sendEnergyDataToBlynk()
{
    emon.calcVI(20, 2000); // Calculate all. No.of half wavelengths (crossings), time-out

    // Calculate energy consumed in kWh
    unsigned long currentMillis = millis();
    kWh += emon.apparentPower * (currentMillis - lastMillis) / 3600000000.0;
    lastMillis = currentMillis;

    // Print data to Serial for debugging
    if (emon.Vrms < 50)
    {
        emon.Vrms = 0;
    }
    emon.Irms = emon.Irms * 1000;
    if (emon.Irms < 75)
    {
        emon.Irms = 0;
    }
    Serial.printf("Vrms: %.2fV\tIrms: %.4fmA\tPower: %.4fW\tkWh: %.5fkWh\n",
                  emon.Vrms, emon.Irms, emon.apparentPower, kWh);

    // Save the latest values to EEPROM
    saveEnergyDataToEEPROM();

    // Send data to Blynk
    Blynk.virtualWrite(V1, emon.Vrms);
    Blynk.virtualWrite(V3, emon.Irms);
    Blynk.virtualWrite(V4, emon.apparentPower);
    // Blynk.virtualWrite(V3, kWh);
}

void readEnergyDataFromEEPROM()
{
    // Read the stored kWh value from EEPROM
    EEPROM.get(addrKWh, kWh);

    // Check if the read value is a valid float. If not, initialize it to zero
    if (isnan(kWh))
    {
        kWh = 0.0;
        saveEnergyDataToEEPROM(); // Save the initialized value to EEPROM
    }
}

void saveEnergyDataToEEPROM()
{
    // Write the current kWh value to EEPROM
    EEPROM.put(addrKWh, kWh);

    // Commit changes to EEPROM
    EEPROM.commit();
}