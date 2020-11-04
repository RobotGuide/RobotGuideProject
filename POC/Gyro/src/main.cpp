#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#define NUMBER_SAMPLES 500
#define LOW_PASS_FILTER 0.02f
#define HIGH_PASS_FILTER 0.98f

Adafruit_MPU6050 mpu;

float x = 0;
float y = 0;
float z = 0;

float xOffset = 0;
float yOffset = 0;
float zOffset = 0;

unsigned long last = 0;

void setup(void)
{
    Serial.begin(115200);
    while (!Serial)
        delay(10); // will pause Zero, Leonardo, etc until serial console opens

    Serial.println("Adafruit MPU6050 test!");

    // Try to initialize!
    if (!mpu.begin())
    {
        Serial.println("Failed to find MPU6050 chip");
        while (1)
        {
            delay(10);
        }
    }
    Serial.println("MPU6050 Found!");

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);

    Serial.println("");

    const int repetitions = 1000;

    for (int cal_int = 0; cal_int < repetitions; cal_int++)
    {
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);

        //Add the gyro x offset to the gyro_x_cal variable
        xOffset += g.gyro.x;
        //Add the gyro y offset to the gyro_y_cal variable
        yOffset += g.gyro.y;
        //Add the gyro z offset to the gyro_z_cal variable
        zOffset += g.gyro.z;
        //Delay 3us to have 250Hz for-loop
        delay(3);
    }

    xOffset /= repetitions;
    yOffset /= repetitions;
    zOffset /= repetitions;
    last = millis();
}

void loop()
{

    /* Get new sensor events with the readings */
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    double deltaTime = (millis() - last) / 1000.0;

    double deltaX = ((g.gyro.x + xOffset)) * deltaTime;
    double deltaY = ((g.gyro.y + yOffset)) * deltaTime;
    double deltaZ = ((g.gyro.z + zOffset)) * deltaTime;

    double accelerationX = atan(a.acceleration.x / sqrt(pow(a.acceleration.y, 2) + pow(a.acceleration.z, 2)));
    double accelerationY = atan(a.acceleration.y / sqrt(pow(a.acceleration.x, 2) + pow(a.acceleration.z, 2)));
    double accelerationZ = atan(sqrt(pow(a.acceleration.x, 2) + pow(a.acceleration.y, 2)) / a.acceleration.z);

    x = (HIGH_PASS_FILTER * (x * DEG_TO_RAD + deltaX) + LOW_PASS_FILTER * accelerationX) * RAD_TO_DEG;
    y = (HIGH_PASS_FILTER * (y * DEG_TO_RAD + deltaY) + LOW_PASS_FILTER * accelerationY) * RAD_TO_DEG;
    z = (HIGH_PASS_FILTER * (z * DEG_TO_RAD + deltaZ) + LOW_PASS_FILTER * accelerationZ) * RAD_TO_DEG;

    Serial.print("X: ");
    Serial.print(x);
    Serial.print(", Y: ");
    Serial.print(y);
    Serial.print(", Z: ");
    Serial.print(z);
    Serial.println(" angle");

    last = millis();
}
