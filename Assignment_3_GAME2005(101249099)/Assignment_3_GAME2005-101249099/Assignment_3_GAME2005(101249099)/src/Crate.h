#pragma once
#ifndef __CRATE__
#define __CRATE__

#include "Constant.h"
#include "DisplayObject.h"
#include "TextureManager.h"

class Crate : public DisplayObject
{
public:
	Crate(glm::vec2 Position = glm::vec2(0.0f, 0.0f));
	~Crate();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void reset(glm::vec2 pos);
	void StopMoving();

private:
	float TravelTime;
};

#endif /* defined (__CRATE__) */
