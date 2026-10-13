#include "Grass.h"

void Grass::Init()
{
	m_model = std::make_shared<KdModelData>();
	//m_model->Load("Asset/Models/Grass/Grass.gltf");
	// フライウエイトパターン
	m_model = KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Grass/Grass.gltf");

	Math::Matrix transmat = Math::Matrix::CreateTranslation(KdRandom::GetFloat(-100.0f, 100.0f), 0.0f, KdRandom::GetFloat(-100.0f, 100.0f));
	Math::Matrix scalemat = Math::Matrix::CreateScale(KdRandom::GetInt(1, 3));
	Math::Matrix rotmat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(KdRandom::GetFloat(0.0f, 180.0f)));
	m_mWorld = scalemat * rotmat * transmat;
}

void Grass::DrawLit()
{
	// 裏面カリング解除
	KdShaderManager::Instance().ChangeRasterizerState(KdRasterizerState::CullNone);

	// 10/8 黒崎授業追加１２
	// 風の影響を受ける
	KdShaderManager::Instance().m_StandardShader.SetWindEffectEnable(true);
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);

	// 裏面カリング有効化
	KdShaderManager::Instance().ChangeRasterizerState(KdRasterizerState::CullBack);
}
