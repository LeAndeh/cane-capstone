// Include the necessary libraries for the HX711 load cell amplifier.
#include <HX711.h>
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>

// Define the pins for the HX711 load cell amplifier.
#define LOADCELL_DOUT_PIN 3
#define LOADCELL_SCK_PIN 2

// Define the WiFi credentials.
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Define the Arduino Cloud server and port.
const char* server = "api.arduino.cc";
const int port = 443;

// Define the Arduino Cloud thing ID and thing secret.
const char* thingId = "your_THING_ID";
const char* thingSecret = "your_THING_SECRET";

// Instantiate an object of the HX711 class, representing the load cell amplifier.
HX711 scale;

// Instantiate an object of the WiFiClient class, representing the WiFi client.
WiFiClient wifiClient;

// Instantiate an object of the HttpClient class, representing the HTTP client.
HttpClient httpClient = HttpClient(wifiClient, server, port);

// The `setup` function initializes the environment when the Arduino board powers on or resets.
void setup() {
  // Initiate serial communication at 9600 baud rate.
  Serial.begin(9600);

  // Connect to the WiFi network.
  connectWiFi();

  // Initialize the HX711 load cell amplifier.
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

// The `loop` function continuously cycles as long as the Arduino is powered.
void loop() {
  // Read the load cell value.
  long loadCellValue = scale.read();

  // Convert the load cell value to a string.
  String loadCellString = String(loadCellValue);

  // Send the load cell data to the Arduino Cloud.
  sendDataToCloud(loadCellString);

  // Introduce a delay of 1 second between each data logging.
  delay(1000);
}

/* Connects to the WiFi network */
void connectWiFi() {
  // Set the WiFi mode to station mode.
  WiFi.begin(ssid, password);

  // Wait until the WiFi connection is established.
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi!");
}

/**
 * Sends the load cell data to the Arduino Cloud.
 * 
 * @param data The load cell data to be sent to the cloud.
 */
void sendDataToCloud(String data) {
  // Create the request URL.
  String url = "/create/your_THING_ID/your_THING_SECRET/your_PROPERTY_NAME";
  url.replace("your_THING_ID", thingId);
  url.replace("your_THING_SECRET", thingSecret);
  url.replace("your_PROPERTY_NAME", "load_cell_data");

  // Create the request body.
  String requestBody = "{\"value\": " + data + "}";

  // Send the POST request to the Arduino Cloud.
  httpClient.beginRequest();
  httpClient.post(url, "application/json");
  httpClient.sendHeader("Content-Length", requestBody.length());
  httpClient.beginBody();
  httpClient.print(requestBody);
  httpClient.endRequest();

  // Read and print the response from the Arduino Cloud.
  int statusCode = httpClient.responseStatusCode();
  String response = httpClient.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
}
