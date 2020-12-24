#pragma once
#ifndef __END_SCENE__
#define __END_SCENE__

#include "Scene.h"
#include "Label.h"
#include "Button.h"
#include "Brick.h"
#include "Pool.h"
#include "Ball.h"
class EndScene final : public Scene
{
public:
	EndScene();
	~EndScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:
	Label* m_label{};

	Button* m_pRestartButton;
	Button* m_pBackButton;
	Pool* m_pPool;
	//Ball* m_pBall;
	Brick* m_pBrick;

	// Balls
	//int m_numberOfBalls = 1;
	std::vector<Ball*> m_pBallVec;
	void SpawnBall();
	void DespawnBall();
};

#endif /* defined (__END_SCENE__) */