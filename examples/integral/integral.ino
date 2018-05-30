/*
 * Copyright (c) 2014 by Laurent Eschenauer <laurent@eschenauer.be>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 */

#include <Wire.h>
#include "PX4Flow.h"

#define PARAM_FOCAL_LENGTH_MM 16

// Pin 13 has an LED connected on most Arduino boards.
// Pin 11 has the LED on Teensy 2.0
// Pin 6  has the LED on Teensy++ 2.0
// Pin 13 has the LED on Teensy 3.0
// give it a name:
#define LED 13

long last_check = 0;
int px = 0;
int py = 0;
float focal_length_px = (PARAM_FOCAL_LENGTH_MM) / (4.0f * 6.0f) * 1000.0f;
  
// Initialize PX4Flow library
PX4Flow sensor = PX4Flow(); 

void setup()
{
  // Initialize the digital pin as an output.
  pinMode(LED, OUTPUT);   
  
  // Initialize the I2C bus
  Wire.begin();       
  
  // Initialize the serial connection
  Serial.begin(115200);  
}

void loop()
{
  long loop_start = millis();
    
  if (loop_start - last_check > 10) {
    // Fetch I2C data  
    sensor.update_integral();
    int x_rate = sensor.gyro_x_rate_integral();       // 10 * mrad
    int y_rate = sensor.gyro_y_rate_integral();       // 10 * mrad
    int flow_x = sensor.pixel_flow_x_integral();      // 10 * mrad
    int flow_y = sensor.pixel_flow_y_integral();      // 10 * mrad  
    int timespan = sensor.integration_timespan(); // microseconds
    int ground_distance = sensor.ground_distance_integral(); // mm
    int quality = sensor.quality_integral();
    
    Serial.print(millis());Serial.print("\t");  
    Serial.print(quality);Serial.print("\t");    
    Serial.print(x_rate);Serial.print("\t");
    Serial.print(y_rate);Serial.print("\t");  
    Serial.print(flow_x);Serial.print("\t");
    Serial.print(flow_y);Serial.print("\t"); 
    Serial.println(ground_distance);
    
    last_check = loop_start;
  }
}
