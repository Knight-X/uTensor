#ifndef UTENSOR_MPU6050_OPS_H
#define UTENSOR_MPU6050_OPS_H
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "operatorBase.hpp"
#include "context.hpp"


namespace uTensor {

class MPU_OP : public OperatorInterface<2, 1> {
    public:
      enum names_in : uint8_t {a, b};
      enum names_out : uint8_t {c};

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
      uint8_t mpuIntStatus;
      float ypr[3];
      VectorFloat gravity;
      Quaternion q;
};
}
#endif
