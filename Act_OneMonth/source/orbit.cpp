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

	//サイズを設定する
	float fLength = sqrtf(vec.x * vec.x + vec.y * vec.y);
	m_size.x = fLength;
	m_size.y = m_fHeight;

	//位置を設定
	m_pos = (m_offset[0] + m_offset[1]) * 0.5f;

	//初期化
	HRESULT hr = CObject3D::Init();

	//色を設定
	SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

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
	m_fHeight -= 0.2f;
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
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//カリングをオフ
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//描画
	CObject3D::Draw();

	//カリングをオン
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//==========================================
//  生成処理
//==========================================
COrbit* COrbit::Create(D3DXVECTOR3 offset0, D3DXVECTOR3 offset1, float fHeight)
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
	pOrbit->m_fHeight = fHeight;

	//初期化処理
	pOrbit->Init();

	return pOrbit;
}
