#include "GameScene.h"
#include "../SceneManager.h"

#include "../../Object/Ground/Ground.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Back/Back.h"
#include "../../Object/Cannon/Cannon.h"
#include "../../Object/Enemy/Enemy.h"
#include "../../Object/Ghost/Ghost.h"

void GameScene::Event()
{
	KdDebugGUI::Instance().ClearLog();
	KdDebugGUI::Instance().AddLog("%d", m_objList.size());

	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

	// カメラ処理
	// 左右の入力でカメラを移動させる
	/*static float x = 0.0f;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		x -= 0.1f;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		x += 0.1f;
	}*/

	Math::Vector3 camPos = { 0,1,-5 };
	Math::Matrix transMat = Math::Matrix::CreateTranslation(camPos + m_player->GetPos());
	m_camera->SetCameraMatrix(transMat);
}

void GameScene::Init()
{
	// カメラを追加
	m_camera = std::make_unique<KdCamera>();

	// 地面を追加
	// ①ポインタを作る
	std::shared_ptr<Ground> ground;

	// ②実体化
	ground = std::make_shared<Ground>();
	// ③初期化
	// ※黒崎授業ではコンストラクタでInit関数を呼んでいるので不要

	// ④オブジェクトリストに追加
	m_objList.push_back(ground);
	//AddObject(ground); // これでも可

	m_player = std::make_shared<Player>();
	m_objList.push_back(m_player);

	std::shared_ptr<Back> back;
	back = std::make_shared<Back>();
	m_objList.push_back(back);

	//キャノン追加
	std::shared_ptr<Cannon> cannon;
	cannon = std::make_shared<Cannon>();
	m_objList.push_back(cannon);

	// 敵追加(5体)
	std::shared_ptr<Enemy> enemy;
	// オブジェクト指向
	for (int i = 0; i < 5; ++i)
	{
		enemy = std::make_shared<Enemy>();
		enemy->SetPos({ -20.0f + (float)i, 3.0f, 0.0f });
		m_objList.push_back(enemy);
	}

	// ゴースト追加
	std::shared_ptr<Ghost> ghost;
	ghost = std::make_shared<Ghost>();
	ghost->SetTarget(m_player);
	m_objList.push_back(ghost);
}
