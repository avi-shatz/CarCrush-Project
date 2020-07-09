#include "CollisionHandling.h"
#include "CollisionHandling.h"

#include <functional>
#include <iostream>
#include <map>
#include <typeindex>
#include "Coin.h"
#include "Player.h"
#include "GiftTime.h"
#include "Data.h"


namespace { // anonymous namespace — the standard way to make function "static"

// primary collision-processing functions
void carWall(Obj& car, Obj& wall)
{
    auto& carS = static_cast<Car&>(car);
    carS.collideWithWall();
    if(carS.getType() == Type::Player)
       Data::instance().decScore(3);


}

void robotJoint(Obj& robotDriver, Obj& joint)
{
    static_cast<RobotDriver&>(robotDriver).
        collideWithJoint(static_cast<Joint&> (joint));
}
void PlayerCoin(Obj& player, Obj& coin)
{
    Data::instance().incScore(57);

    static_cast<Coin&>(coin).eat();
}
void PlayerGiftTime(Obj& player, Obj& giftTime)
{
    Data::instance().incLimiTime(13);

    static_cast<Coin&>(giftTime).eat();
}

void carCar(Obj& car1, Obj& car2)
{
    auto& car1s = static_cast<Car&>(car1);
    auto& car2s = static_cast<Car&>(car2);

    if (car1s.getType() == Type::Player)
    {
        car1s.collideWithWall();

        car2s.moveBack();
        car2s.pause();

        Data::instance().decScore(5);

        //music
    }
    else
    {
        car1s.pause();
        car1s.moveBack();
    }
}

using HitFunctionPtr = std::function<void(Obj&, Obj&)>;
using Key = std::pair<std::type_index, std::type_index>;
using HitMap = std::map<Key, HitFunctionPtr>;

HitMap initializeCollisionMap()
{
    HitMap phm;
    phm[Key(typeid(Car), typeid(Car))] = &carCar;
    phm[Key(typeid(Car), typeid(Wall))] = &carWall;
    phm[Key(typeid(RobotDriver), typeid(Joint))] = &robotJoint;
    phm[Key(typeid(Player), typeid(Coin))] = &PlayerCoin;
    phm[Key(typeid(Player), typeid(GiftTime))] = &PlayerGiftTime;

    return phm;
}

HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
{
    static HitMap collisionMap = initializeCollisionMap();
    const auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
    if (mapEntry == collisionMap.end())
    {
        return nullptr;
    }
    return mapEntry->second;
}

} // end namespace

void processCollision(Obj& object1, Obj& object2)
{
	const auto collisionHandler = lookup(typeid(object1), typeid(object2));
    if (!collisionHandler)
    {
        throw UnknownCollision(object1, object2);
    }
    collisionHandler(object1, object2);
}

