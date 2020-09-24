#include "robot.h"
#include "opencv2/imgproc.hpp"

using namespace cv;

Robot::Robot(float width, float length, Wheel wheel, float speed, float angularSpeed) :
	m_width(width),
	m_length(length),
	m_wheel(wheel),
	m_speed(speed),
	m_angularSpeed(speed),
	m_angle(0)
{

}

void Robot::setSpeed(const float speed)
{
	m_speed = speed;
}

float Robot::getSpeed() const
{
	return m_speed;
}

void Robot::setAngularSpeed(const float angularSpeed)
{
	m_angularSpeed = angularSpeed;
}

float Robot::getAngularSpeed() const
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

int32_t Robot::draw(cv::Mat& inputImage, cv::Mat& outputImage)
{
	if (inputImage.empty() == true)
	{
		return -1;
	}

	if (inputImage.cols != m_area.width || inputImage.rows != m_area.height)
	{
		return -2;
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

	line(outputImage, leftHigh, leftLow, black);
	line(outputImage, rightHigh, rightLow, black);
	line(outputImage, leftHigh, rightHigh, black);
	line(outputImage, leftLow, rightLow, black);

	return 0;
}
