//==========================================
//
//  移動を繋ぐ線(course.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "course.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "sound.h"
#include "marker.h"
#include "gamemanager.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const float POLYGON_HEIGHT = 40.0f;
	const float HIT_LENGTH = 50.0f;
}

//==========================================
//  コンストラクタ
//==========================================
CCourse::CCourse(int nPriority) : CObject3D(nPriority),
m_start(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
m_end(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{

}

//==========================================
//  デストラクタ
//==========================================
CCourse::~CCourse()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CCourse::Init(void)
{
	// 初期化
	HRESULT hr = CObject3D::Init();

	// 色の設定
	SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// テクスチャ割り当て
	BindTexture(CManager::GetInstance()->CManager::GetInstance()->GetInstance()->GetTexture()->GetAddress(CTexture::ARROW));

	// 敵の接触判定
	Hit();

	// 初期化
	return hr;
}

//==========================================
//  終了処理
//==========================================
void CCourse::Uninit(void)
{
	// 終了
	CObject3D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CCourse::Update(void)
{
	// 状態が切り替わったら削除する
	if (CGameManager::GetState() != CGameManager::STATE_CONCENTRATE)
	{
		Uninit();
	}

	// 更新
	CObject3D::Update();
}

//==========================================
//  描画処理
//==========================================
void CCourse::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ライティングを無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Zテストの無効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 描画
	CObject3D::Draw();

	// アルファブレンディングの設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// アルファテストの無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// Zテストの有効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ライティングを有効化
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================
//  生成処理
//==========================================
CCourse* CCourse::Create(D3DXVECTOR3 start, D3DXVECTOR3 end)
{
	// インスタンス生成
	CCourse* pCourse = new CCourse;

	// NULLチェック
	if (pCourse == nullptr) { return nullptr; }

	// 値を設定
	pCourse->SetInfo(start, end);

	// 初期化処理
	pCourse->Init();

	// 値を返す
	return nullptr;
}

//==========================================
//  ポリゴンの情報を設定する
//==========================================
void CCourse::SetInfo(D3DXVECTOR3 start, D3DXVECTOR3 end)
{
	// ポリゴンの端を保存
	m_start = start;
	m_end = end;

	// 中心座標を設定
	m_pos = (start + end) * 0.5f;

	// ポリゴンの端から端へのベクトルを作成
	D3DXVECTOR3 vecPolygon = end - start;

	// ベクトルの向きを算出
	m_rot.z = atan2f(vecPolygon.y, vecPolygon.x);

	// ポリゴンの横幅を算出
	m_size.x = sqrtf((vecPolygon.x * vecPolygon.x) + (vecPolygon.y * vecPolygon.y));
	m_size.y = POLYGON_HEIGHT;
}

//==========================================
//  敵との当たり判定
//==========================================
void CCourse::Hit()
{
	//当たり判定の生成
	for (int nCntPriority = 0; nCntPriority < PRIORITY_NUM; nCntPriority++)
	{
		//先頭のアドレスを取得
		CObject* pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			//次のアドレスを保存
			CObject* pNext = pObj->GetNext();

			if (pObj->GetType() == CObject::TYPE_ENEMY) //敵の場合
			{
				if (pObj->GetObjState() == CObject::NORMAL) // 通常状態の場合
				{
					// 目標点を取得する
					D3DXVECTOR3 pos = pObj->GetPos();

					// 始点から終点までのベクトルを求める
					D3DXVECTOR3 vecLine = m_end - m_start;

					// 始点から目標点までのベクトルを求める
					D3DXVECTOR3 vecToPos = pos - m_start;

					// 各ベクトルの大きさを求める
					float lengthLine = sqrtf((vecLine.x * vecLine.x) + (vecLine.y * vecLine.y));
					float lengthToPos = sqrtf((vecToPos.x * vecToPos.x) + (vecToPos.y * vecToPos.y));

					// 媒介変数tを求める
					float t = (lengthLine * lengthToPos) / (lengthLine * lengthLine);

					// 目標点から直線に垂線を下した時の交点を求める
					D3DXVECTOR3 posCross = m_start + (t * vecLine);

					// 交点から目標点までのベクトルを求める
					D3DXVECTOR3 vecToCross = pos - posCross;

					// 判定距離の比較
					if (HIT_LENGTH * HIT_LENGTH >= (vecToCross.x * vecToCross.x) + (vecToCross.y * vecToCross.y))
					{
						// 線分の判定
						if (0.0f <= t && t <= 1.0f)
						{
							// 当たっていた時の演出系処理
							CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SLICE);
							CMarker::Create(pos);
							pObj->SetState(CObject::MARKING);
						}
					}
				}
			}

			//次のアドレスにずらす
			pObj = pNext;
		}
	}
}
