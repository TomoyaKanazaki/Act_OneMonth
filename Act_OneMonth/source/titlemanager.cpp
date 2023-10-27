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
#include "title.h"
#include "texture.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
CLight* CTitleManager::m_pLight = NULL;
CTitle* CTitleManager::m_pTitle = NULL;

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
	//タイトルロゴ
	m_pTitle =  CTitle::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(500.0f, 300.0f, 0.0f));

	//ライトの生成
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
		m_pLight->Init();
	}

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
	CManager::GetManager()->GetSound()->Stop();
}

//==========================================
//  更新処理
//==========================================
void CTitleManager::Update(void)
{
	//画面遷移
	if (CManager::GetManager()->GetManager()->GetJoyPad()->GetTrigger(CJoyPad::BUTTON_A) || CManager::GetManager()->GetManager()->GetKeyboard()->GetTrigger(DIK_RETURN))
	{
		if (CManager::GetManager()->GetManager()->GetSceneManager()->SetNext(CSceneManager::GAME))
		{
			m_pTitle->CutTitle();
		}
		return;
	}
	else if (m_nCntScene >= 900)
	{
		CManager::GetManager()->GetManager()->GetSceneManager()->SetNext(CSceneManager::RANKING);
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
