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

	//BGMの再生
	CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_RESULT);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CResultManager::Uninit(void)
{
	//BGMの停止
	CManager::GetInstance()->GetInstance()->GetSound()->Stop();
}

//==========================================
//  更新処理
//==========================================
void CResultManager::Update(void)
{
	//シーン経過時間を加算
	m_fCntScene += CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

	//画面遷移
	if (CManager::GetInstance()->GetInstance()->GetJoyPad()->GetTrigger(CJoyPad::BUTTON_A) || m_fCntScene >= 15.0f || CManager::GetInstance()->GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		CManager::GetInstance()->GetInstance()->GetSceneManager()->SetNext(CSceneManager::TITLE);
		CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_END);
		return;
	}
}

//==========================================
//  描画処理
//==========================================
void CResultManager::Draw(void)
{

}
