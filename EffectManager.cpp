#include "EffectManager.h"
#include "Dxlib.h"
#include <random>
#include "ScrollManager.h"

EffectManager* EffectManager::GetInstance()
{
	static EffectManager instance;

	return &instance;
}

void EffectManager::Initialize()
{
	effects_.clear();
}

void EffectManager::Update()
{
	for (Effect& effect : effects_) {
		effect.way.y += 0.1f;
		effect.pos += effect.way;
		effect.r -= 0.25f;
	}
	//€‚ñ‚¾“G‚Ìíœ
	effects_.remove_if([](Effect& effect) {
		if (effect.r <= 0) {
			return true;
		}
		return false;
	});
}

void EffectManager::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);	//‚±‚±‚©‚ç
	for (Effect& effect : effects_) {
		DrawBox(effect.pos.x - effect.r, effect.pos.y - effect.r + ScrollManager::GetInstance()->GetScroll(), effect.pos.x + effect.r, effect.pos.y + effect.r + ScrollManager::GetInstance()->GetScroll(), GetColor(effect.color.x, effect.color.y, effect.color.z),false);
		DrawBox(effect.pos.x - effect.r - 1, effect.pos.y - effect.r + ScrollManager::GetInstance()->GetScroll() - 1, effect.pos.x + effect.r - 1, effect.pos.y + effect.r + ScrollManager::GetInstance()->GetScroll() - 1, GetColor(effect.color.x, effect.color.y, effect.color.z), false);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//‚±‚±‚Ü‚Å—LŒø
}

void EffectManager::Pop(Vector2 pos)
{
	//ƒ‰ƒ“ƒ_ƒ€
	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());

	std::uniform_real_distribution<float> x(-10, 10);
	std::uniform_real_distribution<float> y(0, 5);
	std::uniform_real_distribution<float> colorX(0, 250);
	std::uniform_real_distribution<float> colorY(0, 250);
	std::uniform_real_distribution<float> colorZ(0, 250);

	Effect newEffect;
	newEffect.pos = pos;
	newEffect.r = 10;
	newEffect.way = {x(engine),y(engine)};
	newEffect.color = { colorX(engine) ,colorY(engine) ,colorZ(engine) };
	effects_.push_back(newEffect);
}

