// I2C (Inter-Integrated Circuit) Protocol is a bus communication protocol.
// It allows multiple slave devices to be connected to a single master device.
#include <Wire.h>

// HX711 library provides an interface to the HX711 load cell amplifier module.
// HX711 is used to read load cell data.
#include <HX711.h>

// EEPROM library provides functions to read and write data to the Arduino's EEPROM memory.
#include <EEPROM.h>

// Define the pins for HX711 module.
#define LOADCELL_DOUT_PIN  3
#define LOADCELL_CLK_PIN  2

// Define the address where the data will be stored in the EEPROM.
#define EEPROM_ADDRESS 0

// Instantiate an object of the HX711 class, representing the load cell amplifier module.
HX711 scale;

// The `setup` function initializes the environment when the Arduino board powers on or resets.
void setup() {
  // Initiate serial communication at 9600 baud rate.
  Serial.begin(9600);

  // Initialize the HX711 module.
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_CLK_PIN);

  // Set the gain factor to 128.
  // This value depends on the load cell and the specific configuration.
  scale.set_scale(128);

  // Tare the scale to remove any initial load.
  scale.tare();
}

// The `loop` function continuously cycles as long as the Arduino is powered.
void loop() {
  // Read the load cell data.
  float weight = scale.get_units();

  // Log the load cell data to the EEPROM.
  logData(weight);

  // Wait for 1 second before taking the next reading.
  delay(1000);
}

/**
 * Logs the load cell data to the EEPROM.
 * 
 * @param weight The weight value to be logged.
 */
void logData(float weight) {
  // Read the current address from the EEPROM.
  int address = EEPROM.read(EEPROM_ADDRESS);

  // Increment the address by 1 to move to the next available location.
  address++;

  // Write the weight value to the EEPROM at the current address.
  EEPROM.put(address, weight);

  // Update the address in the EEPROM.
  EEPROM.put(EEPROM_ADDRESS, address);

  // Print the logged data to the Serial Monitor.
  Serial.print("Logged weight: ");
  Serial.println(weight);
}

/**
 * Reads the logged data from the EEPROM and saves it to an Excel file on the local PC.
 * 
 * Note: Since there is no SD card available, this function assumes that the Arduino is connected to the PC via USB.
 * The Arduino acts as a serial device and sends the data to the PC, where it is processed and saved to an Excel file.
 * 
 * To read the data on the PC, you can use a serial communication program like Arduino IDE's Serial Monitor or a
 * third-party program like PuTTY or CoolTerm. Set the baud rate to 9600 and make sure the correct COM port is selected.
 * 
 * After opening the serial communication program, run this function by calling it from the Arduino code.
 * The logged data will be sent to the serial communication program and can be copied and saved to an Excel file.
 */
void readDataToExcel() {
  // Read the address from the EEPROM.
  int address = EEPROM.read(EEPROM_ADDRESS);

  // Print the data to the Serial Monitor.
  for (int i = 1; i <= address; i++) {
    // Read the weight value from the EEPROM at the current address.
    float weight;
    EEPROM.get(i, weight);

    // Print the weight value to the Serial Monitor.
    Serial.print("Weight ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(weight);
  }
}
