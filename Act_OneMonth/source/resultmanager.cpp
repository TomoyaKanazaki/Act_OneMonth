//==========================================
//
//  リザルトマネージャ(resultmanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "resultmanager.h"
#include "manager.h"
#include "gametime.h"
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
	m_fCntScene = 0.0f;
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
	if (CSceneManager::GetClear())
	{
		CLogo::Create(D3DXVECTOR3(CENTER_WIDTH, CENTER_HEIGHT, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CTexture::CLEAR);
	}
	else
	{
		CLogo::Create(D3DXVECTOR3(CENTER_WIDTH, CENTER_HEIGHT, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CTexture::OVER);
	}

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CResultManager::Uninit(void)
{
	//BGMの停止
	CManager::GetManager()->GetManager()->GetSound()->Stop();
}

//==========================================
//  更新処理
//==========================================
void CResultManager::Update(void)
{
	//シーン経過時間を加算
	m_fCntScene += CManager::GetManager()->GetGameTime()->GetDeltaTimeFloat();

	//画面遷移
	if (CManager::GetManager()->GetManager()->GetJoyPad()->GetTrigger(CJoyPad::BUTTON_A) || m_fCntScene >= 15.0f || CManager::GetManager()->GetManager()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		CManager::GetManager()->GetManager()->GetSceneManager()->SetNext(CSceneManager::TITLE);
		return;
	}
}

//==========================================
//  描画処理
//==========================================
void CResultManager::Draw(void)
{

}
