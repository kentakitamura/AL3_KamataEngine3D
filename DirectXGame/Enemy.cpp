#include "Enemy.h"


void Enemy::Initialize(Model* model, ViewProjection* viewProjection) {

	worldTransform_.Initialize();
	model_ = model;
	viewProjection_ = viewProjection;
}

void Enemy::Update() {}

void Enemy::Draw() {
	// 3Dモデル描画
	model_->Draw(worldTransform_, *viewProjection_);
}
