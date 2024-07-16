#include "Enemy.h"


void Enemy::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {

	worldTransform_.Initialize();
	model_ = model;
	worldTransform_.translation_ = position;
	viewProjection_ = viewProjection;
	model_ = Model::CreateFromOBJ("enemy", true);
}

void Enemy::Update() {}

void Enemy::Draw() {
	// 3Dモデル描画
	model_->Draw(worldTransform_, *viewProjection_);
}
