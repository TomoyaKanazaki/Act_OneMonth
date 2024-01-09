//==========================================
//
//  テクスチャ管理クラス(texture.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//==========================================
//  マクロ定義
//==========================================
#define MAX_TEXTURE (256) //使用するテクスチャの最大数

//==========================================
//  テクスチャ管理クラス
//==========================================
class CTexture
{
public:
	//テクスチャの種類の列挙型定義
	enum TEXTURE
	{
		BG = 0, //背景
		NUMBER, //数字
		TITLE, //タイトル
		CLEAR, //ゲームクリア
		OVER, //ゲームオーバー
		FIELD, //床
		ARROW, //矢印
		SLASH, //斬撃エフェクト
		SLICE, //ｼﾞｬｷﾝｼﾞｬｷﾝ
		KATANA, //刀
		MARKER, //マーカー
		WATER, //水
		SKY, //空
		ENEMY_00, //敵
		ENEMY_01, //敵
		ENEMY_02, //敵
		ENEMY_03, //敵
		ENEMY_04, //敵
		TUTORIAL_00, //チュートリアル00
		TUTORIAL_01, //チュートリアル01
		TUTORIAL_02, //チュートリアル02
		LEAF, //葉っぱ
		OHUDA, // お札
		EFFECT, // エフェクト
		TEXTURE_MAX
	};

	CTexture(); //コンストラクタ
	~CTexture(); //デストラクタ

	//メンバ関数
	HRESULT Load(void); //テクスチャのロード
	void UnLoad(void); //テクスチャの破棄
	int Regist(const char *pFilName); //テクスチャの登録
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx) { return m_apTexture[nIdx]; } //テクスチャの取得
	int GetNum(void) { return m_nNumAll; }

	//静的メンバ関数
	static bool GetLoadState(void) { return m_bLoad; }; //テクスチャの読み込み状態を取得

private:

	//メンバ変数
	LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXTURE]; //テクスチャ情報
	char m_sFilePass[MAX_TEXTURE][256]; //既に読み込まれているテクスチャのパス
	int m_nNumAll; //テクスチャの総数

	//静的メンバ変数
	static bool m_bLoad;

};

#endif
