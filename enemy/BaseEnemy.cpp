#include "BaseEnemy.h"

void BaseEnemy::Initialize(Vector2 pos)
{
	pos_ = pos;
	isDead_ = false;
}

Vector2 BaseEnemy::Col(int num)
{
	return Vector2(-10000, 0);
}
