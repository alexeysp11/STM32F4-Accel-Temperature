namespace Simulation3d
{
    /// <summary>
    /// Structure for storing values of rotation angle. 
    /// </summary>
    public struct Angle
    {
        public float X; 
        public float Y; 
        public float Z; 
    }

    /// <summary>
    /// Structure for storing values of acceleration. 
    /// </summary>
    public struct Acceleration
    {
        public float X; 
        public float Y; 
        public float Z; 
    }

    /// <summary>
    /// Provides functionality for rotating 3D model and setting its 
    /// acceleration along each of 3 axis. 
    /// </summary>
    /// <remarks>
    /// Maybe it is necessary to use Singleton pattern to avoid creating 
    /// the object of `CircuitBoard` class multiple times because there is 
    /// only one cicuit board in this system. 
    /// </remarks>
    public class CircuitBoard 
    {
        #region Members
        private Angle _Angle; 
        private Acceleration _Accel; 
        #endregion  // Members

        #region Properties 
        private float Temperature = 0.0f; 
        #endregion  // Properties

        #region Constructor
        public CircuitBoard()
        {
            _Angle.X = 0.0f; 
            _Angle.Y = 0.0f; 
            _Angle.Z = 0.0f; 
        }
        #endregion  // Constructor

        #region Temperature methods 
        /// <summary>
        /// Gets current temperature. 
        /// </summary>
        /// <returns>
        /// Temperature in the current moment (floating point number). 
        /// </returns>
        public float GetTemperature()
        {
            return Temperature; 
        }

        /// <summary>
        /// Sets current temperature. 
        /// </summary>
        /// <param name="temp">
        /// Temperature in the current moment (floating point number). 
        /// </param>
        public void SetTemperature(float temp)
        {
            this.Temperature = temp; 
        }
        #endregion  // Temperature methods

        #region Rotation methods 
        /// <returns>
        /// An instance of Angle struct. 
        /// </returns>
        public Angle GetRotation()
        {
            return _Angle; 
        }

        /// <summary>
        /// Sets values of an instance of Angle structure. 
        /// Adds deltas to rotation angle around each of axis and corrects
        /// the values if they are less than -360 or bigger than 360. 
        /// </summary>
        /// <param name="dx">
        /// Delta for rotation around X axis (by default is equal to zero). 
        /// </param>
        /// <param name="dy">
        /// Delta for rotation around Y axis (by default is equal to zero). 
        /// </param>
        /// <param name="dz">
        /// Delta for rotation around Z axis (by default is equal to zero). 
        /// </param>
        public void SetRotation(float dx = 0, float dy = 0, float dz = 0)
        {
            // Set angles. 
            _Angle.X += dx; 
            _Angle.Y += dy; 
            _Angle.Z += dz; 

            // Correct value of rotation angle around X axis. 
            if (_Angle.X >= 360)
            {
                _Angle.X -= 360; 
            }
            else if (_Angle.X <= -360)
            {
                _Angle.X += 360; 
            }

            // Correct value of rotation angle around Y axis. 
            if (_Angle.Y >= 360)
            {
                _Angle.Y -= 360; 
            }
            else if (_Angle.Y <= -360)
            {
                _Angle.Y += 360; 
            }

            // Correct value of rotation angle around Z axis. 
            if (_Angle.Z >= 360)
            {
                _Angle.Z -= 360; 
            }
            else if (_Angle.Z <= -360)
            {
                _Angle.Z += 360; 
            }
        }
        #endregion  // Rotation methods

        #region Acceleration methods 
        /// <summary>
        /// Gets values of acceleration along each of 3 axis. 
        /// </summary>
        /// <returns>
        /// An instance of Acceleration struct. 
        /// </returns>
        public Acceleration GetAcceleration()
        {
            return _Accel; 
        }

        /// <summary>
        /// Sets values of acceleration along each of 3 axis. 
        /// </summary>
        public void SetAcceleration(float dx = 0, float dy = 0, float dz = 0)
        {
            // Adjust all accelerations. 
            _Accel.X += dx; 
            _Accel.Y += dy; 
            _Accel.Z += dz;

            // Calculate rotation using acceleration. 
            float dxAngle = (float)System.Math.Atan2(_Accel.Y,
                System.Math.Sqrt(System.Math.Pow(_Accel.X, 2) + System.Math.Pow(_Accel.Z, 2))); 
            float dyAngle = (float)System.Math.Atan2(_Accel.X,
                System.Math.Sqrt(System.Math.Pow(_Accel.Y, 2) + System.Math.Pow(_Accel.Z, 2))); 
            float dzAngle = (float)System.Math.Atan2(System.Math.Sqrt(System.Math.Pow(_Accel.X, 2) + System.Math.Pow(_Accel.Y, 2)),
                _Accel.Z);

            this.SetRotation(dxAngle, dyAngle, dzAngle);
        }

        /// <summary>
        /// Adjust acceleration (decrease acceleration if it's negative, 
        /// increase acceleration if it's positive, do nothing 
        /// if acceleration is equal to 0). 
        /// </summary>
        /// <remarks>
        /// It is needed because acceleration cannot be the same, 
        /// if the state of a real life object does not change.
        /// </remarks>
        public void AdjustAcceleration()
        {
            if (_Accel.X > 0)       // Decrease acceleration by 1 if it is positive. 
            {
                _Accel.X -= 1; 
            }
            else if (_Accel.X < 0)  // Increase acceleration if it is negative by 1. 
            {
                _Accel.X += 1;
            }

            if (_Accel.Y > 0)       // Decrease acceleration by 1 if it is positive. 
            {
                _Accel.Y -= 1;
            }
            else if (_Accel.Y < 0)  // Increase acceleration if it is negative by 1. 
            {
                _Accel.Y += 1;
            }

            if (_Accel.Z > 0)       // Decrease acceleration by 1 if it is positive. 
            {
                _Accel.Z -= 1;
            }
            else if (_Accel.Z < 0)  // Increase acceleration if it is negative by 1. 
            {
                _Accel.Z += 1;
            }
        }
        #endregion  // Acceleration methods
    }
}