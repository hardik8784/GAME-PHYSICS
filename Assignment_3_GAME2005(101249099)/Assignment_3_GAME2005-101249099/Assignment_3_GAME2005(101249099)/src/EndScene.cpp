#include "EndScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"
#include"SoundManager.h"
#include "Util.h"

EndScene::EndScene()
{
	EndScene::start();
}

EndScene::~EndScene()
= default;

void EndScene::draw()
{
	drawDisplayList();
}

void EndScene::update()
{
	updateDisplayList();

	//glm::vec2 mouseVector = TheGame::Instance()->getMousePosition();
	//getTransform()->position = glm::vec2(mouseVector.x, mouseVector.y);

	//m_pBrick->getTransform()->position = glm::vec2(mouseVector.x, mouseVector.y);

	for (auto ball : m_pBallVec)
	{
		auto position = ball->getTransform()->position;
		auto halfWidth = ball->getWidth() * 0.5f;
		auto halfHeight = ball->getHeight() * 0.5f;
		if (position.y + halfHeight > Config::SCREEN_HEIGHT)
		{
			SoundManager::Instance().playSound("Poing", 0, 1);
			ball->collisionResponse(Config::SCREEN_HEIGHT, glm::vec2(1.0f, -1.0f), 0);
		}
		else if (position.y - halfHeight < 0.0f)
		{
			SoundManager::Instance().playSound("Poing", 0, 1);
			ball->collisionResponse(0.0f, glm::vec2(1.0f, -1.0f), 0);
		}
		if (position.x + halfWidth > Config::SCREEN_WIDTH)
		{
			SoundManager::Instance().playSound("Poing", 0, 1);
			ball->collisionResponse(Config::SCREEN_WIDTH, glm::vec2(-1.0f, 1.0f), 0);
		}
		else if (position.x - halfWidth < 0.0f)
		{
			SoundManager::Instance().playSound("Poing", 0, 1);
			ball->collisionResponse(0.0f, glm::vec2(-1.0f, 1.0f), 0);
		}

		if (m_pBrick->isColliding(ball))
		{
			SoundManager::Instance().playSound("Explosion", 0);
		}

	}

	
}

void EndScene::clean()
{
	removeAllChildren();
}

void EndScene::handleEvents()
{
	EventManager::Instance().update();

	//// Button Events
	//m_pRestartButton->update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
	
}

void EndScene::start()
{
	// Pool Sprite
	m_pPool = new Pool();
	addChild(m_pPool);

	//// Ball Sprite
	//m_pBall = new Ball();
	//addChild(m_pBall);

	// Brick Sprite
	m_pBrick = new Brick();
	addChild(m_pBrick);
	SpawnBall();
	SoundManager::Instance().load("../Assets/audio/Scene2.mp3", "scene2", SoundType::SOUND_MUSIC);
	SoundManager::Instance().playMusic("scene2");
	SoundManager::Instance().load("../Assets/audio/Poing.wav", "Poing", SoundType::SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/Explosion.wav", "Explosion", SoundType::SOUND_SFX);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 8);
	
	//const SDL_Color blue = { 0, 0, 255, 255 };
	//m_label = new Label("END SCENE", "Dock51", 80, blue, glm::vec2(400.0f, 40.0f));
	//m_label->setParent(this);
	//addChild(m_label);

	// Restart Button
	m_pRestartButton = new Button("../Assets/textures/restartButton.png", "restartButton", RESTART_BUTTON);
	m_pRestartButton->getTransform()->position = glm::vec2(730, Config::SCREEN_HEIGHT - getWidth() - 30.0f);
	m_pRestartButton->addEventListener(CLICK, [&]()-> void
	{
		m_pRestartButton->setActive(false);
		TheGame::Instance()->changeSceneState(START_SCENE);
	});

	m_pRestartButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pRestartButton->setAlpha(128);
	});

	m_pRestartButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pRestartButton->setAlpha(255);
	});

	addChild(m_pRestartButton);

	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(100, Config::SCREEN_HEIGHT - getWidth() - 30.0f);
	m_pBackButton->addEventListener(CLICK, [&]()-> void
		{
			m_pBackButton->setActive(false);
			TheGame::Instance()->changeSceneState(PLAY_SCENE);
		});

	m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pBackButton->setAlpha(128);
		});

	m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pBackButton->setAlpha(255);
		});

	addChild(m_pBackButton);

}

void EndScene::SpawnBall()
{
	m_pBallVec.push_back(new Ball);
	addChild(m_pBallVec.back());
	m_pBallVec.back()->getTransform()->position = glm::vec2(rand() % Config::SCREEN_WIDTH, rand() % Config::SCREEN_HEIGHT);
	m_pBallVec.back()->getRigidBody()->velocity = glm::vec2((rand() % 20), (rand() % 20));
}

void EndScene::DespawnBall()
{
	removeChild(m_pBallVec.back());
	m_pBallVec.pop_back();
}
