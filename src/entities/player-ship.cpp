#include "player-ship.hpp"
#include "input.hpp"
#include "othermath.h"
#include "resources.hpp"
#include "log.hpp"
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <algorithm>

using namespace std;

PlayerShip::PlayerShip(float x, float y, unsigned int w, unsigned int h, sf::Texture* texture) 
: Entity(x, y, w, h),
  gun(this, 0U), 
  specialGun(this, 1U) {
    sprite.setTexture(*texture);
    type = Entity::types::PLAYER_SHIP;
}

PlayerShip::PlayerShip(float x, float y, unsigned int w, unsigned int h) 
: Entity(x, y, w, h),
  gun(this, 0U), 
  specialGun(this, 1U) {
    setTexture(Resources::get(Resources::ID::PLAYERSHIP));
}

PlayerShip::~PlayerShip() {

}
void PlayerShip::checkCollision(Entity* entity){

}
void PlayerShip::update(sf::Time frameTime, sf::RenderWindow* window, std::vector<Entity*> entities) {
    if(teleportTimer.getElapsedTime().asMilliseconds() > (int)BLINK_DELAY) {
        canBlink = true;
    }

    handleUserInput();
    face(sf::Vector2f(Input::mousePosition.x + window->getView().getCenter().x - window->getSize().x / 2, Input::mousePosition.y + window->getView().getCenter().y - window->getSize().y / 2)); // face the mouse cursor
    // slow down ship
    if(!up && !down && !left && !right) {
        velocity *= FRICTION;
    }
    applyMovement(frameTime);
    gun.update(frameTime, window, entities); 
    specialGun.update(frameTime, window, entities);
    collisionBox.update(position.x, position.y);
}

void PlayerShip::handleUserInput() {
    
    if(up = Input::checkKey(sf::Keyboard::W)) {
        addVelocity(sf::Vector2f(0, -(float)ACCELERATION));
    }
    if(left = Input::checkKey(sf::Keyboard::A)) {
        addVelocity(sf::Vector2f(-(float)ACCELERATION, 0));
    }
    if(down = Input::checkKey(sf::Keyboard::S)) {
        addVelocity(sf::Vector2f(0, (float)ACCELERATION));
    }
    if(right = Input::checkKey(sf::Keyboard::D)) {
        addVelocity(sf::Vector2f((float)ACCELERATION,0));
    }
    if(Input::checkKey(sf::Keyboard::Space)) {
        teleport(angle);
    }
    if(Input::checkMouse(sf::Mouse::Left)){
        firePrimary();      
        std::cout << "basic bullet shot" << std::endl;
    }
    if(Input::checkMouse(sf::Mouse::Right)){
        fireSpecial();
    }
}

void PlayerShip::teleport(float angle) {
    if(canBlink) {
        nextPosition.x += BLINK_DISTANCE * cosf(degreesToRadians(angle - 90));
        nextPosition.y += BLINK_DISTANCE * sinf(degreesToRadians(angle - 90));
        // velocity.x += 1;
        // velocity.y += 1;
        // float velocityAngle = radiansToDegrees(atanf(velocity.y / velocity.x));
        // velocity.x -= 1;
        // velocity.y -= 1;
        // nextPosition.x += BLINK_DISTANCE * cosf(degreesToRadians(velocityAngle));
        // nextPosition.y += BLINK_DISTANCE * sinf(degreesToRadians(velocityAngle));
        canBlink = false;
        teleportTimer.restart();
    }
    
}

void PlayerShip::firePrimary() {
    if(shootTimer.getElapsedTime().asMilliseconds() > (int)SHOOT_DELAY){
        gun.shoot();
        shootTimer.restart();
    }
}

void PlayerShip::fireSpecial() {
    if(specialShootTimer.getElapsedTime().asMilliseconds() > (int)SPECIAL_SHOOT_DELAY) {
        specialGun.shoot();
        specialShootTimer.restart();
    }
}

void PlayerShip::damage(unsigned int amount) {

}

void PlayerShip::repair(unsigned int amount) {

}

void PlayerShip::giveSpecialAmmo(unsigned int amount) {

}

void PlayerShip::giveSpecialWeapon() {

}

void PlayerShip::draw(sf::RenderWindow* window){
    Entity::draw(window);
    gun.draw(window);
    specialGun.draw(window);
}