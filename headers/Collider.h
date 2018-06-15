#pragma once
#include <SFML/Graphics.hpp>


class CollisionBox {
public:
    CollisionBox();
    ~CollisionBox();

    virtual bool checkCollision(CollisionBox *other, sf::Vector2f &direction, float push)=0;
    virtual void move(float dx, float dy)=0;

    virtual sf::Vector2f getPosition()=0;
    virtual sf::Vector2f getHalfSize()=0;
    //virtual bool isColliding(CollisionBox *other);
};

// Objects used for detecting collisions
// Args:
// body - the body of the object which will have collision detection (will be modified in place)
// velocity - the velocity of the body bound to the collider
class Collider: public CollisionBox {
public:
    Collider(sf::RectangleShape &body, sf::Vector2f velocity);
    ~Collider();

    // Maybe not needed
    void move(float dx, float dy);

    bool checkCollision(CollisionBox *other, sf::Vector2f &direction, float push);
    sf::Vector2f getPosition();
    sf::Vector2f getHalfSize();

private:
    sf::RectangleShape &body;
    sf::Vector2f velocity;
};

class SpriteCollider: public CollisionBox {
public:
    SpriteCollider(sf::Sprite &sprite, sf::Vector2f velocity);
    ~SpriteCollider();

    void move(float dx, float dy);

    bool checkCollision(CollisionBox *other, sf::Vector2f &direction, float push);

    sf::Vector2f getPosition();
    sf::Vector2f getHalfSize();

private:
    sf::Sprite &body;
    sf::Vector2f velocity;
};
