//Copyright Sam Collier 2022
#pragma once

#include "gf/Actor.h"
#include "gf/Animation.h"
#include "gf/Vector.h"
#include "Resources.h"

class Mario : public Actor
{
	public:
		Mario(const TextureHolder& textures, sf::RenderWindow* window);

		void handleAnimations(const float dt);
		virtual void updateCurrent(const float dt) override;
		virtual unsigned int getCategory() const override;
		virtual void onCollisionEnter(Actor* other, unsigned int sides, const sf::FloatRect& overlap) override;
		virtual void whileColliding(Actor* other, unsigned int sides, const sf::FloatRect& overlap) override;
		virtual void onCollisionExit(Actor* other, unsigned int sides, const sf::FloatRect& overlap) override;
		void jump();
		void crouch();
		void stopCrouch();
		void setDir(int dir);
		short getDir();
		std::string getVelocity();
		void updateView();

	private:
		sf::Vector2f dir = {0.f,0.f};
		float gravity = 981;
		bool bOnFloor = false;
		bool bCanMoveRight = true;
		bool bCanMoveLeft = true;
		float jumpSpeed = 350.f;
		sf::Vector2f velocity = {0.f,0.f};
		float maxSpeed = 120.f;
		float acceleration = 300.f;

		Animation walk;
		int walkWidth = 15;
		int walkHeight = 21;
		int walkFrames = 4;
		float walkSpeed = 0.1f;

		sf::Vector2f displacementFromLastFrame;

		sf::RenderWindow* window;
		sf::View view;
};

