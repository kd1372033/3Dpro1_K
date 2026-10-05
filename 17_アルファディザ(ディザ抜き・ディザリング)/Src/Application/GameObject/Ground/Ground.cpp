#include "Ground.h"

void Ground::Init()
{
	m_model[0] = std::make_shared<KdModelData>();
	m_model[0]->Load("Asset/Models/Ground/Ground.gltf");

	m_model[1] = std::make_shared<KdModelData>();
	m_model[1]->Load("Asset/Models/map/map.gltf");

	Math::Matrix scalemat = Math::Matrix::CreateScale(100);
	m_mWorld = scalemat;
}

void Ground::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model[0], m_mWorld);
	// 行列の初期値
	// 単位行列
	/*
	* 1, 0, 0, 0
	* 0, 1, 0, 0
	* 0, 0, 1, 0
	* 0, 0, 0, 1
	*/
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model[1], Math::Matrix::Identity);
}
