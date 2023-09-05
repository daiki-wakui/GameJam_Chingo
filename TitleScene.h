#pragma once
#include "DxLib.h"
#include "Player.h"
#include <memory>

class TitleScene
{
private:

	//playerクラス初期化
	std::unique_ptr<Player> player = std::make_unique<Player>();
	

public:

	void Initialize();
	void Update();
	void Draw();
};

