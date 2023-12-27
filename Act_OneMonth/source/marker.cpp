//==========================================
//
//  ヒットマーカー(marker.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "marker.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"
#include "gamemanager.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
const D3DXVECTOR3 CMarker::mc_size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);

//==========================================
//  コンストラクタ
//==========================================
CMarker::CMarker(int nPriority) : CObject3D(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CMarker::~CMarker()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CMarker::Init(void)
{
	//サイズの設定
	m_size = mc_size;

	//初期化
	HRESULT hr = CObject3D::Init();

	//カラーの設定
	SetCol(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CMarker::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CMarker::Update(void)
{
	//集中状態中のみ
	if (CGameManager::GetState() != CGameManager::STATE_CONCENTRATE)
	{
		Uninit();
	}

	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CMarker::Draw(void)
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
CMarker* CMarker::Create(const D3DXVECTOR3 pos)
{
	//変数宣言
	CMarker* pMarker = nullptr;

	//インスタンス生成
	pMarker = new CMarker;

	//値を設定
	pMarker->m_pos = pos;

	//初期化処理
	pMarker->Init();

	//テクスチャを割り当て
	pMarker->BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::MARKER));

	return pMarker;
}
