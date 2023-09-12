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
}

void TitleScene::Update()
{
	Player::GetInstance()->Update();

	for (int i = 0; i < 3; i++) {
		if (ColliderManager::GetInstance()->CircleCol(Player::GetInstance()->GetPos(0), 30, Vector2{ gameStartUI.x + (100 * i), gameStartUI.y }, 48)) {
			isChangeStart = true;
			PlaySoundMem(startSE, DX_PLAYTYPE_BACK, true);
		}
	}

	//�}�E�X�̏ꏊ�擾
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

	//�V�[���؂�ւ��G�t�F�N�g
	if (isChangeStart) {
		timer++;

		for (int i = 0; i < BUBBLE_SUM; i++) {
			bubblePos[i] = bubblePos[i].lerp(start[i], end[i], Easing::EaseIn(timer, maxTimer));
			size[i] -= 1.5f;
			size[i] = max(size[i], 0);
		}

		titleUI.y -= 30;
		gameStartUI.y -= 60;
		startUIRot_++;
	}
	
	//�V�[���؂�ւ�
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


	for (int i = 0; i < 3; i++) {
		DrawCircle(gameStartUI.x + (100 * i), gameStartUI.y, 48, GetColor(255, 255, 255), true);
	}

	DrawRotaGraph(gameStartUI.x + 90, gameStartUI.y, 0.5, startUIRot_, gameStartImage, true);
	
	DrawRotaGraph3(mouseUI.x + 20, mouseUI.y-10, -startUISize_ ,-startUISize_ , 0.5, 0.5, 0, fukidasiImage, true);
	if (state_) {
		DrawRotaGraph3(mouseUI.x + 120, mouseUI.y + 80, -startUISize_, -startUISize_, 0.25, 0.25, 0, mouseImage[0], true);
	}
	else {
		DrawRotaGraph3(mouseUI.x + 120, mouseUI.y + 80, -startUISize_, -startUISize_, 0.25, 0.25, 0, mouseImage[1], true);
	}
	
	DrawFormatString(0, 0, GetColor(255, 255, 255), "title");
}
