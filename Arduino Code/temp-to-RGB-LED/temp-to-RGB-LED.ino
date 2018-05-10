// RMIT University
// School of Design
//
// Wearables Studio
// Temperature RGB Display
// 
// Written by Scott Mitchell
// Released under a GNU General Public License


// define the Arduino pins
int tempSensor = A0;
int LEDRpin = 11;
int LEDGpin = 10;
int LEDBpin = 9;

void setup() {
  // setup the pins
  pinMode(LEDRpin, OUTPUT);
  pinMode(LEDGpin, OUTPUT);
  pinMode(LEDBpin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //getting the voltage reading from the temperature sensor
  int reading = analogRead(tempSensor);

  // converting that reading to voltage, for 3.3v arduino use 3.3
  float voltage = reading * 5.0;
  voltage /= 1024.0;

  // print out the voltage
  Serial.print(voltage); Serial.print(" volts  ");

  // now get the temperature in degrees C.
  float temperatureC = (voltage - 0.5) * 100 ; //converting from 10 mv per degree wit 500 mV offset
  //to degrees ((voltage - 500mV) times 100)
  Serial.print(temperatureC); Serial.println(" degrees C");

  // convert to integer
  int tempValue = temperatureC;

  int blueValue = 0;
  if (tempValue <= 20) {
    blueValue = map(tempValue, 0, 20, 255, 0);
  }
  blueValue = constrain(blueValue, 0, 255);

  int greenValue = 0;
  if (tempValue <= 20) {
    greenValue = map(tempValue, 0, 20, 0, 255);
  } else {
    greenValue = map(tempValue, 21, 40, 255, 0);
  }
  greenValue = constrain(greenValue, 0, 255);


  int redValue = 0;
  if (tempValue > 20) {
    redValue = map(tempValue, 20, 40, 0, 255);
  }
  redValue = constrain(redValue, 0, 255);

  // set the RGB LED values
  analogWrite(LEDRpin, redValue);
  analogWrite(LEDGpin, greenValue);
  analogWrite(LEDBpin, blueValue);

  // delay in between reads for stability
  delay(1);
}
