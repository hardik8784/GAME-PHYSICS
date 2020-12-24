#include "Crate.h"

Crate::Crate(glm::vec2 Position)
{
	TextureManager::Instance()->load("../Assets/textures/mine.png", "crate");

	const auto size = TextureManager::Instance()->getTextureSize("crate");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = Position;
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(CRATE);
	setEnabled(true);
}

Crate::~Crate() = default;

void Crate::draw()
{
	if (isEnabled()) {
		// alias for x and y
		const auto x = getTransform()->Position.x;
		const auto y = getTransform()->Position.y;

		// draw the target
		TextureManager::Instance()->draw("crate", x, y, 0, 255, false);
	}
}

void Crate::update()
{
	if (isEnabled()) {

		getRigidBody()->Velocity += getRigidBody()->acceleration * Constant::DeltaTime;

		getTransform()->Position += getRigidBody()->Velocity * Constant::DeltaTime;

	}
}

void Crate::clean()
{

}

void Crate::reset(glm::vec2 Position)
{
	getTransform()->Position = Position;
	StopMoving();
}

void Crate::StopMoving()
{
	getRigidBody()->acceleration = glm::vec2(0.0f);
	getRigidBody()->Velocity = glm::vec2(0.0f);
}


