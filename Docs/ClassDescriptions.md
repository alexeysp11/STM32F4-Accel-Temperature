# Class descriptions 

## Table of contents

1. [Measuring System](#measuringsystem)
1. [GUI](#gui)

## Measuring System <div id="measuringsystem"></div>

### Packet "Application"

#### MeasureTask

![MeasureTask](img/UML/ClassDesriptions/MeasureTask.png)

#### SendTask 

![SendTask](img/UML/ClassDesriptions/SendTask.png)

### Packet "Measurement"

#### Acceleration 

![Acceleration](img/UML/ClassDesriptions/Acceleration.png)

#### Temperature 

![ClassDescriptionTemperature](img/UML/ClassDesriptions/Temperature.png)

### Packet "Filter" 

#### Filter

![Filter](img/UML/ClassDesriptions/Filter.png)

### Packet "Transmission"

#### TransmissionManager

![TransmissionManager](img/UML/ClassDesriptions/TransmissionManager.png)

### Packet "Peripherals"

#### TempSensor

![TempSensor](img/UML/ClassDesriptions/TempSensor.png)

#### AccelDriver

![AccelDriver](img/UML/ClassDesriptions/AccelDriver.png)

#### AdcDriver

![AdcDriver](img/UML/ClassDesriptions/AdcDriver.png)

#### I2CDriver

![I2CDriver](img/UML/ClassDesriptions/I2CDriver.png)

#### UartDriver

![UartDriver](img/UML/ClassDesriptions/UartDriver.png)

### Packet "CPU"

#### Adc 

![Adc](img/UML/ClassDesriptions/Adc.png)

#### I2C 

![I2C](img/UML/ClassDesriptions/I2C.png)

#### Uart 

![Uart](img/UML/ClassDesriptions/Uart.png)

## GUI <div id="gui"></div>

### Общее описание

Подсистема графического интерфейса ответственна за считывания данных, переданных по последовательному порту, корректное отображение измеренных данных акселерометра и вращение трёхмерной модели. 

Соответственно, программа должна содержать следующие сущности: 
- главное окно; 
- трёхмерная модель объекта; 
- последовательный порт. 

<!--
Use Case-диаграмма для GUI представлена на рисунке ниже: 

![GuiUseCase](img/GuiUseCase.png)

Состояния графического интерфейса при коммуникации с пользователем следующие: 
1. Прорисовка графических элементов при загрузке приложения; 
1. 
-->

### MainWindow

### ComPort 

### CircuitBoard 

### Angle3dModel

### Acceleration3dModel

### Exceptions 
