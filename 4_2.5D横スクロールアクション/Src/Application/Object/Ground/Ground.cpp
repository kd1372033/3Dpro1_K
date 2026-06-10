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

	
	// 「当てられる側」の処理======
	
	// 当たり判定を付けたいから実体化
	m_pCollider = std::make_unique<KdCollider>();
	// モデルの形状で当たり判定を登録
	m_pCollider->RegisterCollisionShape
	(
		"GroundCollision",				// 識別用の名前
		m_model,						// 登録したいモデルの形状
		KdCollider::Type::TypeGround	//当たり判定の種類
	);
	// ============================

}

void Ground::DrawLit()
{
	static float d = 0;//書くときはメンバー変数で
	if (GetAsyncKeyState('Q') & 0x8000)
	{
		d += 0.01;
		if (d > 1)
		{
			d = 1;
		}
	}
	if (GetAsyncKeyState('W') & 0x8000)
	{
		d -= 0.01;
		if (d < 0)
		{
			d = 0;
		}
	}
	//ディゾルブ(溶ける)									 ↓0～1
	KdShaderManager::Instance().m_StandardShader.SetDissolve(d);

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
