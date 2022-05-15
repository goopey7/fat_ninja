//Copyright Sam Collier 2022

#include "Enemy.h"
#include <cmath>

Enemy::Enemy(const TextureHolder& textures, World* currentWorld, Mario* player)
	: Actor(textures,currentWorld), player(player)
{
	setCategory(Category::Enemy | Category::Actor);
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
	velocity.x = dir.x * speed;
	velocity.y += gravity * dt;

	// ray cast to find player
	sf::Vector2f rayOrigin = getWorldPosition();
	rayOrigin.y += 10.f;
	if(dir.x == 1)
		rayOrigin.x += getCollisionBox().width;
	sf::Vector2f rayDir = dir;
	sf::Vector2f cp, cn;
	float hitTime;
	sf::Vector2f playerPos = player->getWorldPosition();
	//TODO add debug line for debug mode
	//setLinePoints(rayOrigin-playerPos,(rayOrigin + (rayDir * rangeOfSight))-playerPos);
	if(Collision::RayVsActor(rayOrigin,rayDir*rangeOfSight,player,cp,cn,hitTime))
	{
		velocity.x = 0.f;
		Shuriken* s = new Shuriken(textures,currentWorld);
		s->setPosition(sf::Vector2f(getWorldPosition()));
		s->setupTarget(player->getWorldPosition());
		s->setTexture(Textures::Shuriken);
		sf::Vector2u textureSize = s->getTextureSize();
		s->setCollisionBox(sf::FloatRect(0.f,0.f,textureSize.x,textureSize.y));
		s->setTextureRect(sf::IntRect(0.f,0.f,textureSize.x,textureSize.y));
		s->setIsDynamic(true);
		s->setOrigin(textureSize.x/2.f, textureSize.y/2.f);
		s->setCategory(Category::EnemyProjectile | Category::Actor);
		spawn(new Node::NodePtr(s));
	}
}

void Enemy::onCollisionEnter(Actor* other, sf::Vector2f& contactPoint, sf::Vector2f& contactNormal, float& hitTime, const float dt)
{
	if(contactNormal.y == 0)
		dir.x = contactNormal.x;
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
	if(dir.x < 0.f)
		walk.setFlipped(true);
	else if(dir.x > 0.f)
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
}

