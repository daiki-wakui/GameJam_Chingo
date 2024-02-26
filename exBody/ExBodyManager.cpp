#include "ExBodyManager.h"
#include "LevelManager.h"
#include "Player.h"
#include "ScrollManager.h"
#include <random>
#include "BulletManager.h"
#include "EffectManager.h"

ExBodyManager* ExBodyManager::GetInstance()
{
	static ExBodyManager instance;

	return &instance;
}

void ExBodyManager::Initialize()
{
	for (int i = 0; i < MAX_BODY; i++) {
		bodyType_[i] = NONE;
	}
	isSelect_ = false;
	for (int i = 0; i < 3; i++) {
		choice_[i] = 0;
	}

	bulletTimer_ = TIME_BULLET;
	isSet_ = false;
	isPadSelect_ = false;
	ChangeVolumeSoundMem(140, UI_Select);
}

void ExBodyManager::Update()
{
	BulletManager* bulletM = BulletManager::GetInstance();
	Player* player = Player::GetInstance();

	//パッド
	oldPadInput = padInput;
	GetJoypadXInputState(DX_INPUT_PAD1, &padInput);

	if (!isSelect_) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) || padInput.Buttons[XINPUT_BUTTON_A]) {
			isRelease = true;
		}
		else {
			isRelease = false;
		}
	}
	else {
		if (!((GetMouseInput() & MOUSE_INPUT_LEFT) || padInput.Buttons[XINPUT_BUTTON_A])) {
			isRelease = false;
		}

		if (player->GetIsUsePad()) {
			if (((padInput.Buttons[XINPUT_BUTTON_DPAD_RIGHT] && !oldPadInput.Buttons[XINPUT_BUTTON_DPAD_RIGHT])|| (padInput.ThumbLX > 10000 && oldPadInput.ThumbLX <= 10000)) && !isPadSelect_) {
				if (padSelect_ < 2) {
					padSelect_++;
				}
				isPadSelect_ = true;
			}
			else if (((padInput.Buttons[XINPUT_BUTTON_DPAD_LEFT] && !oldPadInput.Buttons[XINPUT_BUTTON_DPAD_LEFT]) || (padInput.ThumbLX < -10000 && oldPadInput.ThumbLX >= -10000)) && !isPadSelect_) {
				if (padSelect_ > 0) {
					padSelect_--;
				}
				isPadSelect_ = true;
			}
			else {
				isPadSelect_ = false;
			}
		}

		int mouseX, mouseY;
		GetMousePoint(&mouseX, &mouseY);

		if (!((GetMouseInput() & MOUSE_INPUT_LEFT) || padInput.Buttons[XINPUT_BUTTON_A]) && isSet_) {
			if (!player->GetIsUsePad()) {
				if (mouseY > 320 && mouseY < 890) {
					if (mouseX > 45 && mouseX <= 440) {
						AddBody(choice_[0] + 1);
						isSelect_ = false;
						LevelManager::GetInstance()->isSetRat(true);
						PlaySoundMem(UI_Select, DX_PLAYTYPE_BACK, true);
					}
					if (mouseX > 440 && mouseX <= 840) {
						AddBody(choice_[1] + 1);
						isSelect_ = false;
						LevelManager::GetInstance()->isSetRat(true);
						PlaySoundMem(UI_Select, DX_PLAYTYPE_BACK, true);
					}
					if (mouseX > 840 && mouseX <= 1240) {
						AddBody(choice_[2] + 1);
						isSelect_ = false;
						LevelManager::GetInstance()->isSetRat(true);
						PlaySoundMem(UI_Select, DX_PLAYTYPE_BACK, true);
					}
				}
			}
			else {
				AddBody(choice_[padSelect_] + 1);
				isSelect_ = false;
				LevelManager::GetInstance()->isSetRat(true);
				PlaySoundMem(UI_Select, DX_PLAYTYPE_BACK, true);
			}
		}

		isSet_ = false;

		if (((GetMouseInput() & MOUSE_INPUT_LEFT) || padInput.Buttons[XINPUT_BUTTON_A]) && !isRelease) {
			isSet_ = true;
		}
	}

	if (--bulletTimer_ <= 0) {
		for (int i = 0; i < 3; i++) {
			if (Player::GetInstance()->GetActiveBody() > (i + 1) * EX_BODY_SPACE) {
				if (bodyType_[i] == MAGICIAN) {
					bulletM->Pop(Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE), { 1,0 });
					bulletM->Pop(Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE), { 1,-1 });
					bulletM->Pop(Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE), { 0,-1 });
					bulletM->Pop(Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE), { -1,-1 });
					bulletM->Pop(Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE), { -1,0 });
					bulletM->Pop(Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE), { -1,1 });
					bulletM->Pop(Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE), { 0,1 });
					bulletM->Pop(Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE), { 1,1 });
				}
				else if (bodyType_[i] == GAMING) {
					EffectManager::GetInstance()->Pop(Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE));
				}
			}
		}
		bulletTimer_ = TIME_BULLET;
	}
	for (int i = 0; i < 3; i++) {
		if (Player::GetInstance()->GetActiveBody() > (i + 1) * EX_BODY_SPACE) {
			if (bodyType_[i] == GAMING) {
				EffectManager::GetInstance()->Pop(Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE));
				EffectManager::GetInstance()->Pop(Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE) + Vector2(80, 0));
				EffectManager::GetInstance()->Pop(Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE) + Vector2(-80, 0));
			}
		}
	}
}

