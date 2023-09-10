#include "LevelManager.h"
#include "Player.h"

LevelManager* LevelManager::GetInstance()
{
	static LevelManager instance;

	return &instance;
}

void LevelManager::Initialize()
{
	nowLevel_ = 1;
	nextExp_ = EXP_LV1;
	nowExp_ = 0;
	haveExp_ = 0;

	for (int i = 0; i < 3; i++) {
		haveExpGaugeXRight_[i] = 0;
		nowExpGaugeXRight_[i] = 0;
	}

	levelImage[0] = LoadGraph("GameAssets/Sprite/level1.png");
	levelImage[1] = LoadGraph("GameAssets/Sprite/level2.png");
	levelImage[2] = LoadGraph("GameAssets/Sprite/level3.png");
}

void LevelManager::Update()
{
	Player* player = Player::GetInstance();

	//���x���Ǘ�
	if (nowExp_ >= EXP_LV3) {
		nowLevel_ = 4;
		nextExp_ = 0;
		player->SetThickness(BODY_THICKNESS_LV4);
	}
	else if (nowExp_ >= EXP_LV2) {
		nowLevel_ = 3;
		nextExp_ = EXP_LV3;
		player->SetThickness(BODY_THICKNESS_LV3);
	}
	else if (nowExp_ >= EXP_LV1) {
		nowLevel_ = 2;
		nextExp_ = EXP_LV2;
		player->SetThickness(BODY_THICKNESS_LV2);
	}

	//�����Ă�a�̃Q�[�W����(����)
	if (nowLevel_ == 1) {
		haveExpGaugeXRight_[0] = haveExp_ * 12;
	}
	if (nowLevel_ == 2) {
		haveExpGaugeXRight_[1] = haveExp_ * 3;
	}
	if (nowLevel_ == 3) {
		haveExpGaugeXRight_[2] = haveExp_ * 1.7f;
	}

	//�L�ё����Ă�ԂɎ��̃��x���ɂȂ������̗�O����
	if (nowLevel_ == 1 && GetNowAndHaveExp() >= 100) {
		haveExpGaugeXRight_[1] = (GetNowAndHaveExp() - 100) * 3;
		haveExpGaugeXRight_[0] = 1200 - nowExpGaugeXRight_[0];
	}
	if (nowLevel_ == 2 && GetNowAndHaveExp() >= 500) {
		haveExpGaugeXRight_[2] = (GetNowAndHaveExp() - 500);
		haveExpGaugeXRight_[1] = 1200 - nowExpGaugeXRight_[1];
	}

	
	for (int i = 0; i < 3; i++) {
		//���x���A�b�v�܂ł̎c��Q�[�W
		restGrauge[i] = GaugeLength - nowExpGaugeXRight_[i];

		//�Q�[�W�����܂肫������\�����Ȃ�
		if (restGrauge[i] <= 0) {
			haveExpGaugeXRight_[i] = 0;
		}
	}

	if (nowLevel_ == 2) {
		nowExpGaugeXRight_[0] = nowExpGaugeXLeft_[0];
	}
	if (nowLevel_ == 3) {
		nowExpGaugeXRight_[1] = nowExpGaugeXLeft_[1];
	}
}

