
#include "MPU.hpp"
namespace uTensor {
void MPU_Op::setup()
{
    pc.printf("Initializing I2C devices...\n");
    mpu.initialize();

    // verify connection
    pc.printf("Testing device connections...\n");
    pc.printf(mpu.testConnection() ? "MPU6050 connection successful\n" : "MPU6050 connection failed\n");

    // load and configure the DMP
    pc.printf("Initializing DMP...\n");
    uint8_t devStatus = mpu.dmpInitialize();
    
    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        pc.printf("Enabling DMP...\n");
        this->mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        //Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
        //attachInterrupt(0, dmpDataReady, RISING);
        this->mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        pc.printf("DMP ready!\n");
        this->dmpReady = true;

        // get expected DMP packet size for later comparison
        this->packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        printf("DMP Initialization failed (code %d)\n", devStatus);
    }
}
void MPU_OP::kernel()
{
    uint8_t fifoBuffer[64];
    if (!this->dmpReady) return;
    // get current FIFO count
    this->fifoCount = this->mpu.getFIFOCount();
    
    if (this->fifoCount == 1024) {
        // reset so we can continue cleanly
        this->mpu.resetFIFO();

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (this->fifoCount >= 42) {
        // read a packet from FIFO

        this->mpu.getFIFOBytes(this->fifoBuffer, this->packetSize);
        

            // display Euler angles in degrees
            
        this->mpu.dmpGetQuaternion(&this->q, fifoBuffer);
        this->mpu.dmpGetGravity(&this->gravity, &this->q);
        this->mpu.dmpGetYawPitchRoll(this->ypr, &this->q, &this->gravity);
        printf("ypr %7.2f ", ypr[0] * 180/M_PI);

    }

}


}
