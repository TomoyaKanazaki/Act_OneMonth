//==========================================
//
//  矢印クラス(arrow.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "arrow.h"
#include "manager.h"
#include "gamemanager.h"
#include "player.h"
#include "input.h"
#include "texture.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
const float CArrow::m_fPlayerLenge = 50.0f;
const D3DXVECTOR3 CArrow::m_cSize = D3DXVECTOR3(30.0f, 10.0f, 0.0f);

//==========================================
//  コンストラクタ
//==========================================
CArrow::CArrow(int nPriority) : CObject3D(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CArrow::~CArrow()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CArrow::Init(void)
{
	//スティックの角度を取得
	D3DXVECTOR3 vecStick = CManager::GetManager()->GetJoyPad()->GetStickR(0.1f);
	float fAngle = atan2f(vecStick.y, vecStick.x);
	m_rot.z = atan2f(vecStick.x, vecStick.y);

	//プレイヤー座標の取得
	D3DXVECTOR3 PlayerPos = CGameManager::GetPlayer()->GetCenter();

	//自分の座標を算出
	m_pos = PlayerPos + D3DXVECTOR3(cosf(fAngle) * m_fPlayerLenge, -sinf(fAngle) * m_fPlayerLenge, 0.0f);

	//サイズを設定
	m_size = m_cSize;

	return CObject3D::Init();
}

//==========================================
//  終了処理
//==========================================
void CArrow::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CArrow::Update(void)
{
	//スティックの角度を取得
	D3DXVECTOR3 vecStick = CManager::GetManager()->GetJoyPad()->GetStickR(0.1f);
	float fAngle = atan2f(vecStick.y, vecStick.x);
	m_rot.z = -fAngle;

	//プレイヤー座標の取得
	D3DXVECTOR3 PlayerPos = CGameManager::GetPlayer()->GetCenter();

	//自分の座標を算出
	m_pos = PlayerPos + D3DXVECTOR3(cosf(fAngle) * m_fPlayerLenge, -sinf(fAngle) * m_fPlayerLenge, 0.0f);

	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CArrow::Draw(void)
{
	CObject3D::Draw();
}

//==========================================
//  生成処理
//==========================================
CArrow* CArrow::Create()
{
	//変数宣言
	CArrow* pArrow = nullptr;

	//インスタンス生成
	pArrow = new CArrow;

	//初期化処理
	pArrow->Init();

	//テクスチャの割り当て
	pArrow->BindTexture(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::ARROW));

	return pArrow;
}
