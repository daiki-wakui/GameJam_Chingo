#include "Shake.h"
#include "DxLib.h"
#include <stdlib.h>
#include <time.h>

//�R���X�g���N�^�̒�`
Shake::Shake() {
	randX = 0;
	randY = 0;
	isShakeing = 0;
	timer = 0;
	max = 21;
	min = 10;
}

//�V�F�C�N�̏����֐�
void Shake::Effect() {

	//�V�F�C�N�̃t���O�����Ă�
	if (isShakeing == 1) {
		timer++;
		randX = rand() % max - min;
		randY = rand() % max - min;

		//5�t���[�����ƂɃV�F�C�N������������
		if (timer % 3 == 0) {
			max -= 2;
			min--;
		}

		//50�t���[���ŃV�F�C�N�I��
		if (timer >= 30) {
			isShakeing = 0;
			timer = 0;
		}
	}
	//�V�F�C�N���Ă��Ȃ��Ƃ�
	else {
		randX = 0;
		randY = 0;
	}
}
