#pragma once

class Player : public KdGameObject
{
public:
	Player() { Init(); }
	~Player(){}

	void Init() override;
	void DrawLit() override;

private:

	std::shared_ptr<KdSquarePolygon> m_polygon;
};