//==========================================
//
//  斬られたポリゴン(cut_polygon.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "cut_polygon.h"
#include "manager.h"
#include "renderer.h"

//==========================================
//  コンストラクタ
//==========================================
CCutPolygon::CCutPolygon(int nPriority) : CObject3D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==========================================
//  デストラクタ
//==========================================
CCutPolygon::~CCutPolygon()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CCutPolygon::Init(void)
{
	//初期化
	HRESULT hr = CObject3D::Init();

	//テクスチャ座標の設定
	if (m_move.y > 0.0f)
	{
		SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 0.5f));
	}
	if (m_move.y < 0.0f)
	{
		SetTex(D3DXVECTOR2(0.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	}

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CCutPolygon::Uninit(void)
{
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CCutPolygon::Update(void)
{
	//移動
	m_pos += m_move;

	//慣性による移動の停止
	//m_move.x += (0.0f - m_move.x) * 0.1f;

	//透明度を下げる
	D3DXCOLOR col = GetCol();
	col.a += (0.0f - col.a) * 0.1f;
	SetCol(col);

	//透明度0で消滅
	if (col.a <= 0.0f)
	{
		Uninit();
		return;
	}

	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CCutPolygon::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetManager()->GetRenderer()->GetDevice();

	//アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//アルファブレンディングを減算合成に設定
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_SUBTRACT);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject3D::Draw();

	//アルファブレンディングの設定を元に戻す
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
CCutPolygon* CCutPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, LPDIRECT3DTEXTURE9 tex)
{
	//インスタンス生成
	CCutPolygon* pCut = new CCutPolygon;

	//値を設定
	pCut->m_pos = pos;
	pCut->m_size = size;
	pCut->m_move = move;

	//初期化処理
	pCut->Init();

	//テクスチャ割り当て
	pCut->BindTexture(tex);

	return pCut;
}
