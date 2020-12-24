#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "SoundManager.h"
#include "Util.h"
#include "imgui.h"
#include "imgui_sdl.h"

PlayScene::PlayScene()
{
	PlayScene::start();

	/*m_pPool = new BulletPool(10);*/
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();

	
}

void PlayScene::update()
{
	updateDisplayList();

	if (SDL_GetTicks() - bulletSpawnTimerStart >= bulletSpawnTimerDuration)
	{
		SpawnBullet();
	}

	if (m_pPlayer->getTransform()->position.x < 0.0f)
	{
		m_pPlayer->getTransform()->position.x = 0.0f;
		m_pPlayer->getRigidBody()->velocity.x = 0.0f;
	}
	else if (m_pPlayer->getTransform()->position.x > Config::SCREEN_WIDTH)
	{
		m_pPlayer->getTransform()->position.x = Config::SCREEN_WIDTH;
		m_pPlayer->getRigidBody()->velocity.x = 0.0f;
	}
	if (m_pPlayer->getTransform()->position.y < 0.0f)
	{
		m_pPlayer->getTransform()->position.y = 0.0f;
		m_pPlayer->getRigidBody()->velocity.y = 0.0f;
	}
	else if (m_pPlayer->getTransform()->position.y > Config::SCREEN_HEIGHT)
	{
		m_pPlayer->getTransform()->position.y = Config::SCREEN_HEIGHT;
		m_pPlayer->getRigidBody()->velocity.y = 0.0f;
	}

	vector<Bullet*>& activeBullets = m_pPool->active;
	for (vector<Bullet*>::iterator myiter = activeBullets.begin(); myiter != activeBullets.end(); ++myiter)
	{

		Bullet* bullet = *myiter;
		if (bullet->getTransform()->position.y >= Config::SCREEN_HEIGHT)
		{
			m_pPool->DeSpawn(bullet);
			break;
			/*active.at(i) == active.back();
			active.pop_back();*/
		}
		if (bullet->isColliding(m_pPlayer))
		{
			SoundManager::Instance().playSound("Explosion", 0);
		}
	}
	/*if (bullet->isColliding(m_pPlayer))
	{
		SoundManager::Instance().playSound("hit", 0, 1);
	}*/
	//bulletSpawnTimer += 

	//std::string labelText = "";
	//if (m_pPlayer->isColliding(m_pEnemy)) {
	//	labelText = "HIT";
	//}
	//else {
	//	labelText = "Distance = " + std::to_string(m_pPlayer->getDistance(m_pEnemy));
	//}

	//m_pDistanceLabel->setText(labelText);
	//
	////std::string velocityText = std::to_string(magnitude);
	//
	//m_pVelocityLabel->setText("Velocity = " + std::to_string(Util::magnitude(m_pPlayer->getRigidBody()->velocity)));
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		m_pPlayer->moveLeft();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		m_pPlayer->moveRight();
	}

	else {
		m_pPlayer->stopMovingX();
	}
	
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W)) {
		m_pPlayer->moveUp();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S)) {
		m_pPlayer->moveDown();
	}

	else {
		m_pPlayer->stopMovingY();
	}
	
	
	
	/*else {
		m_pPlayer->stopMoving();
	}
	*/

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}
}

void PlayScene::start()
{
	//Background Sprite
	background = new Background();
	addChild(background);
	SoundManager::Instance().load("../Assets/audio/Explosion.wav", "Explosion", SoundType::SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/Scene1.ogg", "scene1", SoundType::SOUND_MUSIC);
	SoundManager::Instance().playMusic("scene1");
	Mix_VolumeMusic(MIX_MAX_VOLUME / 8);

	// Player Sprite
	m_pPlayer = new Player();
	addChild(m_pPlayer);
	
	//// Enemy Sprite
	//m_pBullet = new Bullet();
	//addChild(m_pBullet);
	m_pPool = new BulletPool(10);
	bulletSpawnTimerStart = SDL_GetTicks();

	// Restart Button
	m_pRestartButton = new Button("../Assets/textures/restartButton.png", "restartButton", RESTART_BUTTON);
	m_pRestartButton->getTransform()->position = glm::vec2(730, Config::SCREEN_HEIGHT-getWidth()-30.0f);
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

	// Next Button
	m_pNextButton = new Button("../Assets/textures/nextButton.png", "nextButton", NEXT_BUTTON);
	m_pNextButton->getTransform()->position = glm::vec2(100, Config::SCREEN_HEIGHT - getWidth() - 30.0f);
	m_pNextButton->addEventListener(CLICK, [&]()-> void
		{
			m_pNextButton->setActive(false);
			TheGame::Instance()->changeSceneState(END_SCENE);
		});

	m_pNextButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pNextButton->setAlpha(128);
		});

	m_pNextButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pNextButton->setAlpha(255);
		});

	addChild(m_pNextButton);

	//for (int i = 0; i < 12; i++)
	//{
	//	Bullet* bullet = m_pPool->Spawn();
	//	if (bullet)
	//	{
	//		addChild(bullet);
	//		bullet->getTransform()->position = glm::vec2(rand() % 800, 0);
	//	}
	//	/*addChild(m_pPool->Spawn());*/
	//}
	//// Distance Label
	//const SDL_Color blue = { 0, 0, 255, 255 };
	//m_pDistanceLabel = new Label("Distance", "Consolas", 40, blue, glm::vec2(400.0f, 40.0f));
	//m_pDistanceLabel->setParent(this);
	//addChild(m_pDistanceLabel);

	//// Velocity Label
	//m_pVelocityLabel = new Label("Velocity", "Consolas", 40, blue, glm::vec2(400.0f, 80.0f));
	//m_pVelocityLabel->setParent(this);
	//addChild(m_pVelocityLabel);
}

void PlayScene::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Controls", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	
	ImGui::Separator();

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}

void PlayScene::SpawnBullet()
{
	Bullet* bullet = m_pPool->Spawn();
	if (bullet)
	{
		addChild(bullet);
		bullet->getTransform()->position = glm::vec2(rand() % 800, 0);
	}

	bulletSpawnTimerStart = SDL_GetTicks();
}
