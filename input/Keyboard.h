#pragma once
#include "DxLib.h"
#include "Vector3.h"
#include "Vector2.h"

class Keyboard
{
private:
	Keyboard() = default;
	~Keyboard() = default;
public:
	//コピーコンストラクタ無効
	Keyboard(const Keyboard& obj) = delete;
	//代入演算子を無効
	Keyboard& operator=(const Keyboard& obj) = delete;

	static Keyboard* GetInstance();


private:

	Vector2 test;

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

public:

	void Update();

	//引数を呼ぶ時は"KEY_INPUT_○○"で出てくる

	bool KeyPush(INT16 key);	//押してる間
    bool KeyTriggerPush(INT16 key);	//押した瞬間
	bool KeyRelease(INT16 key);	//離してる間
	bool KeyTriggerRelease(INT16 key);	//離した瞬間

};

