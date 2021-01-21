#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#define NUMBER_SAMPLES 500
#define LOW_PASS_FILTER 0.02f
#define HIGH_PASS_FILTER 0.98f

Adafruit_MPU6050 mpu;

float yaw = 0;
float pitch = 0;
float roll = 0;

float xOffset = 0;
float yOffset = 0;
float zOffset = 0;

double deltaX;
double deltaY;

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
    mpu.setGyroRange(MPU6050_RANGE_250_DEG);
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

double length(double valueA, double valueB)
{
    return sqrt(pow(valueA, 2) + pow(valueB, 2));
}

void loop()
{

    /* Get new sensor events with the readings */
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    double deltaTime = (millis() - last) / 1000.0;

    deltaX += ((g.gyro.x - xOffset)) * deltaTime;
    deltaY += ((g.gyro.y - yOffset)) * deltaTime;

    //Filter accelerometer
    double accelerationX = atan(a.acceleration.y / length(a.acceleration.x, a.acceleration.z));
    double accelerationY = atan(-1 * a.acceleration.x / length(a.acceleration.y, a.acceleration.z));

    roll = HIGH_PASS_FILTER * deltaX + LOW_PASS_FILTER * accelerationX;
    pitch = HIGH_PASS_FILTER * deltaY + LOW_PASS_FILTER * accelerationY;
    yaw += ((g.gyro.z - zOffset)) * deltaTime;

    Serial.print(roll * RAD_TO_DEG);
    Serial.print(" ");
    Serial.print(pitch * RAD_TO_DEG);
    Serial.print(" ");
    Serial.println(yaw * RAD_TO_DEG);

    last = millis();
}
