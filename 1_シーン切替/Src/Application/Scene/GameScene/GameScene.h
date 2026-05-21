#pragma once

#include "../BaseScene/BaseScene.h"


class GameScene : public BaseScene
{
public:
	GameScene() { Init(); }
	~GameScene() {}

	void Init()			override;
	void Update()		override;
	void DrawSprite()	override;
	void Release()		override;

private:

	static const int maxDigits = 10;	//9999999999まで


	KdTexture m_tex;
	// unsigned intなら6万までいける
	unsigned long m_score = 0;
	int m_digits[maxDigits] = {};
};