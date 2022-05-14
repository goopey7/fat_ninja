//Copyright Sam Collier 2022

#include "Enemy.h"
#include <cmath>

Enemy::Enemy(const TextureHolder& textures, World* currentWorld)
	: Actor(textures,currentWorld)
{
	for(int i=0; i<walkFrames; i++)
		walk.addFrame(sf::IntRect(i*walkWidth,0,walkWidth,walkHeight));
	walk.setFrameSpeed(walkSpeed);

	sprite.setTexture(textures.get(Textures::Mario));
	sprite.setTextureRect(walk.getCurrentFrame());
	sprite.setScale({1.2f,1.2f});

	collisionBox.left = 3.f;
	collisionBox.top = 3.f;

	collisionBox.width = sprite.getTextureRect().width * sprite.getScale().x - collisionBox.left;
	collisionBox.height = sprite.getTextureRect().height * sprite.getScale().y - collisionBox.top;

	collisionBox.width -= 5.f;
	collisionBox.height -= 0.f;

	box.setSize(sf::Vector2f(collisionBox.width,collisionBox.height));
	box.setPosition(collisionBox.left,collisionBox.top);

}
void Enemy::updateCurrent(const float dt)
{
	handleAnimations(dt);
}

void Enemy::fixedUpdateCurrent(const float dt)
{
	Actor::fixedUpdateCurrent(dt);
}

unsigned int Enemy::getCategory() const
{
	return Category::Actor | Category::Enemy;
}

void Enemy::onCollisionEnter(Actor* other, sf::Vector2f& contactPoint, sf::Vector2f& contactNormal, float& hitTime, const float dt)
{
}

void Enemy::drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	Actor::drawCurrent(target,states);
}

Enemy::~Enemy()
{
}

void Enemy::handleAnimations(const float dt)
{
	if(fabs(velocity.x) != 0.f)
	{
		walk.play();
		walk.animate(dt);
	}
	else
	{
		walk.pause();
		walk.setToInitialFrame();
	}
	if(velocity.x < 0.f)
		walk.setFlipped(true);
	else if(velocity.x > 0.f)
		walk.setFlipped(false);
	sprite.setTextureRect(walk.getCurrentFrame());
}

void Enemy::onDynamicVsDynamicEnter(Actor* other)
{
	if(other->getCategory() & Category::PlayerCharacter)
	{
		// apply damage to player
		other->applyDamage(damage);
	}
	else if(other->getCategory() == Category::Shuriken)
	{
		// apply damage to self
		applyDamage(other->getDamage());
		std::cout << "OUCH\n";
		Shuriken* s = reinterpret_cast<Shuriken*>(other);
		s->stopMoving();
		s->setIsDynamic(false);
	}
}

