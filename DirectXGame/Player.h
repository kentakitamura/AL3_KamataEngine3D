#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Player {

public:
	// 初期化
	void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection);
	// 更新
	void update();
	// 描画
	void Draw();

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	ViewProjection* viewProjection_ = nullptr;
};
