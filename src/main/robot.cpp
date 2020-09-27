#include "robot.h"
#include "opencv2/imgproc.hpp"

using namespace cv;

Robot::Robot(
	const float width, 
	const float length, 
	const Wheel wheel, 
	const cv::Point2f center, 
	const float angle, 
	const float speed, const float angularSpeed
) :
	m_width(width),
	m_length(length),
	m_wheel(wheel),
	m_center(center),
	m_angle(angle),
	m_speed(speed),
	m_angularSpeed(speed)
{
	auto white = Scalar(0xFF, 0xFF, 0xFF);
	auto size = Size(1080, 720);
	auto area = Mat(size, CV_8UC3, white);
	
	setArea(area);
	setCenter(area);
}

void Robot::setSpeed(const float speed)
{
	m_speed = speed;
}

float Robot::speed() const
{
	return m_speed;
}

void Robot::setAngularSpeed(const float angularSpeed)
{
	m_angularSpeed = angularSpeed;
}

float Robot::angularSpeed() const
{
	return m_angularSpeed;
}

void Robot::setArea(Size2i area)
{
	m_area = area;
}

int32_t Robot::setArea(Mat image)
{
	if (image.empty() == true)
	{
		return -1;
	}
	m_area.width = image.cols;
	m_area.height = image.rows;

	return 0;
}

int32_t Robot::setCenter(float centerX, float centerY)
{
	m_center.x = centerX;
	m_center.y = centerY;

	return 0;
}

int32_t Robot::setCenter(cv::Mat image)
{
	if (image.empty() == true)
	{
		return -1;
	}

	m_center.x = (float)image.cols / 2.0;
	m_center.y = (float)image.rows / 2.0;

	return 0;
}

int32_t Robot::move(Direction direction)
{
	switch (direction)
	{
		case Direction::FORWARD:
		{
			m_center.y += m_speed * cosf(m_angle) ;
			m_center.x -= m_speed * sinf(m_angle);
			break;
		}
		case Direction::BACK:
		{
			m_center.y -= m_speed * cosf(m_angle);
			m_center.x += m_speed * sinf(m_angle);
			break;
		}
		case Direction::LEFT:
		{
			m_center.y -= m_speed * sinf(m_angle);
			m_center.x -= m_speed * cosf(m_angle);
			break;
		}
		case Direction::RIGHT:
		{
			m_center.y += m_speed * sinf(m_angle);
			m_center.x += m_speed * cosf(m_angle);
			break;
		}
		default:
		{
			break;
		}
	}

	return 0;
}

int32_t Robot::rotate(Rotation rotation)
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

int32_t Robot::go(Direction direction, Rotation rotation)
{
	move(direction);
	rotate(rotation);

	return 0;
}

int32_t Robot::draw(cv::Mat &image)
{
	if (image.cols != m_area.width || image.rows != m_area.height)
	{
		return -1;
	}

	auto leftHigh = Point2f();
	leftHigh.x = m_center.x - (m_width / 2.0) * cosf(m_angle) - (m_length / 2.0) * sinf(m_angle);
	leftHigh.y = m_area.height - (m_center.y - (m_width / 2.0) * sinf(m_angle) + (m_length / 2.0) * cosf(m_angle));

	auto leftLow = Point2f();
	leftLow.x = m_center.x - (m_width / 2.0) * cosf(m_angle) + (m_length / 2.0) * sinf(m_angle);
	leftLow.y = m_area.height - (m_center.y - (m_width / 2.0) * sinf(m_angle) - (m_length / 2.0) * cosf(m_angle));

	auto rightHigh = Point2f();
	rightHigh.x = m_center.x + (m_width / 2.0) * cosf(m_angle) - (m_length / 2.0) * sinf(m_angle);
	rightHigh.y = m_area.height - (m_center.y + (m_width / 2.0) * sinf(m_angle) + (m_length / 2.0) * cosf(m_angle));

	auto rightLow = Point2f();
	rightLow.x = m_center.x + (m_width / 2.0) * cosf(m_angle) + (m_length / 2.0) * sinf(m_angle);
	rightLow.y = m_area.height - (m_center.y + (m_width / 2.0) * sinf(m_angle) - (m_length / 2.0) * cosf(m_angle));

	auto black = Scalar(0x00, 0x00, 0x00);

	line(image, leftHigh, leftLow, black);
	line(image, rightHigh, rightLow, black);
	line(image, leftHigh, rightHigh, black);
	line(image, leftLow, rightLow, black);

	return 0;
}

float Robot::angle() const
{
	return m_angle;
}

float Robot::width() const
{
	return m_width;
}

float Robot::length() const
{
	return m_length;
}

Point2f Robot::center() const
{
	return m_center;
}

Size2i Robot::area() const
{
	return m_area;
}
