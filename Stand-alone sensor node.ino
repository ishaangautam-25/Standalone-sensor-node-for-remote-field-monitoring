#define TINY_GSM_MODEM_SIM800
#include <Wire.h>
#include <TinyGsmClient.h>
#include <DFRobot_SHT20.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const char server[] = "api.thingspeak.com";
const char resource[] = "/update";
const int port = 80;
const char apn[] = "bsnlnet";
const char gprsUser[] = "";
const char gprsPass[] = "";
const char simPIN[] = "";
String apiKeyValue = "NI67S7PN0UMVVWOS";
String channelID = "2597621";

#define MODEM_RST 5
#define MODEM_PWKEY 4
#define MODEM_POWER_ON 23
#define MODEM_TX 27
#define MODEM_RX 26
#define I2C_SDA 2    // GPIO pin 2 for I2C SDA
#define I2C_SCL 4    // GPIO pin 4 for I2C SCL
#define SOIL_MOISTURE_PIN 34 // GPIO pin 34 for soil moisture sensor
#define LED_DATA_COLLECT 19  // GPIO pin 19 for data collection LED
#define LED_DATA_SEND 21     // GPIO pin 21 for data sending LED
#define DALLAS_PIN 18        // GPIO pin 18 for Dallas sensor

#define SerialMon Serial
#define SerialAT Serial1

#define TINY_GSM_RX_BUFFER 1024

TwoWire I2CPower = TwoWire(0);
DFRobot_SHT20 sht20;

OneWire oneWire(DALLAS_PIN);
DallasTemperature sensors(&oneWire);

TinyGsm modem(SerialAT);
TinyGsmClient client(modem);

#define uS_TO_S_FACTOR 1000000UL
#define TIME_TO_SLEEP 3600

#define IP5306_ADDR 0x75
#define IP5306_REG_SYS_CTL0 0x00

bool setPowerBoostKeepOn(int en) {
  I2CPower.beginTransmission(IP5306_ADDR);
  I2CPower.write(IP5306_REG_SYS_CTL0);
  if (en) {
    I2CPower.write(0x37);
  } else {
    I2CPower.write(0x35);
  }
  return I2CPower.endTransmission() == 0;
}

void setup() {
  SerialMon.begin(115200);
  I2CPower.begin(I2C_SDA, I2C_SCL, 400000);
  bool isOk = setPowerBoostKeepOn(1);
  SerialMon.println(String("IP5306 KeepOn ") + (isOk ? "OK" : "FAIL"));

  pinMode(MODEM_PWKEY, OUTPUT);
  pinMode(MODEM_RST, OUTPUT);
  pinMode(MODEM_POWER_ON, OUTPUT);
  digitalWrite(MODEM_PWKEY, LOW);
  digitalWrite(MODEM_RST, HIGH);
  digitalWrite(MODEM_POWER_ON, HIGH);

  pinMode(LED_DATA_COLLECT, OUTPUT);
  pinMode(LED_DATA_SEND, OUTPUT);
  digitalWrite(LED_DATA_COLLECT, LOW);
  digitalWrite(LED_DATA_SEND, LOW);

  SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
  delay(3000); // Allow time for modem to stabilize

  SerialMon.println("Initializing modem...");
  modem.restart();
  if (strlen(simPIN) && modem.getSimStatus() != 3) {
    modem.simUnlock(simPIN);
  }

  Wire.begin(I2C_SDA, I2C_SCL); // Initialize Wire library with GPIO pins for I2C
  sht20.initSHT20();
  delay(100); // Short delay after sensor initialization
  sht20.checkSHT20();

  sensors.begin(); // Initialize Dallas Temperature library
}

bool connectToAPN() {
  SerialMon.print("Connecting to APN: ");
  SerialMon.print(apn);
  if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
    SerialMon.println(" fail");
    return false;
  }
  SerialMon.println(" OK");
  return true;
}

