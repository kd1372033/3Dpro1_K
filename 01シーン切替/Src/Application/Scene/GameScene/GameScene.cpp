#include "GameScene.h"
#include "../SceneManager.h"

void GameScene::Init()
{
	
}

void GameScene::Update()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
	}

}

void GameScene::DrawSprite()
{
	// キャラ表示もどき
	KdShaderManager::Instance().m_spriteShader.DrawCircle(0,0,100);
}

void GameScene::Release()
{

}