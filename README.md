# Posturainer
## Badges
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
## Authors
- [Sameep Pote](https://github.com/Sameep2808) - Graduate student at University of Maryland pursuing M.Eng. Robotics.Loves to watch animes.

## License
```
MIT License

Copyright (c) 2018 Sameep Pote

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

## Overview

## Objective 
- An innovative way to tackle the increasing problem of improper postures.
- To condition the muscles eventually leading to a habit of proper posture.
- Detailed analysis and performance report. To ensure healthy sitting habits and a backache-free 
society.

## Working
![g1](https://github.com/Sameep2808/Posturainer/blob/main/Video/ezgif.com-gif-maker.gif)
- The FRDM-K64F consists of an inbuilt Accelerometer and Gyroscope that is used to measure both initial reference and the corresponding changes when in use.
- When Posturainer is in calibration mode, the reference values are recorded by the FRDM-controller.
- Whenever there is a change in the posture beyond a certain level, the device starts vibrating. These warnings can also be controlled over time and frequency. They can also be programmed in a smart sense so as to notify the direction of slouching as well. A simple 5V battery source is used for the same.
- RESET button and multi-colour LEDs are also used for indications and user assistance.

## Issues Faced
- Main issue faced while implementation was Multiple Serial Communication at the same time. As we were using Accelerometer and Bluetooth module at the same time and both uses TX and RX for serial communication the signals sent by the sensors were getting interfered by each other
- It was resolved by changing the type of communication. The accelerometer used SDA pin to send data to the processor while the Bluetooth module continued using TX and RX for Serial Communication



