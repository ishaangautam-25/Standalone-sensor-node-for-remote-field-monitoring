This repository contains the implementation of a stand-alone sensor node designed for monitoring environmental parameters in rural and agricultural settings. The sensor node leverages renewable solar energy and transmits real-time data to a remote server via GPRS.

Overview: This project is developed under NABARD's initiative to enhance agricultural productivity and rural development by employing IoT-based solutions. The sensor node is powered by a solar panel and integrates advanced sensors to monitor parameters like soil moisture, environmental temperature and humidity, and water temperature in reservoirs. Data is transmitted to the cloud (ThingSpeak) for real-time analysis using the TTGO T-Call ESP32 SIM800L board.

Features Renewable Energy Powered: Operates on solar power with a 12V lead-acid battery for energy storage. Remote Monitoring: Uses a BSNL 4G SIM card for data transmission via GPRS, eliminating the dependency on Wi-Fi. Real-Time Data Logging: Sends sensor readings to ThingSpeak for analysis and visualization. Compact and Integrated Design: Combines NodeMCU and SIM800L module functionalities in the TTGO T-Call ESP32 board. Upgradable: Designed to integrate weather prediction APIs and advanced algorithms for irrigation planning. Components Used

1 Node MCU (TTGO T-Call ESP32 SIM800L) 2 Soil moisture sensor V1.2 3 Temperature and humidity sensor SHT20 4 Water temperature sensor DS18B20 5 Solar panel (3W) 6 Solar charge controller SY2024H 7 Battery Lead-acid (12V) 8 LEDs

How It Works?

Data Collection:

Soil Moisture Sensor (V1.2): Measures soil moisture levels using capacitive sensing. SHT20 Sensor: Monitors environmental temperature and humidity with high precision. DS18B20 Sensor: Measures water temperature in reservoirs.

Data Transmission:

Sensor readings are gathered by the TTGO T-Call ESP32 board and transmitted to the ThingSpeak server using a SIM800L GPRS connection.

Energy Management:

The solar panel charges a 12V lead-acid battery through the SY2024H solar charge controller. LEDs indicate system status: Red: Power ON. Yellow: Data acquisition in progress. Green: Data logging to ThingSpeak.

Real-Time Monitoring:

The collected data is visualized on ThingSpeak, enabling remote monitoring and analysis of environmental conditions. Advanced Features

Weather Prediction Integration (Future Scope): By incorporating weather APIs, users can plan irrigation and farming activities based on soil conditions and forecasted weather.

Energy Conservation: Solar power usage reduces dependency on external power sources, ensuring sustainable operation.

Installation and Usage

Hardware Setup:

Connect all sensors (Soil Moisture, SHT20, DS18B20) to the TTGO T-Call ESP32 board.
Wire the solar panel to the SY2024H solar charge controller and connect it to the 12V battery.
Software Configuration:

Install necessary libraries for ESP32 and ThingSpeak integration.
Configure the GPRS module with a BSNL 4G SIM card.
Update the code with your ThingSpeak API key and other necessary parameters.
Upload Code:

Use Arduino IDE to upload the code to the TTGO T-Call ESP32 board.

Monitor Data:

Access ThingSpeak to view real-time sensor readings and historical data trends.

Future Enhancements: Integration of weather prediction algorithms for smart irrigation planning. Addition of more environmental sensors for comprehensive monitoring. Optimization of power consumption for extended operation.

Contributing: Contributions are welcome! Feel free to submit issues, pull requests, or suggestions to enhance this project.
