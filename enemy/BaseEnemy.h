#pragma once
#include "MathManager.h"

class BaseEnemy {
public:
	virtual void Initialize(Vector2 pos);
	virtual void Update() = 0;
	virtual void Draw() = 0;

	void SetRotation(float rot) {
		rot_ = rot;
	}

	Vector2 GetPos() {
		return pos_;
	}
	int GetR() {
		return r_;
	}

	bool GetIsDead() {
		return isDead_;
	}
	void SetIsDead() {
		isDead_ = true;
	}
	int GetHang() {
		return healHang_;
	}
	int GetEXP() {
		return exp_;
	}
	int GetLv() {
		return lv_;
	}

protected:
	int healHang_ = 1; //�v���C���[���H�ׂ����ɋ󕠓x�񕜂����
	int exp_ = 1;	//�v���C���[���H�ׂ����ɓ�����o���l
	int lv_ = 1;

	Vector2 pos_;
	int r_;
	float rot_;

	int texture_;

	bool isDead_;
};