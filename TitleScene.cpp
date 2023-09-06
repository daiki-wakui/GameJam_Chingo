#include "TitleScene.h"
#include "Player.h"
#include <random>

void TitleScene::Initialize()
{
	Player::GetInstance()->Initialize();

	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());

	for (int i = 0; i < BUBBLE_SUM; i++) {
		std::uniform_real_distribution<float> x(-128, 1280);
		std::uniform_real_distribution<float> y(900, 1800);

		std::uniform_real_distribution<float> randomSize(32, 128);

		bubblePos[i].x = x(engine);
		bubblePos[i].y = y(engine);
		size[i] = randomSize(engine);
	}
}

void TitleScene::Update()
{
	Player::GetInstance()->Update();

	//ƒ}ƒEƒX‚ÌêŠæ“¾
	GetMousePoint(&mouseX_, &mouseY_);

	emitterLeftTop.x = mouseX_ - 128;
	emitterLeftTop.y = mouseY_ - 128;
	emitterRightBotoom.x = mouseX_ + 128;
	emitterRightBotoom.y = mouseY_ + 128;

	for (int i = 0; i < BUBBLE_SUM; i++) {
		bubblePos[i].y -= 20;
	}
}

void TitleScene::Draw()
{
	Player::GetInstance()->Draw();

//	DrawBox(emitterLeftTop.x, emitterLeftTop.y, emitterRightBotoom.x, emitterRightBotoom.y, GetColor(255, 0, 0), false);
	
	//DrawGraph(0, 0, bubbleImage, true);
	for (int i = 0; i < BUBBLE_SUM; i++) {
		
		DrawExtendGraph(0 + bubblePos[i].x, 0 + bubblePos[i].y, size[i] + bubblePos[i].x, size[i] + bubblePos[i].y, bubbleImage, true);

	}
	
	DrawFormatString(0, 0, GetColor(255, 255, 255), "title");
}
