//==========================================
//
//  斬撃エフェクトクラス(slice.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "slice.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"

//==========================================
//  コンストラクタ
//==========================================
CSlice::CSlice(int nPriority)
{
}

//==========================================
//  デストラクタ
//==========================================
CSlice::~CSlice()
{
}

//==========================================
//  初期化処理
//==========================================
HRESULT CSlice::Init(void)
{
	//値を設定
	SetAnim(10, 3, false, TYPE_U);

	return CObject3D_Anim::Init();
}

//==========================================
//  終了処理
//==========================================
void CSlice::Uninit(void)
{
	CObject3D_Anim::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CSlice::Update(void)
{
	CObject3D_Anim::Update();
}

//==========================================
//  描画処理
//==========================================
void CSlice::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	////アルファブレンディングを加算合成に設定
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject3D_Anim::Draw();

	////アルファブレンディングの設定を元に戻す
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//アルファテストの無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//==========================================
//  生成処理
//==========================================
CSlice* CSlice::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 rot)
{
	//変数宣言
	CSlice* pSlice = nullptr;

	//インスタンス生成
	pSlice = new CSlice;

	//値を保存
	pSlice->m_pos = pos;
	pSlice->m_size = size;
	pSlice->m_rot = rot;

	//初期化処理
	pSlice->Init();

	//テクスチャを割り当て
	pSlice->BindTexture(CManager::GetManager()->CManager::GetManager()->GetManager()->GetTexture()->GetAddress(CTexture::SLICE));

	return pSlice;
}
