// #include <ESP8266HTTPUpdateServer.h>
// #include <ESP8266WiFi.h>
// #include <DNSServer.h>
// #include <ESP8266WebServer.h>
// #include <ESP8266SSDP.h>
// #include <WiFiManager.h>
// #include <ESP8266mDNS.h>
// #include <WiFiUdp.h>
// #include <ArduinoOTA.h>
// #include <PubSubClient.h>
// #include <ArduinoJson.h>
#include "OpenBCI_Wifi.h"
#include "PTW-Arduino-Assert.h"

int ledPin = 0;

void testGetOutputMode() {
  test.describe("getOutputMode");

  // RAW
  test.assertEqualString(wifi.getOutputMode(wifi.OUTPUT_MODE_RAW),"raw","Should have gotten 'raw' string");

  // JSON
  test.assertEqualString(wifi.getOutputMode(wifi.OUTPUT_MODE_JSON),"json","Should have gotten 'json' string");
}

void testGetScaleFactorCyton() {
  test.describe("getScaleFactorCyton");

}

void testGetScaleFactorGanglion() {
  test.describe("getScaleFactorGanglion");


}



void testGetters() {
  testGetOutputMode();
  testGetScaleFactorCyton();
  testGetScaleFactorGanglion();
}

void testInt24To32() {
  test.describe("int24To32");

  uint8_t arr[3];
  arr[0] = 0x00; arr[1] = 0x06; arr[2] = 0x90;
  test.assertEqualInt(wifi.int24To32(arr), 1680, "Should convert a small positive number");

  arr[0] = 0x02; arr[1] = 0xC0; arr[2] = 0x01; // 0x02C001 === 180225
  test.assertEqualInt(wifi.int24To32(arr), 180225, "converts a large positive number");

  arr[0] = 0xFF; arr[1] = 0xFF; arr[2] = 0xFF; // 0xFFFFFF === -1
  test.assertEqualInt(wifi.int24To32(arr), -1, "converts a small negative number");

  arr[0] = 0x81; arr[1] = 0xA1; arr[2] = 0x01; // 0x81A101 === -8281855
  test.assertEqualInt(wifi.int24To32(arr), -8281855, "converts a large negative number");
}

void testRawToLongLong() {
  test.describe("rawToLongLong");

  uint8_t expected_gain = 25;
  float channelScaleFactor = ADS1299_VREF / expected_gain / (2^23 - 1);
  uint8_t expectedNumChannels = 8;

  uint8_t arr[24];
  for (int i = 0; i < 24; i++) {
    if (i%3==2) arr[i]=i+1;
    else arr[i] = 0;
  }

  long long

  test.assertApproximately(103.01, 103.3, 1, "should be within 1");

  for (let i = 0; i < k.OBCINumberOfChannelsDefault; i++) {
  expect(sample.channelData[i]).to.be.approximately(newSample.channelData[i], 0.001);
}

  // for (let i = 0; i < k.OBCINumberOfChannelsDefault; i++) {
  // expect(sample.channelData[i]).to.be.approximately(newSample.channelData[i], 0.001);

}

void testUtils() {
  testInt24To32();
  testRawToLongLong();
}

void go() {
  // Start the test
  test.begin();
  digitalWrite(ledPin, HIGH);
  testGetters();
  testUtils();
  test.end();
  digitalWrite(ledPin, LOW);
}

void setup() {
  pinMode(ledPin,OUTPUT);
  Serial.begin(115200);
  test.setSerial(Serial);
  test.failVerbosity = true;

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    Serial.read();
    go();
  }
}
