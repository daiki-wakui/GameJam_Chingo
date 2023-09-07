#include "TitleScene.h"
#include "Player.h"
#include "Easing.h"
#include <random>

void TitleScene::Initialize()
{
	Player::GetInstance()->Initialize();

	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());

	for (int i = 0; i < BUBBLE_SUM; i++) {
		std::uniform_real_distribution<float> x(-128, 1280);
		std::uniform_real_distribution<float> y(900, 1800);

		std::uniform_real_distribution<float> randomSize(32, 256);

		bubblePos[i].x = x(engine);
		bubblePos[i].y = y(engine);
		size[i] = randomSize(engine);

		start[i] = bubblePos[i];
		end[i].x = bubblePos[i].x;
		end[i].y = bubblePos[i].y - 2000;
	}
}

void TitleScene::Update()
{
	Player::GetInstance()->Update();

	//マウスの場所取得
	GetMousePoint(&mouseX_, &mouseY_);

	emitterLeftTop.x = mouseX_ - 128;
	emitterLeftTop.y = mouseY_ - 128;
	emitterRightBotoom.x = mouseX_ + 128;
	emitterRightBotoom.y = mouseY_ + 128;

	//シーン切り替えエフェクト
	if (isChangeStart) {
		timer++;

		for (int i = 0; i < BUBBLE_SUM; i++) {
			bubblePos[i] = bubblePos[i].lerp(start[i], end[i], Easing::EaseIn(timer, maxTimer));
			size[i] -= 1.5f;
			size[i] = max(size[i], 0);
		}
	}
	
	//シーン切り替え
	if (timer >= maxTimer) {
		isChange = true;
	}
}

void TitleScene::Draw()
{
	Player::GetInstance()->Draw();

//	DrawBox(emitterLeftTop.x, emitterLeftTop.y, emitterRightBotoom.x, emitterRightBotoom.y, GetColor(255, 0, 0), false);

	for (int i = 0; i < BUBBLE_SUM; i++) {
		
		DrawExtendGraph(0 + bubblePos[i].x, 0 + bubblePos[i].y, size[i] + bubblePos[i].x, size[i] + bubblePos[i].y, bubbleImage, true);

	}
	
	DrawFormatString(0, 0, GetColor(255, 255, 255), "title");
}
