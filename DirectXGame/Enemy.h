#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Enemy {
	

	public:
	/// 初期化
	
	
	void Initialize(Model* model, const Vector3& position, ViewProjection* viewProjection);
	void Initialize(const Vector3& position, ViewProjection* viewProjection);



	/// 更新
	void Update();

	/// 描画

	void Draw();
  



  private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_ = nullptr;
	// モデル
	Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};