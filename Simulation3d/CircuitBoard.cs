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


        #region Constructor

        public CircuitBoard()
        {
            _Angle.X = 0; 
            _Angle.Y = 0; 
            _Angle.Z = 0; 
        }

        #endregion  // Constructor


        #region Methods 

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
            _Accel.X += dx; 
            _Accel.Y += dy; 
            _Accel.Z += dz;
        } 
        
        #endregion  // Methods
    }
}