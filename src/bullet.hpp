#ifndef BULLET_HPP
#define BULLET_HPP
#include "entity.hpp"
#include "SFML/graphics.hpp"
#include "SFML/system.hpp"

class Bullet : public Entity {

    private:

    public:
        Bullet(sf::Vector2f, sf::Vector2u, unsigned int, unsigned int, sf::Time);
        virtual void update(sf::Time frameTime, sf::RenderWindow* window, std::vector<Entity*> entities);
        
        ~Bullet();
        bool isDead();
        virtual void onDeath() = 0;

    protected:
        unsigned int initialSpeed;
        unsigned int damage;

        bool dead;

        sf::Clock timeAlive;
        sf::Time maxTimeAlive;

        sf::Vector2f finalPosition;

        virtual void checkCollision(Entity* entity) = 0;
    
};
#endif 