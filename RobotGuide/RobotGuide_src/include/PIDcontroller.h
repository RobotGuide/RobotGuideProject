#ifndef ROBOTGUIDE_PIDCONTROLLER_H
#define ROBOTGUIDE_PIDCONTROLLER_H

class PIDcontroller
{
public:
    PIDcontroller(float pScale, float iScale, float dScale);
    PIDcontroller(const PIDcontroller&) = delete;
    PIDcontroller& operator=(const PIDcontroller&) = delete;

    float getPScale() const;
    float getIScale() const;
    float getDScale() const;

    void setPScale(float scale);
    void setIScale(float scale);
    void setDScale(float scale);

    void integratorEnabled(bool enabled);

    float calculateControlSignal(long error, long deltaTime);

    void resetController();

private:
    float pScale_;
    float iScale_;
    float dScale_;

    float lastError_;
    float errorIntegral_;

    bool integratorEnabled_;

    float calculateScale(long compValue, float scale);
};

#endif