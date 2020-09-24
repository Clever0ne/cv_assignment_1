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
	Robot() = default;
	Robot(float width, float lenght, Wheel wheel, float speed = 0, float angularSpeed = 0);
	~Robot() = default;

	void setSpeed(const float speed);
	float getSpeed() const;

	void setAngularSpeed(const float speed);
	float getAngularSpeed() const;

	void setArea(cv::Size2i area);
	int32_t setArea(cv::Mat image);

	int32_t setCenter(float centerX, float centerY);
	int32_t setCenter(cv::Mat image);

	int32_t draw(cv::Mat& inputImage, cv::Mat& outputImage);

	int32_t move(Direction direction);
	int32_t rotate(Rotation rotation);

	int32_t go(Direction direction, Rotation rotation);

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

