//==========================================
//
//  ゲームマネージャクラス(gamemanager.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "gamemanager.h"
#include "manager.h"
#include "sound.h"
#include "player.h"
#include "light.h"
#include "camera.h"
#include "debugproc.h"
#include "manager.h"
#include "input.h"
#include "scenemanager.h"
#include "model.h"
#include "renderer.h"
#include "bg.h"
#include "enemy.h"
#include "field.h"
#include "gametime.h"
#include "icon.h"
#include "build.h"
#include "tutorial.h"
#include "tutorial_wall.h"
#include "fog.h"

//==========================================
//  静的メンバ変数宣言
//==========================================
const float CGameManager::m_fDashTime = 0.8f;
CPlayer* CGameManager::m_pPlayer = NULL;
CEnemy* CGameManager::m_pBoss = NULL;
CCamera *CGameManager::m_pCamera = NULL;
CLight *CGameManager::m_pLight = NULL;
CGameManager::State CGameManager::m_State = NONE;
CGameManager::State CGameManager::m_oldState = NONE;
CGameManager::Progress CGameManager::m_Progress = TUTORIAL_ENEMY;
CIcon* CGameManager::m_pIcon = nullptr;
CTutorial* CGameManager::m_pTutorial = nullptr;
CTutorialWall* CGameManager::m_pTutorialWall = nullptr;

//==========================================
//  コンストラクタ
//==========================================
CGameManager::CGameManager()
{
	m_fTimer = 0.0f;
	m_Progress = TUTORIAL_ENEMY;
}

//==========================================
//  デストラクタ
//==========================================
CGameManager::~CGameManager()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CGameManager::Init(void)
{
	//状態の初期化
	m_State = STATE_START;

	//プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(-2500.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));

	//ボスの生成
	m_pBoss = CEnemy::Create(D3DXVECTOR3(1800.0f, 100.0f, 0.0f), CEnemy::BOSS_MAIN);

	//敵の配置
	CEnemy::Create(D3DXVECTOR3(-1300.0f, 100.0f, 0.0f), CEnemy::STOP);
	CEnemy::Create(D3DXVECTOR3(-900.0f, 100.0f, 0.0f), CEnemy::NORMAL);
	CEnemy::Create(D3DXVECTOR3(-750.0f, 150.0f, 0.0f), CEnemy::STOP);
	CEnemy::Create(D3DXVECTOR3(-900.0f, 200.0f, 0.0f), CEnemy::NORMAL);
	CEnemy::Create(D3DXVECTOR3(-300.0f, 100.0f, 0.0f), CEnemy::HOMING);
	CEnemy::Create(D3DXVECTOR3(-300.0f, 200.0f, 0.0f), CEnemy::HOMING);
	CEnemy::Create(D3DXVECTOR3(-200.0f, 100.0f, 0.0f), CEnemy::HOMING);
	CEnemy::Create(D3DXVECTOR3(-100.0f, 200.0f, 0.0f), CEnemy::HOMING);
	CEnemy::Create(D3DXVECTOR3(-50.0f, 200.0f, 0.0f), CEnemy::INVINCIBLE);
	CEnemy::Create(D3DXVECTOR3(-50.0f, 100.0f, 0.0f), CEnemy::INVINCIBLE);
	CEnemy::Create(D3DXVECTOR3(50.0f, 200.0f, 0.0f), CEnemy::INVINCIBLE);
	CEnemy::Create(D3DXVECTOR3(50.0f, 100.0f, 0.0f), CEnemy::INVINCIBLE);

	//建物の生成
	CBuild::Create();

	//背景の生成
	CBg::Create(D3DXVECTOR3(0.0f, 0.0f, 20000.0f), D3DXVECTOR3(60000.0f, 0.0f, 20000.0f), 1);

	//床の生成
	CFeild::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(6000.0f, 0.0f, 720.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 6.0f), CFeild::SOIL);
	
	//水の生成
	CFeild::Create(D3DXVECTOR3(0.0f, -3000.0f, 0.0f), D3DXVECTOR3(60000.0f, 0.0f, 60000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), CFeild::WATER);

	//カメラの生成
	if (m_pCamera == NULL)
	{
		m_pCamera = CSceneManager::GetCamera();
		m_pCamera->Init();
	}

	//ライトの生成
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
		m_pLight->Init();
	}

	//BGMの再生
	CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_GAME);

	// フォグを生成
	Fog::Set(true);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CGameManager::Uninit(void)
{
	//ライトの終了、破棄
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	//チュートリアルを終了
	m_pTutorial = nullptr;

	m_pCamera = NULL;

	//BGMの停止
	CManager::GetInstance()->GetInstance()->GetSound()->Stop();
}

