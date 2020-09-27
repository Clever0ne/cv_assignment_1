#pragma once

#include "robot.h"

class CombatModule
{
public:
	CombatModule(
		const float width = 40, 
		const float length = 60, 
		const cv::Point2f center = cv::Point2f(0, 0), 
		const float angle = 0, 
		const float angularSpeed = 0);
	~CombatModule() = default;

	int32_t rotate(Rotation rotation);

	std::vector<cv::Point2f> points();

	void setAngularSpeed(const float speed);
	float angularSpeed() const;

private:
	cv::Point2f m_center;
	const float m_width;
	const float m_length;
	float m_angle;
	float m_angularSpeed;
};

