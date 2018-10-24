
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "../headers/Player.h"
#include "../headers/Settings.h"
#include "../headers/Utils.h"
#include "../headers/Collider.h"

Player::Player(sf::RectangleShape body, Settings *settings) {
    pos = sf::Vector2f(0, 0);
    this->settings = settings;
    speedMult = 1;
    switchedSpells = false;
    selectedSpell = 0;
    std::vector<sf::Sprite> projectiles = std::vector<sf::Sprite> {};
    spellInventory = std::vector<Spell *> {};
    buffs = std::vector<Buff*> {};
    playeracc = 0.5;
    originalPlayerAcc = playeracc;
    fric = 1.2;
    this->body = body;
    this->body.setFillColor(sf::Color::Green);
    this->body.setOrigin(sf::Vector2f(body.getSize().x / 2, body.getSize().y / 2));
    castProgress = 0;
    casting = false;
    maxHp = 20;
    hitpoints = maxHp;
    maxMana = 100;
    mana = maxMana;
    manaRegen = 5;
    timeSinceHurt = 0;
    level = 1;
}

Player::Player() {

}

Player::~Player() {

}

void Player::castSpell() {
    float cost = (*spellInventory[selectedSpell]).getManaCost();
    if (cost <= mana) {
        (*spellInventory[selectedSpell]).use();
        spendMana(cost);
        castProgress = 0;
    }
}

void Player::addSpell(Spell *spell) {
    spellInventory.push_back(spell);
}

void Player::addProjectile(Projectile projectile) {
    projectiles.push_back(projectile);
}

void Player::clearProjectiles() {
    projectiles.clear();
}

std::vector<Projectile> &Player::getProjectiles() {
    return projectiles;
}

Spell *Player::getSpell(int index) {
    return spellInventory[index];
}

sf::Vector2f Player::getPos() {
    return body.getPosition();
}

void Player::setPos(sf::Vector2f newPos) {
    pos = newPos;
    body.setPosition(newPos);
}

void Player::setVel(sf::Vector2f newVel) {
    vel = newVel;
}

void Player::update(float dt) {
    (*hpBar).update(hitpoints);
    (*manaBar).update(mana);
    acc = sf::Vector2f(0, 0);
    casting = false;
    switchedSpells = false;
    pos = body.getPosition();
    if (sf::Keyboard::isKeyPressed((*settings).keyMap.up)) {
        acc.y = -playeracc;
    }
    if (sf::Keyboard::isKeyPressed((*settings).keyMap.down)) {
        acc.y = playeracc;
    }
    if (sf::Keyboard::isKeyPressed((*settings).keyMap.left)) {
        acc.x = -playeracc;
    }
    if (sf::Keyboard::isKeyPressed((*settings).keyMap.right)) {
        acc.x = playeracc;
    }
    if (sf::Keyboard::isKeyPressed((*settings).keyMap.spell1) && selectedSpell != 0) {
        selectedSpell = 0;
        switchedSpells = true;
    }
    if (sf::Keyboard::isKeyPressed((*settings).keyMap.spell2) && selectedSpell != 1) {
        selectedSpell = 1;
        switchedSpells = true;
    }
    if (sf::Keyboard::isKeyPressed((*settings).keyMap.spell3) && selectedSpell != 2) {
        selectedSpell = 2;
        switchedSpells = true;
    }
    if (sf::Keyboard::isKeyPressed((*settings).keyMap.spell4) && selectedSpell != 3) {
        selectedSpell = 3;
        switchedSpells = true;
    }
    if (sf::Keyboard::isKeyPressed((*settings).keyMap.spell5) && selectedSpell != 4) {
        selectedSpell = 4;
        switchedSpells = true;
    }
    if (sf::Keyboard::isKeyPressed((*settings).keyMap.spell6) && selectedSpell != 5) {
        selectedSpell = 5;
        switchedSpells = true;
    }
    if (sf::Keyboard::isKeyPressed((*settings).keyMap.useSpell)) {
        casting = true;
        castProgress += 0.1 * (dt / (*settings).TIMESCALE);
        if (castProgress > (*spellInventory[selectedSpell]).getCastTime() 
            && (*spellInventory[selectedSpell]).isReady) {
          castSpell();
        }
        if (!(*spellInventory[selectedSpell]).isReady || mana - (*spellInventory[selectedSpell]).getManaCost() < 0) {
            casting = false;
        }

    }
    
    for (int i = 0; i < buffs.size(); i++) {
        (*buffs[i]).update(*this, dt);
        if ((*buffs[i]).kill) {
            (*buffs[i]).end(*this);
            buffs.erase(buffs.begin() + i);
        }
    }

    if (!casting || switchedSpells) {
      castProgress = 0;
    }

    if(!(acc.x == 0.0f || acc.y == 0.0f)) {
        acc = normalizedVec(acc) * playeracc;
    }

    acc += vel / fric;

    vel = acc;

    pos += vel * (dt / (*settings).TIMESCALE) * speedMult;

    body.setPosition(pos);

    for (int i = 0; i < projectiles.size(); i++) {
        if (projectiles[i].kill) {
            projectiles.erase(projectiles.begin() + i);
        }
    }
    
    uiCastBar.update(castProgress, (*spellInventory[selectedSpell]).getCastTime(), casting);
    if (switchedSpells) {
        (*spellBar).changeSelection(selectedSpell + 1);
    }

    if (timeSinceHurt > 0) {
        timeSinceHurt -= dt;
    }

    if (maxMana > mana) {
        restoreMana(std::min((float)(dt * manaRegen / 1000.0), maxMana - mana));
    }
      
    for (int i = 0; i < spellInventory.size(); i++) {
        (*((*spellBar).getIcons()))[i].setCooldown(1 - (
        (*spellInventory[i]).getCooldownTimer() / 
        (*spellInventory[i]).getCooldown()));
                                                       
    }
    (*spellBar).update();

    if (hitpoints < 0) {
        hitpoints = 0;
    }
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(body);
}

