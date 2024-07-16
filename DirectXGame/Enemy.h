#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Enemy {
	

	public:
	/// 初期化
	
	
	void Initialize(Model* model, ViewProjection* viewProjection);

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

};