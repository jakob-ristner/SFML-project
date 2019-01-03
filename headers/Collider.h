#pragma once
#include <SFML/Graphics.hpp>

// Abstract superclass for collision
// CollisionBoxes are not persistent objects. They are created once every tick
// if an object want's to check any collisions.
class CollisionBox {
public:
    CollisionBox();
    ~CollisionBox();

    bool checkCollision(CollisionBox *other, sf::Vector2f &direction, float push);
    // Same thing but doesn't move the collision boxes
    bool isColliding(CollisionBox *other);
    virtual void move(float dx, float dy)=0;

    virtual sf::Vector2f getPosition()=0;
    virtual sf::Vector2f getHalfSize()=0;
    //virtual bool isColliding(CollisionBox *other);
};

// Subclass for generating collisions from RectableShape data
// Args:
// body     - the body of the object which will have collision detection 
//            (will be modified in place)
// velocity - the velocity of the body bound to the collider
class Collider: public CollisionBox {
public:
    Collider(sf::RectangleShape &body, sf::Vector2f velocity);
    ~Collider();

    // Maybe not needed
    void move(float dx, float dy);

    sf::Vector2f getPosition();
    sf::Vector2f getHalfSize();

private:
    sf::RectangleShape &body;
    sf::Vector2f velocity;
};

// Subclass for generating collisions from sprite data
// Args:
// sprite   - reference to the sprite from which the collider will be generated
// velocity - the sprites current velocity, used as collision direction
class SpriteCollider: public CollisionBox {
public:
    SpriteCollider(sf::Sprite &sprite, sf::Vector2f velocity);
    ~SpriteCollider();

    void move(float dx, float dy);

    sf::Vector2f getPosition();
    sf::Vector2f getHalfSize();

private:
    sf::Sprite &body;
    sf::Vector2f velocity;
};

// Circular collider
// Args:
// epicenter - coordinates to center of collider
// radius    - radius of collider
class CollisionCircle {
public:
    CollisionCircle(sf::Vector2f epicenter, float radius);
    ~CollisionCircle();
    
    bool isColliding(CollisionCircle *other);
    bool isColliding(CollisionBox *other);

    sf::Vector2f getEpicenter();
    float getRadius();
    
private:
    sf::Vector2f epicenter;
    float radius;
};
