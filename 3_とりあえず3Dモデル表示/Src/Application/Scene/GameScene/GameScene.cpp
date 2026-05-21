#include "GameScene.h"
#include "../SceneManager.h"

void GameScene::Init()
{
	// カメラの初期化
	m_camera.SetProjectionMatrix(60.0f);
	m_model.Load("Asset/Models/Ship/Ship.gltf");
}

void GameScene::Update()
{
	// カメラの位置を調整
	Math::Vector3 camPos = { 0, 10, -35 };
	Math::Matrix transMat = Math::Matrix::CreateTranslation(camPos);
	m_camera.SetCameraMatrix(transMat);

	// 船の処理
	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_pos.z += 0.1f;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_pos.z -= 0.1f;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_angleY -= 1;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_angleY += 1;
	}

}

void GameScene::DrawSprite()
{

}

void GameScene::DrawLit()
{
	// カメラ採用
	m_camera.SetToShader();

	// 船
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angleY));
	// 基本的な行列の合成は S R T
	Math::Matrix WorldMat = rotMat * transMat;

	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model, WorldMat);
}

void GameScene::Release()
{

}