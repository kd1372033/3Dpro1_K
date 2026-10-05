#pragma once
class Ground : public KdGameObject
{
public:

	Ground() { Init(); };
	~Ground() {};

	void DrawLit() override;

private:
	void Init() override;

	std::shared_ptr<KdModelData> m_model;

	// 9/10 黒崎授業追加４
	// 水面表現用のテクスチャ
	std::shared_ptr<KdTexture> m_normalTex;
};
