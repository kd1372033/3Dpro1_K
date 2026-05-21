#include "GameScene.h"
#include"../SceneManager.h"

#include"../../Object/Ground/Ground.h"
#include"../../Object/Player/Player.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

	// カメラ処理
	// 左右の入力でカメラを移動させる
	static float x = 0.0f;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		x -= 0.1f;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		x += 0.1f;
	}

	Math::Vector3 camPos = { x,1,-5 };
	Math::Matrix transMat = Math::Matrix::CreateTranslation(camPos);
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

	std::shared_ptr<Player> player;
	player = std::make_shared<Player>();
	m_objList.push_back(player);

}
