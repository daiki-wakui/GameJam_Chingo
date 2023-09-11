#pragma once
#include "MathManager.h"

class Player {
private:
	Player() = default;
	~Player() = default;
public:
	//コピーコンストラクタ無効
	Player(const Player& obj) = delete;
	//代入演算子を無効
	Player& operator=(const Player& obj) = delete;

	static Player* GetInstance();

public:
	void Initialize();
	void Update();
	void ResultUpdate();
	void Draw(bool scroll = true);

	int GetActiveBody() {
		return activeLength_;
	}
	
	Vector2 GetPos(int i) {
		return pos_[i];
	}

	Vector2 GetOriginPos() {
		return originPos_;
	}

	void AddBodyLength(int num) {
		maxHunger_+= num;
	}
	void SubBodyLength() {
		maxHunger_ -= 100;
	}

	bool GetIsShakeing() {
		return isBackShakeing_;
	}

	void SetIsShakeing(bool shakeing) {
		isBackShakeing_ = shakeing;
	}

	int GetAngle(int i) {
		return angle_[i];
	}

	void SetMaxLength(int num) {
		maxHunger_ = num;
	}

	bool GetIsExtend();

	unsigned int GetBodyColor(int i);

	int GetNumNeck() {
		return NUM_NECK;
	}

	void SetThickness(int num) {
		thickness_ = num;
	}
	int GetThickness() {
		return thickness_;
	}

	bool GetInv();
	void SetInv() {
		invTime_ = TIME_INVISIBLE;
	}

	void ReSetBody();

	void AddBodySpace(int num) {
		bodySpace_ += num;
	}

	void AddSpeedNeck(int num) {
		speedNeck_ += num;
	}

private:
	int eyeTexure_;

	static const int MAX_BODY = 10000; //体の最大数
	const int NUM_NECK = 5;	 //首から上の数
	const int TIME_INVISIBLE = 3 * 60;//無敵時間

	const int START_BODY_LENGTH = 100; //スタート時の体の最大長さ
	const int START_BODY_THICKNESS = 30;
	const int START_BODY_SPACE = 10;		//体の間隔
	const int START_SPEED_NECK = 5; //首の最大回転スピード

	Vector2 pos_[MAX_BODY];//顏の位置
	int angle_[MAX_BODY];//角度
	Vector2 neckWay_;//首の角度
	int oldNeckWay_;//1フレ前の角度
	Vector2 originPos_;//チンアナゴの出る位置
	int mouseX_, mouseY_;

	int maxHunger_;
	int activeLength_;

	int mouseAngle_;//マウスの角度

	bool isReturn_;

	bool isBackShakeing_;
	int shrinkDistance_;

	int oldLevel_;

	int thickness_;

	int invTime_;

	int bodySpace_;
	int speedNeck_;

	int addHang_;
};