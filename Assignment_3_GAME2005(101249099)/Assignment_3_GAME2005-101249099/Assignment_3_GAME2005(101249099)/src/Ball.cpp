#include "Ball.h"
#include "TextureManager.h"

Ball::Ball()
{
	TextureManager::Instance()->load("../Assets/textures/8Ball.png", "ball");
	const auto size = TextureManager::Instance()->getTextureSize("ball");
	setWidth(size.x);
	setHeight(size.y);
	m_reset();

	//getTransform()->position = glm::vec2(400.0f, 200.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(BALL);
}

Ball::~Ball()
{
}

void Ball::draw()
{
		// alias for x and y
		const auto x = getTransform()->position.x;
		const auto y = getTransform()->position.y;

		TextureManager::Instance()->draw("ball", x, y, 0, 255, true);
}

void Ball::update()
{
	m_move();
	m_checkBounds();

	float deltaTime = 1.0f / 60.0f;
	getRigidBody()->velocity += getRigidBody()->acceleration * deltaTime;
	getTransform()->position += getRigidBody()->velocity * deltaTime;
}

void Ball::clean()
{
}

void Ball::collisionResponse(float CheckBounds, glm::vec2 Position, float velocity)
{
	float deltaTime = 1.0f / 60.0f;
	float ExitPoint;

	if (Position.y > 0.0f) 
	{
		if (getRigidBody()->velocity.x > 0.0f)	
		{
			ExitPoint = getTransform()->position.x + (getWidth() * 0.5f) - CheckBounds;
		}
		else									
		{
			ExitPoint = CheckBounds + getTransform()->position.x - (getWidth() * 0.5f);
		}
		glm::vec2 ChangePos = getRigidBody()->velocity * deltaTime;
		float ChangeDirection = (ExitPoint / ChangePos.x) * 1.0f;
		ChangePos.x *= ChangeDirection;
		ChangePos.y *= ChangeDirection;

		getTransform()->position -= ChangePos;
	}
	if (Position.x > 0.0f)
	{
		if (getRigidBody()->velocity.y > 0.0f)	
		{
			ExitPoint = getTransform()->position.y + (getHeight() * 0.5f) - CheckBounds;
		}
		else									
		{
			ExitPoint = CheckBounds + getTransform()->position.y - (getHeight() * 0.5f);
		}
		
		glm::vec2 ChangePos = getRigidBody()->velocity * deltaTime;
		float ChangeDirection = (ExitPoint / ChangePos.y) * 1.1f;
		ChangePos.x *= ChangeDirection;
		ChangePos.y *= ChangeDirection;

		
		getTransform()->position -= ChangePos;
	}
	getRigidBody()->velocity *= Position;
}

bool Ball::isColliding(GameObject* pOther)
{
	float myRadius = getWidth() * 0.5f;
	float otherRadius = pOther->getWidth() * 0.5f;

	return (getDistance(pOther) <= myRadius + otherRadius);
}

float Ball::getDistance(GameObject* pOther)
{
	glm::vec2 myPos = getTransform()->position;
	glm::vec2 otherPos = pOther->getTransform()->position;

	// Use pythagorean to calculate distance c = sqrt(a^2 + b^2)
	float a = myPos.x - otherPos.x;
	float b = myPos.y - otherPos.y;
	return sqrt(a * a + b * b);
}

void Ball::m_move()
{
	getTransform()->position = getTransform()->position + getRigidBody()->velocity * 0.5f;
}

void Ball::m_checkBounds()
{
	
}

void Ball::m_reset()
{
	/*int HalfWidth = Config::SCREEN_WIDTH / 2;
	int HalfHeight = Config::SCREEN_HEIGHT / 2;
	int xinitialpos = rand() % (Config::SCREEN_WIDTH - getWidth()) + HalfWidth;
	int yinitalpos = rand() % (Config::SCREEN_HEIGHT - getHeight()) + HalfHeight;
	getTransform()->position = glm::vec2(xinitialpos, yinitalpos);

	int xInitialVelocity = rand() % 20 - 10;
	int yInitialVelocity = rand() % 20 - 10;
	getRigidBody()->velocity = glm::vec2(xInitialVelocity, yInitialVelocity);*/
	
}
