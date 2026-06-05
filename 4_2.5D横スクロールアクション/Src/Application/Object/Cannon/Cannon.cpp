#include "Cannon.h"

void Cannon::Init()
{
	// m_modelを実体化
	m_model = std::make_shared<KdModelData>();
	// COL1,COL2と名付けて見えない床,壁を作る
	m_model->Load("Asset/Models/NewCannon/NewCannon.gltf");

	Math::Matrix transmat = Math::Matrix::CreateTranslation(-1.0f, -2.0f, 0.0f);
	Math::Matrix scalemat = Math::Matrix::CreateScale(2.0f);
	Math::Matrix rotmat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90.0f));
	// 行列合成
	m_mWorld = scalemat * rotmat * transmat;

	// 「当てられる側」の処理======

	// 当たり判定を付けたいから実体化
	m_pCollider = std::make_unique<KdCollider>();
	// モデルの形状で当たり判定を登録
	m_pCollider->RegisterCollisionShape
	(
		"CannonCollision",				// 識別用の名前
		m_model,						// 登録したいモデルの形状
		KdCollider::Type::TypeGround	//当たり判定の種類
	);
	// ============================

}

void Cannon::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
