#include "Bullet.h"

#include "../../Scene/SceneManager.h"

void Bullet::Init()
{
	//デバックワイヤー実体化　★
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	//メモリ確保
	m_model = std::make_shared<KdModelData>();
	//モデルの読み込み
	m_model->Load("Asset/Models/Bullet/Bullet.gltf");

	// トレイルポリゴン初期化
	m_tPoly = std::make_shared<KdTrailPolygon>();
	m_tPoly->SetMaterial("Asset/Textures/jet.png");
	// 板ポリをカメラに向けるようにする(ビルボード処理)した方が見た目がいい
	m_tPoly->SetPattern(KdTrailPolygon::Trail_Pattern::eBillboard);
}

void Bullet::Update()
{
	// マイフレーム寿命を削る
	m_lifespan--;
	if (m_lifespan < 0)
	{
		m_isExpired = true;
	}

	//移動
	m_pos += m_dir * m_speed;

	//座標行列
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = transMat;

	// トレイルポリゴンを追加(ベジエ曲線を使うとカクつかなくなる)
	m_tPoly->AddPoint(m_mWorld);
}

void Bullet::PostUpdate()
{
	//球判定★
	//球判定用　変数
	KdCollider::SphereInfo sphere;
	sphere.m_sphere.Center = m_pos;//中心点
	sphere.m_sphere.Radius = 1.0f;//半径
	sphere.m_type = KdCollider::TypeDamage;//攻撃判定

	//デバック
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius, kRedColor);

	//全オブジェクトと当たり判定を行う
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		//球と当たり判定
		//前までの当たり判定は　↓当たったオブジェクトの情報を格納するリスト
		if (obj->Intersects(sphere, nullptr) == true)
		{//当たったかどうかを調べるだけならリストは必要ない
			//★OnHit★　はKdGameObject　に追加した関数
			//当たった!!!
			obj->OnHit();
		}

	}
}

void Bullet::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Bullet::DrawBright()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);

	// トレイルポリゴン表示
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_tPoly);
}
