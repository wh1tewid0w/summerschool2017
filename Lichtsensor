const int analogInPin = A1;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  analogReadResolution(12);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  
  float voltage = (3.3/4096*analogRead(A1));
  float strom = (voltage/10020);
  float lichtstrom = (strom*2*1000000);
 Serial.print(lichtstrom,2);
 
Serial.print("\n");

 delay(1000);
}
