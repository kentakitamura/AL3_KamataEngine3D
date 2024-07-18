#include "Enemy.h"



void Enemy::Initialize(Model* model, const Vector3& position, ViewProjection* viewProjection) {

	worldTransform_.Initialize();
	model_ = model;
	worldTransform_.translation_ = position;
	viewProjection_ = viewProjection;
	model_ = Model::CreateFromOBJ("enemy", true);

	velocity_ = { -kWalkspeed,0,0,};

	walkTimer_ = 0.0f;
}

void Enemy::Update() {
	//敵の移動
	worldTransform_.translation_.x += velocity_.x;


	worldTransform_.UpdateMatrix(); 

	walkTimer_ += 1.0f / 60.0f;

	float param = std::sin(walkTimer_/6);
	float radian = kWalkMotionAngleStart + kWalkMotionAngleEng * (param + 1.0f) / 2.0f;



}

void Enemy::Draw() {
	// 3Dモデル描画
	model_->Draw(worldTransform_, *viewProjection_);
}
