//==========================================
//
//  プレイヤークラス(player.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "object_char.h"

//==========================================
//  前方宣言
//==========================================
class CArrow;

//==========================================
//  プレイヤークラスの定義
//==========================================
class CPlayer : public CObject_Char
{
public:

	//状態定義
	enum State
	{
		NEUTRAL = 0, //待機状態
		WALK, //歩行状態
		JUMP, //ジャンプ状態
		FALL, //落下状態
		IAI, //居合状態
		DEATH, //死亡状態
		MAX
	};

	CPlayer(int nPriority = 4); //コンストラクタ
	~CPlayer(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetCenter(void) { return m_CenterPos; }
	bool GetDeath(void) { return m_State == DEATH ? true : false; }
	State GetState(void) { return m_State; }
	bool GetDash() const { return m_bDash; }
	int GetLevel() { return m_nLevel; } // レベルの取得
	void AddLevel(int nAdd); // レベルの加算
	void SetMovePos(const D3DXVECTOR3 posMove); // 移動先の設定

	//静的メンバ関数
	static CPlayer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));

private:

	//定数定義
#define PLAYER_SPEED (350.0f) //プレイヤーの移動速度
#define PLAYER_HEIGHT (40.0f) //プレイヤーの高さ
#define DASH_DISTANCE (200.0f) //ダッシュの移動距離
#define HIT_RANGE (220.0f) //ヒットする範囲
#define JUMP_MOVE (750.0f) //ジャンプ力
#define GRAVITY (25.0f) //重力
#define CAMERA_WIDTH (420.0f) //カメラから離れられる範囲
#define CAMERA_HEIGHT (220.0f) //カメラから離れられる範囲
#define MAX_LEVEL (10) // レベル上限

	//メンバ関数
	void Motion(void);
	void Limit(void);
	void Move(void);
	void Rotate(void);
	void Jump(void);
	void Gravity(void);
	void Dash(void);
	void Death(void);

	//メンバ変数
	D3DXVECTOR3 m_CenterPos; //中心座標
	D3DXVECTOR3 m_vecStick; //前回の右スティック入力
	float m_fDashAngle; //前回の右スティック入力
	bool m_bRand;
	bool m_bDash;
	D3DXMATERIAL *m_pDefMat;
	CArrow* m_pArrow;
	State m_State;
	State m_oldState;
	float m_fMoveTimer; // 移動のタイマー
	int m_nLevel; // レベル
	int m_nCntMove; // 移動先の保存数
	D3DXVECTOR3 m_posMove[MAX_LEVEL]; // 移動先の保存用変数

	//モデル情報
	D3DXVECTOR3 m_oldposModel;

};

#endif
