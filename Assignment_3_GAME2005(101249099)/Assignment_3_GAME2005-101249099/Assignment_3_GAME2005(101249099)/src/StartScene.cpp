#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void StartScene::start()
{
	SoundManager::Instance().load("../Assets/audio/Start.wav", "Start", SoundType::SOUND_MUSIC);
	SoundManager::Instance().playMusic("Start");
	Mix_VolumeMusic(MIX_MAX_VOLUME / 8);


	const SDL_Color Red = { 255,0,0,255 };
	const SDL_Color Green = { 0,255,0,255 };
	const SDL_Color Blue = { 0, 0, 255, 255 };

	m_pStartLabel = new Label("Assignment Group 46", "Consolas", 60, Red, glm::vec2(400.0f, 40.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pInstructionsLabel = new Label("Press 1 to go Scene1 or click on Scene1", "Consolas", 30, Blue, glm::vec2(400.0f, 120.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);

	m_pInstructionsLabel = new Label("Press 2 to go Scene2 or click on Scene2", "Consolas", 30, Blue, glm::vec2(400.0f, 160.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);


	m_pInstructionsLabel = new Label("Hardik Shah-101249099", "Consolas", 40, Blue, glm::vec2(400.0f, 220.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);

	///*Instructions Label */
	//m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View in game", "Consolas");
	//m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 500.0f);

	//addChild(m_pInstructionsLabel);
	// Scene 1 Button
	m_pScene1 = new Button("../Assets/textures/scene1.png", "scene1",START_BUTTON);
	m_pScene1->getTransform()->position = glm::vec2(200.0f, 400.0f);

	m_pScene1->addEventListener(CLICK, [&]()-> void
		{
			m_pScene1->setActive(false);
			TheGame::Instance()->changeSceneState(PLAY_SCENE);
		});

	m_pScene1->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pScene1->setAlpha(128);
		});

	m_pScene1->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pScene1->setAlpha(255);
		});
	addChild(m_pScene1);

	// Scene 2 Button
	m_pScene2 = new Button("../Assets/textures/scene2.png", "scene2", RESTART_BUTTON);
	m_pScene2->getTransform()->position = glm::vec2(600.0f, 400.0f);
	m_pScene2->addEventListener(CLICK, [&]()-> void
		{
			m_pScene2->setActive(false);
			TheGame::Instance()->changeSceneState(END_SCENE);
		});

	m_pScene2->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pScene2->setAlpha(128);
		});

	m_pScene2->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pScene2->setAlpha(255);
		});

	addChild(m_pScene2);






	//const SDL_Color blue = { 0, 0, 255, 255 };
	//m_pStartLabel = new Label("START SCENE", "Consolas", 80, blue, glm::vec2(400.0f, 40.0f));
	//m_pStartLabel->setParent(this);
	//addChild(m_pStartLabel);

	//m_pInstructionsLabel = new Label("Press 1 to Play", "Consolas", 40, blue, glm::vec2(400.0f, 120.0f));
	//m_pInstructionsLabel->setParent(this);
	//addChild(m_pInstructionsLabel);


	//m_pShip = new Ship();
	//m_pShip->getTransform()->position = glm::vec2(400.0f, 300.0f); 
	//addChild(m_pShip); 

	//// Start Button
	//m_pStartButton = new Button();
	//m_pStartButton->getTransform()->position = glm::vec2(400.0f, 400.0f); 

	//m_pStartButton->addEventListener(CLICK, [&]()-> void
	//{
	//	m_pStartButton->setActive(false);
	//	TheGame::Instance()->changeSceneState(PLAY_SCENE);
	//});
	//
	//m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
	//{
	//	m_pStartButton->setAlpha(128);
	//});

	//m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
	//{
	//	m_pStartButton->setAlpha(255);
	//});
	//addChild(m_pStartButton);

	//
}

