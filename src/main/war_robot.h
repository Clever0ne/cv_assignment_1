#pragma once

#include "robot.h"
#include "combat_module.h"

class WarRobot : public Robot
{
public:
	WarRobot(
		const float width = 60,
		const float length = 120,
		const Wheel wheel = { 20, 80 },
		const CombatModule combatModule = CombatModule(),
		const cv::Point2f center = cv::Point2f(0, 0),
		const float angle = 0, 
		const float speed = 0, 
		const float angularSpeed = 0
	);
	~WarRobot() = default;

	CombatModule& combatModule();

	int32_t draw(cv::Mat& image);

private:
	CombatModule m_combatModule;
};
