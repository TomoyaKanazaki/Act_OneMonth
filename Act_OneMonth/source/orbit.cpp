//==========================================
//
//  ダッシュの軌跡クラス
//  Author : Tomoya Kanazaki
//
//==========================================
#include "orbit.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "texture.h"
#include "slice.h"
#include "gamemanager.h"
#include "icon.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
const float COrbit::m_fDefaultHeight = 20.0f;

//==========================================
//  コンストラクタ
//==========================================
COrbit::COrbit(int nPriority) : CObject3D(nPriority)
{
	m_offset[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_offset[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fHeight = 0.0f;
}

//==========================================
//  デストラクタ
//==========================================
COrbit::~COrbit()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT COrbit::Init(void)
{
	//角度を設定する
	D3DXVECTOR3 vec = m_offset[1] - m_offset[0];
	m_rot.z = atan2f(vec.y, vec.x);

	//長さを設定する
	float fLength = sqrtf(vec.x * vec.x + vec.y * vec.y);
	m_size.x = fLength;

	//高さを設定する
	m_fHeight = m_fDefaultHeight;
	if (CGameManager::GetIcon() != nullptr)
	{
		m_fHeight *= CGameManager::GetIcon()->GetLIfe();
	}
	m_size.y = m_fHeight;

	//位置を設定
	m_pos = (m_offset[0] + m_offset[1]) * 0.5f;

	//初期化
	HRESULT hr = CObject3D::Init();

	//色を設定
	SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

	//テクスチャを割り当てる
	BindTexture(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::SLASH));

	return hr;
}

//==========================================
//  終了処理
//==========================================
void COrbit::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void COrbit::Update(void)
{
	//小さくする
	if (CGameManager::GetIcon() != nullptr)
	{
		m_fHeight = m_fDefaultHeight * CGameManager::GetIcon()->GetLIfe();
	}
	m_size.y = m_fHeight;

	//小さくなったら消す
	if (m_size.y <= 0.0f)
	{
		Uninit();
	}

	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void COrbit::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

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
COrbit* COrbit::Create(D3DXVECTOR3 offset0, D3DXVECTOR3 offset1)
{
	//変数宣言
	COrbit* pOrbit = nullptr;

	//メモリを確保
	if (pOrbit == nullptr)
	{
		pOrbit = new COrbit;
	}

	//値を設定
	pOrbit->m_offset[0] = offset0;
	pOrbit->m_offset[1] = offset1;

	//初期化処理
	pOrbit->Init();

	return pOrbit;
}