bool connectToServer() {
  SerialMon.print("Connecting to ");
  SerialMon.print(server);
  if (!client.connect(server, port)) {
    SerialMon.println(" fail");
    return false;
  }
  SerialMon.println(" OK");
  return true;
}

void disconnectFromAPN() {
  modem.gprsDisconnect();
  SerialMon.println(F("GPRS disconnected"));
}

void restartModem() {
  SerialMon.println("Restarting modem...");
  digitalWrite(MODEM_POWER_ON, LOW);
  delay(1000);
  digitalWrite(MODEM_POWER_ON, HIGH);
  delay(1000);
  modem.restart();
  SerialMon.println("Modem restarted");
}

void loop() {
  digitalWrite(LED_DATA_COLLECT, HIGH); // Turn on data collection LED

  float temperature = sht20.readTemperature();
  float humidity = sht20.readHumidity();
  int soilMoistureRaw = analogRead(SOIL_MOISTURE_PIN);
  int soilMoisture = soilMoistureRaw / 4; // Divide the raw value by 4

  sensors.requestTemperatures();
  float dallasTemperature = sensors.getTempCByIndex(0);

  SerialMon.print("SHT20 Temperature: ");
  SerialMon.println(temperature);
  SerialMon.print("SHT20 Humidity: ");
  SerialMon.println(humidity);
  SerialMon.print("Soil Moisture: ");
  SerialMon.println(soilMoisture);
  SerialMon.print("Dallas Temperature: ");
  SerialMon.println(dallasTemperature);

  // Try to connect to the APN with retries
  int retryCount = 0;
  const int maxRetries = 5;
  while (!connectToAPN() && retryCount < maxRetries) {
    retryCount++;
    SerialMon.print("Retrying to connect to APN... Attempt ");
    SerialMon.println(retryCount);
    delay(5000); // Wait 5 seconds before retrying
  }
  if (retryCount == maxRetries) {
    SerialMon.println("Failed to connect to APN after max retries");
    restartModem();
    digitalWrite(LED_DATA_COLLECT, LOW); // Turn off data collection LED
    return;
  }

  // Try to connect to the server with retries
  retryCount = 0;
  while (!connectToServer() && retryCount < maxRetries) {
    retryCount++;
    SerialMon.print("Retrying to connect to server... Attempt ");
    SerialMon.println(retryCount);
    delay(5000); // Wait 5 seconds before retrying
  }
  if (retryCount == maxRetries) {
    SerialMon.println("Failed to connect to server after max retries");
    disconnectFromAPN();
    restartModem();
    digitalWrite(LED_DATA_COLLECT, LOW); // Turn off data collection LED
    return;
  }

  digitalWrite(LED_DATA_SEND, HIGH); // Turn on data sending LED

  SerialMon.println("Performing HTTP POST request...");
  String httpRequestData = "api_key=" + apiKeyValue 
                           + "&channel_id=" + channelID
                           + "&field1=" + String(temperature) 
                           + "&field2=" + String(humidity)
                           + "&field3=" + String(soilMoisture)
                           + "&field4=" + String(dallasTemperature);

  client.print(String("POST ") + resource + " HTTP/1.1\r\n");
  client.print(String("Host: ") + server + "\r\n");
  client.println("Connection: close");
  client.println("Content-Type: application/x-www-form-urlencoded");
  client.print("Content-Length: ");
  client.println(httpRequestData.length());
  client.println();
  client.println(httpRequestData);

  unsigned long timeout = millis();
  while (client.connected() && millis() - timeout < 10000L) {
    while (client.available()) {
      char c = client.read();
      SerialMon.print(c);
      timeout = millis();
    }
  }
  SerialMon.println();

  client.stop();
  SerialMon.println(F("Server disconnected"));
  disconnectFromAPN();

  digitalWrite(LED_DATA_COLLECT, LOW); // Turn off data collection LED
  digitalWrite(LED_DATA_SEND, LOW);    // Turn off data sending LED

  delay(10000); // Adjusted delay to 10 seconds before the next loop iteration
}
