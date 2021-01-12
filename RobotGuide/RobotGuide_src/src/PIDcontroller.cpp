#include "PIDcontroller.h"

PIDcontroller::PIDcontroller(float pScale, float iScale, float dScale)
    :pScale_(pScale), iScale_(iScale), dScale_(dScale), errorIntegral_(0), lastError_(0), integratorEnabled_(true)
{}

float PIDcontroller::getPScale() const
{
    return pScale_;
}

float PIDcontroller::getIScale() const
{
    return iScale_;
}

float PIDcontroller::getDScale() const
{
    return dScale_;
}

void PIDcontroller::setPScale(float scale)
{
    pScale_ = scale;
}

void PIDcontroller::setIScale(float scale)
{
    iScale_ = scale;
}

void PIDcontroller::setDScale(float scale)
{
    dScale_ = scale;
}

void PIDcontroller::integratorEnabled(bool enabled)
{
    integratorEnabled_ = enabled;
}

float PIDcontroller::calculateControlSignal(long error, long deltaTime)
{
    float errorFloat = (float)error;
    float deltaTimeFloat = (float)deltaTime;

    float compP = 0;
    float compI = 0;
    float compD = 0;

    compP = error * pScale_;

    if(integratorEnabled_)
    {
        errorIntegral_ += (errorFloat * deltaTimeFloat);
        compI = errorIntegral_ * iScale_;
    }

    float derivativeValue = (error - lastError_) / deltaTime;
    compD = derivativeValue * dScale_;


    return compP + compI + compD;
}

void PIDcontroller::resetController()
{
    errorIntegral_ = 0;
}

//unused method?
float PIDcontroller::calculateScale(long compValue, float scale)
{
    long longScale = scale * 1000L;
    long longCompValue = compValue * 1000L;

    long actualValue = longCompValue * longScale;

    return actualValue / 1000000L;
}