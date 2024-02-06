//==========================================
//
//  ボスクラス(boss.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "boss.h"
#include "model.h"
#include "motion.h"
#include "gamemanager.h"
#include "camera.h"
#include "debugproc.h"
#include "manager.h"
#include "gametime.h"
#include "boss_effect.h"
#include "texture.h"
#include "orbit.h"
#include "player.h"
#include "bullet.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 BOSS_SIZE = D3DXVECTOR3(100.0f, 100.0f, 50.0f); // ボスの大きさ
	const D3DXVECTOR3 CENTER_POS = D3DXVECTOR3(0.0f, 40.0f, 0.0f); // 中心座標とオブジェクト座標の差
	const D3DXVECTOR3 TARGET_POS[2] = { D3DXVECTOR3(1450.0f, 150.0f, 0.0f), D3DXVECTOR3(2150.0f, 150.0f, 0.0f) }; // 基本待機位置
	const float MAX_LIFE = 100.0f; // 体力の最大値
	const float DAMAGE = 1.0f; // 一回の攻撃から受けるダメージ量
	const float INVINCIBLE_TIME = 0.1f; // 無敵時間
	const float MOVE_SPEED = 200.0f; // 移動速度
	const float POS_ERROR = 10.0f; // 目標位置との許容誤差
	const float ACTION_DEFERMENT = 1.0f; // 次の行動までの猶予時間
	const float ATTACK_LENGTH = 500.0f; // 遠距離攻撃をする距離
	const int ATTACK_KIND = 3; // 攻撃の種類
	const float SCREEN_CENTER = 1800.0f; // 画面の中心
	const float DASH_BEFORE = 1.5f; // 突進の前に画面外で待機する時間
	const float DASH_AFTER = 0.5f; // 突進の後に画面外で待機する時間
	const float DASH_SPEED = -5.0f; // 突進の速度
	const float LIMIT_HEIGHT = 50.0f; // 最低の高さ
}

//==========================================
//  コンストラクタ
//==========================================
CBoss::CBoss(int nPriority) : CEnemy(nPriority),
m_State(POP),
m_oldState(POP),
m_MoveTimer(0.0f),
m_Wait(false),
m_Dash(false)
{
	m_pOrbit[0] = m_pOrbit[1] = nullptr;
} 

//==========================================
//  デストラクタ
//==========================================
CBoss::~CBoss()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CBoss::Init(void)
{
	// タイプの設定
	SetType(TYPE_ENEMY);

	// 階層構造情報を生成
	m_pLayer = CLayer::Set(CLayer::ENEMY_BOSS);

	// 初期化
	HRESULT hr = CObject_Char::Init();

	// セットアップ
	m_pMotion->SetModel(m_ppModel, m_pLayer->nNumModel, CMotion::BOSS_POP);

	// サイズを設定
	m_size = BOSS_SIZE;
	CalcHitLength(m_size);

	// 体力を設定
	m_fLife = MAX_LIFE;

	// 出現エフェクトの発生
	CBossEffect::Create(m_pos);

	// 色変更フラグを立てる
	ChangeColor(true);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	// 中心座標の設定
	m_posCenter = m_pos + CENTER_POS;

	// 剣に軌跡を付ける
	if (m_pOrbit[0] == nullptr)
	{
		m_pOrbit[0] = COrbit::Create(m_ppModel[4], D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -110.0f), 30);
		m_pOrbit[0]->SwitchDraw(false);
	}
	if (m_pOrbit[1] == nullptr)
	{
		m_pOrbit[1] = COrbit::Create(m_ppModel[5], D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -110.0f), 30);
		m_pOrbit[1]->SwitchDraw(false);
	}

	// モーションを設定
	m_pMotion->Set(CMotion::BOSS_WAIT);

	return hr;
}

