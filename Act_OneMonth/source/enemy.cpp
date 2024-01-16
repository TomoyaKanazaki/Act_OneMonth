//==========================================
//
//  敵クラス(enemy.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "enemy.h"
#include "model.h"
#include "motion.h"
#include "gamemanager.h"
#include "manager.h"
#include "renderer.h"
#include "slice.h"
#include "player.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const float SLICE_SCALE = 1.0f;
	const D3DXVECTOR3 ENEMY_SIZE_DEFAULT = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
}

//==========================================
//  コンストラクタ
//==========================================
CEnemy::CEnemy(int nPriority) :
m_type(NONE)
{

}

//==========================================
//  デストラクタ
//==========================================
CEnemy::~CEnemy()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CEnemy::Init(void)
{
	//タイプの設定
	SetType(TYPE_ENEMY);

	//階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::PLAYER_LAYER);

	// 初期化
	HRESULT hr = CObject_Char::Init();

	//モーション情報にモデルを渡す
	m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::PLAYER_WAIT);

	// サイズを設定
	m_size = ENEMY_SIZE_DEFAULT;

	// 中心座標を設定
	m_posCenter = m_pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f);

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CEnemy::Uninit(void)
{
	// 終了
	CObject_Char::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CEnemy::Update(void)
{
	// 状態毎の処理
	if (m_ObjState == MARKING) // マーキングされたとき
	{
		if (CGameManager::GetPlayer()->GetState() != CPlayer::IAI)
		{
			CSlice::Create(m_posCenter, m_size * SLICE_SCALE, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			Uninit();
			return;
		}
	}
	else // その他
	{
		m_pos += m_move;
	}

	// 中心座標を設定
	m_posCenter = m_pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f);

	//回転
	Rotate();

	CObject_Char::Update();
}

//==========================================
//  描画処理
//==========================================
void CEnemy::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//カリングをオフ
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	CObject_Char::Draw();

	//カリングをオン
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//アルファテストの無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//==========================================
//  生成処理
//==========================================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, CEnemy::TYPE type)
{
	//変数宣言
	CEnemy* pEnemy = nullptr;

	//メモリを確保
	switch (type)
	{
	case NORMAL:
		pEnemy = new CEnemy;
		//pEnemy = new CEnemy_Normal;
		break;

	default:
		pEnemy = nullptr;
		break;
	}

	// NULLチェック
	if (pEnemy == nullptr) { return nullptr; }

	//値を設定
	pEnemy->m_pos = pos;
	pEnemy->m_type = type;

	//初期化処理
	pEnemy->Init();

	return pEnemy;
}

//==========================================
//  移動方向を向く
//==========================================
void CEnemy::Rotate(void)
{
	//移動してない時は回転しない
	if (m_move.x == 0.0f)
	{
		return;
	}

	//右に進む時は右を向く
	if (m_move.x > 0.0f)
	{
		m_rot.y = D3DX_PI;
	}

	//左に進むときは左を向く
	if (m_move.x < 0.0f)
	{
		m_rot.y = 0.0f;
	}
}
