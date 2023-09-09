#pragma once
class Shake
{
public:
	//メンバ変数宣言
	int randX;
	int randY;
	int isShakeing;
	int timer;
	int max;
	int min;

public:
	//コンストラクタ宣言
	Shake();

	//メンバ関数宣言
	void Effect();

	void Reset();
};