void LevelManager::Draw()
{
	//�Q�[�W�̘g
	DrawBox(40, 830, 1240, 880, GetColor(16, 16, 103), true);
	DrawBox(40, 830, 1240, 880, GetColor(0, 0, 0), false);

	//���܂��Ă�Q�[�W�̕`�惌�x��1,2,3
	DrawBox(nowExpGaugeXLeft_[0], 830, nowExpGaugeXRight_[0] + 40, 880, GetColor(46, 104, 214), true);
	DrawBox(nowExpGaugeXLeft_[1], 830, nowExpGaugeXRight_[1] + 40, 880, GetColor(46, 104, 214), true);
	DrawBox(nowExpGaugeXLeft_[2], 830, nowExpGaugeXRight_[2] + 40, 880, GetColor(46, 104, 214), true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	//�����Q�[�W�̕`�惌�x��1,2,3
	DrawBox(haveExpGaugeXLeft_[0] + nowExpGaugeXRight_[0], 830, haveExpGaugeXRight_[0] + nowExpGaugeXRight_[0] + 40, 880, GetColor(46, 104, 214), true);
	DrawBox(haveExpGaugeXLeft_[1] + nowExpGaugeXRight_[1], 830, haveExpGaugeXRight_[1] + nowExpGaugeXRight_[1] + 40, 880, GetColor(46, 104, 214), true);
	DrawBox(haveExpGaugeXLeft_[2] + nowExpGaugeXRight_[2], 830, haveExpGaugeXRight_[2] + nowExpGaugeXRight_[2] + 40, 880, GetColor(46, 104, 214), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	
	//���݂̃��x���\��
	for (int i = 0; i < 3; i++) {
		if (nowLevel_ == i + 1) {
			DrawExtendGraph(1100, 790, 128+1100, 128+790, levelImage[i], true);
		}
	}

	//���x���A�b�v�\�\��
	if (nowLevel_ == 1 && GetNowAndHaveExp() >= 100 || nowLevel_ == 2 && GetNowAndHaveExp() >= 500) {
		DrawExtendGraph(1100, 700, 128 + 1100, 128 + 700, levelUpImage, true);
	}
	

	DrawFormatString(0,80,GetColor(255,255,255),"nowLevel = %d",nowLevel_);
	DrawFormatString(0, 100, GetColor(255, 255, 255), "haveExp_ = %d",haveExp_);
	DrawFormatString(0, 120, GetColor(255, 255, 255), "nowExp_ = %d / %d", nowExp_,nextExp_);
}

void LevelManager::IncludeExp()
{
	nowExp_ += haveExp_;

	//���x��1�̃Q�[�W����
	if (nowLevel_ == 1) {
		nowExpGaugeXRight_[0] += haveExp_ * 12;
		nowExpGaugeXRight_[0] = min(nowExpGaugeXRight_[0], 1200);
	}

	//���x��2�̃Q�[�W����
	if (nowLevel_ == 2) {
		nowExpGaugeXRight_[1] += haveExp_ * 3;

		if (nowExpGaugeXRight_[1] >= 1200) {
			nowExpGaugeXRight_[1] = 1200;
		}
	}
	else if (nowLevel_ == 1 && nowExp_ >= 100) {
		nowExpGaugeXRight_[1] += (nowExp_ - 100) * 3;
	}

	//���x��3�̃Q�[�W����
	if (nowLevel_ == 3) {
		nowExpGaugeXRight_[2] += haveExp_ * 1.7f;

		if (nowExpGaugeXRight_[2] >= 1200) {
			nowExpGaugeXRight_[2] = 1200;
		}
	}
	else if (nowLevel_ == 2 && nowExp_ >= 500) {
		nowExpGaugeXRight_[2] += (nowExp_ - 500);
	}

	if (nowLevel_ == 4) {
		nowExpGaugeXRight_[2] = 1200;
	}

	haveExp_ = 0;
	Update();
}

void LevelManager::GetMax()
{
	Player* player = Player::GetInstance();

	if (nowExp_ >= EXP_LV3) {
		player->SetMaxLength(HANG_LV4);
	}
	else if (nowExp_ >= EXP_LV2) {
		player->SetMaxLength(HANG_LV3);
	}
	else if (nowExp_ >= EXP_LV1) {
		player->SetMaxLength(HANG_LV2);
	}
	else {
		player->SetMaxLength(HANG_LV1);
	}
}

void LevelManager::Debug()
{
	if (nowLevel_ == 1) {
		nowExp_ += EXP_LV1;
	}
	else if (nowLevel_ == 2) {
		nowExp_ += EXP_LV2;
	}
	else if (nowLevel_ == 3) {
		nowExp_ += EXP_LV3;
	}
}

