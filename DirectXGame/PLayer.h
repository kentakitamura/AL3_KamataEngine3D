#include "Model.h"
#include "WorldTransform.h"

class Player{

public:


//初期化
	void Initialize(Model* model , uint32_t textureHandle);
	//更新
	void update();
	//描画
	void Draw();


private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;



};


