#pragma once

// クラスを継承するときのみインクルード許可！！！
#include "../BaseScene/BaseScene.h"

class TitleScene : public BaseScene
{
public:
	TitleScene() { Init(); }
	~TitleScene() {}

	// override ･･･ 
	void Init()			override;
	void Update()		override;
	void DrawSprite()	override;
	void Release()		override;

private:

	KdTexture m_tex;
	KdTexture m_starttex;

	float m_alpha;
	float m_delta;
};