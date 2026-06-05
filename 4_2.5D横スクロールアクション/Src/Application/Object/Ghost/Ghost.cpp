#include "Ghost.h"

#include "../../Scene/SceneManager.h"
#include "../Player/Player.h"

void Ghost::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/char.png");

	// 画像を分割
	m_polygon->SetSplit(6, 6);

	m_pos = {  };
}

void Ghost::Update()
{
	m_polygon->SetUVRect(34);

	// 移動処理
	// プレイヤーにホーミング
	Math::Vector3 targetPos;
	if (m_target.expired() == false)
	{
		// 領域が存在している
		targetPos = m_target.lock()->GetPos();
		//					 ↑shared_ptrに変換
	}
	// ターゲットの方向を算出
	Math::Vector3 dir = (targetPos + Math::Vector3(0.0f, 0.5f, 0.0f)) - m_pos;
	// 方向ベクトルの長さは絶対に「1」
	dir.Normalize();
	// ターゲットの方向に向かって移動
	m_pos += dir * m_speed;

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	// 行列合成　←こいつは絶対Updateの最後!!!!!
	m_mWorld = transMat;
}

void Ghost::DrawLit()
{
	Math::Color color = { 1,1,1,0.25f };
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld, color);
}
