//Copyright Sam Collier 2022
#include "Ninja.h"
#include <cmath>

Ninja::Ninja(const TextureHolder& textures, World* currentWorld, sf::RenderWindow* window)
	: Actor(textures,currentWorld), window(window), view(window->getView())
{
	setCategory(Category::PlayerCharacter | Category::Actor);
	for(int i=0; i<walkFrames; i++)
		walk.addFrame(sf::IntRect(i*walkWidth,0,walkWidth,walkHeight));
	walk.setFrameSpeed(walkSpeed);

	sprite.setTexture(textures.get(Textures::Ninja));
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

	line = new Line();
}

void Ninja::handleAnimations(const float dt)
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

void Ninja::updateCurrent(const float dt)
{
	handleAnimations(dt);
}

void Ninja::fixedUpdateCurrent(const float dt)
{
	Actor::fixedUpdateCurrent(dt);

	if(thrownShuriken != nullptr)
	{
		if(thrownShuriken->hasHitWall() && sf::Mouse::isButtonPressed(sf::Mouse::Left) && bMouseReleased)
		{
			// INITIAL CALCULATIONS BEFORE SWING STARTS
			state = Swinging;
			grapplePos = thrownShuriken->getWorldPosition();
			ropePos = getWorldPosition();
			ropeAngleVelocity = 0;
			ropeAngle = Vector<float>::angle(grapplePos,sf::Vector2f(ropePos.x + collisionBox.width,ropePos.y));
			ropeLength = Vector<float>::distance(grapplePos,ropePos);
			shurikenDir = (thrownShuriken->getWorldPosition().x > getWorldPosition().x) ? (1) : (-1);
			bMouseReleased = false;
			thrownShuriken->setIsBeingUsed(true);
		}
		else if(thrownShuriken->hasHitWall() && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			state = Normal;
			thrownShuriken->setIsBeingUsed(false);
			thrownShuriken = nullptr;
			bMouseReleased = true;
			line->setPoints(sf::Vector2f(0.f,0.f),sf::Vector2f(0.f,0.f));
		}
	}

	switch(state)
	{
		case Normal:
			{
				velocity.x = dir.x * maxSpeed;
				velocity.y += gravity * dt;
			}
			break;

		case Swinging:
			{
				// APPLY SWING MOTION
				//float ropeAngleAcceleration = dir.x * 2.4f;
				ropeAngleVelocity = shurikenDir * dir.x * 180.f*PI/180.f;
				float clampedRopeAngleVelocity = std::clamp(ropeAngleVelocity,-40.f*PI/180.f,40.f*PI/180.f);
				ropeAngle += ropeAngleVelocity * dt;
				ropeAngle = std::clamp(ropeAngle,-200.f*PI/180.f,20.f*PI/180.f);
				ropePos.x = grapplePos.x + shurikenDir * ropeLength * cosf(ropeAngle);
				ropePos.y = grapplePos.y + ropeLength * -sinf(ropeAngle);
				velocity = ropePos - getWorldPosition();
				/*
				std::cout << "ANGLE: " << ropeAngle*180.f/PI << " degrees\n";
				std::cout << "ANGLE VELOCITY: " << ropeAngleVelocity*180.f/PI << " degrees/sec\n";
				std::cout << "CLAMPED ANGLE VELOCITY: " << clampedRopeAngleVelocity*180.f/PI << " degrees/sec\n";
				std::cout << "LENGTH: " << ropeLength << '\n';
				*/

				line->setPoints(sf::Vector2f(collisionBox.width/2.f,collisionBox.height/2.f),-getWorldPosition()+thrownShuriken->getWorldPosition()
						+sf::Vector2f(thrownShuriken->getCollisionBox().width/2.f,thrownShuriken->getCollisionBox().height/2.f));
			}
			break;
	}
	updateView();
}

void Ninja::jump()
{
	if(bCanJump)
		velocity.y = -jumpSpeed;
	bCanJump = false;
}

void Ninja::crouch()
{
}

void Ninja::stopCrouch()
{
}

void Ninja::setDir(int dir)
{
	this->dir.x = dir;
}

short Ninja::getDir()
{
	return dir.x;
}

std::string Ninja::getVelocity()
{
	return std::to_string(velocity.x) + " , " + std::to_string(velocity.y) + '\n';
}

void Ninja::updateView()
{
	sf::View view = window->getView();
	if(getCategory() & Category::PlayerCharacter)
	{
		view.setCenter(getWorldPosition());
	}
	else
	{
		view.setCenter(getWorldPosition().x,400.f);
	}
	window->setView(view);
}

void Ninja::onCollisionEnter(Actor* other, sf::Vector2f& contactPoint, sf::Vector2f& contactNormal, float& hitTime, const float dt)
{
	if(contactNormal.y == -1.f)
	{
		bCanJump = true;
	}
	if(other->getCategory() & Category::OriginTP)
	{
		setPosition(3000.f,123.f);
	}
}

void Ninja::setShuriken(Shuriken& shuriken)
{
	thrownShuriken = &shuriken;
}

Ninja::State Ninja::getState()
{
	return state;
}

void Ninja::drawCurrent(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	/*
	if(thrownShuriken != nullptr)
		target.draw(*line,states);
	*/
	target.draw(*line,states);
	Actor::drawCurrent(target,states);
}

Ninja::~Ninja()
{
	delete line;
}

void Ninja::setLinePoints(sf::Vector2f p1, sf::Vector2f p2)
{
	line->setPoints(p1,p2);
}

