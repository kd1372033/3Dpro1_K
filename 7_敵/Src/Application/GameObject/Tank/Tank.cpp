#include "Tank.h"

#include "../Camera/TPSCamera/TPSCamera.h"
#include "../../Scene/SceneManager.h"

void Tank::Init()
{
	m_model = std::make_shared<KdModelData>();

	m_model->Load("Asset/Models/Tank/Tank.gltf");

	m_pos = {};

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

}

void Tank::Update()
{
	// カメラの回転行列を取得
	Math::Matrix camRotYMat;
	// カメラが存在しているかどうかを確認
	if (m_camera.expired() == false)
	{
		// カメラが存在している
		camRotYMat = m_camera.lock()->GetRotationYMatrix();
	}
	// 方向ベクトル
	Math::Vector3 dir;
	bool moveFlg = false;

	if (GetAsyncKeyState('W') & 0x8000)
	{
		dir += Math::Vector3::TransformNormal({ 0, 0, 1 }, camRotYMat);
		moveFlg = true;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		dir += Math::Vector3::TransformNormal({ -1, 0, 0 }, camRotYMat);
		moveFlg = true;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		dir += Math::Vector3::TransformNormal({ 0, 0, -1 }, camRotYMat);
		moveFlg = true;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		dir += Math::Vector3::TransformNormal({ 1, 0, 0 }, camRotYMat);
		moveFlg = true;
	}

	if (moveFlg == true)
	{
		// 方向ベクトルを正規化：ベクトルの長さを１にする
		dir.Normalize();

		/* 内積：２つのベクトルのなす角を求めるときに使う
		　ベクトルＡ* ベクトルＢ* cos（なす角）
		 　=		1		*		1	 * cos（なす角）
		 　=cas（なす角）
		 　cosをacosで計算すると角度が出る				*/

		  // 今キャラが向いている方向(壁に弾痕が付けたいときとか)
		  // ①キャラの回転行列を作る
		Math::Matrix nowrotmat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));

		//②ベクトルを変形させる
		Math::Vector3 nowDir = Math::Vector3::TransformNormal(Math::Vector3(0, 0, 1), nowrotmat);

		// ※もっと簡単に取る方法
		//dir = m_mWorld.Backward();

		// 向きたい方向
		Math::Vector3 toDir = dir;

		// 内積を求める
		float dot = nowDir.Dot(toDir);	//A・B
		//	   ↑cos（なす角）
		// 角度を出す（ラジアン角）
		float angle = acos(dot);
		angle = DirectX::XMConvertToDegrees(angle);

		// 求めた角度が少しでもあるなら
		if (angle >= 0.1f)
		{
			if (angle > 5)
			{
				// 回転角度の上限を設定
				angle = 5;
			}

			// 外積：２つのベクトルに対し垂直なベクトルを算出A×B
			Math::Vector3 cross = nowDir.Cross(toDir);
			if (cross.y >= 0)
			{
				// 外積が上を向いている
				//angle = angle;
				m_angle += angle;
				if (m_angle > 360)
				{
					m_angle -= 360;
				}
			}
			else
			{
				// 外積が下を向いている
				//angle = -angle;
				m_angle -= angle;
				if (m_angle < 0)
				{
					m_angle += 360;
				}
			}

		}

		KdDebugGUI::Instance().AddLog("%f\n", m_angle);

		// 回転行列
		Math::Matrix rotmat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));

		// 移動処理
		m_pos += dir * 0.3f;
		// 座標行列
		Math::Matrix transmat = Math::Matrix::CreateTranslation(m_pos);

		// 座標の合成（ＳＲＴ）
		m_mWorld = rotmat * transmat;
	}

}

void Tank::PostUpdate()
{

	// レイに当たったリストから一番近いオブジェクトを探す
	// どうやってわかる？→一番遠い距離からの余りを算出して比較する
	//		↓レイの時は余った長さ
	float maxOverLap = 0;	// 初期化！
	Math::Vector3 hitPos;
	bool hit = false;		// 初期化！

	// =====================
	//	球(スフィア)判定
	// =====================
	// 球判定用の変数を作成
	KdCollider::SphereInfo sphere;
	// 球の中心座標
	sphere.m_sphere.Center = m_pos;
	sphere.m_sphere.Center.y += 1.0f;
	// 球の半径を設定
	sphere.m_sphere.Radius = 1.5f;
	// 当たり判定をしたいタイプを設定
	sphere.m_type = KdCollider::Type::TypeDamage;

	// デバッグ
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

	// 球に当たったオブジェクト情報を格納するリスト
	std::list<KdCollider::CollisionResult> retSphereList;
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

	// 球に当たったリストから一番近いオブジェクトを探す！
	//	↓こいつ　レイ判定の時に宣言してるので使いまわす
	maxOverLap = 0;	// 球の時はめり込んだ長さ
	//	↓こいつ　レイ判定の時に宣言してるので使いまわす
	hit = false;
	// 当たった方向を格納する変数
	Math::Vector3 hitDir;
	for (auto& ret : retSphereList)
	{
		// 球にめり込んだ長さが一番長いものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			// 更新
			maxOverLap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;
			hit = true;
		}
	}

	if (hit == true)
	{
		// Z方向への押し戻し無効
		hitDir.z = 0;
		// 正規化（長さを１にする）
		hitDir.Normalize();
		// 押し戻し処理			↓めり込んだ長さ
		m_pos += hitDir * maxOverLap;
		//		↑当たった方向(方向ベクトルは長さ１)
	}
}

void Tank::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
