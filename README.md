# cane capstone
smart cane arduino code used in capstone project

list of materials:
- arduino mega 2560
- hx711 load cell amplifier
- esp8266 wifi transceiver
- arduino uno r4
- DYMH-103 Mini Load Cell

eeprom.ino was the code used to save data locally onto the onboard memory
read-load-cell was the main code used to read data from the loadcell
calibrate-load-cell was to calibrate the load cell to get accurate readings

A “smart” cane that is capable of collecting data
This data will come from an integrated load cell
The load cell will be connected to an Arduino  
Arduino IoT clouds services communicate the Cane
Data will be monitored through mobile device

Data collection is for research purposes
Load applied on canes is correlated to user condition
Data can be used as a screening method for user health
Upward trends in load could indicate other health issues, prompting an earlier check up
Data could be used to determine if patients need aid in mobility
