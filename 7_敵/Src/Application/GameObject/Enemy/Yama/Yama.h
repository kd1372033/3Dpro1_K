#pragma once

class Yama :public KdGameObject
{
public:
	Yama() { Init(); }
	~Yama() {}

	void Update() override;
	void DrawLit() override;

	void SetPos(const Math::Vector3& _pos) override { m_pos = _pos; }

	void SetTarget(const std::shared_ptr<KdGameObject>& target) { m_target = target; }

	void OnHit() override
	{
		m_isExpired = true;
	}

private:
	void Init() override;

	std::shared_ptr<KdModelData> m_model;

	Math::Vector3 m_pos = {};

	// 参照カウンタは増やさない
	std::weak_ptr<KdGameObject> m_target;

	float m_angle = 0;
};