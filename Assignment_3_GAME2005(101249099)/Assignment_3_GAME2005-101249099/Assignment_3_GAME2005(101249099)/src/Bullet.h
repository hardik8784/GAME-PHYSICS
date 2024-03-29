#pragma once
#ifndef __BULLET__
#define __BULLET__

#include "Sprite.h"

class Bullet : public Sprite
{
public:
	Bullet();
	~Bullet();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void Reset();
	bool active = false;
	bool isColliding(Sprite*);
	float getDistance(Sprite*);
//private:
//	BulletPool* m_pPool;
};

#endif /* defined (__BULLET__) */


