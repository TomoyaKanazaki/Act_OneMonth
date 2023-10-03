//==========================================
//
//  タイトルマネージャ(titlemanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "titlemanager.h"
#include "manager.h"
#include "scenemanager.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "sound.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
CLight *CTitleManager::m_pLight = NULL;

//==========================================
//  コンストラクタ
//==========================================
CTitleManager::CTitleManager()
{
	m_nCntScene = 0;
}

//==========================================
//  デストラクタ
//==========================================
CTitleManager::~CTitleManager()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CTitleManager::Init(void)
{
	//ライトの生成
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
		m_pLight->Init();
	}

	//BGMの再生
	CManager::GetSound()->Play(CSound::SOUND_LABEL_BGM000);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CTitleManager::Uninit(void)
{
	//ライトの終了、破棄
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	//BGMの停止
	CManager::GetSound()->Stop();
}

//==========================================
//  更新処理
//==========================================
void CTitleManager::Update(void)
{
	//シーン経過時間を加算
	//m_nCntScene++;

	//画面遷移
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetMouse()->GetTrigger(CMouse::BUTTON_LEFT))
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::GAME);
		CManager::GetSound()->Play(CSound::SOUND_LABEL_ENTER);
		return;
	}
	else if (m_nCntScene >= 900)
	{
		CManager::GetSceneManager()->SetNext(CSceneManager::RANKING);
		return;
	}

	//ライトの更新
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}
}

//==========================================
//  描画処理
//==========================================
void CTitleManager::Draw(void)
{

}
