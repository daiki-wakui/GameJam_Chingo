#pragma once
#include "DxLib.h"
#include <memory>
#include "Shake.h"
#include "Keyboard.h"

class GameScene
{
private:

	int backImage = LoadGraph("GameAssets/Sprite/back.png");

	std::unique_ptr<Shake> shake = std::make_unique<Shake>();

	Keyboard* keyboard_ = Keyboard::GetInstance();
public:

	void Initialize();
	void Update();
	void Draw();
};

