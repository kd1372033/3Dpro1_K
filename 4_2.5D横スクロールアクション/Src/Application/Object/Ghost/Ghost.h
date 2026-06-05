#pragma once



class Ghost : public KdGameObject
{
public:
	Ghost() { Init(); }
	~Ghost() {}

	void Init() override;
	void Update() override;
	void DrawLit() override;

	// ターゲットをセット
	void SetTarget(std::shared_ptr<KdGameObject> _target) { m_target = _target; }

private:

	std::shared_ptr<KdSquarePolygon> m_polygon;
	Math::Vector3 m_pos;

	// ターゲットのポインタ(参照カウンタ)
	std::weak_ptr<KdGameObject> m_target;

	float m_speed = 0.02f;

};