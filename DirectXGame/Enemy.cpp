#include "Enemy.h"



void Enemy::Initialize(Model* model, const Vector3& position, ViewProjection* viewProjection) {

	worldTransform_.Initialize();
	model_ = model;
	worldTransform_.translation_ = position;
	viewProjection_ = viewProjection;
	model_ = Model::CreateFromOBJ("enemy", true);

	velocity_ = { -kWalkspeed,0,0,};
}

void Enemy::Update() {
	//敵の移動
	worldTransform_.translation_.x += velocity_.x;


	worldTransform_.UpdateMatrix(); }

void Enemy::Draw() {
	// 3Dモデル描画
	model_->Draw(worldTransform_, *viewProjection_);
}
