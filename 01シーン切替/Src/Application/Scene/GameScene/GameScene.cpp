#include "GameScene.h"
#include "../SceneManager.h"

void GameScene::Init()
{
	m_tex.Load("Asset/Textures/numbers.png");
}

void GameScene::Update()
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_score += 100;
		if (m_score > 9999999999)
		{
			m_score = 9999999999;
		}
	}

	// 配列に各桁の数値を格納
	unsigned long tmp = m_score;
	for (int i = maxDigits - 1; i >= 0; --i)
	{
		// 下位の桁から抽出し、配列に格納
		m_digits[i] = tmp % 10;
		tmp /= 10;
	}

	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
	}
}

void GameScene::DrawSprite()
{
	// キャラ表示もどき
	KdShaderManager::Instance().m_spriteShader.DrawCircle(0,0,100);

	// スコア表示
	/*
	i++; 後置インクリメント
	++i; 前置インクリメント
	*/
	for (int i = 0; i < maxDigits; ++i)
	{
		Math::Rectangle rc = { 7 * m_digits[i],0,7,10 };

		float posX = -300;

		// 桁別に表示(サイズを10倍にしています)
		KdShaderManager::Instance().m_spriteShader.DrawTex(
			&m_tex,
			posX + (i * 70),	//x
			0,					//y
			70,					//幅
			100,				//高さ
			&rc);
	}
}

void GameScene::Release()
{

}