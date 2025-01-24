# Stand-Alone Sensor Node for Remote Field Monitoring  

This project, developed under **HIMCOSTE** and **NABARD**, focuses on a solar-powered stand-alone sensor node designed for monitoring environmental parameters in remote areas. The system integrates sensors for soil moisture, environmental temperature and humidity, and water temperature, with data transmission handled via GPRS using a TTGO T-Call ESP32 SIM800L module.

---

## Table of Contents  

1. [Introduction](#introduction)  
2. [Features](#features)  
3. [Components](#components)  
4. [Working Principle](#working-principle)  
5. [Sensor Integration and Implementation](#sensor-integration-and-implementation)  
6. [System Overview](#system-overview)  

---

## Introduction  

The **National Bank for Agriculture and Rural Development (NABARD)** is an apex institution that promotes sustainable and inclusive development in rural India. This project aligns with NABARD's goals by creating a renewable energy-powered sensor node for real-time environmental monitoring and data analysis.  

---

## Features  

- Solar-powered stand-alone device with 12V lead-acid battery.  
- Real-time monitoring of soil moisture, environmental temperature, humidity, and water temperature.  
- GPRS-enabled data transmission using BSNL 4G network.  
- Remote data access via ThingSpeak for visualization and analysis.  
- Energy-efficient and eco-friendly operation.  
- LED indicators for system status.  

---

## Components  

| S.No. | Component                       | Model                     | Quantity |  
|-------|----------------------------------|---------------------------|----------|  
| 1     | Microcontroller                  | TTGO T-Call ESP32 SIM800L | 1        |  
| 2     | Soil Moisture Sensor             | V1.2                      | 1        |  
| 3     | Temperature & Humidity Sensor    | SHT20                     | 1        |  
| 4     | Water Temperature Sensor         | DS18B20                   | 1        |  
| 5     | Solar Panel                      | 3-Watt                    | 1        |  
| 6     | Solar Charge Controller          | SY2024H                   | 1        |  
| 7     | Battery                          | Lead-acid (12V)           | 1        |  
| 8     | LEDs                             | -                         | 3        |  

---

## Working Principle  

This sensor node monitors various environmental parameters and uploads the data to ThingSpeak for remote analysis:  

1. **Power Supply**: The system uses a solar panel to charge a 12V lead-acid battery, ensuring a sustainable power source.  
2. **Sensor Monitoring**:  
   - Soil moisture levels are monitored using a capacitive soil moisture sensor.  
   - Temperature and humidity are measured using the SHT20 sensor.  
   - Water temperature is tracked using the DS18B20 sensor.  
3. **Data Transmission**: The TTGO T-Call ESP32 SIM800L module uploads real-time data to ThingSpeak using a GPRS-enabled SIM card (BSNL 4G).  
4. **System Indication**: LEDs provide visual feedback for system power, data acquisition, and data logging statuses.  

---

## Sensor Integration and Implementation  

### 1. Soil Moisture Sensor (V1.2):  
- Measures soil moisture using capacitive sensing.  
- **Voltage Range**: 3.3V to 5.5V.  
- Outputs analog signals corresponding to soil moisture levels.  

### 2. Temperature and Humidity Sensor (SHT20):  
- Measures temperature and humidity using capacitive and band-gap sensors.  
- **Interface**: I2C.  
- **Working Voltage**: 2.1V to 3.6V.  

### 3. Dallas Water Temperature Sensor (DS18B20):  
- Measures water temperature in reservoirs.  
- **Interface**: 1-Wire.  
- **Voltage Range**: 3V to 5.5V.  
- **Accuracy**: ±0.5°C.  

### 4. Solar Charge Controller (SY2024H):  
- Ensures safe charging of the 12V lead-acid battery.  
- Features built-in protections (short circuit, overload, reverse polarity).  

---

## System Overview  

### **Energy Conservation**  
The sensor node utilizes a solar panel for charging, ensuring reduced dependence on external power sources.  

### **Remote Access and Monitoring**  
Data is uploaded to ThingSpeak, enabling real-time analysis and trend tracking. Users can remotely access and analyze data for informed decision-making.  

### **Future Scope**  
Integration with weather prediction APIs can enable advanced irrigation management by comparing real-time data with weather forecasts to optimize resource usage.  

