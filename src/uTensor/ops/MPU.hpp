
#include "platform/mbed_thread.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"


namespace uTensor {

class MPU_OP : public OperatorInterface<2, 1>
{
    public:
      enum names_in : uint8_t {a, b};
      enum names_out : float_t {c};

    protected:
      virtual void compute() {

          setup();
          kernel();
      }
      void setup();
      void kernel();
    private:
      MPU6050 mpu;
      bool dmpReady;
      uint16_t packetSize;
      uint16_t fifoCount;
      float ypr[3];
      VectorFloat gravity;
      Quaternion q;
};
}
