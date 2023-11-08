# STM32F4-Accel-Temperature 

[English](README.md) | [Русский](README.ru.md)

`STM32F4-Accel-Temperature` is a project that involves interfacing an accelerometer and temperature sensor with a microcontroller, collecting data from the sensors, and transmitting it to a computer. The application written in C++ will facilitate the data transfer process.

## Overall description

This project allows you to determine the position of an object in *three-dimensional space* with the transfer of data from MCU to a computer.
Data from *accelerometer* to *microcontroller* is transmitted via **I2C** interface, and from *microcontroller* to *computer* via **USART** interface.

The application allows to measure *relative accelerations* of an object using an accelerometer **ADXL345** and *temperature* using embedded temperature sensor. 

The application is written in `C++` for microcontroller **STM32F411RE**. 

[Click here](Docs/Design.md) to read about design of this application. 

### Goal

The goal of the project is to develop a system that can determine the position of an object in three-dimensional space by collecting data from an accelerometer and transferring it to a computer.

### Scope

The scope of the project includes integrating an accelerometer (ADXL345) and temperature sensor with the microcontroller (STM32F411RE), and developing an application in C++ to collect and transfer data from the sensors to a computer.

### Who can use this library

This project can be used by engineers, researchers, or hobbyists who are interested in measuring relative accelerations and temperature of objects in three-dimensional space.

### Examples of similar projects 

Similar projects could include those that involve interfacing sensors with microcontrollers and transferring data to a computer, such as IoT projects or sensor data acquisition systems. Open-source examples may be available on platforms like GitHub. As for similar projects written in C#, they may include sensor data acquisition systems or IoT applications that involve data transfer from microcontrollers to computers.

### Possible limitations

Possible limitations of this project could include constraints on the accuracy and precision of the accelerometer and temperature sensor, limitations in the data transfer rate due to the interfaces used (I2C and USART), and potential challenges in calibrating and synchronizing the sensor data for accurate three-dimensional positioning. Additionally, limitations could arise from the processing power and memory constraints of the microcontroller.

## How to use 

### Prerequisites

- Windows OS; 
- IAR Embedded Workbench 8.40.2; 
- Microcontroller *STM32F411RE*;
- Accelerometer *ADXL345*; 
- Any text editor (*VS Code*, *Sublime Text*, *Notepad++* etc). 

### UI 

In order to visualize the measured data, you can use [Model3d-SerialPort-WPF](https://github.com/alexeysp11/Model3d-SerialPort-WPF) or [Thermometer-SerialPort-WPF](https://github.com/alexeysp11/Thermometer-SerialPort-WPF). 

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
