#include "GameScene.h"
#include "TextureManager.h"
#include "myMath.h"
#include <cassert>
#include <map>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete modelBlock_;
	delete modelPlayer_;
	delete modelSkydome_;

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}



	worldTransformBlocks_.clear();

	delete debugCamera_;
	delete mapChipField_;


//	Model::StaticInitialize;
	
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("block.png");
	// 3Dモデルの生成
	model_ = Model::Create();
	modelBlock_ = Model::Create();
	modelSkydome_ = Model::CreateFromOBJ("sphere", true);
	modelPlayer_ = Model::CreateFromOBJ("player", true);
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	Vector3 playerpositon = mapChipField_->GetMapChipPositionByIndex(1, 19 );
	player_->Initialize(modelPlayer_,playerpositon, &viewProjection_);

	


	// ドームの生成
	skydome_ = new Skydome();

	// ドームの初期化
	skydome_->Initialize(model_, &viewProjection_);


	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	//マップチップの生成
	mapChipField_ = new MapChipField();
	mapChipField_->LoadMapChipCsv("Resources/map.csv");

	//カメラコントロール生成
	cameraController_ = new CameraController();

	//カメラコントロールの初期化
	cameraController_->Initialize();

	//追従セット
	cameraController_->SetTarget(player_);

	//リセット
	cameraController_->Reset();




	GenerateBlocks();


	//マップチップデータセット
	mapChipField_ = new MapChipField;
	mapChipField_->LoadMapChipCsv("Resources/blocks.csv");

	player_->SetMapChipField(mapChipField_);
		
}

void GameScene::GenerateBlocks(){
	// 要素数
	uint32_t numBlockVirtical = mapChipField_->GetNumBlockVirtical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();
	// ブロック1個分の横幅
//	const float kBlockWidth = 2.0f;
//	const float kBlockHeight = 2.0f;
	// 要素数を変更する
	worldTransformBlocks_.resize(numBlockVirtical);

	// キューブの生成
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		worldTransformBlocks_[i].resize(numBlockHorizontal);
	}

	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		for (uint32_t j = 0; j < numBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ =
				    mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
};


void GameScene::Update() {

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE)) {
		if (isDebugCameraActive_ == true)
			isDebugCameraActive_ = false;
		else
			isDebugCameraActive_ = true;
	}
#endif

	// カメラ処理
	if (isDebugCameraActive_) {
		// デバッグカメラ,カメラコントロールの更新
		debugCamera_->Update();
		cameraController_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

        viewProjection_.matView = cameraController_->GetViewProjection().matView;
		viewProjection_.matProjection = cameraController_->GetViewProjection().matProjection;

		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		
		// ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}

	// 自キャラの更新
	player_->Update();
	skydome_->Update();
	
	// 縦横ブロック更新
	for (std::vector<WorldTransform*> worldTransformBlockTate : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlockYoko : worldTransformBlockTate) {
			if (!worldTransformBlockYoko)
				continue;

			// アフィン変換行列の作成
			worldTransformBlockYoko->UpdateMatrix();

			worldTransformBlockYoko->TransferMatrix();
		}
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	// 3Dモデル描画
		//model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	// 自キャラの描画
	    player_->Draw();
	    // ームの描写
	    modelSkydome_->Draw(worldTransform_, viewProjection_);
	// 縦横ブロック描画
	for (std::vector<WorldTransform*> worldTransformBlockTate : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlockYoko : worldTransformBlockTate) {
			if (!worldTransformBlockYoko)
				continue;

			modelBlock_->Draw(*worldTransformBlockYoko, viewProjection_);
		}
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}