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

        public void SetRotation(float dx, float dy, float dz)
        {
            _Angle.X += dx; 
            _Angle.Y += dy; 
            _Angle.Z += dz; 
        }

        public void GetAcceleration()
        {

        } 

        public void SetAcceleration()
        {

        } 
        
        #endregion  // Methods
    }
}