# Stm32Project 

`Stm32Project` is a project that allows you to determine the position of an object in *three-dimensional space* with the transfer of data from MCU to a computer.

![RotationOnGui](Docs/img/Usage/RotationOnGui.png)

This application allows you to rotate a *3D model* on the screen, rotating a *real object* on which an *accelerometer* is attached. 
Getting relative acceleration of an object, you can calculate its rotation as shown on the figure below. 

Data from *accelerometer* to *microcontroller* is transmitted via **I2C** interface, and from *microcontroller* to *computer* via **USART** interface.

The application is divided into two parts:
- `MeasuringSystem`: measurements  of *relative accelerations* of an object using an accelerometer **ADXL345** and *temperature* using embedded temperature sensor (this part is written in `C++` for microcontroller **STM32F411RE**);
- `Simulation3d`: visual representation of the received data and rotation of an object (written in `C#` using **WPF**). 

Click [here](Docs/Design.md) to read about design of this application. 

## How to use 

### Prerequisites

- Windows OS; 
- .NET Core 3.1; 
- IAR Embedded Workbench 8.40.2; 
- Microcontroller *STM32F411RE*;
- Accelerometer *ADXL345*; 
- Any text editor (*VS Code*, *Sublime Text*, *Notepad++* etc) or Visual Studio; 
- Windows command line (if you do not use Visual Studio). 

Dependencies for `Simulation3d`: 
- System.IO.Ports (Version 4.4.0). 

### C++ FreeRTOS wrapper 

In order to perform both parallel measurements using two sensors (accelerometer and embedded temperature sensor) and sending all measured data via **USART**, FreeRTOS wrapper written in `C++` is used. 

Code from [this repository]() was used as an example of the wrapper. 

[Here](MeasuringSystem/README.adoc) you can read desciption on how the FreeRTOS wrapper is used in this particular application. 

### COM-port configuration

For the program to work correctly, it is critical to **set a delay** for *data transmission* from the microcontroller to the computer so that `Simulation3d` does not hang.
Because when there is a constant stream of data, at best, `Simulation3d` stops responding to anything, but most often it just crashes with an **APPCRASH** exception.

**COM-port configuration** (parity, number of stop bits, number of data bits, baud rate) is made in the code itself depending on technical requirements.
Click [here](Docs/DataTransmission.md) to read full information on how to configure data transmission in this application. 

### How to download this repository and edit code 

In order to download this repository, just type into console the following command: 
```
git clone https://github.com/alexeysp11/Stm32Project
```

Then just open main directory using any text editor and just edit code. 

<!--
In order to open `Simulation3d` application with Visual Studio, just open `Simulation3d.sln` solution. 
-->

If you want to edit code for `MeasuringSystem`, just open the *MeasuringSystem* directory in the JetBrains Clion. 
Or if you use IAR 8.40.2, open the `test.eww` workspace or `iarproject.ewp` project.

### How to run 

If you are not using Visual Studio, you can run `Simulation3d` using *Windows command line*. 
So just write the following command into console: 
```
simulate.cmd
```

In order to run `Simulation3d` without building, write: 
```
simulate.cmd --no-build
```
