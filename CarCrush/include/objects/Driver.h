#pragma once
#include "Obj.h"
#include "Car.h"


class Driver : public Obj
{
public:
	Driver(const sf::Vector2f position);
	~Driver() =0 {};

	virtual void attachCar(Car* car);
	void dettachCar();

	void draw(sf::RenderTarget& target) const override;
	virtual void update(float dt) =0;

	virtual sf::Vector2f getPosition() const override;
	virtual float getRotation() const override;
	virtual sf::Sprite& getSprite() override;
	virtual void setRotation(float rotation) override;
	virtual void setOrigin(sf::Vector2f origin)override;
	virtual void setPosition(sf::Vector2f position)override;
	virtual void setColor(sf::Color color) override;
	Car* getCar();

protected:
	Car* m_car;
};

