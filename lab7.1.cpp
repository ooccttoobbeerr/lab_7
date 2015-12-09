#include <SFML/Graphics.hpp>
#include <iostream> 
#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>


using namespace sf;
using namespace std;

const int RADIUS = 100;
const int X = 100;
const int Y = 100;
const int AMOUNT_DOTS = 60;

Vector2f HOUR_ARROW = { 65, 4 };
Vector2f MINUTE_ARROW = { 80, 3 };
Vector2f SECOND_ARROW = { 95, 2 };

struct Shapes {
	ConvexShape hourArrow;
	ConvexShape minuteArrow;
	ConvexShape secondArrow;
	RectangleShape dot;
}shapes;

void creating_arrows(ConvexShape & arrow, float height, float width, Color color) {
	arrow.setPointCount(3);
	arrow.setPoint(0, Vector2f(0, 0));
	arrow.setPoint(1, Vector2f(height / 2, -width));
	arrow.setPoint(2, Vector2f(height, 0));
	arrow.setPosition(float(X), float(Y));
	arrow.setOrigin(height / 2, -width / 8);
	arrow.setFillColor(color);
}

void draw_arrow(RenderWindow & window, Shapes & shapes)
{
	creating_arrows(shapes.hourArrow, HOUR_ARROW.y, HOUR_ARROW.x, Color::Red);
	window.draw(shapes.hourArrow);
	creating_arrows(shapes.minuteArrow, MINUTE_ARROW.y, MINUTE_ARROW.x, Color::White);
	window.draw(shapes.minuteArrow);
	creating_arrows(shapes.secondArrow, SECOND_ARROW.y, SECOND_ARROW.x, Color::White);
	window.draw(shapes.secondArrow);
}

void draw_dots(RenderWindow & window, Shapes & shape, Vector2f(& coordinatePoints)[AMOUNT_DOTS])
{
	Vector2f coordinatePoint;
	for (int i = 0; i < AMOUNT_DOTS; i++) {
		coordinatePoint.x = X + 90 * cos(i * 6 * float(M_PI) / 180);
		coordinatePoint.y = Y + 90 * sin(i * 6 * float(M_PI) / 180);
		coordinatePoints[i] = { coordinatePoint.x, coordinatePoint.y };
	}

	for (int i = 0; i < AMOUNT_DOTS; i++) {
		if (i % 15 == 0) {
			shape.dot.setSize(Vector2f(5, 5));
			shape.dot.setOrigin(5 / 2, 5 / 2);
			shape.dot.setFillColor(sf::Color::White);
		}
		else if (i % 5 == 0) {
			shape.dot.setSize(Vector2f(3, 3));
			shape.dot.setOrigin(3 / 2, 3 / 2);
			shape.dot.setFillColor(sf::Color::White);
		}
		else {
			shape.dot.setSize(Vector2f(1, 1));
			shape.dot.setOrigin(1 / 2, 1 / 2);
			shape.dot.setFillColor(sf::Color::White);
		}
		shape.dot.setPosition(coordinatePoints[i].x, coordinatePoints[i].y);
		window.draw(shape.dot);
	}
}


int main() 
{
	ContextSettings settings; 
	settings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(200, 200), "Clock", Style::Default, settings);
	Vector2f coordinatePoints[AMOUNT_DOTS];
	SYSTEMTIME sysTime;
	while (window.isOpen()) {
		GetSystemTime(&sysTime);
		shapes.secondArrow.setRotation(float(sysTime.wSecond * 6));
		shapes.minuteArrow.setRotation(float(sysTime.wMinute * 6));
		shapes.hourArrow.setRotation(float((sysTime.wHour + 3) * 30));
		cout << sysTime.wHour + 3 << " " << sysTime.wMinute << " " << sysTime.wSecond << endl;
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		draw_arrow(window, shapes);
		draw_dots(window, shapes, coordinatePoints);
		window.display();
	}
	return 0;
}
