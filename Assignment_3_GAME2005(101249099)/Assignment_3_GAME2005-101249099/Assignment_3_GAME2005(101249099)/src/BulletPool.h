#pragma once
#ifndef __BULLETPOOL__
#define __BULLETPOOL__

#include"Bullet.h"
#include<iostream>
#include <vector>
using namespace std;
class BulletPool
{
public:
	BulletPool(int);
	~BulletPool();

	Bullet* Spawn();
	void DeSpawn(Bullet*);
	vector<Bullet*> active;
private:

	
	vector<Bullet*> inactive;
};

#endif /* defined (__BULLETPOOL__) */
