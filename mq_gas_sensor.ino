//www.elegoo.com
//2016.12.8

// Define Pins
#define BLUE 3
#define GREEN 5
#define RED 6

int buzzer = 12; 
const int mqPin = A0; // Connect the sensor's analog output to A0
float sensorVoltage; // Voltage read from the sensor
float sensorValue;   // Raw analog value from the sensor
float ppm;           // Gas concentration in ppm (simplified approximation)


void setup()
{
Serial.begin(9600);
Serial.println("MQ Gas Sensor Reading");
pinMode(RED, OUTPUT);
pinMode(GREEN, OUTPUT);
pinMode(BLUE, OUTPUT);
digitalWrite(RED, HIGH);
digitalWrite(GREEN, LOW);
digitalWrite(BLUE, LOW);

pinMode(buzzer, OUTPUT); 
}

// define variables
int redValue;
int greenValue;
int blueValue;

// main loop
void loop()
{
  int adjust = -1; 

  // Read the raw analog value from the sensor
  sensorValue = analogRead(mqPin);

  // Convert the analog value to voltage
  sensorVoltage = sensorValue * (5.0 / 1023.0); // Assuming a 5V ADC reference

  // Estimate the gas concentration (you may need a specific formula for your gas and sensor)
  // The conversion formula will vary based on your MQ sensor type and its datasheet
  ppm = map(sensorValue, 0, 1023, 0, 1000); // Simplified ppm calculation for demonstration
 
  // Print the values to the Serial Monitor
  Serial.print("Analog Value: ");
  Serial.print(sensorValue);
  Serial.print("\tVoltage: ");
  Serial.print(sensorVoltage);
  Serial.print(" V\tEstimated PPM: ");
  Serial.println(ppm);

  if (ppm < 264 - adjust) {
    analogWrite(RED, 0); 
    analogWrite(GREEN, 0); 
    analogWrite(BLUE, 0); 
    delay(1000); 
  }else if (ppm == 264 - adjust) {
    analogWrite(RED, 255); 
    analogWrite(GREEN, 0); 
    analogWrite(BLUE, 0); 
    delay(1000); 
  }else if (ppm == 265 - adjust) {
    analogWrite(RED, 255); 
    analogWrite(GREEN, 10); 
    analogWrite(BLUE, 0); 
    delay(1000); 
  }else if (ppm == 266 - adjust) {
    analogWrite(RED, 255); 
    analogWrite(GREEN, 255); 
    analogWrite(BLUE, 0); 
    delay(1000); 
  }else if (ppm == 267 - adjust) { 
    analogWrite(RED, 0); 
    analogWrite(GREEN, 255); 
    analogWrite(BLUE, 0); 
    buzz(200); 
  }else if (ppm == 268 - adjust) {
    analogWrite(RED, 0); 
    analogWrite(GREEN, 0); 
    analogWrite(BLUE, 255); 
    buzz(150);
  }else if (ppm == 269 - adjust) {
    analogWrite(RED, 255); 
    analogWrite(GREEN, 0); 
    analogWrite(BLUE, 255); 
    buzz(100); 
  }else if (ppm > 269 - adjust) {
    analogWrite(RED, 255); 
    analogWrite(GREEN, 255); 
    analogWrite(BLUE, 255); 
    buzz(75); 
  }
}

void buzz(int d) {
  for (int i = 0; i < 1000/d; i++) {
    digitalWrite(buzzer, HIGH); 
    delay(d/4); 
    digitalWrite(buzzer, LOW); 
    delay(d); 
  }
}
