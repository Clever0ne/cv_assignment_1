#include "combat_module.h"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

CombatModule::CombatModule(
	const float width, 
	const float length,
	const cv::Point2f center,
	const float angle, 
	const float angularSpeed
) :
	m_width(width),
	m_length(length),
	m_center(center),
	m_angle(angle),
	m_angularSpeed(angularSpeed)
{

}

void CombatModule::setAngularSpeed(const float angularSpeed)
{
	m_angularSpeed = angularSpeed;
}

float CombatModule::angularSpeed() const
{
	return m_angularSpeed;
}

int32_t CombatModule::rotate(Rotation rotation)
{
	switch (rotation)
	{
		case Rotation::CLOCKWISE:
		{
			m_angle -= m_angularSpeed;
			break;
		}
		case Rotation::COUNTER_CLOCKWISE:
		{
			m_angle += m_angularSpeed;
			break;
		}
		default:
		{
			break;
		}
	}

	return 0;
}

vector<cv::Point2f> CombatModule::points()
{
	vector<Point2f> points =
	{
		Point2f(m_center.x + m_width / 2.0 * cosf(m_angle), 
		        m_center.y + m_width / 2.0 * sinf(m_angle)),
		Point2f(m_center.x + m_width / 4.0 * cosf(m_angle) - m_length / 2.0 * sinf(m_angle),
		        m_center.y + m_width / 4.0 * sinf(m_angle) + m_length / 2.0 * cosf(m_angle)),
		Point2f(m_center.x - m_width / 4.0 * cosf(m_angle) - m_length / 2.0 * sinf(m_angle),
		        m_center.y - m_width / 4.0 * sinf(m_angle) + m_length / 2.0 * cosf(m_angle)),
		Point2f(m_center.x - m_width / 2.0 * cosf(m_angle),
		        m_center.y - m_width / 2.0 * sinf(m_angle)),
		Point2f(m_center.x - m_width / 4.0 * cosf(m_angle) + m_length / 2.0 * sinf(m_angle),
		        m_center.y - m_width / 4.0 * sinf(m_angle) - m_length / 2.0 * cosf(m_angle)),
		Point2f(m_center.x + m_width / 4.0 * cosf(m_angle) + m_length / 2.0 * sinf(m_angle),
		        m_center.y + m_width / 4.0 * sinf(m_angle) - m_length / 2.0 * cosf(m_angle))
	};

	return points;
}
