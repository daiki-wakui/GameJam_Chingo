#include "ExBodyManager.h"
#include "LevelManager.h"
#include "Player.h"
#include "ScrollManager.h"
#include <random>
#include "BulletManager.h"

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
}

void ExBodyManager::Update()
{
	BulletManager* bulletM = BulletManager::GetInstance();

	if (!isSelect_) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			isRelease = true;
		}
		else {
			isRelease = false;
		}
	}
	else {
		if (!((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {
			isRelease = false;
		}


		int mouseX, mouseY;
		GetMousePoint(&mouseX, &mouseY);

		if (!((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) && isSet_) {
			if (mouseY > 320 && mouseY < 680) {
				if (mouseX > 100 && mouseX <= 380) {
					AddBody(choice_[0] + 1);
					isSelect_ = false;
					LevelManager::GetInstance()->isSetRat(true);

				}
				if (mouseX > 500 && mouseX <= 780) {
					AddBody(choice_[1] + 1);
					isSelect_ = false;
					LevelManager::GetInstance()->isSetRat(true);

				}
				if (mouseX > 900 && mouseX <= 1180) {
					AddBody(choice_[2] + 1);
					isSelect_ = false;
					LevelManager::GetInstance()->isSetRat(true);

				}
			}
		}

		isSet_ = false;

		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && !isRelease) {
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
			}
		}
		bulletTimer_ = TIME_BULLET;
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
		//DrawBox(100, 320, 380, 680, GetColor(255, 0, 0), true);
		//DrawBox(500, 320, 780, 680, GetColor(0, 255, 0), true);
		//DrawBox(900, 320, 1180, 680, GetColor(0, 0, 255), true);
		SelectDraw();
	}
}

void ExBodyManager::BodyDraw(int i)
{
	float angle = GetBodyAngle(i);

	switch (bodyType_[i])
	{
	case MUSCLE:
		//DrawCircle(Player::GetInstance()->GetPos((i + 1) * 10), 55, GetColor(255, 0, 0));

		DrawRotaGraph3(
			Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE).x,
			Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE).y + ScrollManager::GetInstance()->GetScroll(),
			384, 256, 0.45f * GetScale(), 0.45f * GetScale(), angle, muscularImage, true);
		break;
	case MAGICIAN:
		//DrawCircle(Player::GetInstance()->GetPos((i + 1) * 10), 55, GetColor(0, 255, 0));

		DrawRotaGraph3(
			Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE).x,
			Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE).y + ScrollManager::GetInstance()->GetScroll(),
			256, 256, 0.45f * GetScale(), 0.45f * GetScale(), angle, magicianImage, true);
		break;
	case JET:
		//DrawCircle(Player::GetInstance()->GetPos((i + 1) * 10), 55, GetColor(0, 0, 255));

		DrawRotaGraph3(
			Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE).x,
			Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE).y + ScrollManager::GetInstance()->GetScroll(),
			256, 256, 0.45f * GetScale(), 0.45f * GetScale(), angle, jetImage, true);
		break;
	case GAMING:
		//DrawCircle(Player::GetInstance()->GetPos((i + 1) * 10), 55, GetColor(0, 0, 255));

		DrawRotaGraph3(
			Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE).x,
			Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE).y + ScrollManager::GetInstance()->GetScroll(),
			256, 256, 0.45f * GetScale(), 0.45f * GetScale(), angle, gamingImage, true);
		break;
	case Shark:
		//DrawCircle(Player::GetInstance()->GetPos((i + 1) * 10), 80, GetColor(0, 0, 255));
		DrawRotaGraph3(
			Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE).x,
			Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE).y + ScrollManager::GetInstance()->GetScroll(),
			256, 256, 0.5f * GetScale(), 0.5f * GetScale(), angle, shakeImage, true);

		break;
	case SAKABAN:
		DrawCircle(Player::GetInstance()->GetPos((i + 1) * 10), 80, GetColor(0, 0, 255));
		/*DrawRotaGraph3(
			Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE).x,
			Player::GetInstance()->GetPos((i + 1) * EX_BODY_SPACE).y + ScrollManager::GetInstance()->GetScroll(),
			256, 256, 0.45f, 0.45f, angle, shakeImage, true);*/

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
			tempPos = { 40,300 };
		}
		else if (i == 1) {
			tempPos = { 440,300 };
		}
		else {
			tempPos = { 840,300 };
		}

		if (choice_[i] == 0) {
			//MUSCLE
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "マッスル");
			DrawExtendGraph(tempPos.x, tempPos.y, tempPos.x + 400, tempPos.y + 400, muscularCard, true);
		}
		else if (choice_[i] == 1) {
			//MAGICIAN
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "マジシャン");
			DrawExtendGraph(tempPos.x, tempPos.y, tempPos.x + 400, tempPos.y + 400, magicianCard, true);
		}
		else if (choice_[i] == 2) {
			//JET
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "ジェット");
			DrawExtendGraph(tempPos.x, tempPos.y, tempPos.x + 400, tempPos.y + 400, jetCard, true);
		}
		else if (choice_[i] == 3) {
			//GAMING
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "ゲーミング");
			DrawExtendGraph(tempPos.x, tempPos.y, tempPos.x + 400, tempPos.y + 400, gamingCard, true);
		}
		else if (choice_[i] == 4) {
			//Shark
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "シャーク");
			DrawExtendGraph(tempPos.x, tempPos.y, tempPos.x + 400, tempPos.y + 400, shakeCard, true);
		}
		else if (choice_[i] == 5) {
			//Shark
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "サカバンバスピス");
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
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "マッスル");
			DrawRotaGraph3(temptexturePos.x, temptexturePos.y,
				384, 256, 0.5f, 0.5f, 0, muscularImage, true);
		}
		else if (bodyType_[i] == 2) {
			//MAGICIAN
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "マジシャン");

			DrawRotaGraph3(temptexturePos.x, temptexturePos.y,
				256, 256, 0.5f, 0.5f, 0, magicianImage, true);
			//DrawGraph(tempPos.x, tempPos.y, magicianImage, true);
		}
		else if (bodyType_[i] == 3) {
			//JET
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "ジェット");
			DrawRotaGraph3(temptexturePos.x, temptexturePos.y,
				256, 256, 0.65f, 0.65f, 0, jetImage, true);
			//DrawGraph(tempPos.x, tempPos.y, jetImage, true);
		}
		else if (bodyType_[i] == 4) {
			//GAMING
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "ゲーミング");
			DrawRotaGraph3(temptexturePos.x, temptexturePos.y,
				256, 256, 0.5f, 0.5f, 0, gamingImage, true);
			//DrawGraph(tempPos.x, tempPos.y, gamingImage, true);
		}
		else if (bodyType_[i] == 5) {
			//Shark
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "シャーク");
			//DrawRotaGraph3(temptexturePos.x, temptexturePos.y,
			//	256, 256, 0.5f, 0.5f, 0, gamingImage, true);
			//DrawGraph(tempPos.x, tempPos.y, gamingImage, true);
		}
		else if (bodyType_[i] == 6) {
			//Shark
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "サカバンバスピス");
			//DrawRotaGraph3(temptexturePos.x, temptexturePos.y,
			//	256, 256, 0.5f, 0.5f, 0, gamingImage, true);
			//DrawGraph(tempPos.x, tempPos.y, gamingImage, true);
		}
	}
	DrawFormatString(840, 400, GetColor(255, 255, 255), "チンアナゴ～！");
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
