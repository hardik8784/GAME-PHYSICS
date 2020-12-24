#pragma once
#ifndef __BRICK__
#define __BRICK__

#include "Sprite.h"
#include "Label.h"


class Brick : public Sprite
{
public:
	Brick();
	~Brick();
	//Inherited from GameObject
	void draw() override;
	void update() override;
	void clean() override;
	//CollisionType shape = CollisionType::Rectangle;

	bool isColliding(GameObject*);
	float getDistance(GameObject*);
private:
	void m_move();
	void m_checkBounds();
	void m_reset();
	glm::vec2 m_previousposition;
};

#endif /*Defined __BRICK__*/

