#ifndef PLAYER_SHIP_HPP
#define PLAYER_SHIP_HPP

#include "allpch.hpp"
#include "input.hpp"
#include "othermath.h"
#include "gun.hpp"
#include "entity.hpp"
#include "entity-data.hpp"

class PlayerShip : public Entity {
	public:
		PlayerShip(float x, float y, unsigned int w, unsigned int h, sf::Texture* texture, Level* level, unsigned int hitPoints = EntityData::PlayerShip::hitpoints);
		PlayerShip(sf::Vector2f position, sf::Vector2u size, sf::Texture* texture, Level* level, unsigned int hitPoints = EntityData::PlayerShip::hitpoints);
		~PlayerShip();
		void init();

		void update(sf::Time frameTime);
		void handleUserInput();
		void teleport(float angle);
		void firePrimary();
		void fireSpecial();
		void giveSpecialAmmo(unsigned int amount);
		void giveSpecialWeapon();

		Gun* getPrimaryWeapon();
		Gun* getSecondaryWeapon();

	private:
	// stats
		unsigned int shieldLevel;
		unsigned int powerLevel;

		bool up = false;
		bool down = false;
		bool right = false;
		bool left = false;

		Gun gun;
		Gun specialGun;

	// teleporting
		bool canBlink;
		sf::Clock teleportTimer;
		sf::Clock shootTimer;
		sf::Clock specialShootTimer;

		const unsigned int MAX_SPEED = 1000; // MAX_SPEED MUST BE LARGER THAN ACCELERATION
		const unsigned int ACCELERATION = 100;
		const unsigned int BLINK_DELAY = 750; // in milliseconds
		const unsigned int SHOOT_DELAY = 200;
		const unsigned int SPECIAL_SHOOT_DELAY = 1000;
		const unsigned int BLINK_DISTANCE = 200;
		const unsigned int MAX_SHIELD_LEVEL = 5;
		const unsigned int MAX_POWER_LEVEL = 10;
		const float FRICTION = 0.95;
};

#endif
