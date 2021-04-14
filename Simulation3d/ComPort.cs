using System;
using System.Windows.Controls; 
using System.Windows.Media; 
using System.Windows.Documents; 
using System.IO.Ports;

namespace Simulation3d
{
    /// <summary>
    /// Implements COM-port. 
    /// </summary>
    class ComPort
    {
        #region Members
        /// <summary>
        /// An instance of `SerialPort` class. 
        /// </summary>
        protected SerialPort comPort = null;    
        /// <summary>
        /// An instance of `Label` to display message. 
        /// </summary>
        protected Label _InfoLabel = null; 
        /// <summary>
        /// Represents the System.Object type, which is the root type in the C# class hierarchy. 
        /// Used when there's no way to identify the object type at compile time. 
        /// </summary>
        private object Obj;
        /// <summary>
        /// An instance of CircuitBoard that helps to change its state directly 
        /// from this class. 
        /// </summary>
        private CircuitBoard _CurcuitBoard = null; 
        #endregion  // Members

        #region Properties
        /// <summary>
        /// Public static field of string elements that represent COM-port. 
        /// </summary>
        public static string[] Ports { get { return SerialPort.GetPortNames(); } }
        /// <summary>
        /// Stores boolean value that represents if COM-port is connected or not. 
        /// </summary>
        public bool IsConnected { get; private set; }
        /// <summary>
        /// Size of a packet for getting one floating point value via 
        /// data transmission. 
        /// </summary>
        private static int PacketSize = 6; 
        #endregion  // Properties

        #region Constructors
        /// <summary>
        /// Constructor of class `ComPort` that creates an object of 
        /// `SerialPort` class. 
        /// </summary>
        /// <param name="InfoLabel">
        /// Notification label where to display messages.
        /// </param>
        /// <param name="board">
        /// Instance of CircuitBoard (passed by reference).
        /// </param>
        public ComPort(Label InfoLabel, ref CircuitBoard board)
        {
            // Assign `comPort` as an object of `SerialPort` class. 
            comPort = new SerialPort();
            _CurcuitBoard = board;

            // Assign `Label` element. 
            _InfoLabel = InfoLabel;

            /* Event `System.IO.Ports.SerialPort.DataReceived` indicates
            that data has been received through a port represented 
            by the SerialPort object. 
            Delegate `SerialDataReceivedEventHandler` represents the method 
            that will handle the DataReceived event of a SerialPort object. */
            comPort.DataReceived += new SerialDataReceivedEventHandler(DataReceived);
            
            /* Assign `Obj` as object of class `System.Object` for using it in `lock`
            statements. */
            Obj = new object();

            IsConnected = false; 
        }
        #endregion  // Constructors

        #region Port configuration
        /// <summary>
        /// COM port configuration. 
        /// </summary>
        /// <param name="portName">Name of the COM port.</param>
        /// <param name="baudRate">Baud rate.</param>
        /// <param name="parity">Parity selection.</param>
        /// <param name="stopBits">Number of stop bits.</param>
        /// <exception cref="System.Exception">
        /// Thrown when unable to convert passed parameters in order to 
        /// configure COM port. 
        /// </exception>
        public void Config(string portName, string baudRate="19200", 
            string parity="None", string stopBits="1")
        {
            /* Get a value indicating the open or closed status of the 
            SerialPort object. 
            Close serial port if it is open at the initial time. */
            if (comPort.IsOpen == true) 
            {
                this.Close(); 
            }

            try
            {
                comPort.PortName = portName;
                comPort.BaudRate = Int32.Parse(baudRate);
                comPort.Parity = (Parity)Enum.Parse(typeof(Parity), parity);
                comPort.StopBits = (StopBits)Enum.Parse(typeof(StopBits), stopBits);
                comPort.DataBits = 8;
            }
            catch (System.Exception ex)
            {
                GraphWPF.Exceptions.DisplayException(ex);
            }
        }

