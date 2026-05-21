#include "Player.h"

void Player::Init()
{
	// 実体化
	m_polygon = std::make_shared<KdSquarePolygon>();

	// テクスチャの設定
	m_polygon->SetMaterial("Asset/Textures/char.png");
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}
