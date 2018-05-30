# PX4Flow library for Arduino

A small library wrapping the Wire I2C calls to a [PX4Flow](http://pixhawk.org/modules/px4flow) Optical Flow Tracker.

## Requirements

The PX4Flow firmware keeps on evolving and sometimes introduce backward incompatible changes. If you have purchased a PX4Flow module online, make sure to first install the latest firmware.

This library has last been tested on August 18th with the PX4Flow firmware built from the master, at the following
commit: https://github.com/PX4/Flow/commit/5f014d3576793c5c32c04dbad8c7ebb284aba24c

## Usage

* Clone this repository on your local system
* Add the arduino-px4flow-i2c folder in your arduino libraries (Sketch -> Import Library -> Add Library)
* Start using it by including "PX4Flow.h" in your project

## Example

This example is also available in 'examples/basic/basic.ino'.

```
#include <Wire.h>
#include "PX4Flow.h"

PX4Flow sensor = PX4Flow(); 

void setup()
{
  Wire.begin();       
  Serial.begin(115200);  
}

void loop()
{
  sensor.update();
  
  Serial.print("#");
  Serial.print(sensor.vx());Serial.print(",");
  Serial.print(sensor.vy());Serial.print(",");
  Serial.println(sensor.altitude());

  delay(100);
}
```
## Support

You can always open an issue on Github and I'll try to follow up. If your issue is related to the PX4Flow hardware, then best is to ask in the user [forum](https://groups.google.com/forum/#!forum/px4users) on Google Groups.

## License

The MIT License

Copyright (c) 2014 by Laurent Eschenauer <laurent@eschenauer.be>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
