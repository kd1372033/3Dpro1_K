#include "GameScene.h"
#include"../SceneManager.h"


#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include"../../GameObject/Ground/Ground.h"
#include"../../GameObject/Tank/Tank.h"
#include"../../GameObject/Enemy/Moto/Moto.h"
#include"../../GameObject/Enemy/Yama/Yama.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}
}

void GameScene::Init()
{

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

	// 敵(本さん)
	std::shared_ptr<Moto> moto;
	moto = std::make_shared<Moto>();
	//moto->Init();
	moto->SetPos(Math::Vector3(0.0f, 0.0f, 20.0f));
	moto->SetTarget(tank);
	m_objList.push_back(moto);

	// 敵(山さん)
	std::shared_ptr<Yama> yama;
	yama = std::make_shared<Yama>();
	yama->SetPos(Math::Vector3(0.0f, 0.0f, -20.0f));
	yama->SetTarget(tank);
	//yama->Init();
	m_objList.push_back(yama);
}