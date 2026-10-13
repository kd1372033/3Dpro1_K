#pragma once
class Grass : public KdGameObject
{
public:

	Grass() { Init(); };
	~Grass() {};

	void DrawLit() override;

private:
	void Init() override;

	std::shared_ptr<KdModelData> m_model;
};
