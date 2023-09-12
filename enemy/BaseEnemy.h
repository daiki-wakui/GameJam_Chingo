#pragma once
#include "MathManager.h"

class BaseEnemy {
public:
	virtual void Initialize(Vector2 pos);
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual Vector2 Col(int num);

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
	int GetColNum() {
		return colNum_;
	}

	void SetIsCook() {
		isCook_ = true;
	}
	bool GetIsCook() {
		return isCook_;
	}

	void SetType(int num) {
		type_ = num;
	}
	int GetType() {
		return type_;
	}
protected:
	int healHang_ = 1; //プレイヤーが食べた時に空腹度回復する量
	int exp_ = 1;	//プレイヤーが食べた時に得られる経験値
	int lv_ = 1;

	Vector2 pos_;
	int r_;
	float rot_;

	int texture_;

	bool isDead_;

	int colNum_ = 0;

	bool isCook_ = false;

	int type_ = 0;

};