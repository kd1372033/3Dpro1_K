#include "Effect.h"

#include "../../Scene/SceneManager.h"

void Effect::Init()
{
	// デバッグ用のポインタを実体化
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/effect.png");

	m_polygon->SetSplit(4, 4);


	Math::Matrix transmat = Math::Matrix::CreateTranslation(-20, 2, 0);

	// 行列合成（基本的な合成はSRT）
	m_mWorld = transmat;
}

void Effect::Update()
{
	//0～11のアニメーション
	m_polygon->SetUVRect(m_anime);
	m_anime += 0.5;
	if (m_anime >= 12)
	{
		// アニメーションが終わったら領域を消したい
		// Expired 期限
		m_isExpired = true;
	}

}

void Effect::PostUpdate()
{
	// 早期リターン　最初の時だけ当たり判定を付ける
	if (m_anime >= 4) return;

	// ================
	// 球判定
	// ================
	// 球判定用の変数
	KdCollider::SphereInfo sphere;
	sphere.m_sphere.Center = GetPos();	// KdGameObjectのGetPosを使いSetPosと同じ座標を使う
	sphere.m_sphere.Radius = 0.3f;
	sphere.m_type = KdCollider::TypeDamage;	// 攻撃判定

	// デバッグ
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius, kRedColor);

	// 全オブジェクトと当たり判定を行う
	for (auto& obj : SceneManager::Instance().GetObjList())
	{

		// 球と当たり判定する！！		↓当たったオブジェクトの情報を格納するリスト
		if (obj->Intersects(sphere, nullptr) == true)
		{						//	↑当たったかどうかを調べるだけならいらない
			//ここに入ってくるものは全て敵
			// 当たった！！
			obj->OnHit();
		}
	}
}

void Effect::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void Effect::DrawBright()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}
