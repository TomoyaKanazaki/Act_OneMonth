//==========================================
//
//  紋章クラス(icon.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "icon.h"
#include "manager.h"
#include "renderer.h"
#include "gamemanager.h"
#include "player.h"
#include "gametime.h"
#include "debugproc.h"
#include "texture.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
const float CIcon::m_fMaxLife = 5.0f;

//==========================================
//  コンストラクタ
//==========================================
CIcon::CIcon(int nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CIcon::~CIcon()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CIcon::Init(void)
{
	//座標を設定
	m_pos = CGameManager::GetPlayer()->GetCenter();

	//寿命を設定
	m_fLife = m_fMaxLife;

	//サイズを設定
	m_size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	m_size *= m_fLife;

	return CObject3D::Init();
}

//==========================================
//  終了処理
//==========================================
void CIcon::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CIcon::Update(void)
{
	//寿命0なら殺す
	if (m_fLife <= 0.0f)
	{
		Uninit();
	}

	//寿命を減少
	m_fLife -= CManager::GetManager()->GetGameTime()->GetDeltaTimeFloat();

	//サイズを減少
	m_size = D3DXVECTOR3(50.0f, 50.0f, 0.0f) * m_fLife;

	//座標を設定
	m_pos = CGameManager::GetPlayer()->GetCenter();

	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CIcon::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject3D::Draw();

	//アルファブレンディングの設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//アルファテストの無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//==========================================
//  生成処理
//==========================================
CIcon* CIcon::Create(void)
{
	//変数宣言
	CIcon* pIcon = nullptr;

	//インスタンス生成
	pIcon = new CIcon;

	//初期化処理
	pIcon->Init();

	//テクスチャを割り当て
	pIcon->BindTexture(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::KATANA));

	return pIcon;
}
