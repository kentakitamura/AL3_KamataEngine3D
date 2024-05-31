#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Player {

public:
	// ������
	void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection);
	// �X�V
	void update();
	// �`��
	void Draw();

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	ViewProjection* viewProjection_ = nullptr;
};