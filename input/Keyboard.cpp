#include "Keyboard.h"

Keyboard* Keyboard::GetInstance()
{
	static Keyboard instance;

	return &instance;
}

void Keyboard::Update()
{
	// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
	for (int i = 0; i < 256; ++i)
	{
		oldkeys[i] = keys[i];
	}
	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);
}

bool Keyboard::KeyPush(INT16 key)
{
	if (keys[key]) {
		return true;
	}
	return false;
}

bool Keyboard::KeyTriggerPush(INT16 key)
{
	if (keys[key] && !oldkeys[key]) {
		return true;
	}

	return false;
}

bool Keyboard::KeyRelease(INT16 key)
{
	if (!keys[key]) {
		return true;
	}

	return false;
}

bool Keyboard::KeyTriggerRelease(INT16 key)
{
	if (!keys[key] && oldkeys[key]) {
		return true;
	}

	return false;
}
