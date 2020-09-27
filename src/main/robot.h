#pragma once

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

enum class Direction
{
	FORWARD,
	BACK,
	LEFT,
	RIGHT
};

enum class Rotation
{
	CLOCKWISE,
	COUNTER_CLOCKWISE
};

struct Wheel
{
	float width;
	float diameter;
};

class Robot
{
public:
	Robot(
		const float width = 60,
		const float length = 120,
        const Wheel wheel = { 20, 80 }, 
		const cv::Point2f center = cv::Point2f(0, 0),
		const float angle = 0, 
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

	virtual int32_t draw(cv::Mat& image);

	int32_t move(Direction direction);
	int32_t rotate(Rotation rotation);

	int32_t go(Direction direction, Rotation rotation);

	float angle() const;
	float width() const;
	float length() const;
	cv::Point2f center() const;
	

private:
	cv::Point2f m_center;
	float m_angle;
	const float m_width;
	const float m_length;
	const Wheel m_wheel;
	float m_speed;
	float m_angularSpeed;
	cv::Size2i m_area;
};
