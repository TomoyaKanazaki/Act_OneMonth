//==========================================
//
//  斬られたポリゴン(cut.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "cut.h"
#include "cut_polygon.h"

//==========================================
//  コンストラクタ
//==========================================
CCut::CCut()
{
	tex = nullptr;
}

//==========================================
//  デストラクタ
//==========================================
CCut::~CCut()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CCut::Init(void)
{
	//生成するポリゴンの移動方向を決定
	D3DXVECTOR3 move;
	while (1)
	{
		float fRot = atan2f((float)rand(), (float)rand());
		move = D3DXVECTOR3(cosf(fRot), sinf(fRot), 0.0f);
		if (move.y != 0.0f)
		{
			break;
		}
	}

	//生成する座標を決定
	D3DXVECTOR3 posUp = m_pos, posDawn = m_pos;
	posUp.y += m_size.y * 0.5f;
	posDawn.y -= m_size.y * 0.5f;

	//生成するポリゴンのサイズ
	D3DXVECTOR3 size = D3DXVECTOR3(m_size.x, m_size.y * 0.5f, m_size.z);

	//ポリゴンを生成する
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (move.y > 0.0f)
		{
			CCutPolygon::Create(posUp, size, move, tex);
		}
		if (move.y < 0.0f)
		{
			CCutPolygon::Create(posDawn, size, move, tex);
		}
		move *= -1.0f;
	}

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CCut::Uninit(void)
{
	//自分自身の破棄
	Release();
}

//==========================================
//  更新処理
//==========================================
void CCut::Update(void)
{
	Uninit();
}

//==========================================
//  描画処理
//==========================================
void CCut::Draw(void)
{

}

//==========================================
//  生成処理
//==========================================
CCut* CCut::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex)
{
	//インスタンス生成
	CCut* pCut = new CCut;

	//値を設定
	pCut->m_pos = pos;
	pCut->m_size = size;
	pCut->tex = tex;

	//初期化処理
	pCut->Init();

	return pCut;
}
