#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

enum class Direction
{
	FORWARD,
	LEFT,
	BACK,
	RIGHT
};

enum class Rotation
{
	CLOCKWISE,
	COUNTER_CLOCKWISE
};

enum class Quadrant
{
	QUADRANT_I,
	QUADRANT_II,
	QUADRANT_III,
	QUADRANT_IV
};

struct Wheel
{
	float width;
	float diameter;
};

struct Border
{
	float right;
	float top;
	float left;
	float bottom;
};

class Robot
{
public:
	Robot(
		const float width = 60,
		const float length = 120,
        const Wheel wheel = { 10, 40 }, 
		const cv::Point2f center = cv::Point2f(0, 0),
		const float angle = M_PI_2, 
		const float speed = 0, 
		const float angularSpeed = 0
	);
	~Robot() = default;

	void setSpeed(const float speed);
	float speed() const;

	void setAngularSpeed(const float speed);
	float angularSpeed() const;

	void setArea(cv::Size2i area);
	int32_t setArea(cv::Mat image);
	cv::Size2i area() const;

	int32_t setCenter(float centerX, float centerY);
	int32_t setCenter(cv::Mat image);
	cv::Point2f center() const;

	void setBorder(const Border border);
	Border border() const;

	virtual int32_t draw(cv::Mat& image);

	int32_t move(Direction direction);
	int32_t rotate(Rotation rotation);

	int32_t go(Direction direction, Rotation rotation);

	float angle() const;
	float width() const;
	float length() const;
	Wheel wheel() const;

private:
	float calculateDisplacement(Direction direction);
	float calculateAngularDisplacement(Rotation rotation);
	virtual std::vector<cv::Point2f> boundaryPoints();

	cv::Point2f m_center;
	float m_angle;
	const float m_width;
	const float m_length;
	const Wheel m_wheel;
	float m_speed;
	float m_angularSpeed;
	cv::Size2i m_area;
	std::vector<cv::Point2f> m_boundaryPoints;
	Border m_border;
};