Collider Player::getCollider() {
    return Collider(body, vel);
}

void Player::onCollision(sf::Vector2f direction) {
    if (direction.x != 0.0f) {
        vel.x = 0.0f;
        acc.x = 0.0f;
    } else if (direction.y != 0.0f) {
        vel.y = 0.0f;
        acc.y = 0.0f;
    }


    sf::Vector2f oldPos = body.getPosition();
    //body.setPosition(std::round(oldPos.x), std::round(oldPos.y));
    body.setPosition(oldPos.x, oldPos.y);
}

void Player::setMouseAngle(float angle) {
    mouseAngle = angle;
}

float Player::getMouseAngle() {
    return mouseAngle;
}

float Player::getMouseAngleRad() {
    return mouseAngle * (M_PI / 180);
}

sf::Vector2f Player::getMousePos() {
    return mousePos;
}
void Player::setMousePos(sf::Vector2f pos) {
    mousePos = pos;
}

void Player::hurt(float amount) {
    hitpoints -= amount;
    (*hpBar).update(hitpoints);
}

void Player::heal(float amount) {
    hitpoints += amount;
    if (hitpoints > maxHp) {
        hitpoints = maxHp;
    }
    (*hpBar).update(hitpoints);
}

void Player::setHp(float amount) {
    hitpoints = amount;
    (*hpBar).update(hitpoints);
}

void Player::setMaxHp(float amount) {
    maxHp = amount;
    (*hpBar).update(hitpoints);
    (*hpBar).setMaxStat(maxHp);
}

void Player::spendMana(float amount) {
    mana -= amount;
    (*manaBar).update(mana);
}

void Player::restoreMana(float amount) {
    mana += amount;
    (*manaBar).update(mana);
}

void Player::setMana(float amount) {
    mana = amount;
    (*manaBar).update(mana);
}

void Player::setMaxMana(float amount) {
    maxMana = amount;
    (*manaBar).update(mana);
    (*manaBar).setMaxStat(maxMana);
}

float Player::getMaxHp() {
    return maxHp;
}

void Player::setHpBar(PlayerHpBar *bar) {
    hpBar = bar;
}

void Player::setManaBar(PlayerManaBar *bar) {
    manaBar = bar;
}

int Player::getLevel() {
    return level;
}

void Player::setLevel(int newLevel) {
    level = newLevel;
    (*levelIcon).update(level);
}

void Player::setLevelIcon(PlayerLevelIcon *icon) {
    levelIcon = icon;
}

void Player::setMoveSpeed(float newSpeed) {
    playeracc = newSpeed;
}

void Player::setSpeedMult(float newMult) {
    speedMult = newMult;
}

void Player::addBuff(Buff *buff) {
    buffs.push_back(buff);
    (*buff).begin(*this);
}

float Player::getSpeed() {
    return playeracc;
}

float Player::getHp() {
    return hitpoints;
}

std::vector<Spell *> Player::getSpells() {
    return spellInventory;
}
