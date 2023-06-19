# STM32F4-Accel-Temperature 

Read this in other languages: [English](README.md), [Russian/Русский](README.ru.md). 

`STM32F4-Accel-Temperature` is a project that allows you to determine the position of an object in *three-dimensional space* with the transfer of data from MCU to a computer.
Data from *accelerometer* to *microcontroller* is transmitted via **I2C** interface, and from *microcontroller* to *computer* via **USART** interface.

The application allows to measure *relative accelerations* of an object using an accelerometer **ADXL345** and *temperature* using embedded temperature sensor. 

The application is written in `C++` for microcontroller **STM32F411RE**. 

[Click here](Docs/Design.md) to read about design of this application. 

## How to use 

### Prerequisites

- Windows OS; 
- IAR Embedded Workbench 8.40.2; 
- Microcontroller *STM32F411RE*;
- Accelerometer *ADXL345*; 
- Any text editor (*VS Code*, *Sublime Text*, *Notepad++* etc). 

Dependencies for `Simulation3d`: 
- System.IO.Ports (Version 4.4.0). 

### C++ FreeRTOS wrapper 

In order to perform both parallel measurements using the microcontroller, [C++ FreeRTOS wrapper](https://github.com/lamer0k/RtosWrapper) is used. 

### COM-port configuration

**COM-port configuration** (parity, number of stop bits, number of data bits, baud rate) is made in the code itself depending on technical requirements.
Click [here](Docs/DataTransmission.md) to read full information on how to configure data transmission in this application. 

### How to download this repository and edit code 

In order to download this repository, just type into console the following command: 
```
git clone https://github.com/alexeysp11/STM32F4-Accel-Temperature
```

Then just open main directory using any text editor (you can also use JetBrains Clion or IAR 8.40.2), and just edit code. 
If you want to use IAR 8.40.2, open the `test.eww` workspace or `iarproject.ewp` project.
