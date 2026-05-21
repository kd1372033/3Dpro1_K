#include "TitleScene.h"

#include "../SceneManager.h"

void TitleScene::Init()
{
	m_tex.Load("Asset/Textures/title.png");
	m_starttex.Load("Asset/Textures/start.png");

	m_alpha = 0.0f;
	m_delta = 0.01f;
}

void TitleScene::Update()
{
	m_alpha += m_delta;
	if (m_alpha <= 0.5) { m_delta = 0.01f; }
	else if (m_alpha >= 1) { m_delta = -0.01f; }

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
	}

}

void TitleScene::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0);
	Math::Color color(1, 1, 1, m_alpha);
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_starttex, 0, -200, nullptr, &color);

}

void TitleScene::Release()
{

}