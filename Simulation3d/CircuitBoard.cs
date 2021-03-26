namespace Simulation3d
{
    struct Angle
    {
        
    }

    struct Acceleration
    {
        
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

        private Angle _Angle = new Angle(); 
        private Acceleration _Accel = new Acceleration(); 

        #endregion  // Members


        #region Constructor

        public CircuitBoard()
        {
        }

        #endregion  // Constructor


        #region Methods 

        public void GetRotation()
        {

        }

        public void GetAcceleration()
        {

        } 
        
        #endregion  // Methods
    }
}