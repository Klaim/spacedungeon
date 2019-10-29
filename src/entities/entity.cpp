#include "stdpch.hpp"
#include "level.hpp"
#include "entity.hpp"
#include "math-util.hpp"
#include "log.hpp"
#include "level.hpp"
#include "entity-data.hpp"

bool windowContains(sf::View view, sf::Sprite sprite);

Entity::Entity(sf::Vector2f position, sf::Vector2u size, sf::Texture* texture, Level* level, unsigned int hitPoints)
: Damageable(hitPoints, hitPoints)
, velocity(0,0)
, collisionRect(position.x, position.y, size.x, size.y)
, prevPosition(position)
, sprite()
, isDead(false)
, level(level) {
	if(texture != nullptr) {
		sprite.setTexture(*texture);
	}
	setOrigin(sf::Vector2f(size.x/2, size.y/2));
	setPosition(position);
}

Entity::Entity(float x, float y, unsigned int w, unsigned int h, sf::Texture* texture, Level* level, unsigned int hitPoints)
: Damageable(hitPoints, hitPoints)
, velocity(0,0)
, collisionRect(x,y,w,h)
, prevPosition(x,y)
, sprite()
, isDead(false)
, level(level) {
	if(texture != nullptr) {
		sprite.setTexture(*texture);
	}
	setOrigin(sf::Vector2f(w/2, h/2));
	setPosition(x,y);
}

Entity::~Entity() {

}

void Entity::update(sf::Time frameTime) {
	lastFrameTime = frameTime;
	prevPosition = getPosition();
	move(velocity * frameTime.asSeconds());
	collisionRect.left = getPosition().x;
	collisionRect.top = getPosition().y;
	if(animation.getTexture() != nullptr) {
		animation.update(frameTime);
		sprite.setTextureRect(animation.getCurrentCellRect());
	}

}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform(); // will apply all transformations on the entity to the sprite when it is drawn


	//if(windowContains(target.getView(), sprite)) {
		target.draw(sprite, states);
	//}

}

void Entity::face(sf::Vector2f position){
	setRotation(Math::calculateAngleFromTo(getPosition(), position) - 90); // minus 90 degrees because SFML assumes a different direction is 0
}

void Entity::setVelocity(sf::Vector2f newVelocity) {
	velocity = newVelocity;
}

void Entity::accelerate(sf::Vector2f newVelocity) {
	velocity += newVelocity;
}

void Entity::limitVelocity(const unsigned int MAX_SPEED) {

	// Let m be the allowed maximum speed and v=(v₁,v₂) be the current velocity.
	// Calculate |v|² = v₁² + v₂² and check if |v²| > m². If so set
	// v₁ ← m/|v| · v₁
	// v₂ ← m/|v| · v₂
	float velocityMagnitude = sqrtf(powf(velocity.x, 2) + powf(velocity.y, 2));
	if(powf(velocityMagnitude, 2) > powf((float)MAX_SPEED, 2)) {
		velocity.x = MAX_SPEED / velocityMagnitude * velocity.x;
		velocity.y = MAX_SPEED / velocityMagnitude * velocity.y;
	}
}

sf::Vector2f Entity::getVelocity() {
	return velocity;
}

sf::Vector2f Entity::getFrameVelocity() {
	return velocity * lastFrameTime.asSeconds();
}

sf::Vector2u Entity::getSize() {
	sf::IntRect rect = sprite.getTextureRect();
	return sf::Vector2u(rect.width, rect.height);
}

Level* Entity::getLevel() {
	return level;
}

sf::FloatRect Entity::getCollisionRect() {
	return collisionRect;
}

FloatLine Entity::getCollisionLine() {
	return FloatLine(prevPosition, getPosition());
}

bool Entity::windowContains(sf::View view, sf::Sprite sprite) const {
	if(sprite.getPosition().x > -100 + view.getCenter().x - view.getSize().x / 2 && sprite.getPosition().x < 100 + view.getCenter().x + view.getSize().x / 2 &&
	   sprite.getPosition().y > -100 + view.getCenter().y - view.getSize().y / 2 && sprite.getPosition().y < 100 + view.getCenter().y + view.getSize().y / 2){
		return true;
	}

	return false;
}

void Entity::setAnimation(Animation newAnimation){
	animation = newAnimation;
	sprite.setTexture(*animation.getTexture());
	sprite.setTextureRect(animation.getCurrentCellRect());
}

void Entity::setTexture(sf::Texture* texture) {
	sprite.setTexture(*texture);
}

void Entity::restore(){
	this->isDead = false;

	Hitpoints newHp(EntityData::DefaultEntity::hitpoints, EntityData::DefaultEntity::hitpoints);
	switch(type) {
		case ALIEN_SHIP:	newHp.setMax(EntityData::AlienShip::hitpoints); newHp.set(EntityData::AlienShip::hitpoints); break;
		case PLAYER_SHIP:	newHp.setMax(EntityData::PlayerShip::hitpoints); newHp.set(EntityData::PlayerShip::hitpoints); break;
		case BULLET:	newHp.setMax(EntityData::Bullet::hitpoints); newHp.set(EntityData::Bullet::hitpoints); break;
		default:	break;
	}
}

void Entity::setLevel(Level* level){
	this->level = level;
}

bool Entity::isMarkedForDeletion() {
	return isReadyToDelete;
}
