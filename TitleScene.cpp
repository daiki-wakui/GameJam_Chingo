#include "TitleScene.h"
#include "Player.h"
#include "Easing.h"
#include "ColliderManager.h"
#include <random>

void TitleScene::Initialize()
{
	Player::GetInstance()->Initialize();
	ColliderManager::GetInstance()->Initialize();

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

	frame_[0] = 0;
	frame_[1] = 0;
	isChangeStart = false;
	timer = 0;
	titleUI = { 0,0 };
	gameStartUI = { 550,500 };
	startUIRot_ = 0;
	isChange = false;

	ChangeVolumeSoundMem(128, startSE);
	mouseImage[0] = LoadGraph("GameAssets/Sprite/mouseUI.png");
	mouseImage[1] = LoadGraph("GameAssets/Sprite/mouseUI2.png");

	anagoImage[0] = LoadGraph("GameAssets/Sprite/anago1.png");
	anagoImage[1] = LoadGraph("GameAssets/Sprite/anago2.png");

	startAnago[0] = { -110,1400 };
	startAnago[1] = { -110 + 330,1200 };
	startAnago[2] = { -110 + 330 * 2,1000 };
	startAnago[3] = { -110 + 330 * 3,1500 };

	endAnago[0] = { -110,-250 };
	endAnago[1] = { -110 + 330,-250 };
	endAnago[2] = { -110 + 330 * 2,-250 };
	endAnago[3] = { -110 + 330 * 3,-250 };

	feadAlpha = 255;
}

void TitleScene::Update()
{
	Player::GetInstance()->Update();
	Player::GetInstance()->SetIsGamescene(false);

	if (backResult) {
		feadAlpha -= 5;
		feadAlpha = max(feadAlpha, 0);

	}
	
	for (int i = 0; i < 3; i++) {
		if (ColliderManager::GetInstance()->CircleCol(Player::GetInstance()->GetPos(0), 30, Vector2{ gameStartUI.x + (100 * i), gameStartUI.y }, 48)) {
			isChangeStart = true;
			PlaySoundMem(startSE, DX_PLAYTYPE_BACK, true);
		}
	}

	//マウスの場所取得
	GetMousePoint(&mouseX_, &mouseY_);

	frame_[0]++;
	frame_[1]++;

	if (frame_[1] >= 60) {
		if (state_ == 0) {
			state_ = 1;
		}
		else {
			state_ = 0;
		}
		frame_[1] = 0;
	}

	startUISize_ = 0.5f * sinf(2 * 3.14f * frame_[0] / 200) + startUISize_;
	titleUI.y = 0.25f * sinf(2 * 3.14f * frame_[0] / 200) + titleUI.y;
	gameStartUI.y = 0.25f * sinf(2 * 3.14f * frame_[0] / 200) + gameStartUI.y;

	//シーン切り替えエフェクト
	if (isChangeStart) {
		timer++;

		for (int i = 0; i < BUBBLE_SUM; i++) {
			bubblePos[i] = bubblePos[i].lerp(start[i], end[i], Easing::EaseIn(timer, maxTimer));
			size[i] -= 1.5f;
			size[i] = max(size[i], 0);
		}

		AnagoPos[0] = AnagoPos[0].lerp(startAnago[0], endAnago[0], Easing::EaseOutCubic(timer, 60));
		AnagoPos[1] = AnagoPos[1].lerp(startAnago[1], endAnago[1], Easing::EaseOutCubic(timer, 60));
		AnagoPos[2] = AnagoPos[2].lerp(startAnago[2], endAnago[2], Easing::EaseOutCubic(timer, 60));
		AnagoPos[3] = AnagoPos[3].lerp(startAnago[3], endAnago[3], Easing::EaseOutCubic(timer, 60));

		titleUI.y -= 30;
		gameStartUI.y -= 60;
		startUIRot_++;
	}
	else {
		AnagoPos[0] = { -1200,0 };
		AnagoPos[1] = { -1200,0 };
		AnagoPos[2] = { -1200,0 };
		AnagoPos[3] = { -1200,0 };
	}
	
	//シーン切り替え
	if (timer >= maxTimer) {
		isChange = true;
	}
}

void TitleScene::Draw()
{
	DrawGraph(-40, -180, backBottomImage, true);


	for (int i = 0; i < BUBBLE_SUM; i++) {
		DrawExtendGraph(0 + bubblePos[i].x, 0 + bubblePos[i].y, size[i] + bubblePos[i].x, size[i] + bubblePos[i].y, bubbleImage, true);
	}

	
	DrawGraph(0, 0, blueImage, true);
	DrawGraph(0, 0, vignetImage, true);

	DrawRotaGraph(titleUI.x + 1280 / 2+50, titleUI.y + 550 / 2, 0.75, startUIRot_, titleImage, true);


	Player::GetInstance()->Draw(false);

	DrawGraph(555, 700, moleImage, true);


	//for (int i = 0; i < 3; i++) {
	//	DrawCircle(gameStartUI.x + (100 * i), gameStartUI.y, 48, GetColor(255, 255, 255), true);
	//}

	DrawRotaGraph(gameStartUI.x + 90, gameStartUI.y, 0.5, startUIRot_, gameStartImage, true);
	
	DrawRotaGraph3(mouseUI.x + 20, mouseUI.y-10, -startUISize_ ,-startUISize_ , 0.5, 0.5, 0, fukidasiImage, true);
	if (state_) {
		DrawRotaGraph3(mouseUI.x + 120, mouseUI.y + 80, -startUISize_, -startUISize_, 0.25, 0.25, 0, mouseImage[0], true);
	}
	else {
		DrawRotaGraph3(mouseUI.x + 120, mouseUI.y + 80, -startUISize_, -startUISize_, 0.25, 0.25, 0, mouseImage[1], true);
	}

	DrawGraph(AnagoPos[0].x, AnagoPos[0].y, anagoImage[0], true);
	DrawGraph(AnagoPos[1].x, AnagoPos[1].y, anagoImage[1], true);
	DrawGraph(AnagoPos[2].x, AnagoPos[2].y, anagoImage[0], true);
	DrawGraph(AnagoPos[3].x, AnagoPos[3].y, anagoImage[1], true);
	
	if (backResult) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, feadAlpha);
		DrawBox(0, 0, 1280, 900, GetColor(255, 250, 220), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	//DrawFormatString(0, 0, GetColor(255, 255, 255), "title");
}
