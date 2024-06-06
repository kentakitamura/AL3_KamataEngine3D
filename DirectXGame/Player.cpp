#include "Player.h"
#include "cassert"
#include "WorldTransform.h"

void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection) {

	assert(model);
	
	model_ = model;
	textureHandle_ = textureHandle;
    worldTransform_.Initialize();
	viewProjection_ = viewProjection;
}

void Player::update() { worldTransform_.TransferMatrix(); }

void Player::Draw() { model_->Draw(worldTransform_, *viewProjection_, textureHandle_); }