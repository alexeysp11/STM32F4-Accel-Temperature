namespace Simulation3d
{
    public struct Angle
    {
        public float X; 
        public float Y; 
        public float Z; 
    }

    public struct Acceleration
    {
        public float X; 
        public float Y; 
        public float Z; 
    }

    /// <summary>
    /// . 
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

        public Angle GetRotation()
        {
            return _Angle; 
        }

        /// <summary>
        /// Sets values of an instance of Angle structure. 
        /// Adds deltas to rotation angle around each of axis and corrects
        //// the values if they are less than -360 or bigger than 360. 
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
            _Angle.X += dx; 
            _Angle.Y += dy; 
            _Angle.Z += dz; 

            if (_Angle.X >= 360)
            {
                _Angle.X -= 360; 
            }
            else if (_Angle.X <= -360)
            {
                _Angle.X += 360; 
            }

            if (_Angle.Y >= 360)
            {
                _Angle.Y -= 360; 
            }
            else if (_Angle.Y <= -360)
            {
                _Angle.Y += 360; 
            }

            if (_Angle.Z >= 360)
            {
                _Angle.Z -= 360; 
            }
            else if (_Angle.Z <= -360)
            {
                _Angle.Z += 360; 
            }
        }

        public Acceleration GetAcceleration()
        {
            return _Accel; 
        } 

        public void SetAcceleration(float dx = 0, float dy = 0, float dz = 0)
        {
            _Accel.X += dx; 
            _Accel.Y += dy; 
            _Accel.Z += dz;
        } 
        
        #endregion  // Methods
    }
}