//Copyright Sam Collier 2022
#pragma once

#include "gf/Actor.h"
#include "gf/Animation.h"
#include "gf/Vector.h"
#include "gf/Line.h"
#include "Shuriken.h"
#include "Resources.h"

class Mario : public Actor
{
	public:
		Mario(const TextureHolder& textures, World* world, sf::RenderWindow* window);

		void handleAnimations(const float dt);
		virtual void updateCurrent(const float dt) override;
		virtual void fixedUpdateCurrent(const float dt) override;
		virtual unsigned int getCategory() const override;
		virtual void onCollisionEnter(Actor* other, sf::Vector2f& contactPoint, sf::Vector2f& contactNormal, float& hitTime, const float dt) override;
		void jump();
		void crouch();
		void stopCrouch();
		void setDir(int dir);
		short getDir();
		std::string getVelocity();
		void updateView();
		void setShuriken(Shuriken& shuriken);

		enum State
		{
			Normal,
			Swinging,
		}; 

		State getState();

	private:
		sf::Vector2f dir = {0.f,0.f};
		float gravity = 98.1f*6.f;
		float jumpSpeed = 150.f*2.f;
		float maxSpeed = 110.f;

		Animation walk;
		int walkWidth = 15;
		int walkHeight = 21;
		int walkFrames = 4;
		float walkSpeed = 0.1f;

		sf::Vector2f displacementFromLastFrame;

		sf::RenderWindow* window;
		sf::View view;

		bool bCanJump = true;

		Shuriken* thrownShuriken = nullptr;

		State state = Normal;	

		// ROPE STUFF
		sf::Vector2f shurikenPos;
		float ropeAngleVelocity;
		float ropeAngle;
		float ropeLength;
		float ropeX, ropeY;
		sf::Vector2f grapplePos;
		sf::Vector2f ropePos;
		int shurikenDir = 0;

		bool bMouseReleased = true;
};

