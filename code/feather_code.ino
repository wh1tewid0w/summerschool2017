

/*******************************************************************************
   Copyright (c) 2015 Thomas Telkamp and Matthijs Kooijman

   Permission is hereby granted, free of charge, to anyone
   obtaining a copy of this document and accompanying files,
   to do whatever they want with them without any restriction,
   including, but not limited to, copying, modification and redistribution.
   NO WARRANTY OF ANY KIND IS PROVIDED.

   This example sends a valid LoRaWAN packet with payload "Hello,
   world!", using frequency and encryption settings matching those of
   the The Things Network.

   This uses ABP (Activation-by-personalisation), where a DevAddr and
   Session keys are preconfigured (unlike OTAA, where a DevEUI and
   application key is configured, while the DevAddr and session keys are
   assigned/generated in the over-the-air-activation procedure).

   Note: LoRaWAN per sub-band duty-cycle limitation is enforced (1% in
   g1, 0.1% in g2), but not the TTN fair usage policy (which is probably
   violated by this sketch when left running for longer)!

   To use this sketch, first register your application and device with
   the things network, to set or generate a DevAddr, NwkSKey and
   AppSKey. Each device should have their own unique values for these
   fields.

   Do not forget to define the radio type correctly in config.h.

 *******************************************************************************/

#include <lmic.h> //lmic master library (LoRa) 
#include <hal/hal.h>
//#include <SPI.h> falls Sensoren mit SPI betrieben werden sollen

#include <Adafruit_BME280.h> //bme library einbinden
#include <Adafruit_Sensor.h> //Zusatz zur bme library
#define SEALEVELPRESSURE_HPA (1013.25) //
#define VBATPIN A7 

Adafruit_BME280 bme; //I2C


// LoRaWAN NwkSKey, network session key
// This is the default Semtech key, which is used by the early prototype TTN
// network.
static const PROGMEM u1_t NWKSKEY[16] = { 0x71, 0x4A, 0xD9, 0x03, 0x8F, 0x8F, 0x38, 0x21, 0x1E, 0xA5, 0xA2, 0x4D, 0xDC, 0x1C, 0x5D, 0x08 };

// LoRaWAN AppSKey, application session key
// This is the default Semtech key, which is used by the early prototype TTN
// network.
static const u1_t PROGMEM APPSKEY[16] = { 0x3A, 0x67, 0x79, 0xA5, 0x50, 0x4F, 0xC6, 0x82, 0x7C, 0x00, 0x17, 0x14, 0xBC, 0xD3, 0x2B, 0xFD };

// LoRaWAN end-device address (DevAddr)
static const u4_t DEVADDR = 0x26011CD5 ; // <-- Change this address for every node!


//Lichtsensor
const int analogInPin = A1; //Analog input pin that potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int lightsensorValue = 0;


//Bodenfeuchtigkeitssensor
int gndSoilValue = 0; //value for storing moisture value
int gndSoilPin = A2; //Declare a variable for the soil moisture sensor
int gndSoilPower = 7; //Variable for Soil moisture


// These callbacks are only used in over-the-air activation, so they are
// left empty here (we cannot leave them out completely unless
// DISABLE_JOIN is set in config.h, otherwise the linker will complain).
void os_getArtEui (u1_t* buf) { }
void os_getDevEui (u1_t* buf) { }
void os_getDevKey (u1_t* buf) { }



static uint8_t sensordata[8];
static osjob_t sendjob;

// Schedule TX every this many seconds (might become longer due to duty
// cycle limitations).
const unsigned TX_INTERVAL = 20;

// Pin mapping
const lmic_pinmap lmic_pins = {
  .nss = 8,
  .rxtx = LMIC_UNUSED_PIN,
  .rst = 5,
  .dio = {3, 6, LMIC_UNUSED_PIN},
};

