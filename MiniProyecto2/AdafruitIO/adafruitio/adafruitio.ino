// Adafruit IO Publish & Subscribe Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Example Starts Here *******************************/

#define RX 27
#define TX 28

// this int will hold the current count for our sketch
int count = 0;

// Track time of last published messages and limit feed->save events to once
// every IO_LOOP_DELAY milliseconds.
//
// Because this sketch is publishing AND subscribing, we can't use a long
// delay() function call in the main loop since that would prevent io.run()
// from being called often enough to receive all incoming messages.
//
// Instead, we can use the millis() function to get the current time in
// milliseconds and avoid publishing until IO_LOOP_DELAY milliseconds have
// passed.

#define IO_LOOP_DELAY 3500
unsigned long lastUpdate = 0;
int state = 0;
int s1 = 0;
int s2 = 0;

// set up the 'enter' feed
AdafruitIO_Feed *enter = io.feed("enter");
AdafruitIO_Feed *adafruitp1 = io.feed("adafruitp1");
AdafruitIO_Feed *adafruitp2 = io.feed("adafruitp2");

void setup() {
  state = s1 + s2;
  // start the serial connection
  Serial.begin(115200);
  // start the second serial connection
  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  // wait for serial monitor to open
  while (! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // set up a message handler for the count feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  enter->onMessage(handleData);
  adafruitp1->onMessage(handleP1);
  adafruitp2->onMessage(handleP2);

  // wait for a connection
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  enter->get();
  adafruitp1->get();
  adafruitp2->get();
}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming enter.
  io.run();

  if (millis() > (lastUpdate + IO_LOOP_DELAY)) {
    state = s1 + s2;

    // save count to the 'enter' feed on Adafruit IO
    Serial.print("sending -> ");
    Serial.println(count);
    enter->save(count);

    // after publishing, store the current time
    lastUpdate = millis();
  }
  while (Serial2.available()) {
    count = Serial2.read();
    Serial2.write(state);
  }
}

// this function is called whenever a 'enter' message
// is received from Adafruit IO. it was attached to
// the enter feed in the setup() function above.

void handleData(AdafruitIO_Data *enter) {

}

void handleP1(AdafruitIO_Data *data) {

  if (data -> isTrue()) {
    s1 = 1;
    Serial.println("P1 = HIGH");
  }
  else {
    Serial.println("P1 = LOW");
    s1 = 0;
  }
}

void handleP2(AdafruitIO_Data *data) {

  if (data -> isTrue()) {
    Serial.println("P2 = HIGH");
    s2 = 2;
  }
  else {
    Serial.println("P2 = LOW");
    s2 = 0;
  }
}
