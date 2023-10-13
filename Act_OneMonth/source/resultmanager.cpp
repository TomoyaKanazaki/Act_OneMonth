//==========================================
//
//  リザルトマネージャ(resultmanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "resultmanager.h"
#include "manager.h"
#include "debugproc.h"
#include "scenemanager.h"
#include "input.h"
#include "sound.h"
#include "logo.h"
#include "texture.h"

//==========================================
//  コンストラクタ
//==========================================
CResultManager::CResultManager()
{
	m_nCntScene = 0;
	m_nRank = 0;
}

//==========================================
//  デストラクタ
//==========================================
CResultManager::~CResultManager()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CResultManager::Init(void)
{
	CLogo::Create(D3DXVECTOR3(CENTER_WIDTH, CENTER_HEIGHT, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CTexture::RESULT);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CResultManager::Uninit(void)
{
	//BGMの停止
	CManager::GetSound()->Stop();
}

//==========================================
//  更新処理
//==========================================
void CResultManager::Update(void)
{
	//シーン経過時間を加算
	m_nCntScene++;

	//画面遷移
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) || m_nCntScene >= 1500)
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::TITLE);
		return;
	}

	CManager::GetDebugProc()->Print("順位 : %d\n", m_nRank);
}

//==========================================
//  描画処理
//==========================================
void CResultManager::Draw(void)
{

}