        /// <summary>
        /// This method is invoked by `Send()` in order to open serial port. 
        /// </summary>
        /// <exception cref="System.UnauthorizedAccessException">
        /// Thrown when the operating system denies access because of an 
        /// I/O error or a specific type of security error. 
        /// </exception>
        /// <exception cref="System.Exception">
        /// Thrown when something went wrong in `ComPort.DisplayData()` method. 
        /// </exception>
        public bool Open()
        {
            try
            {
                comPort.Open();
                this.DisplayData(Brushes.Black, "Port " + comPort.PortName + " is opened at " + DateTime.Now);
                IsConnected = true; 

                return true;
            }
            catch (System.UnauthorizedAccessException)
            {
                // Close the serial port. 
                comPort.Close();
                this.DisplayData(Brushes.Black, "Port " + comPort.PortName + " is closed at " + DateTime.Now);
                
                // Try to open the serial port again. 
                comPort.Open();
                this.DisplayData(Brushes.Black, "Port " + comPort.PortName + " is opened at " + DateTime.Now);
                IsConnected = true; 
                
                return true;
            }
            catch (System.Exception ex)
            {
                //System.Windows.MessageBox.Show("ERROR: " + ex.Message + "\n" + ex.GetType().ToString());
                GraphWPF.Exceptions.DisplayException(ex);
                return false;
            }
        }

        /// <summary>
        /// This method is invoked by `ComPort.Config` method in order 
        /// to close serial port. 
        /// </summary>
        /// <returns>
        /// true if serial port has been closed, false if serial port has not 
        /// been closed. 
        /// </returns>
        /// <exception cref="System.Exception">
        /// Thrown when .
        /// </exception>
        public bool Close()
        {
            try
            {
                comPort.Close();
                this.DisplayData(Brushes.Black, "Port " + comPort.PortName + " is closed at " + DateTime.Now);
                IsConnected = false;

                return true;
            }
            catch (System.Exception ex)
            {
                GraphWPF.Exceptions.DisplayException(ex);
                return false;
            }
        }
        #endregion  // Port configuration

        #region DataTransmission 
        /// <summary>
        /// Sends a message via COM-port. 
        /// </summary>
        /// <param name="msg">Message to be sent via serial port.</param>
        /// <exception cref="System.Exception">
        /// Thrown when .
        /// </exception>
        public void Send(string msg)
        {
            if (comPort.IsOpen == false)
            {
                this.Open();
            }
            
            try
            {
                lock (Obj)
                {
                    byte[] newMsg = HexToByte(msg);
                    comPort.Write(newMsg, 0, newMsg.Length);
                    this.DisplayData(Brushes.Blue, ByteToHex(newMsg));
                }
            }
            catch (Exception ex)
            {
                GraphWPF.Exceptions.DisplayException(ex);
            }
        }

