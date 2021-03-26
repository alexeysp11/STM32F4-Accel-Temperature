using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Simulation3d
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        #region Members
        
        private CircuitBoard _CurcuitBoard = null; 
        private ComPort _ComPort = null; 
        
        #endregion  // Members


        #region Properties

        private bool Is3dModel = false; 

        #endregion  // Properties


        #region Constructors

        public MainWindow()
        {
            InitializeComponent();

            _CurcuitBoard = new CircuitBoard();
            _ComPort = new ComPort(InfoLabel);

            ArrowAccel.Visibility = Visibility.Collapsed;

            Loaded += (o, e) => {
                Is3dModel = false;
                Model2d.Visibility = Visibility.Visible;
                Viewport3d.Visibility = Visibility.Collapsed;
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
            // Not to copy one COM port multiple times. 
            ComPortsComboBox.Items.Clear();

            // `ComPort.Ports` is hte array of COM ports. 
            string[] arrayOfPorts = ComPort.Ports;

            // Create new instances of COM ports. 
            for (int i = 0; i < arrayOfPorts.Length; i++)
            {
                ComPortsComboBox.Items.Add(arrayOfPorts[i]); 
            }
        }

        /// <summary>
        /// Connects or disconnects selected COM-port and changes content of 
        /// a button that was pressed (from `Connect` to `Dosconnect` and 
        /// vica versa). 
        /// </summary>
        private void ConnectDisconnectBtn_Click(object sender, RoutedEventArgs e)
        {
            if (_ComPort.IsConnected)
            {
                try
                {
                    _ComPort.Close();
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
                    ConnectDisconnectBtn.Content = "Close"; 
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
            if (e.Key == Key.E)
            {
                ArrowAccel.Visibility = Visibility.Collapsed;
                RectangleRotation.Angle += 5; 
                ArrowAccelRotation.Angle += 5; 
            }
            else if (e.Key == Key.Q)
            {
                ArrowAccel.Visibility = Visibility.Collapsed;
                RectangleRotation.Angle -= 5; 
                ArrowAccelRotation.Angle -= 5; 
            }
            else if (e.Key == Key.A)    // Left. 
            {
                ArrowAccel.Visibility = Visibility.Visible;
                ArrowAccelRotation.Angle = 180; 
                
                // Place an arrow to the center of `Model2d`.
                Canvas.SetTop(ArrowAccel, (Canvas.GetTop(Model2d) + Model2d.Height / 2) );
                Canvas.SetLeft(ArrowAccel, (Canvas.GetLeft(Model2d) + Model2d.Width / 2) );
            }
            else if (e.Key == Key.D)    // Right. 
            {
                ArrowAccel.Visibility = Visibility.Visible;
                ArrowAccelRotation.Angle = 0; 
                
                // Place an arrow to the center of `Model2d`.
                Canvas.SetTop(ArrowAccel, (Canvas.GetTop(Model2d) + Model2d.Height / 2) );
                Canvas.SetLeft(ArrowAccel, (Canvas.GetLeft(Model2d) + Model2d.Width / 2) );
            }
            else if (e.Key == Key.W)    // Up. 
            {
                ArrowAccel.Visibility = Visibility.Visible;
                ArrowAccelRotation.Angle = -90; 
                
                // Place an arrow to the center of `Model2d`.
                Canvas.SetTop(ArrowAccel, (Canvas.GetTop(Model2d) + Model2d.Height / 2) );
                Canvas.SetLeft(ArrowAccel, (Canvas.GetLeft(Model2d) + Model2d.Width / 2) );
            }
            else if (e.Key == Key.S)    // Down. 
            {
                ArrowAccel.Visibility = Visibility.Visible;
                ArrowAccelRotation.Angle = 90; 
                
                // Place an arrow to the center of `Model2d`.
                Canvas.SetTop(ArrowAccel, (Canvas.GetTop(Model2d) + Model2d.Height / 2) );
                Canvas.SetLeft(ArrowAccel, (Canvas.GetLeft(Model2d) + Model2d.Width / 2) );
            }
            else if (e.Key == Key.D2)
            {
                Is3dModel = false; 
                Model2d.Visibility = Visibility.Visible;
                Viewport3d.Visibility = Visibility.Collapsed;
            }
            else if (e.Key == Key.D3)
            {
                Is3dModel = true; 
                Model2d.Visibility = Visibility.Collapsed;
                Viewport3d.Visibility = Visibility.Visible;
            }

            myCanvas.Focus();
        }

        #endregion  // Keyboard handling
    }
}
