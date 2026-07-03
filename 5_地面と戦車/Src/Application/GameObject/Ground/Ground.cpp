#include "Ground.h"

void Ground::Init()
{
	m_model = std::make_shared<KdModelData>();

	m_model->Load("Asset/Models/Ground/Ground.gltf");

	Math::Matrix scalemat = Math::Matrix::CreateScale(5);
	m_mWorld = scalemat;
}

void Ground::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
