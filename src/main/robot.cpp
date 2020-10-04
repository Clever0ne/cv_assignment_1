#include "robot.h"
#include "opencv2/imgproc.hpp"

using namespace std;
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

Size2i Robot::area() const
{
	return m_area;
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

	m_center.x = static_cast<float>(image.cols / 2.0);
	m_center.y = static_cast<float>(image.rows / 2.0);

	return 0;
}

Point2f Robot::center() const
{
	return m_center;
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
	if (image.empty() == true)
	{
		return -1;
	}

	if (image.cols != m_area.width || image.rows != m_area.height)
	{
		return -2;
	}

	auto point = [this](const Point2f poligonCenter, const float x, const float y)
	{
		auto point = cv::Point2f();
		point.x = center().x + (x + poligonCenter.x) * cosf(angle()) - (y + poligonCenter.y) * sinf(angle());
		point.y = center().y + (x + poligonCenter.x) * sinf(angle()) + (y + poligonCenter.y) * cosf(angle());

		point.y = static_cast<float>(m_area.height) - point.y;
		return point;
	};

	auto poligon = [](cv::Mat& image, vector<Point2f>& poligon, const Scalar& color)
	{
		line(image, poligon.front(), poligon.back(), color);
		for (int32_t index = 1; index < poligon.size(); index++)
		{
			line(image, poligon.at(index - 1), poligon.at(index), color);
		}
	};

	auto black = Scalar(0x00, 0x00, 0x00);

	vector<Point2f> hull =
	{
		point(Point2f(),  m_width / 2.0,  m_length / 2.0),
		point(Point2f(), -m_width / 2.0,  m_length / 2.0),
		point(Point2f(), -m_width / 2.0, -m_length / 2.0),
		point(Point2f(),  m_width / 2.0, -m_length / 2.0)
	};

	poligon(image, hull, black);

	vector<Point2f> wheelCenter =
	{
		Point2f( (m_width / 2.0 + m_wheel.width),  (m_length - m_wheel.diameter) / 2.0),
		Point2f(-(m_width / 2.0 + m_wheel.width),  (m_length - m_wheel.diameter) / 2.0),
		Point2f(-(m_width / 2.0 + m_wheel.width), -(m_length - m_wheel.diameter) / 2.0),
		Point2f( (m_width / 2.0 + m_wheel.width), -(m_length - m_wheel.diameter) / 2.0)
	};
		
	for (auto currentWheelCenter : wheelCenter)
	{
		vector<Point2f> currentWheel =
		{
			point(currentWheelCenter, -m_wheel.width / 2.0,  m_wheel.diameter / 2.0),
			point(currentWheelCenter, -m_wheel.width / 2.0, -m_wheel.diameter / 2.0),
			point(currentWheelCenter,  m_wheel.width / 2.0, -m_wheel.diameter / 2.0),
			point(currentWheelCenter,  m_wheel.width / 2.0,  m_wheel.diameter / 2.0)
		};

		poligon(image, currentWheel, black);
	}

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

Wheel Robot::wheel() const
{
	return m_wheel;
}