void ExBodyManager::Draw()
{
	for (int i = 0; i < LevelManager::GetInstance()->GetLevel() - 1; i++) {
		if (Player::GetInstance()->GetActiveBody() > (i + 1) * EX_BODY_SPACE) {
			BodyDraw(i);
		}
	}


}

void ExBodyManager::LvUpDraw()
{
	if (isSelect_) {
		SelectDraw();
	}
}

void ExBodyManager::BodyDraw(int i)
{
	float angle = GetBodyAngle(i);

	switch (bodyType_[i])
	{
	case MUSCLE:
		DrawRotaGraph3(
			Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE).x,
			Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE).y + ScrollManager::GetInstance()->GetScroll(),
			384, 256, 0.45f * GetScale(), 0.45f * GetScale(), angle, muscularImage, true);
		break;
	case MAGICIAN:
		DrawRotaGraph3(
			Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE).x,
			Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE).y + ScrollManager::GetInstance()->GetScroll(),
			256, 256, 0.45f * GetScale(), 0.45f * GetScale(), angle, magicianImage, true);
		break;
	case JET:
		DrawRotaGraph3(
			Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE).x,
			Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE).y + ScrollManager::GetInstance()->GetScroll(),
			256, 256, 0.45f * GetScale(), 0.45f * GetScale(), angle, jetImage, true);
		break;
	case GAMING:
		DrawRotaGraph3(
			Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE).x,
			Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE).y + ScrollManager::GetInstance()->GetScroll(),
			256, 256, 0.45f * GetScale(), 0.45f * GetScale(), angle, gamingImage, true);
		break;
	case Shark:
		DrawRotaGraph3(
			Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE).x,
			Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE).y + ScrollManager::GetInstance()->GetScroll(),
			256, 256, 0.5f * GetScale(), 0.5f * GetScale(), angle, shakeImage, true);

		break;
	case SAKABAN:
		DrawRotaGraph3(
			Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE).x,
			Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE).y + ScrollManager::GetInstance()->GetScroll(),
			256, 256, 0.45f, 0.45f, angle, sakabanImage, true);

		break;
	default:
		break;
	}
}

void ExBodyManager::SelectRand()
{
	//ランダム
	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());

	std::uniform_real_distribution<float> x(0, END_BODY_TYPE - 2 + 0.99999f);
	choice_[0] = (int)x(engine);

	while (true)
	{
		std::uniform_real_distribution<float> y(0, END_BODY_TYPE - 2 + 0.99999f);
		choice_[1] = (int)y(engine);
		if (choice_[0] != choice_[1]) {
			break;
		}
	}

	while (true)
	{
		std::uniform_real_distribution<float> z(0, END_BODY_TYPE - 2 + 0.99999f);
		choice_[2] = (int)z(engine);
		if (choice_[0] != choice_[2] && choice_[1] != choice_[2]) {
			break;
		}
	}
}

void ExBodyManager::SelectDraw()
{
	DrawGraph(0, 0, selectBack, true);

	for (int i = 0; i < 3; i++) {
		Vector2 tempPos;
		//選択肢のポジション
		if (i == 0) {
			tempPos = { 240,600 };
		}
		else if (i == 1) {
			tempPos = { 640,600 };
		}
		else {
			tempPos = { 1040,600 };
		}

		if (choice_[i] == 0) {
			//MUSCLE
			//DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "マッスル");
			DrawRotaGraph(tempPos.x, tempPos.y, 0.6f, 0, muscularCard, true);
		}
		else if (choice_[i] == 1) {
			//MAGICIAN
			//DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "マジシャン");
			DrawRotaGraph(tempPos.x, tempPos.y, 0.6f, 0, magicianCard, true);
		}
		else if (choice_[i] == 2) {
			//JET
			//DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "ジェット");
			DrawRotaGraph(tempPos.x, tempPos.y, 0.6f, 0, jetCard, true);
		}
		else if (choice_[i] == 3) {
			//GAMING
			//DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "ゲーミング");
			DrawRotaGraph(tempPos.x, tempPos.y, 0.6f, 0, gamingCard, true);
		}
		else if (choice_[i] == 4) {
			//Shark
			//DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "シャーク");
			DrawRotaGraph(tempPos.x, tempPos.y, 0.6f, 0, shakeCard, true);
		}
		else if (choice_[i] == 5) {
			//Shark
			//DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "サカバンバスピス");
			DrawRotaGraph(tempPos.x, tempPos.y, 0.6f, 0, sakabanCard, true);
		}

		if (Player::GetInstance()->GetIsUsePad()) {
			if (padSelect_ == i) {
				DrawRotaGraph(tempPos.x, tempPos.y - 50, 1, 0, UI_Cursor, true);
			}
		}
	}
}

