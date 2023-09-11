#include "ScrollManager.h"
#include "Player.h"

ScrollManager* ScrollManager::GetInstance()
{
	static ScrollManager instance;

	return &instance;
}

float ScrollManager::GetScroll()
{
	float playerPos = Player::GetInstance()->GetPos(0).y;
	if (originPos_ < playerPos) {
		return 0.0f;
	}
	if (originPos_ - playerPos > STOP) {
		return STOP;
	}
	return originPos_ - playerPos;
}
