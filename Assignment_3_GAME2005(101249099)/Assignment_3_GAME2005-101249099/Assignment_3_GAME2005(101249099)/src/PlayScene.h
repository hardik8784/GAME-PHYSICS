#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Background.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Bullet.h"
#include "BulletPool.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:

	// IMGUI Function
	void GUI_Function();

	const float bulletSpawnTimerDuration = 1000.0f;
	float bulletSpawnTimerStart;
	glm::vec2 m_mousePosition;

	Background* background;
	BulletPool* m_pPool;
	Plane* m_pPlaneSprite;
	Player* m_pPlayer;
	/*Bullet* m_pBullet;*/
	/*Label* m_pDistanceLabel;
	Label* m_pVelocityLabel;*/
	Button* m_pRestartButton;
	Button* m_pBackButton;
	Button* m_pNextButton;

	void SpawnBullet();
};

#endif /* defined (__PLAY_SCENE__) */