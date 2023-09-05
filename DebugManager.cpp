#include "DebugManager.h"
#include "DxLib.h"
#include "Keyboard.h"

DebugManager* DebugManager::GetInstance()
{
	static DebugManager instance;

	return &instance;
}

void DebugManager::Initialize()
{
	isDebugMode_ = false;
}

void DebugManager::Update()
{
	if (Keyboard::GetInstance()->KeyTriggerPush(KEY_INPUT_P)) {
		isDebugMode_ = (isDebugMode_ + 1) % 2;
	}
}

void DebugManager::Draw()
{
	DrawFormatString(1000, 0, GetColor(255, 255, 255), "P kay = debug start");
	if (isDebugMode_) {
		DrawFormatString(1000, 20, GetColor(255, 255, 255), "debugMode Active!");
		DrawFormatString(1000, 40, GetColor(255, 255, 255), "BodyLength 1000");
	}
}
