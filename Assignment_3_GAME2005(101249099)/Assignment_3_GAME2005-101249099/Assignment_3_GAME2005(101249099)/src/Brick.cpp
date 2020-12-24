#include "Brick.h"
#include "TextureManager.h"
#include "Game.h"
#include "SoundManager.h"

Brick::Brick()
{
	TextureManager::Instance()->load("../Assets/textures/Brick.png", "brick");
	const auto size = TextureManager::Instance()->getTextureSize("brick");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(400.0f, 550.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	
	//int halfWidth = getWidth()/2;
	//int halfHeight = getHeight()/2;
	////glm::vec2 m_initialposition = getTransform()->position;
	////m_initialposition.x = Config::SCREEN_HEIGHT / 2 /*- halfHeight*/;
	////m_initialposition.y = Config::SCREEN_WIDTH / 2 /*- halfWidth*/;
	//glm::vec2 m_initialposition(Config::SCREEN_HEIGHT/2 -halfHeight,Config::SCREEN_WIDTH/2-halfWidth);
	//getTransform()->position= m_previousposition = m_initialposition;
	//m_previousposition = m_initialposition;
	setType(BRICK);

	//SoundManager::allocateChannels(2);
	//SoundManager::Instance()->load("../../Assets/audio/points.wav", "points");
	//SoundManager::Instance()->load("../../Assets/audio/points.wav", "points", SoundType::SOUND_SFX);

	//load("../../Assets/audio/points.wav", "points", SoundType::SOUND_SFX);
}

Brick::~Brick()
{
}

void Brick::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("brick", x, y, 0, 255, true);
}

void Brick::update()
{
	m_move();
	m_checkBounds();
}

void Brick::clean()
{
}

bool Brick::isColliding(GameObject* pOther)
{
	float myRadius = getWidth() * 0.5f;
	float otherRadius = pOther->getWidth() * 0.5f;

	return (getDistance(pOther) <= myRadius + otherRadius);
}

float Brick::getDistance(GameObject* pOther)
{
	glm::vec2 myPos = getTransform()->position;
	glm::vec2 otherPos = pOther->getTransform()->position;

	// Use pythagorean to calculate distance c = sqrt(a^2 + b^2)
	float a = myPos.x - otherPos.x;
	float b = myPos.y - otherPos.y;
	return sqrt(a * a + b * b);
}

void Brick::m_move()
{
	/*glm::vec2 mouseVector = TheGame::Instance()->getMousePosition();
	getTransform()->position = glm::vec2(mouseVector.x, mouseVector.y);*/
}

void Brick::m_checkBounds()
{
	if (getTransform()->position.x < 0.0f)
	{
		getTransform()->position.x = 0.0f;
		getRigidBody()->velocity.x = 0.0f;
	}
	else if (getTransform()->position.x > Config::SCREEN_WIDTH)
	{
		getTransform()->position.x = 800.0f;
		getRigidBody()->velocity.x = 0.0f;
	}
	if (getTransform()->position.y < 0.0f)
	{
		getTransform()->position.y = 0.0f;
		getRigidBody()->velocity.y = 0.0f;
	}
	else if (getTransform()->position.y > Config::SCREEN_HEIGHT)
	{
		getTransform()->position.y = 600.0f;
		getRigidBody()->velocity.y = 0.0f;
	}

}

void Brick::m_reset()
{
}
