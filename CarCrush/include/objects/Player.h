#pragma once
#include "Driver.h"

class Player : public Driver
{

public:
    Player(const sf::Vector2f position);
    ~Player() {};
    void processEvents(const sf::Keyboard::Key key);
    virtual void update(float dt) override;
    virtual void attachCar(Car* car) override;

private:

};

