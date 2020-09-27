#include "war_robot.h"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

WarRobot::WarRobot(
	const float width, 
	const float length, 
	const Wheel wheel,
	const CombatModule combatModule,
	const cv::Point2f center,
	const float angle,
	const float speed, 
	const float angularSpeed
) : 
	Robot(width, length, wheel, center, angle, speed, angularSpeed),
	m_combatModule(combatModule)
{

}

CombatModule& WarRobot::combatModule(void)
{
	return m_combatModule;
}

int32_t WarRobot::draw(cv::Mat& image)
{
	if (image.cols != area().width || image.rows != area().height)
	{
		return -1;
	}

	auto leftHigh = Point2f();
	leftHigh.x = center().x - (width() / 2.0) * cosf(angle()) - (length() / 2.0) * sinf(angle());
	leftHigh.y = image.rows - (center().y - (width() / 2.0) * sinf(angle()) + (length() / 2.0) * cosf(angle()));

	auto leftLow = Point2f();
	leftLow.x = center().x - (width() / 2.0) * cosf(angle()) + (length() / 2.0) * sinf(angle());
	leftLow.y = image.rows - (center().y - (width() / 2.0) * sinf(angle()) - (length() / 2.0) * cosf(angle()));

	auto rightHigh = Point2f();
	rightHigh.x = center().x + (width() / 2.0) * cosf(angle()) - (length() / 2.0) * sinf(angle());
	rightHigh.y = image.rows - (center().y + (width() / 2.0) * sinf(angle()) + (length() / 2.0) * cosf(angle()));

	auto rightLow = Point2f();
	rightLow.x = center().x + (width() / 2.0) * cosf(angle()) + (length() / 2.0) * sinf(angle());
	rightLow.y = image.rows - (center().y + (width() / 2.0) * sinf(angle()) - (length() / 2.0) * cosf(angle()));

	auto black = Scalar(0x00, 0x00, 0x00);

	line(image, leftHigh, leftLow, black);
	line(image, rightHigh, rightLow, black);
	line(image, leftHigh, rightHigh, black);
	line(image, leftLow, rightLow, black);

	auto points = m_combatModule.points();

	for (auto &point : points)
	{
		auto buf = point;
		point.x = center().x + (buf.x * cosf(angle()) - buf.y * sinf(angle()));
		point.y = image.rows - (center().y + (buf.x * sinf(angle()) + buf.y * cosf(angle())));
	}

	line(image, points.front(), points.back(), black);
	for (int32_t index = 1; index < points.size(); index++)
	{
		line(image, points.at(index - 1), points.at(index), black);
	}

	return 0;
}
