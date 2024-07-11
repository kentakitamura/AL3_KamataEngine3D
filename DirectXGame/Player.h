#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Easing.h"



/// <summary>
/// 自キャラ
/// </summary>

class MapChipField;

class Player {
public:
	// 左右
	enum class LRDirection {
		kRight,
		kLeft,
	};

	

	enum Corner {
		kRightBottom, // 右下
		kLeftBottom,  // 左下
		kRightTop,    // 右上
		kLeftTop,     // 左上
		kNumCorner    // 要素数
	};

	/// <summary>
	/// 初期化
	/// </summary>
	//	void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection);
	void Initialize(Model*model, const Vector3& position, ViewProjection* viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	const WorldTransform& GetWorldTransform() const { return worldTransform_; }
	const Vector3& GetVelocity() const { return velocity_; }

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }


	

private:

	MapChipField* mapChipField_ = nullptr;

	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	ViewProjection* viewProjection_ = nullptr;

	Vector3 velocity_ = {};

	static inline const float kAcceleration = 0.01f;
	static inline const float kAttenuation = 0.05f;
	static inline const float kAttenuationWall = 0.2f;
	static inline const float kAttenuationLanding = 0.0f;
	static inline const float kLimitRunSpeed = 0.5f;
	static inline const float kBlank = 0.04f;
	static inline const float kGroundSearchHeight = 0.06f;

	LRDirection lrDirection_ = LRDirection::kRight;

	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float turnTimer_ = 0.0f;

	// 旋回時間<秒>
	static inline const float kTimeTurn = 0.3f;

	// 接地状態フラグ
	bool onGround_ = true;
	// 着地フラグ
	bool landing = false;

	// 重力加速度（下方向）
	static inline const float kGravityAcceleration = 0.05f;
	// 最大落下速度（下方向）
	static inline const float kLimitFallSpeed = 0.2f;
	// ジャンプ初速（上方向）
	static inline const float kJumpAcceleration = 0.7f;


	//キャラの当たり判定
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
	

    struct CollisionMapInfo {

		bool isCeiling = false; // 天井衝突フラグ
		bool isRanding = false; // 着地フラグ
		bool ishitWall = false; // 壁接触フラグ

		//移動量
		Vector3 move;


	};

	/// マップ衝突判定上方向
	void MapCollisionTop(CollisionMapInfo& info);

	/// マップ衝突判定
	void MapCollision(CollisionMapInfo& info);




	/// 判定結果反映移動メンバ関数
	void ReflectMove( CollisionMapInfo& info);
	/// 天井衝突時メンバ関数
	void CeilingContact(CollisionMapInfo& info);

	void InputMove();

	void CheckMapCollision(CollisionMapInfo& info);

	void CheckMapCollisionUp(CollisionMapInfo& info);

	void CheckMapCollisionDown(CollisionMapInfo& info);

	void CheckMapCollisionRight(CollisionMapInfo& info);

	void CheckMapCollisionLeft(CollisionMapInfo& info);

	void UpdateOnGround(const CollisionMapInfo& info);
    void AnimateTurn();

	Vector3 CornerPosition(const Vector3& center, Corner Corner);

};