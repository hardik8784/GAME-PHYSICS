#include "BulletPool.h"
#include <iostream>
#include <vector>
using namespace std;
BulletPool::BulletPool(int Size)
{
	for (int i = 0; i < Size; i++)
	{
		inactive.push_back(new Bullet());
	}

	cout << "Bullet Pool created with the size : " << Size << endl;
}

BulletPool::~BulletPool()
{
}

Bullet* BulletPool::Spawn()
{
	Bullet* bullet = NULL;
	if (inactive.size() > 0 )
	{
		bullet = inactive.back();
		bullet->active = true;
		inactive.pop_back();
		active.push_back(bullet);
		cout << "Bullet Spawned " << endl;
		cout << "Active Count " << to_string(active.size()) << endl;
	}
	else
	{
		cout << "ERROR : Maximum Bullets in the screen " << endl;
	}
	return bullet;
}

void BulletPool::DeSpawn(Bullet* bullet)
{
	bullet->Reset();
	//bullet->active = false;
	inactive.push_back(bullet);

	for (vector<Bullet*>::iterator myiter=active.begin();myiter !=active.end();myiter++)
	{
		if (*myiter == bullet)
		{
			active.erase(myiter);
			cout << "Bullet DeSpawned " << endl;
			cout << "Active Count " << to_string(active.size()) << endl;
			return;

			/*active.at(i) == active.back();
			active.pop_back();*/
		}
		
	}
	
}

