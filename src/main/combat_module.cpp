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

vector<cv::Point2f> CombatModule::towerPoints()
{
	auto point = [this](const float x, const float y)
	{
		auto point = cv::Point2f();
		point.x = x * cosf(angle()) - y * sinf(angle());
		point.y = x * sinf(angle()) + y * cosf(angle());
		return point;
	};

	vector<Point2f> points =
	{
		point( m_length / 2.0,  m_width / 4.0),
		point( 0             ,  m_width / 2.0),
		point(-m_length / 2.0,  m_width / 4.0),
		point(-m_length / 2.0, -m_width / 4.0),
		point( 0             , -m_width / 2.0),	
		point( m_length / 2.0, -m_width / 4.0)
	};

	return points;
}

vector<cv::Point2f> CombatModule::gunPoints()
{
	auto point = [this](const float x, const float y)
	{
		auto point = cv::Point2f();
		point.x = (x + length()) * cosf(angle()) - y * sinf(angle());
		point.y = (x + length()) * sinf(angle()) + y * cosf(angle());
		return point;
	};

	vector<Point2f> points =
	{
		point( m_length / 2.0,  m_width / 12.0),
		point(-m_length / 2.0,  m_width / 12.0),
		point(-m_length / 2.0, -m_width / 12.0),
		point( m_length / 2.0, -m_width / 12.0)
	};

	return points;
}

void CombatModule::setCenter(const cv::Point2f center)
{
	m_center = center;
}

cv::Point2f CombatModule::center() const
{
	return m_center;
}

void CombatModule::setAngle(const float angle)
{
	m_angle = angle;
}

float CombatModule::angle() const
{
	return m_angle;
}

float CombatModule::width() const
{
	return m_width;
}

float CombatModule::length() const
{
	return m_length;
}