//==========================================
//  更新処理
//==========================================
void CGameManager::Update(void)
{
	//前回の状態を保存する
	m_oldState = m_State;

#if _DEBUG
	//画面遷移テスト
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN) && CManager::GetInstance()->GetKeyboard()->GetPress(DIK_LSHIFT))
	{
		CManager::GetInstance()->GetSceneManager()->SetNext(CSceneManager::RESULT);
		return;
	}

	//敵
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_E))
	{
		CEnemy::Create(D3DXVECTOR3(300.0f, 50.0f, 0.0f), CEnemy::NORMAL);
		CEnemy::Create(D3DXVECTOR3(300.0f, 100.0f, 0.0f), CEnemy::NORMAL);
		CEnemy::Create(D3DXVECTOR3(300.0f, 150.0f, 0.0f), CEnemy::NORMAL);
	}

	// フォグの切り替え
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_F))
	{
		Fog::Set(!Fog::Get());
	}

#endif

	//状態の切り替え
	if (CManager::GetInstance()->GetJoyPad()->GetLTRT(CJoyPad::BUTTON_RT, 100) || CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_LSHIFT))
	{
		if (m_State == STATE_CONCENTRATE)
		{
			//紋章を召喚
			if (m_pIcon != nullptr)
			{
				m_pIcon->SetLife();
			}

			for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
			{
				//先頭のアドレスを取得
				CObject* pObj = CObject::GetTop(nCntPriority);

				while (pObj != NULL)
				{
					//次のアドレスを保存
					CObject* pNext = pObj->GetNext();

					if (pObj->GetType() == CObject::TYPE_ORBIT)
					{
						pObj->Uninit();;
					}

					//次のアドレスにずらす
					pObj = pNext;
				}
			}
		}
	}

	//状態の切り替え
	if (CManager::GetInstance()->GetJoyPad()->GetLTRT(CJoyPad::BUTTON_LT, 100) || CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_LSHIFT))
	{
		if (m_pPlayer->GetState() != CPlayer::DEATH)
		{
			if (m_State == STATE_NORMAL)
			{
				m_State = STATE_CONCENTRATE;

				//紋章を召喚
				if (m_pIcon == nullptr)
				{
					D3DXVECTOR3 size = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
					m_pIcon = CIcon::Create(size);
				}
			}
		}
	}

	//状態を更新
	if (m_pIcon != nullptr)
	{
		if (m_pIcon->GetLIfe() <= 0.0f && m_State == STATE_CONCENTRATE)
		{
			CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_DASH);
			m_State = STATE_DASH;
			m_pIcon = nullptr;
		}
	}

	//状態を更新
	if (m_State == STATE_DASH)
	{
		if (m_fTimer >= m_fDashTime)
		{
			m_fTimer = 0.0f;
			m_State = STATE_NORMAL;
		}
		m_fTimer += CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();
	}

	//状態を更新
	if (m_State == STATE_START && m_pPlayer->GetPos().x >= -2250.0f)
	{
		m_State = STATE_NORMAL;
	}

	//ライトの更新
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}

	//ゲームクリア
	if (m_pBoss == nullptr)
	{
		m_State = STATE_END;
	}

	//チュートリアルの進行
	if (m_pPlayer->GetPos().x >= -1500.0f && m_Progress == TUTORIAL_ENEMY)
	{
		//チュートリアルの生成
		if (m_pTutorial == nullptr)
		{
			m_pTutorial = CTutorial::Create();
			m_Progress = TUTORIAL_ARROW;

			// 移動制限を生成
			D3DXVECTOR3 pos = m_pPlayer->GetPos();
			pos.x += 500.0f;
			m_pTutorialWall = CTutorialWall::Create();
		}
	}
	if (m_pTutorial != nullptr)
	{
		if (m_Progress == TUTORIAL_ARROW)
		{
			if (m_State == STATE_CONCENTRATE)
			{
				m_pTutorial->NextProgress();

				m_Progress = TUTORIAL_DASH;
			}
		}
		if (m_Progress == TUTORIAL_DASH)
		{
			if (CManager::GetInstance()->GetJoyPad()->GetStickR(0.3f) != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
			{
				m_pTutorial->NextProgress();
				m_Progress = END;
			}
		}
		if (m_Progress == END)
		{
			if (m_State == STATE_NORMAL)
			{
				m_pTutorial->NextProgress();
				m_pTutorial = nullptr;

				// 移動制限を解除
				if (m_pTutorialWall != nullptr)
				{
					m_pTutorialWall->Uninit();
					m_pTutorialWall = nullptr;
				}
			}
		}
	}

	//リザルトに遷移
	if (m_pPlayer->GetPos().x >= 2300.0f || m_pPlayer->GetDeath())
	{
		if (m_pPlayer->GetDeath())
		{
			CSceneManager::SetClear(false);
		}
		else if (m_pPlayer->GetPos().x >= 2300.0f)
		{
			CSceneManager::SetClear(true);
		}

		CManager::GetInstance()->GetSceneManager()->SetNext(CSceneManager::RESULT);
	}
}

//==========================================
//  描画処理
//==========================================
void CGameManager::Draw(void)
{

}
