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
#include "renderer.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
const float CArrow::m_fPlayerLenge = 50.0f;
const D3DXVECTOR3 CArrow::m_cSize = D3DXVECTOR3(120.0f, 40.0f, 0.0f);

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
	D3DXVECTOR3 vecStick = CManager::GetInstance()->GetJoyPad()->GetStickR(0.1f);
	float fAngle = atan2f(vecStick.y, vecStick.x);
	m_rot.z = atan2f(vecStick.x, vecStick.y);

	//プレイヤー座標の取得
	D3DXVECTOR3 PlayerPos = CGameManager::GetPlayer()->GetCenter();

	//自分の座標を算出
	m_pos = PlayerPos + D3DXVECTOR3(cosf(fAngle) * m_fPlayerLenge, -sinf(fAngle) * m_fPlayerLenge, 0.0f);

	//サイズを設定
	m_size = m_cSize;

	//初期化処理
	HRESULT hr = CObject3D::Init();

	//色の設定
	SetCol(D3DXCOLOR(-1.0f, 1.0f, 0.3f, 1.0f));

	return hr;
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
	D3DXVECTOR3 vecStick = CManager::GetInstance()->GetJoyPad()->GetStickR(0.1f);
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
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//カリングをオフ
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//ライティングを無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Zテストの無効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//描画
	CObject3D::Draw();

	//アルファブレンディングの設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//アルファテストの無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//Zテストの有効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//ライティングを有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//カリングをオン
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
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
	pArrow->BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::ARROW));

	return pArrow;
}
