#include "Pool.h"
#include "TextureManager.h"
#include "SoundManager.h"

Pool::Pool()
{
	TextureManager::Instance()->load("../Assets/textures/Pool.png", "Pool");
	const auto size = TextureManager::Instance()->getTextureSize("Pool");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(400.0f, 300.0f);
	//m_reset();
	setType(POOL);
	/*SoundManager::Instance()->load("../../Assets/audio/Cafe.ogg", "cafe", SoundType::SOUND_MUSIC);
	SoundManager::Instance()->playMusic("cafe", -1);*/

	//SoundManager::playMusic()

}

Pool::~Pool()
{
}

void Pool::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("Pool", x, y, 0, 255, true);
}

void Pool::update()
{
}

void Pool::clean()
{
}

void Pool::m_move()
{
}

void Pool::m_checkBounds()
{
}

void Pool::m_reset()
{
}
