#include "Ground.h"

void Ground::Init()
{
	// m_modelを実体化
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/SideViewMap/SideViewMap.gltf");

	Math::Vector3 scale(5.0f, 1.0f, 1.0f);
	Math::Matrix scalemat = Math::Matrix::CreateScale(scale);

	// ↓全オブジェクトに必要なので親クラスがメンバー変数として保持
	m_mWorld = scalemat;
}

void Ground::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
