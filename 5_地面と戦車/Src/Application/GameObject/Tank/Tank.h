#pragma once
class Tank : public KdGameObject
{
public:

	Tank() { Init(); };
	~Tank() {};

	void Update()  override;
	void DrawLit() override;

private:
	void Init() override;

	std::shared_ptr<KdModelData> m_model;

	float m_angle = 0;


};
