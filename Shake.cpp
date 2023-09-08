#include "Shake.h"
#include "DxLib.h"
#include <stdlib.h>
#include <time.h>

//コンストラクタの定義
Shake::Shake() {
	randX = 0;
	randY = 0;
	isShakeing = 0;
	timer = 0;
	max = 21;
	min = 10;
}

//シェイクの処理関数
void Shake::Effect() {

	//シェイクのフラグが立てば
	if (isShakeing == 1) {
		timer++;
		randX = rand() % max - min;
		randY = rand() % max - min;

		//5フレームごとにシェイクを小さくする
		if (timer % 3 == 0) {
			max -= 2;
			min--;
		}

		//50フレームでシェイク終了
		if (timer >= 30) {
			isShakeing = 0;
			timer = 0;
		}
	}
	//シェイクしていないとき
	else {
		randX = 0;
		randY = 0;
	}
}
