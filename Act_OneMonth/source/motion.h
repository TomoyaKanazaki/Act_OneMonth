//==========================================
//
//  モーションクラス(motion.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _MOTION_H_
#define _MOTION_H_

//==========================================
//  前方宣言
//==========================================
class CModel;

//==========================================
//  モーションクラス定義
//==========================================
class CMotion
{
public:

	//定数定義
#define MAX_NUM (32) //各種データの最大数

	typedef enum
	{
		PLAYER_WAIT = 0, //待機モーション
		PLAYER_WALK, //歩行モーション
		PLAYER_JUMP, //ジャンプモーション
		PLAYER_FALL, //落下モーション
		PLAYER_IAI, //居合モーション
		PLAYER_DEATH, //死亡モーション
		MOTION_NONE
	}MOTION;

	typedef struct
	{
		D3DXVECTOR3 pos; //位置
		D3DXVECTOR3 rot; //角度
	}KEY;

	typedef struct
	{
		int nFrame; //フレーム数
		KEY aKey[MAX_NUM]; //キー情報
	}KEY_INFO;

	typedef struct
	{
		bool bLoop; //ループの有無
		int nNumKey; //キー数
		int nNumModel; //モデル数
		KEY_INFO aKeyInfo[MAX_NUM]; //キー情報
	}INFO;

	CMotion(); //コンストラクタ
	~CMotion(); //デストラクタ

	//メンバ関数
	void Update(void);
	void SetModel(CModel **ppModel, int nNum, MOTION type);
	void Set(MOTION type);
	
	//静的メンバ関数
	static void Load(void);
	static void UnLoad(void);

private:

	//メンバ変数
	CModel **m_ppModel;
	INFO m_Info;
	KEY m_oldKey;
	KEY m_startKey[MAX_NUM];
	int m_nNumModel;
	int m_nCntFrame;
	int m_nCntKey;
	bool m_bMotion;

	//静的メンバ変数
	static INFO m_aInfo[MAX_NUM];
	static int m_nNumMotion;

};

#endif
