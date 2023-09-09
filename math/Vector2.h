#pragma once

class Vector2 {

public:
	float x;
	float y;

public:
	//コンストラクタ
	Vector2();
	Vector2(float x, float y);

	//メンバ関数
	float length() const;
	Vector2& normalize();
	float dot(const Vector2& v) const;
	float cross(const Vector2& v) const;

	//線形補間
	const Vector2 lerp(const Vector2& start, const Vector2& end, const float t);


	//単功演算子オーバーロード
	Vector2 operator+() const;
	Vector2 operator-() const;

	//代入演算子オーバーロード
	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator*=(float s);
	Vector2& operator/=(float s);
};

//2項演算子オーバーロード
//※いろんな引数(引数の型と順序)のパターンに対応するため、以下のように準備している
const Vector2 operator+(const Vector2& v1, const Vector2& v2);
const Vector2 operator-(const Vector2& v1, const Vector2& v2);
const Vector2 operator*(const Vector2& v, float s);
const Vector2 operator*(float s, const Vector2& v);
const Vector2 operator/(const Vector2& v, float s);

void DrawCircle(Vector2 pos,int r,unsigned int color);
void DrawLine(Vector2 start,Vector2 end,unsigned int color);
void DrawBox(Vector2 start,Vector2 end,unsigned int color);

void DrawCircleNotScroll(Vector2 pos, int r, unsigned int color);
void DrawLineNotScroll(Vector2 start, Vector2 end, unsigned int color);