#include "GameScene.h"
#include"../SceneManager.h"


#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include"../../GameObject/Ground/Ground.h"
#include"../../GameObject/Tank/Tank.h"
#include "../../GameObject/Grass/Grass.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

	// 10/8 黒崎授業追加１１
	// 風を操作する
	static int ang = 0;
	ang += 1;
	if (ang > 360)
	{
		ang -= 360;
	}
	float w = sin(DirectX::XMConvertToRadians(ang));
	KdShaderManager::Instance().SetWindValue({ w,0,0 });
}

void GameScene::Init()
{
	// 10/8 黒崎授業追加１０
	// 風を有効化
	KdShaderManager::Instance().SetWindEnable(true);

	// カメラはInit()を呼ぶ
	std::shared_ptr<TPSCamera> camera;
	camera = std::make_shared<TPSCamera>();
	camera->Init();
	m_objList.push_back(camera);

	// 地面
	std::shared_ptr<Ground> ground;
	ground = std::make_shared<Ground>();
	//ground->Init();
	m_objList.push_back(ground);

	// 戦車
	std::shared_ptr<Tank> tank;
	tank = std::make_shared<Tank>();
	//tank->Init();
	m_objList.push_back(tank);

	// カメラに戦車をセット（カメラが戦車を追従する）
	camera->SetTarget(tank);

	// 戦車にカメラをセット（tankクラスがカメラを参照したい）
	tank->SetCamera(camera);


	// 草
	std::shared_ptr<Grass> grass;
	for (int i = 0; i < 1000; i++)
	{
		grass = std::make_shared<Grass>();
		//grass->SetPos({ KdRandom::GetFloat(-100.0f, 100.0f), 0, KdRandom::GetFloat(-100.0f, 100.0f) });
		m_objList.push_back(grass);
	}
}