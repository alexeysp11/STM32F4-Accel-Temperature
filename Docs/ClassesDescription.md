# Architecture 

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

### Packet "Peripheral"

#### AccelDriver

![AccelDriver](img/UML/ClassDesriptions/AccelDriver.png)

#### UartDriver

![UartDriver](img/UML/ClassDesriptions/UartDriver.png)

### Packet "CPU"

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