void onEvent (ev_t ev) {
  Serial.print(os_getTime());
  Serial.print(": ");
  switch (ev) {
    case EV_SCAN_TIMEOUT:
      Serial.println(F("EV_SCAN_TIMEOUT"));
      break;
    case EV_BEACON_FOUND:
      Serial.println(F("EV_BEACON_FOUND"));
      break;
    case EV_BEACON_MISSED:
      Serial.println(F("EV_BEACON_MISSED"));
      break;
    case EV_BEACON_TRACKED:
      Serial.println(F("EV_BEACON_TRACKED"));
      break;
    case EV_JOINING:
      Serial.println(F("EV_JOINING"));
      break;
    case EV_JOINED:
      Serial.println(F("EV_JOINED"));
      break;
    case EV_RFU1:
      Serial.println(F("EV_RFU1"));
      break;
    case EV_JOIN_FAILED:
      Serial.println(F("EV_JOIN_FAILED"));
      break;
    case EV_REJOIN_FAILED:
      Serial.println(F("EV_REJOIN_FAILED"));
      break;
    case EV_TXCOMPLETE:
      Serial.println(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
      if (LMIC.txrxFlags & TXRX_ACK)
        Serial.println(F("Received ack"));
      if (LMIC.dataLen) {
        Serial.println(F("Received "));
        Serial.println(LMIC.dataLen);
        Serial.println(F(" bytes of payload"));
      }
      // Schedule next transmission
      os_setTimedCallback(&sendjob, os_getTime() + sec2osticks(TX_INTERVAL), do_send);
      break;
    case EV_LOST_TSYNC:
      Serial.println(F("EV_LOST_TSYNC"));
      break;
    case EV_RESET:
      Serial.println(F("EV_RESET"));
      break;
    case EV_RXCOMPLETE:
      // data received in ping slot
      Serial.println(F("EV_RXCOMPLETE"));
      break;
    case EV_LINK_DEAD:
      Serial.println(F("EV_LINK_DEAD"));
      break;
    case EV_LINK_ALIVE:
      Serial.println(F("EV_LINK_ALIVE"));
      break;
    default:
      Serial.println(F("Unknown event"));
      break;
  }
}

void sensor_data() {

  //Temperatur
  float tempratureReadout = (bme.readTemperature() + 50) * 100; //Temperatur wird um 50°C nach rechts verschoben, dass Temperaturen von -50°C bis +50°C gemessen werden, danach wird mit 100 multipliziert, um Komma zahlen zu vermeiden
  uint16_t temperature = (uint16_t) tempratureReadout; //Temperatur wird gecastet, also von float in ein uint16_t umgewandelt
  uint8_t hightempratureByte = (uint8_t) ((temperature & 0xFF00) >> 8); // bitshift um 8 Stellen nach rechts
  uint8_t lowtempratureByte = (uint8_t) (temperature & 0xFF); //bitshift um 8 Stellen nach links
  Serial.println(hightempratureByte);
  Serial.println(lowtempratureByte);


  //Luftdruck
  float pressureReadout = bme.readPressure() / 100.0F;
  uint16_t pressure = (uint16_t ) ((pressureReadout / 1013.25) * 100);
  uint8_t pressureByte = (uint8_t) pressure;
  Serial.println(pressureByte);


  //Luftfeuchtigkeit
  float humidityReadout = bme.readHumidity() * 100;
  uint16_t humidity = (uint16_t) humidityReadout;
  uint8_t highhumidityByte = (uint8_t) ((humidity & 0xFF00) >> 8);
  uint8_t lowhumidityByte = (uint8_t) (humidity & 0xFF);
  Serial.println(highhumidityByte);
  Serial.println(lowhumidityByte);


  //Lichtsensor
  lightsensorValue = analogRead(analogInPin);
  float lightsensorVoltage = (3.3 / 4096 * lightsensorValue);
  float lightsensorStrom = (lightsensorVoltage / 10020);
  float lightstrom = (lightsensorStrom * 2 * 1000000);
  lightstrom = lightstrom / 6.5852;         //In Prozent 658,52 (Maximalwert) / 100
  uint8_t lightstromInt = (uint8_t) lightstrom;
  Serial.println(lightstromInt);


  //Bodenfeuchtigkeitssensor
  gndSoilPower = analogRead(gndSoilPin);
  uint8_t gndPercent = (uint8_t) ((analogRead(A2) / 33.30F) * 100);
  Serial.println(gndPercent);

  //Akkustand auslesen
  float measuredvbat = analogRead(VBATPIN);
  measuredvbat *= 2;    // we divided by 2, so multiply back
  measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
  measuredvbat /= 4096; // convert to voltage
  uint16_t akkuvoltageInt16 = (uint16_t) (measuredvbat * 100);
  uint8_t akkuVoltage = (uint8_t) akkuvoltageInt16;
  Serial.print("VBat: " ); Serial.println(measuredvbat);

  //Werte ins Array schreiben
  sensordata[0] = hightempratureByte;
  sensordata[1] = lowtempratureByte;
  sensordata[2] = pressureByte;
  sensordata[3] = highhumidityByte;
  sensordata[4] = lowhumidityByte;
  sensordata[5] = lightstromInt;
  sensordata[6] = gndPercent;
  sensordata[7] = akkuVoltage;


}


void do_send(osjob_t* j) {

  sensor_data();

  // Check if there is not a current TX/RX job running
  if (LMIC.opmode & OP_TXRXPEND) {
    Serial.println(F("OP_TXRXPEND, not sending"));
  } else {
    // Prepare upstream data transmission at the next possible time.
    LMIC_setTxData2(1, sensordata, sizeof(sensordata) , 0);
    Serial.println(F("Packet queued"));
  }
  // Next TX is scheduled after TX_COMPLETE event.
}

void setup() {
  delay (5000);
  bool status;

  //bme Initialisierung
  status = bme.begin();
  delay(1000);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  Serial.begin(115200);
  Serial.println(F("Starting"));

  analogReadResolution(12); //Lichtsensor, Bodenfeuchtigkeitssensor

  //Bodenfeuchtigkeitssensor
  pinMode(gndSoilPower, OUTPUT); //Set D7 as an output
  digitalWrite(gndSoilPower, LOW); //Set to Low so no power is flowing through the sensor



#ifdef VCC_ENABLE
  // For Pinoccio Scout boards
  pinMode(VCC_ENABLE, OUTPUT);
  digitalWrite(VCC_ENABLE, HIGH);
  delay(1000);
#endif

  // LMIC init
  os_init();
  // Reset the MAC state. Session and pending data transfers will be discarded.
  LMIC_reset();

  // Set static session parameters. Instead of dynamically establishing a session
  // by joining the network, precomputed session parameters are be provided.
#ifdef PROGMEM
  // On AVR, these values are stored in flash and only copied to RAM
  // once. Copy them to a temporary buffer here, LMIC_setSession will
  // copy them into a buffer of its own again.
  uint8_t appskey[sizeof(APPSKEY)];
  uint8_t nwkskey[sizeof(NWKSKEY)];
  memcpy_P(appskey, APPSKEY, sizeof(APPSKEY));
  memcpy_P(nwkskey, NWKSKEY, sizeof(NWKSKEY));
  LMIC_setSession (0x1, DEVADDR, nwkskey, appskey);
#else
  // If not running an AVR with PROGMEM, just use the arrays directly
  LMIC_setSession (0x1, DEVADDR, NWKSKEY, APPSKEY);
#endif

#if defined(CFG_eu868)
  // Set up the channels used by the Things Network, which corresponds
  // to the defaults of most gateways. Without this, only three base
  // channels from the LoRaWAN specification are used, which certainly
  // works, so it is good for debugging, but can overload those
  // frequencies, so be sure to configure the full frequency range of
  // your network here (unless your network autoconfigures them).
  // Setting up channels should happen after LMIC_setSession, as that
  // configures the minimal channel set.
  // NA-US channels 0-71 are configured automatically
  LMIC_setupChannel(0, 868100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(1, 868300000, DR_RANGE_MAP(DR_SF12, DR_SF7B), BAND_CENTI);      // g-band
  LMIC_setupChannel(2, 868500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(3, 867100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(4, 867300000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(5, 867500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(6, 867700000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(7, 867900000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(8, 868800000, DR_RANGE_MAP(DR_FSK,  DR_FSK),  BAND_MILLI);      // g2-band
  // TTN defines an additional channel at 869.525Mhz using SF9 for class B
  // devices' ping slots. LMIC does not have an easy way to define set this
  // frequency and support for class B is spotty and untested, so this
  // frequency is not configured here.
#elif defined(CFG_us915)
  // NA-US channels 0-71 are configured automatically
  // but only one group of 8 should (a subband) should be active
  // TTN recommends the second sub band, 1 in a zero based count.
  // https://github.com/TheThingsNetwork/gateway-conf/blob/master/US-global_conf.json
  LMIC_selectSubBand(1);
#endif

  // Disable link check validation
  LMIC_setLinkCheckMode(0);

  // TTN uses SF9 for its RX2 window.
  LMIC.dn2Dr = DR_SF9;

  // Set data rate and transmit power for uplink (note: txpow seems to be ignored by the library)
  LMIC_setDrTxpow(DR_SF7, 14);

  // Start job
  do_send(&sendjob);
}

void loop() {
  os_runloop();

}

