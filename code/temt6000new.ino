
// These constants won't change.  They're used to give names
// to the pins used:
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

  
  float voltage = (3.3/4096*sensorValue);
  float strom = (voltage/10020);
  float lichtstrom = (strom*2*1000000);
  lichtstrom = lichtstrom / 6.5852;         //In Prozent 658,52 (Maximalwert) / 100
  uint8_t lichtstrom_int = (uint8_t) lichtstrom;

  Serial.print("Helligkeit: "); 
  Serial.print(lichtstrom_int);
  Serial.print("%");
  Serial.print("\n");

  delay(1000);
}
