// RMIT University
// School of Design
//
// Wearables Studio
// Humidity and Temperature NeoPixel Display
//
// Written by Anthony Despotellis and Scott Mitchell
// Based on code by Tony DiCola
// Released under a GNU General Public License

// Depends on the following Arduino libraries:
// - Adafruit Unified Sensor Library: https://github.com/adafruit/Adafruit_Sensor
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_NeoPixel.h>

// define the Arduino pins
const int DHTpin = 2;            // Pin which is connected to the DHT sensor.
const int NP1pin = 5;            // Pin for NeoPixel Strip 1
const int NP2pin = 6;            // Pin for NeoPixel Strip 2

// define the sensor in use
#define DHTTYPE           DHT11     // DHT 11 
//#define DHTTYPE           DHT22     // DHT 22 (AM2302)
//#define DHTTYPE           DHT21     // DHT 21 (AM2301)

DHT_Unified dht(DHTpin, DHTTYPE);

// set the number of NeoPixels per strip
const int NUMPIXELS = 8;

Adafruit_NeoPixel myPixels1 = Adafruit_NeoPixel(NUMPIXELS, NP1pin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel myPixels2 = Adafruit_NeoPixel(NUMPIXELS, NP2pin, NEO_GRB + NEO_KHZ800);

unsigned long delayMS;

void setup() {
  Serial.begin(9600);
  // Initialize Sensor.
  dht.begin();
  Serial.println("DHT11 Unified Sensor Initialized");

  // Print temp sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");
  Serial.println("------------------------------------");

  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Humidity");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");
  Serial.println("------------------------------------");
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;

  // Initialize the NeoPixels.
  myPixels1.begin();
  myPixels2.begin();
}

void loop() {
  // initallise variables
  int pixelNum1 = 0;
  int pixelNum2 = 0;

  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  // check to see if it is a number (isnan = is not a number)
  if (isnan(event.temperature)) {
    Serial.println("Error reading temperature!");
  }
  else {
    Serial.print("Temperature: ");
    Serial.print(event.temperature);
    Serial.println(" *C");
    pixelNum1 = map(event.temperature, 20, 30, 0, 7);
    pixelNum1 = constrain(pixelNum1, 0, 7);
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  // check to see if it is a number (isnan = is not a number)
  if (isnan(event.relative_humidity)) {
    Serial.println("Error reading humidity!");
  }
  else {
    Serial.print("Humidity: ");
    Serial.print(event.relative_humidity);
    Serial.println("%");
    pixelNum2 = map(event.relative_humidity, 0, 50, 0, 7);
    pixelNum2 = constrain(pixelNum2, 0, 7);
  }

  for (int i = 0; i < NUMPIXELS; i++) {
    if (pixelNum1 >= i) {
      myPixels1.setPixelColor(i, myPixels1.Color(0, 100, 100));
    } else {
      myPixels1.setPixelColor(i, myPixels1.Color(0, 0, 0));
    }
    if (pixelNum2 >= i) {
      myPixels2.setPixelColor(i, myPixels2.Color(150, 0, 0));
    } else {
      myPixels2.setPixelColor(i, myPixels2.Color(0, 0, 0));
    }
  }
  myPixels1.show();
  myPixels2.show();

  // Delay between measurements.
  delay(delayMS);
}


