#include "Vector2.h"
#include <cmath>	//sqrt
#include "DxLib.h"
#include "ScrollManager.h"

Vector2::Vector2()
	:x(0), y(0)
{
}

Vector2::Vector2(float x, float y)
	: x(x), y(y)
{
}

float Vector2::length() const {
	return sqrt((x * x) + (y * y));
}

Vector2& Vector2::normalize() {
	float len = length();
	if (len != 0) {
		return *this /= length();
	}
	return *this;
}

float Vector2::dot(const Vector2& v) const {
	return (x * v.x) + (y * v.y);
}

float Vector2::cross(const Vector2& v) const {
	return (x * v.y) - (y * v.x);
}

const Vector2 Vector2::lerp(const Vector2& start, const Vector2& end, const float t)
{
	return start * (1.0f - t) + end * t;
}

Vector2 Vector2::operator+() const {
	return *this;
}

Vector2 Vector2::operator-() const {
	return Vector2(-x, -y);
}

Vector2& Vector2::operator+=(const Vector2& v) {
	x += v.x;
	y += v.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& v) {
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2& Vector2::operator*=(float s) {
	x *= s;
	y *= s;
	return *this;
}

Vector2& Vector2::operator/=(float s) {
	x /= s;
	y /= s;
	return *this;
}

//Vector2 �N���X�ɑ����Ȃ��֐��Q
//2�����Z�q
const Vector2 operator+(const Vector2& v1, const Vector2& v2) {
	Vector2 temp(v1);
	return temp += v2;
}

const Vector2 operator-(const Vector2& v1, const Vector2& v2) {
	Vector2 tenp(v1);
	return tenp -= v2;
}

const Vector2 operator*(const Vector2& v, float s) {
	Vector2 temp(v);
	return temp *= s;
}

const Vector2 operator*(float s, const Vector2& v) {
	return v * s;
}

const Vector2 operator/(const Vector2& v, float s) {
	Vector2 temp(v);
	temp.x /= s;
	temp.y /= s;
	return temp;
}

void DrawCircle(Vector2 pos, int r, unsigned int color)
{
	DrawCircle((int)pos.x, (int)pos.y + ScrollManager::GetInstance()->GetScroll(), r, color);
}

void DrawLine(Vector2 start, Vector2 end, unsigned int color)
{
	DrawLine((int)start.x, (int)start.y + ScrollManager::GetInstance()->GetScroll(), (int)end.x, (int)end.y + ScrollManager::GetInstance()->GetScroll(),color);
}

void DrawBox(Vector2 start, Vector2 end, unsigned int color)
{
	DrawBox((int)start.x, (int)start.y + ScrollManager::GetInstance()->GetScroll(), (int)end.x, (int)end.y + ScrollManager::GetInstance()->GetScroll(), color,true);
}

void DrawCircleNotScroll(Vector2 pos, int r, unsigned int color)
{
	DrawCircle((int)pos.x, (int)pos.y, r, color);
}

void DrawLineNotScroll(Vector2 start, Vector2 end, unsigned int color)
{
	DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, color);
}
