#include "Navigator.h"

#include <Arduino.h>

Navigator::Navigator(Movement& movement, ObstacleDetection& obstacles)
    : movement(movement)
    , obstacles(obstacles)
    , callback(nullptr)
    , executingCommand(false)
    , nextUpdateTime(0)
    , delay(25)
{

}

bool Navigator::NeedsUpdate(unsigned long time) const
{
    return (executingCommand && time >= nextUpdateTime);
}

void Navigator::Update(unsigned long time)
{
    nextUpdateTime = time + delay;

    if(!movement.IsMoving() && executingCommand)
    {
        NavigationFinished(NavigatorStatus::ARRIVED);
    }

    if(obstacles.ObstacleDetected())
    {
        movement.Brake();
        NavigationFinished(NavigatorStatus::BLOCKED);
    }
}

void Navigator::MoveForward(int millimeters, INavigatorCallback* callback)
{
    this->callback = callback;
    executingCommand = true;
    movement.Move(millimeters);
}

void Navigator::MoveBackward(int millimeters, INavigatorCallback* callback)
{
    this->callback = callback;
    executingCommand = true;
    movement.Move(-millimeters);
}

void Navigator::RotateLeft(int degrees, INavigatorCallback* callback)
{
    this->callback = callback;
    executingCommand = true;
    movement.Rotate(degrees);
}

void Navigator::RotateRight(int degrees, INavigatorCallback* callback)
{
    this->callback = callback;
    executingCommand = true;
    movement.Rotate(-degrees);
}

void Navigator::NavigationFinished(NavigatorStatus status)
{
    executingCommand = false;
    callback->OnNavigationFinished(status);
}