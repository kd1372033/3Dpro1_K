#include "Ground.h"

void Ground::Init()
{
	m_model = std::make_shared<KdModelData>();

	m_model->Load("Asset/Models/Ground/Ground.gltf");

	Math::Matrix scalemat = Math::Matrix::CreateScale(100);
	m_mWorld = scalemat;

	// 9/10 黒崎授業追加５
	m_normalTex = std::make_shared<KdTexture>();
	m_normalTex->Load("Asset/Textures/water.png");

	KdShaderManager::Instance().m_StandardShader.SetWaterNormalTexture(*m_normalTex);
}

void Ground::DrawLit()
{
	// 9/10 黒崎授業追加７
	static Math::Vector2 offset = {};
	offset.x += 0.0005;
	offset.y += 0.0005;
	if (offset.x > 1)
	{
		offset.x -= 1;
	}
	if (offset.y > 1)
	{
		offset.y -= 1;
	}
	KdShaderManager::Instance().m_StandardShader.SetWaterUVOffset(offset);

	// タイリング
	KdShaderManager::Instance().m_StandardShader.SetUVTiling({ 10, 10 });

	// 水面表現有効化
	KdShaderManager::Instance().m_StandardShader.SetWaterEnable(true);
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
	KdShaderManager::Instance().m_StandardShader.SetWaterEnable(false);

}
