//==========================================
//
//  ターゲットクラス(target.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "target.h"
#include "manager.h"
#include "renderer.h"

//==========================================
//  コンストラクタ
//==========================================
CTarget::CTarget(int nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CTarget::~CTarget()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CTarget::Init(void)
{
	// 初期化
	return CObject3D::Init();
}

//==========================================
//  終了処理
//==========================================
void CTarget::Uninit(void)
{
	// 終了
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CTarget::Update(void)
{
	// 更新
	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CTarget::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

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
}

//==========================================
//  生成処理
//==========================================
CTarget* CTarget::Create(const D3DXVECTOR3 pos)
{
	// インスタンス生成
	CTarget* pTarget = new CTarget;

	// NULLチェック
	if (pTarget == nullptr) { return nullptr; }

	// 値を設定
	pTarget->m_pos = pos;

	// 初期化処理
	pTarget->Init();

	// 値を返す
	return pTarget;
}
