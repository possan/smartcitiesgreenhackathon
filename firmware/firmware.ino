#include <dht11.h>
#include <MQ135.h>
// #include <Adafruit_NeoPixel.h>
// #include "FastLED.h"

#define DHT11_PIN 4

dht11 DHT;
MQ135 MQ(A0);

// CRGB leds[15];
// Adafruit_NeoPixel P(15, 8, NEO_RGB + NEO_KHZ400);

int dht_temp_calib = -6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
//  FastLED.addLeds<NEOPIXEL, 6>(leds, 15);
  pinMode(A1, INPUT);
  // P.begin();
}

int last_a0 = 2000;
int last_a1 = 2000;
int last_temp = 99;
int last_humid = 99;
int last_check = -1;
float last_ppm = .0f;
long last_sound_millis = 0;
long last_report_millis = 0;

void loop() {
  long M = millis();

  int a0 = analogRead(A0);
  if (digitalRead(A1) == 0) {
    // A1 is low when sound is above threshold 
    last_sound_millis = M;
  }

  long sound_delay = M - last_sound_millis;
  if (sound_delay > 3000) {
    sound_delay = 3000;
  }
  
  int a1 = (3000 - sound_delay) / 30;
  
  int check = DHT.read(DHT11_PIN);
  int temp = last_temp;
  int humid = last_humid;
  float tempppm = MQ.getCorrectedPPM(temp, humid);
  float ppm = last_ppm;
  if (tempppm < 50000.0) {
    // filter out failures.
    ppm = tempppm;
  }
  // float ppm = MQ.getCorrectedPPM(temp, humid);
  if (check == DHTLIB_OK) {
    temp = DHT.temperature + dht_temp_calib;
    humid = DHT.humidity;
  }

  long report_delay = M - last_report_millis;

  if (report_delay > 60) {
    last_report_millis = M;
    
    if (a0 != last_a0 ||
        a1 != last_a1 ||
        temp != last_temp ||
        humid != last_humid ||
        check != last_check ||
        ppm != last_ppm) {
  
      last_a0 = a0;
      last_a1 = a1;
      last_temp = temp;
      last_humid = humid;
      last_check = check;
      last_ppm = ppm;
  
      switch (check) {
        case DHTLIB_OK:
          // Serial.println("OK");
          break;
   
        case DHTLIB_ERROR_CHECKSUM:
          Serial.println("Checksum error");
          break;
   
        case DHTLIB_ERROR_TIMEOUT:
          // Serial.println("Timeout error");
          break;
  
        default:
          Serial.println("Unknown error");
          break;
      }
  
      // put your main code here, to run repeatedly:
      Serial.print("{ \"ppm\": "); Serial.print(ppm);
      Serial.print(", \"sound\": "); Serial.print(a1, DEC);
      Serial.print(", \"temp\": "); Serial.print(temp, DEC);
      Serial.print(", \"humid\": "); Serial.print(humid, DEC);
      Serial.print(", \"rzero\": "); Serial.print(MQ.getRZero());
    
      Serial.print(", \"lat\": 59.328267");
      Serial.print(", \"lng\": 18.021221");
      Serial.print(" }\n");
    }
  }
//  delay(1);
}