        /// <summary>
        /// This method is called when event `System.IO.Ports.SerialPort.DataReceived` 
        /// indicated that data has been received through a port represented
        /// by the `SerialPort` object. 
        /// </summary>
        /// <exception cref="System.Exception">
        /// Thrown when the calling thread cannot access the object because a different 
        /// thread owns it.
        /// </exception>
        private void DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                /* This piece of code do not allows other threads to use COM-port 
                until you finish to receive data completely. */
                lock (Obj)
                {
                    byte[] comBuffer = new byte[24];
                    comPort.Read(comBuffer, 0, comBuffer.Length);

                    // Unpack receiced message. 
                    this.DecodeMeasuredData(comBuffer); 
                }
            }
            catch (System.Exception ex)
            {
                GraphWPF.Exceptions.DisplayException(ex); 
            }
        }
        #endregion  // DataTransmission

        #region DataProcessing
        /// <summary>
        /// Converts hex to byte. 
        /// </summary>
        /// <param name="msg">Message to be converted into bytes.</param>
        /// <returns>Array of bytes.</returns>
        public byte[] HexToByte(string msg)
        {
            msg = msg.Replace(" ", "");
            byte[] comBuffer = new byte[msg.Length / 2];
            
            for (int i = 0; i < msg.Length / 2; i++)
            {
                comBuffer[i] = Convert.ToByte(msg.Substring(i * 2, 2), 16);
            }
            
            return comBuffer;
        }

        /// <summary>
        /// Converts byte to hex. 
        /// </summary>
        /// <param name="comByte">Array of bytes.</param>
        /// <returns>String of HEX.</returns>
        public string ByteToHex(byte[] comByte)
        {
            var builder = new System.Text.StringBuilder(comByte.Length * 3);
           
            foreach (byte data in comByte)
            {
                builder.Append(Convert.ToString(data, 16).PadLeft(2, '0').
                    PadRight(3, ' '));
            }
            
            return builder.ToString().ToUpper();
        }

        /// <summary>
        /// Decodes measured data such as temperature and relative 
        /// accelerations. 
        /// </summary>
        /// <remarks>
        /// When you decode a message, just set these parameters into 
        /// Angle and Acceleration structures. 
        /// </remarks>
        /// <param name="comByte">Array of bytes.</param>
        private void DecodeMeasuredData(byte[] comByte)
        {
            // Bytes for sensor decoding (see dtregisters.h). 
            byte TempSensor     = 0b00000000 | 0b00000100; 
            byte AccelerometerX = 0b10000000 | 0b00100000; 
            byte AccelerometerY = 0b10000000 | 0b00010000; 
            byte AccelerometerZ = 0b10000000 | 0b00001000; 

            string message = ""; 

            for (int i = 0; i < comByte.Length; i++)
            {
                /* Size of a packet is 6 bytes in the MeasuringSystem, 
                so sensor index is every 6th. */ 
                if (i % PacketSize == 0)     // Get what sensor sent data. 
                {
                    if (comByte[i] == TempSensor)
                    {
                        message += "Temperature: ";
                        float value = System.BitConverter.ToSingle(comByte, i+1);     // Get 4 bytes. 
                        _CurcuitBoard.SetTemperature(value);
                        message += $"{value}"; 
                        message += $"{comByte[i+5]}"; 
                    }
                    else if (comByte[i] == AccelerometerX)
                    {
                        message += "AccelX: ";
                        float value = System.BitConverter.ToSingle(comByte, i+1);     // Get 4 bytes. 
                        message += $"{value}"; 
                        message += $"{comByte[i+5]}"; 
                    }
                    else if (comByte[i] == AccelerometerY)
                    {
                        message += "AccelY: ";
                        float value = System.BitConverter.ToSingle(comByte, i+1);     // Get 4 bytes. 
                        message += $"{value}"; 
                        message += $"{comByte[i+5]}"; 
                    }
                    else if (comByte[i] == AccelerometerZ)
                    {
                        message += "AccelZ: ";
                        float value = System.BitConverter.ToSingle(comByte, i+1);     // Get 4 bytes. 
                        message += $"{value}"; 
                        message += $"{comByte[i+5]}"; 
                    }
                }
            }

            this.DisplayData(Brushes.Green, message);
        }
        #endregion  // DataProcessing

        #region Display 
        /// <summary> 
        /// This method is invoked by almost every method of this class
        /// in order to display some information into `FlowDocument`. 
        /// </summary>
        /// <param name="color">Foreground color for message.</param>
        /// <param name="msg">Message to be displayed.</param>
        protected void DisplayData(Brush color, string msg)
        {
            if (_InfoLabel != null)
            {
                _InfoLabel.Dispatcher.Invoke(() => {
                    // Change content of the label. 
                    _InfoLabel.Content = msg; 
                    _InfoLabel.Foreground = color; 
                });
            }
        }
        #endregion  // Display
    }
}
