#include "ClearScene.h"
#include "exBody/ExBodyManager.h"
#include "MathManager.h"

void ClearScene::Initialize()
{
}

void ClearScene::Update()
{

}

void ClearScene::Draw()
{
	ExBodyManager* exM =  ExBodyManager::GetInstance();
	for (int i = 0; i < 3; i++) {
		Vector2 tempPos;
		//�I�����̃|�W�V����
		if (i == 0) {
			tempPos = { 540,400 };
		}
		else if (i == 1) {
			tempPos = { 640,400 };
		}
		else {
			tempPos = { 740,400 };
		}

		if (exM->GetBodyType(i) == 1) {
			//MUSCLE
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "�}�b�X��");
		}
		else if (exM->GetBodyType(i) == 2) {
			//MAGICIAN
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "�}�W�V����");
		}
		else if (exM->GetBodyType(i) == 3) {
			//JET
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "�W�F�b�g");
		}
		else if (exM->GetBodyType(i) == 4) {
			//GAMING
			DrawFormatString(tempPos.x, tempPos.y, GetColor(255, 255, 255), "�Q�[�~���O");
		}
	}
	DrawFormatString(840, 400, GetColor(255, 255, 255), "�`���A�i�S�`�I");


	DrawFormatString(0, 0, GetColor(255, 255, 255), "clear");
}
