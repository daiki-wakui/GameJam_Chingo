#include "TitleScene.h"
#include "Player.h"
#include "Easing.h"
#include "ColliderManager.h"
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

	/*Player* player = Player::GetInstance();
	for (int p = 0; p < player->GetActiveBody(); p++) {
		Vector2 P = player->GetPos(p);

	}*/

	if (ColliderManager::GetInstance()->CircleCol(Player::GetInstance()->GetPos(0), 30, Vector2{500,600}, 32)) {
		int i = 0;
		i++;
	}

	//マウスの場所取得
	GetMousePoint(&mouseX_, &mouseY_);

	emitterLeftTop.x = mouseX_ - 128;
	emitterLeftTop.y = mouseY_ - 128;
	emitterRightBotoom.x = mouseX_ + 128;
	emitterRightBotoom.y = mouseY_ + 128;

	if (mouseY_ > gameStartUIRight.x && mouseY_ < gameStartUIRight.y) {
		if (mouseX_ > gameStartUILeft.x && mouseX_ <= gameStartUILeft.y) {
			
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
				isChangeStart = true;
			}
		}
	}
	

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
	Player::GetInstance()->Draw(false);

	DrawBox(gameStartUILeft.x, gameStartUIRight.x, gameStartUILeft.y, gameStartUIRight.y, GetColor(255, 255, 255), true);
	DrawGraph(gameStartUILeft.x-65, gameStartUIRight.x+20, gameStartImage, true);

//	DrawBox(emitterLeftTop.x, emitterLeftTop.y, emitterRightBotoom.x, emitterRightBotoom.y, GetColor(255, 0, 0), false);

	DrawCircle(500, 600, 32, GetColor(255, 255, 255), true);

	for (int i = 0; i < BUBBLE_SUM; i++) {
		
		DrawExtendGraph(0 + bubblePos[i].x, 0 + bubblePos[i].y, size[i] + bubblePos[i].x, size[i] + bubblePos[i].y, bubbleImage, true);

	}
	
	DrawFormatString(0, 0, GetColor(255, 255, 255), "title");
}
