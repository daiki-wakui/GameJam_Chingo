#pragma once
#include "PlayerBullet.h"
#include <list>
#include <memory>

class BulletManager {
private:
	BulletManager() = default;
	~BulletManager() = default;
public:
	//�R�s�[�R���X�g���N�^����
	BulletManager(const BulletManager& obj) = delete;
	//������Z�q�𖳌�
	BulletManager& operator=(const BulletManager& obj) = delete;

	static BulletManager* GetInstance();

	std::list<PlayerBullet*> GetBulletList() {
		bullets2_.clear();
		for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
			bullets2_.push_back(bullet.get());
		}
		return bullets2_;
	}

	void Initialize();
	void Update();
	void Draw();

	void Pop(Vector2 pos, Vector2 way);

	int GetSize() {
		return bullets_.size();
	}

private:
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
	std::list<PlayerBullet*> bullets2_;


};