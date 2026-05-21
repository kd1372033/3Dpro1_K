#pragma once

// 前方宣言
class BaseScene;

class SceneManager
{
public:

	// シーンの情報
	// enum･･･列挙型　int型の羅列
	enum SceneType
	{
		Title,	// タイトル
		Game,	// ゲーム
		Result,	// リザルト
	};

	void PreUpdate();	//Updateの前に実行してほしいもの
	void Update();
	void Draw();

	//次のシーンを予約する
	void SetNextScene(SceneType _nextScene)
	{
		m_nextSceneType = _nextScene;
	}

	// 現在のシーンを取得する
	SceneType GetCurrentSceneType() const
	{
		return m_currentSceneType;
	}

private:

	// 保守性を高めるために、他で呼べないようにする
	void Init();
	void Release();
	void ChangeScene(SceneType _sceneType);

	std::shared_ptr<BaseScene> m_currentScene;	// 現在のシーンを管理しているポインタ

	SceneType m_currentSceneType = SceneType::Title;	// 現在のシーンの種類
	SceneType m_nextSceneType = m_currentSceneType;		// 次のシーンの種類

	// シングルトンパターン(デザインパターン)
	// 実体が1つしかないことを保証するデザインパターン
	// ※何でもかんでもシングルトンにはしない！！！
private:

	SceneManager(){Init();}
	~SceneManager() { Release(); }

public:
	static SceneManager& Instance()
	{
		static SceneManager instance;
		return instance;
	}
};