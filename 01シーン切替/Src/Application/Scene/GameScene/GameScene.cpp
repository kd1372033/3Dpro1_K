#include "GameScene.h"

void GameScene::Init()
{
	
}

void GameScene::Update()
{
	

}

void GameScene::DrawSprite()
{
	// キャラ表示もどき
	KdShaderManager::Instance().m_spriteShader.DrawCircle(0,0,100);
}

void GameScene::Release()
{

}