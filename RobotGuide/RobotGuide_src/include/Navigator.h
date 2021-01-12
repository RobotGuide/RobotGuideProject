#ifndef ROBOTGUIDE_NAVIGATOR_H
#define ROBOTGUIDE_NAVIGATOR_H

#include "ILoopComponent.h"
#include "INavigatorCallback.h"
#include "ObstacleDetection.h"
#include "Movement.h"

class Navigator : ILoopComponent
{
public:
    Navigator(Movement& movement, ObstacleDetection& obstacles);
    Navigator(const Navigator& other) = delete;
    Navigator& operator=(const Navigator&) = delete;
    ~Navigator() override = default;

    bool NeedsUpdate(unsigned long time) const override;
    void Update(unsigned long time) override;

    void MoveForward(int millimeters, INavigatorCallback* callback);
    void MoveBackward(int millimeters, INavigatorCallback* callback);
    void RotateLeft(int degrees, INavigatorCallback* callback);
    void RotateRight(int degrees, INavigatorCallback* callback);

private:
    Movement& movement;
    ObstacleDetection& obstacles;
    INavigatorCallback* callback;
    bool executingCommand;
    unsigned long nextUpdateTime;
    const int delay;

    void NavigationFinished(NavigatorStatus status);
};

#endif