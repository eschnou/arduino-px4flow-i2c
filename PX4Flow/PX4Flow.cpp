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

#include <Arduino.h>
#include <Wire.h>
#include "PX4Flow.h":

PX4Flow::PX4Flow()
{
    //TODO Enable to setup a different address when initializing
}

void PX4Flow::update()
{
  //send 0x0 to PX4FLOW module and receive back 22 Bytes data 
  Wire.beginTransmission(PX4FLOW_ADDRESS);
  Wire.write(0x0);  
  Wire.endTransmission();  
  
  // request 22 bytes from the module
  Wire.requestFrom(PX4FLOW_ADDRESS, 22);    

  // wait for all data to be available
  // TODO we could manage a timeout in order not to block
  // the loop when no component is connected
  while(Wire.available() < 22);
  
  data.frame_count       = read16();
  data.pixel_flow_x_sum  = read16();
  data.pixel_flow_y_sum  = read16();
  data.flow_comp_m_x     = read16();
  data.flow_comp_m_y     = read16();
  data.qual              = read16();
  data.gyro_x_rate       = read16();
  data.gyro_y_rate       = read16();
  data.gyro_z_rate       = read16();
  data.gyro_range        = read8();
  data.sonar_timestamp   = read8();
  data.ground_distance   = read16();
  
  // if too many bytes are available, we drain in order to be synched
  // on next read
  if(Wire.available()) {
    #if PX4FLOW_DEBUG == true
    {
      Serial.println("ERROR [PX4Flow] : Too many bytes available.");
    }
    #endif
    while(Wire.available()) {Wire.read();}
  }
}

uint16_t PX4Flow::frame_count() {
  return data.frame_count;
}

int16_t PX4Flow::altitude() {
  return data.ground_distance;
}

int16_t PX4Flow::vx() {
  return data.flow_comp_m_x;
}
int16_t PX4Flow::vy() {
  return data.flow_comp_m_y;
}
int16_t PX4Flow::quality() {
  return data.qual;
}

uint16_t PX4Flow::read16() {
  return Wire.read() + (uint16_t) (Wire.read() << 8);
}

uint8_t PX4Flow::read8() {
  return Wire.read();
}
