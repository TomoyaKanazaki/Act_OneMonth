//==========================================
//
//  プレイヤークラス(player.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "object.h"
#include "layer.h"

//==========================================
//  前方宣言
//==========================================
class CModel;
class CMotion;

//==========================================
//  プレイヤークラスの定義
//==========================================
class CPlayer : public CObject
{
public:
	CPlayer(int nPriority = 4); //コンストラクタ
	~CPlayer(); //デストラクタ

	//メンバ関数
	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	D3DXVECTOR3 GetMove(void) { return m_move; }

	//静的メンバ関数
	static CPlayer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));

private:

	//定数定義
#define PLAYER_SPEED (400.0f) //プレイヤーの移動速度
#define PLAYER_HEIGHT (40.0f) //プレイヤーの高さ
#define DASH_DISTANCE (300.0f) //ダッシュの移動距離
#define HIT_RANGE (350.0f) //ヒットする範囲
#define JUMP_MOVE (1000.0f) //ジャンプ力
#define GRAVITY (25.0f) //重力

	//メンバ関数
	void Limit(void);
	void Move(void);
	void Rotate(void);
	void Jump(void);
	void Gravity(void);
	void Dash(void);
	void Orbit(void);
	void Hit(void);

	//メンバ変数
	D3DXVECTOR3 m_vecStick; //前回の右スティック入力
	float m_fDashAngle; //前回の右スティック入力
	bool m_bRand;
	bool m_bDash;
	D3DXMATERIAL *m_pDefMat;

	//モデル情報
	CModel **m_ppModel; //モデル情報
	CLayer::LAYERDATA *m_pLayer; //階層構造情報
	CMotion *m_pMotion;
	D3DXVECTOR3 m_oldposModel;

};

#endif
