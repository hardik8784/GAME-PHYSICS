#pragma once
#ifndef __BALL__
#define __BALL__

#include "Sprite.h"



class Ball : public Sprite
{
public:
	Ball();
	~Ball();
	//Inherited from GameObject
	void draw() override;
	void update() override;
	void clean() override;

	void collisionResponse(float CheckBounds, glm::vec2 normal, float velocity);

	bool isColliding(GameObject*);
	float getDistance(GameObject*);
private:
	void m_move();
	void m_checkBounds();
	void m_reset();
};

#endif /*Defined __BALL__*/
