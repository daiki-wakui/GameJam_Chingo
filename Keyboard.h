#pragma once
#include "DxLib.h"

class Keyboard
{
private:

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

public:

	Keyboard();
	~Keyboard();

	void Update();

	//引数を呼ぶ時は"KEY_INPUT_○○"で出てくる

	bool KeyPush(INT16 key);	//押してる間
    bool KeyTriggerPush(INT16 key);	//押した瞬間
	bool KeyRelease(INT16 key);	//離してる間
	bool KeyTriggerRelease(INT16 key);	//離した瞬間

};

