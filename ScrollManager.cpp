#include "ScrollManager.h"

ScrollManager* ScrollManager::GetInstance()
{
	static ScrollManager instance;

	return &instance;
}

float ScrollManager::GetScroll()
{
	return 0.0f;
}
