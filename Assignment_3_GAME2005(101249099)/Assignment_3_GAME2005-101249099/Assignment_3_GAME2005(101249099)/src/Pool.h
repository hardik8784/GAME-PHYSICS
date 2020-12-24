#pragma once
#ifndef __POOL__
#define __POOL__

#include "DisplayObject.h"

class Pool : public DisplayObject
{
public:
	Pool();
	~Pool();
	//Inherited from GameObject
	void draw() override;
	void update() override;
	void clean() override;
private:
	void m_move();
	void m_checkBounds();
	void m_reset();

};

#endif /*Defined __POOL__*/