void ExBodyManager::ResultDraw()
{
	for (int i = 0; i < 3; i++) {
		Vector2 tempPos;

		Vector2 temptexturePos;
		//選択肢のポジション
		if (i == 0) {
			tempPos = { 540,400 };

			temptexturePos = { 640,400 };
		}
		else if (i == 1) {
			tempPos = { 640,400 };

			temptexturePos = { 640,550 };
		}
		else {
			tempPos = { 740,400 };

			temptexturePos = { 640,700 };
		}

		if (bodyType_[i] == 1) {
			//MUSCLE
			//DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "マッスル");
			DrawRotaGraph3(temptexturePos.x, temptexturePos.y,
				384, 256, 0.5f, 0.5f, 0, muscularImage, true);
		}
		else if (bodyType_[i] == 2) {
			//MAGICIAN
			//DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "マジシャン");

			DrawRotaGraph3(temptexturePos.x, temptexturePos.y,
				256, 256, 0.5f, 0.5f, 0, magicianImage, true);
			//DrawGraph(tempPos.x, tempPos.y, magicianImage, true);
		}
		else if (bodyType_[i] == 3) {
			//JET
			//DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "ジェット");
			DrawRotaGraph3(temptexturePos.x, temptexturePos.y,
				256, 256, 0.65f, 0.65f, 0, jetImage, true);
			//DrawGraph(tempPos.x, tempPos.y, jetImage, true);
		}
		else if (bodyType_[i] == 4) {
			//GAMING
			//DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "ゲーミング");
			DrawRotaGraph3(temptexturePos.x, temptexturePos.y,
				256, 256, 0.5f, 0.5f, 0, gamingImage, true);
			//DrawGraph(tempPos.x, tempPos.y, gamingImage, true);
		}
		else if (bodyType_[i] == 5) {
			//Shark
			//DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "シャーク");
			//DrawRotaGraph3(temptexturePos.x, temptexturePos.y,
			//	256, 256, 0.5f, 0.5f, 0, gamingImage, true);
			//DrawGraph(tempPos.x, tempPos.y, gamingImage, true);
		}
		else if (bodyType_[i] == 6) {
			//Shark
			//DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "サカバンバスピス");
			//DrawRotaGraph3(temptexturePos.x, temptexturePos.y,
			//	256, 256, 0.5f, 0.5f, 0, gamingImage, true);
			//DrawGraph(tempPos.x, tempPos.y, gamingImage, true);
		}
	}
	//DrawFormatString(840, 400, GetColor(255, 255, 255), "チンアナゴ～！");
}

void ExBodyManager::AddBody(int num)
{
	bodyType_[LevelManager::GetInstance()->GetLevel() - 2] = num;
	switch (num)
	{
	case MUSCLE:
		Player::GetInstance()->AddHang(100);
		break;
	case JET:
		Player::GetInstance()->AddBodySpace(2);
		break;
	case GAMING:
		Player::GetInstance()->AddSpeedNeck(2);
		break;
	case SAKABAN:
		Player::GetInstance()->SetSakaban();
		break;
	default:
		break;
	}
}

void ExBodyManager::SetIsSelect()
{
	isSelect_ = true;
	padSelect_ = 1;
	SelectRand();
}

float ExBodyManager::GetBodyAngle(int i)
{
	float temp = 3.141592f / 180.0f * Player::GetInstance()->GetAngle((i + 1) * EX_BODY_SPACE);

	temp -= 3.14192f;

	return temp;
}

float ExBodyManager::GetScale()
{
	switch (LevelManager::GetInstance()->GetLevel())
	{
	case 2:
		return 1.2f;
	case 3:
		return 1.4f;
	case 4:
		return 1.6f;
	default:
		return 1.0f;
	}
}
