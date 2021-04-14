using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace Simulation3d
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        #region Members
        /// <summary>
        /// Instance that stores all values measured by MCU. 
        /// </summary>
        private CircuitBoard _CurcuitBoard = null; 
        /// <summary>
        /// Instance that implements serial port. 
        /// </summary>
        private ComPort _ComPort = null; 
        /// <summary>
        /// This timer is used for updating labels for displaying rotation
        /// angle, acceleration and temperature in the current moment. 
        /// </summary>
        private System.Windows.Threading.DispatcherTimer updateLabelsTimer = null; 
        /// <summary>
        /// This timer is used to timely clear InfoLabel (notification label). 
        /// </summary>
        private System.Windows.Threading.DispatcherTimer clearInfoLabelTimer = null; 
        /// <summary>
        /// Structure for storing values of rotation angle (X, Y and Z). 
        /// </summary>
        private Angle angle;
        /// <summary>
        /// Structure for storing values of relative accelerations (X, Y and Z). 
        /// </summary>
        private Acceleration accel;
        #endregion  // Members

        #region Properties
        /// <summary>
        /// Measured temperature. 
        /// </summary>
        private float temperature;
        /// <summary>
        /// Allows to handle if it's simulation mode or measuring mode. 
        /// </summary>
        private bool IsSimalation = true; 
        /// <summary>
        /// Variable that stores name of connected COM-port for preventing 
        /// change of COM-port while it's connected. 
        /// </summary>
        private string ComPortText = null; 
        #endregion  // Properties

        #region Constructors
        public MainWindow()
        {
            InitializeComponent();

            _CurcuitBoard = new CircuitBoard();
            _ComPort = new ComPort(InfoLabel, ref _CurcuitBoard);

            // updateLabelsTimer starts when window is loaded and updates 
            // every 100 ms. 
            updateLabelsTimer = new System.Windows.Threading.DispatcherTimer();
            updateLabelsTimer.Tick += (sender, args) => {
                // Adjust acceleration because acceleration cannot be the same
                // if the state of a real life object does not change.
                _CurcuitBoard.AdjustAcceleration();
                
                // Get acceleration, rotation angle and temperature. 
                this.accel = _CurcuitBoard.GetAcceleration();
                this.angle = _CurcuitBoard.GetRotation();
                this.temperature = _CurcuitBoard.GetTemperature(); 

                // Rotate 3D model. 
                Model3dRotateAngleX.Angle = this.angle.X;
                Model3dRotateAngleY.Angle = this.angle.Y;
                Model3dRotateAngleZ.Angle = this.angle.Z;

                // Display rotation angle. 
                AngleX.Content = $"{angle.X}"; 
                AngleY.Content = $"{angle.Y}"; 
                AngleZ.Content = $"{angle.Z}";
                
                // Display acceleration. 
                AccelX.Content = $"{accel.X}"; 
                AccelY.Content = $"{accel.Y}"; 
                AccelZ.Content = $"{accel.Z}";
                
                // Display temperature. 
                TemperatureLabel.Content = $"{temperature}"; 
            }; 
            updateLabelsTimer.Interval = TimeSpan.FromSeconds(0.1);

            // Clear InfoLabel after 5 seconds when user clicked on Connect
            // or Disconnect, then it stops. 
            clearInfoLabelTimer = new System.Windows.Threading.DispatcherTimer();
            clearInfoLabelTimer.Tick += (sender, args) => {
                InfoLabel.Content = ""; 
                clearInfoLabelTimer.Stop();
            };
            clearInfoLabelTimer.Interval = TimeSpan.FromSeconds(3);

            Loaded += (sender, args) => {
                updateLabelsTimer.Start();  // Start updating notifications. 
            };

            myCanvas.Focus();
        }
        #endregion  // Constructors

        #region UI buttons handling
        /// <summary>
        /// If Refresh button was pressed, get all available COM-ports.  
        /// </summary>
        private void RefreshBtn_Click(object sender, RoutedEventArgs e)
        {
            if (this.IsSimalation)  // Do nothing if it's a simualtion mode. 
            {
                System.Windows.MessageBox.Show("Unable to refresh COM-ports in simulation mode.");
                return; 
            }

            // Refresh only when COM-port is not connected. 
            if (!_ComPort.IsConnected)
            {
                // Not to copy one COM port multiple times. 
                ComPortsComboBox.Items.Clear();

                // `ComPort.Ports` is the array of COM ports. 
                string[] arrayOfPorts = ComPort.Ports;

                // Create new instances of COM ports. 
                for (int i = 0; i < arrayOfPorts.Length; i++)
                {
                    ComPortsComboBox.Items.Add(arrayOfPorts[i]); 
                }
            }
            else
            {
                System.Windows.MessageBox.Show("COM-port is already connected!");
            }
        }

        /// <summary>
        /// Disable DropDown when COM-port is already selected, and enable 
        /// DropDown when COM-port is not selected. 
        /// </summary>
        private void ComPortsComboBox_DropDownOpened(object sender, EventArgs e)
        {
            ComboBox cb = sender as ComboBox;

            if (this.ComPortText == null)
            {
                cb.IsDropDownOpen = true;
            }
            else
            {
                cb.IsDropDownOpen = false;
            }
        }

        /// <summary>
        /// Connects or disconnects selected COM-port and changes content of 
        /// a button that was pressed (from `Connect` to `Disconnect` and 
        /// vica versa). 
        /// </summary>
        /// <exception cref="System.Exception">
        /// Thrown when an instance of `ComPort` class is not created. 
        /// </exception>
        private void ConnectDisconnectBtn_Click(object sender, RoutedEventArgs e)
        {
            if (this.IsSimalation)  // Do nothing if it's a simulation mode. 
            {
                System.Windows.MessageBox.Show("Unable to connect COM-ports in simulation mode.");
                return; 
            }

            clearInfoLabelTimer.Start();    // Start timer for updating labels. 

            if (_ComPort.IsConnected)
            {
                try
                {
                    _ComPort.Close();
                    this.ComPortText = null; 
                    ConnectDisconnectBtn.Content = "Connect"; 
                }
                catch (System.Exception ex)
                {
                    GraphWPF.Exceptions.DisplayException(ex); 
                }
            }
            else
            {
                try
                {
                    _ComPort.Config(ComPortsComboBox.Text);
                    _ComPort.Open();
                    this.ComPortText = ComPortsComboBox.Text; 

                    // Change label only if COM-port is connected. 
                    if (_ComPort.IsConnected)
                    {
                        ConnectDisconnectBtn.Content = "Close"; 
                    }
                }
                catch (System.Exception ex)
                {
                    GraphWPF.Exceptions.DisplayException(ex); 
                }
            }
        }
        #endregion  // UI buttons handling

        #region Keyboard handling
        /// <summary>
        /// If user pressed some key. 
        /// </summary>
        private void KeyUp_Handling(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.M)         // Change mode (from simulation to measuring and vica versa). 
            {
                if (_ComPort.IsConnected)
                {
                    System.Console.WriteLine("Unable to change mode while COM-port is connected.");
                    return;
                }
                else
                {
                    this.IsSimalation = !this.IsSimalation;
                }
            }

            if (this.IsSimalation)
            {
                ModeLabel.Content = "MODE: simulation"; 
            }
            else
            {
                ModeLabel.Content = "MODE: measurement"; 
                return; 
            }

            if (e.Key == Key.E)         // Rotation around X axis.
            {
                _CurcuitBoard.SetRotation(5, 0, 0); 
                this.angle = _CurcuitBoard.GetRotation(); 
                Model3dRotateAngleX.Angle = this.angle.X; 
            }
            else if (e.Key == Key.Q)    // Rotation around X axis.
            {
                _CurcuitBoard.SetRotation(-5, 0, 0); 
                this.angle = _CurcuitBoard.GetRotation(); 
                Model3dRotateAngleX.Angle = this.angle.X; 
            }
            else if (e.Key == Key.R)    // Rotation around Y axis.
            {
                _CurcuitBoard.SetRotation(0, 5, 0); 
                this.angle = _CurcuitBoard.GetRotation(); 
                Model3dRotateAngleY.Angle = this.angle.Y; 
            }
            else if (e.Key == Key.F)    // Rotation around Y axis.
            {
                _CurcuitBoard.SetRotation(0, -5, 0); 
                this.angle = _CurcuitBoard.GetRotation(); 
                Model3dRotateAngleY.Angle = this.angle.Y; 
            }
            else if (e.Key == Key.X)    // Rotation around Z axis.
            {
                _CurcuitBoard.SetRotation(0, 0, 5); 
                this.angle = _CurcuitBoard.GetRotation(); 
                Model3dRotateAngleZ.Angle = this.angle.Z; 
            }
            else if (e.Key == Key.Z)    // Rotation around Z axis.
            {
                _CurcuitBoard.SetRotation(0, 0, -5); 
                this.angle = _CurcuitBoard.GetRotation(); 
                Model3dRotateAngleZ.Angle = this.angle.Z; 
            }
            else if (e.Key == Key.A)    // Left (acceleration). 
            {
                _CurcuitBoard.SetAcceleration(-5, 0, 0);
                this.accel = _CurcuitBoard.GetAcceleration();
            }
            else if (e.Key == Key.D)    // Right (acceleration). 
            {
                _CurcuitBoard.SetAcceleration(5, 0, 0);
                this.accel = _CurcuitBoard.GetAcceleration();
            }
            else if (e.Key == Key.W)    // Up (acceleration). 
            {
                _CurcuitBoard.SetAcceleration(0, 5, 0);
                this.accel = _CurcuitBoard.GetAcceleration();
            }
            else if (e.Key == Key.S)    // Down (acceleration). 
            {
                _CurcuitBoard.SetAcceleration(0, -5, 0);
                this.accel = _CurcuitBoard.GetAcceleration();
            }
            else if (e.Key == Key.C)    // Up (acceleration). 
            {
                _CurcuitBoard.SetAcceleration(0, 0, 5);
                this.accel = _CurcuitBoard.GetAcceleration();
            }
            else if (e.Key == Key.V)    // Down (acceleration). 
            {
                _CurcuitBoard.SetAcceleration(0, 0, -5);
                this.accel = _CurcuitBoard.GetAcceleration();
            }

            myCanvas.Focus();
        }
        #endregion  // Keyboard handling
    }
}