//==========================================
//  終了処理
//==========================================
void CBoss::Uninit(void)
{
	// 軌跡の終了
	for (int i = 0; i < 2; ++i)
	{
		if (m_pOrbit[i] != nullptr)
		{
			m_pOrbit[i]->Uninit();
			m_pOrbit[i] = nullptr;
		}
	}

	CEnemy::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CBoss::Update(void)
{
	// デルタタイムの取得
	m_fDeltaTime = CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

	// 不透明度を加算する
	if (m_col.a < 1.0f)
	{
		m_col.a += m_fDeltaTime;

		if (m_col.a > 1.0f) // 出現完了
		{
			m_col.a = 1.0f;
			ChangeColor(false);
			m_State = MOVE;

			// 目標位置を設定
			m_TargetPos = TARGET_POS[rand() % 2];
		}
	}

	// 被撃時の処理
	Attacked();

	// 待機中に行動の抽選を行う
	if (m_State == NEUTRAL)
	{
		Neutral();
	}

	//移動中と待機中にプレイヤーを向く
	if (m_State == NEUTRAL || m_State == MOVE)
	{
		RotateToPlayer();
	}

	// 移動
	Move();

	// 死亡する
	if (m_fLife <= 0.0f)
	{
		m_State = DEATH;
	}

	// モーション
	Motion();

	// 攻撃処理
	Attack();

	// デバッグ表示
	DebugProc::Print("ボスの体力 : %f\n", m_fLife);
	DebugProc::Print("移動量 : %f\n", m_move.x);
	DebugProc::Print("位置 : %f, %f", m_pos.x, m_pos.y);

	// 更新
	CEnemy::Update();

	// 中心座標の設定
	m_posCenter = m_pos + CENTER_POS;
}

//==========================================
//  描画処理
//==========================================
void CBoss::Draw(void)
{
	CEnemy::Draw();
}

//==========================================
//  被撃時の処理
//==========================================
void CBoss::Attacked()
{
	// 出現状態および死亡状態中は攻撃を受けない
	if (m_State == POP || m_State == DEATH)
	{
		return;
	}

	// 状態毎の処理
	if (m_ObjState == ATTACKED)
	{
		m_fLife -= DAMAGE;
		m_AllDamage += DAMAGE;
		m_ObjState = INVINCIBLE;
		WhiteOut(true);
		return;
	}
	else if (m_ObjState == INVINCIBLE)
	{
		// 時間の加算
		m_fInvincible += CManager::GetInstance()->GetGameTime()->GetDeltaTimeFloat();

		// 無敵時間の解除
		if (m_fInvincible >= INVINCIBLE_TIME)
		{
			m_ObjState = NORMAL;
			m_fInvincible = 0.0f;
			WhiteOut(false);
		}
	}
}

//==========================================
//  モーション
//==========================================
void CBoss::Motion()
{
	//モーションを更新
	if (m_State != m_oldState)
	{
		switch (m_State)
		{
		case POP: // 出現状態
			m_pMotion->Set(CMotion::BOSS_POP);
			break;
		case MOVE: // 移動状態
			m_pMotion->Set(CMotion::BOSS_WAIT);
			break;
		case NEUTRAL: // 待機状態
			m_pMotion->Set(CMotion::BOSS_WAIT);
			break;
		case DEATH: // 死亡状態
			break;
		case ATTACK: // 通常攻撃
			break;
		case DASH: // 突進攻撃
			break;
		case BULLET: // 遠距離攻撃
			break;
		}
	}

	//現在の状態を保存
	m_oldState = m_State;
}

//==========================================
//  移動処理
//==========================================
void CBoss::Move()
{
	// 移動状態の時のみ
	if (m_State != MOVE)
	{
		return;
	}

	// 目標位置と現在位置を結ぶベクトルを作成する
	D3DXVECTOR3 vec = m_TargetPos - m_pos;

	// ベクトルの大きさが誤差範囲内なら停止
	if (POS_ERROR * POS_ERROR >= vec.x * vec.x + vec.y * vec.y)
	{
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_State = NEUTRAL;
		return;
	}

	// ベクトルを正規化
	D3DXVec3Normalize(&vec, &vec);

	// 移動量を目標位置に向ける
	vec *= MOVE_SPEED * m_fDeltaTime;

	// 移動量を適用
	m_move = vec;
}

//==========================================
//  待機中の行動
//==========================================
void CBoss::Neutral()
{
	// 行動タイマーの加算
	m_MoveTimer += m_fDeltaTime;

	// 一定時間が経過していない場合
	if (m_MoveTimer <= ACTION_DEFERMENT)
	{
		return;
	}

	// 行動タイマーのリセット
	m_MoveTimer = 0.0f;

	// 攻撃の種類を決める乱数
	int Rand = rand() % ATTACK_KIND;

	// プレイヤーの座標を取得
	D3DXVECTOR3 posPlayer = CGameManager::GetPlayer()->GetPos();

	// プレイヤーまでのベクトルを算出
	D3DXVECTOR3 vec = posPlayer - m_posCenter;
	
	// ベクトルの大きさを比較する
	if (ATTACK_LENGTH * ATTACK_LENGTH <= vec.x * vec.x + vec.y * vec.y)
	{
		// 遠距離攻撃を選択肢に入れる
		switch (Rand)
		{
		case 0:
			m_State = ATTACK;
			break;
		default:
			m_State = BULLET;
			break;
		}
	}
	else
	{
		// 近距離攻撃と突進のみで抽選する
		switch (Rand)
		{
		case 0:
			m_State = ATTACK;
			break;
		default:
			m_State = DASH;
			break;
		}
	}
}

//==========================================
//  攻撃処理
//==========================================
void CBoss::Attack()
{
	Shot();
	TriAttack();
	Dash();
}

//==========================================
//  遠距離攻撃
//==========================================
void CBoss::Shot()
{
	// 遠距離攻撃状態じゃなかったら抜ける
	if (m_State != BULLET)
	{
		return;
	}

	// 攻撃モーションが完了したら弾を出す
	//if (m_pMotion->GetFinish())
	//{
		// たまあああああああああああああああ
		CBullet::Create(m_posCenter);

		// 移動行動に戻る
		m_State = MOVE;
	//}
}

//==========================================
//  三連攻撃
//==========================================
void CBoss::TriAttack()
{
	// 攻撃状態じゃなかったら抜ける
	if (m_State != ATTACK)
	{
		return;
	}

	m_State = MOVE;
}

//==========================================
//  突進攻撃
//==========================================
void CBoss::Dash()
{
	// 突進状態じゃなかったら抜ける
	if (m_State != DASH)
	{
		return;
	}

	// 一度画面外に出る
	if (!m_Wait)
	{
		if (m_pos.x < SCREEN_CENTER)
		{
			m_move.x = -MOVE_SPEED * m_fDeltaTime;
		}
		else
		{
			m_move.x = MOVE_SPEED * m_fDeltaTime;
		}

		// 画面外に出たら
		if (!CGameManager::GetCamera()->OnScreen(m_posCenter))
		{
			m_MoveTimer += m_fDeltaTime; // 時間を加算
		}

		// 一定時間が経過したら
		if (m_MoveTimer > DASH_BEFORE)
		{
			// プレイヤーの高さに合わせる
			m_pos.y = CGameManager::GetPlayer()->GetCenterPos().y;

			// 高さ制限
			if (m_pos.y < LIMIT_HEIGHT)
			{
				m_pos.y = LIMIT_HEIGHT;
			}

			//移動量に倍率をかける
			m_move.x *= DASH_SPEED;

			// フラグを立てる
			m_Wait = true;

			// タイマーをリセット
			m_MoveTimer = 0.0f;

			// 軌跡を発生
			for (int i = 0; i < 2; ++i)
			{
				if (m_pOrbit[i] != nullptr)
				{
					m_pOrbit[i]->SwitchDraw(true);
				}
			}
		}
	}
	else
	{
		// 画面内に入ったら突進中フラグを立てる
		if (!m_Dash && CGameManager::GetCamera()->OnScreen(m_posCenter))
		{
			m_Dash = true;
		}

		// 突進中に画面外に出たら
		if (m_Dash && !CGameManager::GetCamera()->OnScreen(m_posCenter))
		{
			m_MoveTimer += m_fDeltaTime; // 時間を加算
		}

		// 一定時間が経過したら
		if (m_MoveTimer > DASH_AFTER)
		{
			// フラグをへし折る
			m_Wait = false;
			m_Dash = false;

			// タイマーをリセット
			m_MoveTimer = 0.0f;

			// 移動状態に戻る
			m_State = MOVE;

			// 目標位置を設定
			m_TargetPos = TARGET_POS[rand() % 2];

			// 軌跡を削除
			for (int i = 0; i < 2; ++i)
			{
				if (m_pOrbit[i] != nullptr)
				{
					m_pOrbit[i]->SwitchDraw(false);
				}
			}
		}
	}
}
