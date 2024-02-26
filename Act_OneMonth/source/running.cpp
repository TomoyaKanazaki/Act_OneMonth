//==========================================
//
//  人形クラス(running.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "running.h"
#include "motion.h"

//==========================================
//  コンストラクタ
//==========================================
CRunning::CRunning(int nPriority) : CObject_Char(nPriority)
{

}

//==========================================
//  デストラクタ
//==========================================
CRunning::~CRunning()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CRunning::Init(void)
{
	//タイプの設定
	SetType(TYPE_PLAYER);

	//向きの設定
	m_rot.y = -D3DX_PI * 0.5f;

	//階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::PLAYER_LAYER);

	//初期化処理
	HRESULT hr = CObject_Char::Init();

	//モーション情報にモデルを渡す
	m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::PLAYER_WAIT);
	m_pMotion->Set(CMotion::PLAYER_WALK);

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CRunning::Uninit(void)
{
	CObject_Char::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CRunning::Update(void)
{
	CObject_Char::Update();
}

//==========================================
//  描画処理
//==========================================
void CRunning::Draw(void)
{
	CObject_Char::Draw();
}

//==========================================
//  移動処理
//==========================================
void CRunning::Dash(void)
{
	//位置を保存
	D3DXVECTOR3 pos = m_pos;
	m_pos *= -1.0f;
}

//==========================================
//  生成処理
//==========================================
CRunning* CRunning::Create()
{
	//インスタンス生成
	CRunning* pDoll = new CRunning;

	//初期化処理
	pDoll->Init();

	return pDoll;
}
