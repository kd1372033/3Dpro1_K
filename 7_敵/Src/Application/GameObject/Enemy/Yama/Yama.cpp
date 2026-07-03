#include "Yama.h"

void Yama::Init()
{
	m_model = std::make_shared<KdModelData>();

	m_model->Load("Asset/Models/yama/yama.gltf");

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape
	(
		"Yama",							// 識別用の名前
		m_model,						// 登録したいモデルの形状
		KdCollider::Type::TypeDamage	//当たり判定の種類
	);

}


void Yama::Update()
{
	// ターゲットの座標を取得
	Math::Vector3 targetPos;
	// アドレス先が実在するかどうか調べる
	if (m_target.expired() == false)
	{
		targetPos = m_target.lock()->GetPos();
	}
	// ターゲットへの方向ベクトルを算出
	Math::Vector3 targetDir = targetPos - m_pos;

	// targerDirは正規化前に自分とターゲットの距離がとれる
	float distance = targetDir.Length();
	if (targetDir.Length() < 10)
	{
		// 長さを１にする
		targetDir.Normalize();
		// ターゲットに向かって移動
		m_pos += targetDir * 0.05f;
	}

	// 今向いている方向ベクトル
	Math::Vector3 nowDir = m_mWorld.Backward();
	// 向きたい方向
	Math::Vector3 toDir = targetDir;

	// 内積を求める
	float dot = nowDir.Dot(toDir);	//A・B
	float angle = DirectX::XMConvertToDegrees(acos(dot));

	// 求めた角度が少しでもあるなら
	if (angle >= 0.1f)
	{
		// 回転角度の上限
		if (angle > 5)
		{
			angle = 5;
		}

		// 外積：２つのベクトルに対し垂直なベクトルを算出A×B
		Math::Vector3 cross = nowDir.Cross(toDir);
		if (cross.y >= 0)
		{
			// 外積が上を向いている場合は、右に回転
			m_angle += angle;
			if (m_angle > 360)
			{
				m_angle -= 360;
			}
		}
		else
		{
			// 外積が下を向いている場合は、左に回転
			m_angle -= angle;
			if (m_angle < 0)
			{
				m_angle += 360;
			}
		}

	}

	// 回転行列
	Math::Matrix rotmat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
	// 座標行列
	Math::Matrix transmat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = rotmat * transmat;
}

void Yama::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);

}