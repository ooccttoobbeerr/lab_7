#include <SFML/Graphics.hpp>
#include <iostream> 
#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>


using namespace sf;
using namespace std;

const int RADIUS = 100;
const int START_X = 100;
const int START_Y = 100;
const int AMOUNT_DOTS = 60;
const int SCALE = 90;

Vector2f WINDOW_SIZE = { 200, 200 };

struct Shapes 
{
	RectangleShape backgroung;
	ConvexShape hourArrow;
	ConvexShape minuteArrow;
	ConvexShape secondArrow;
	CircleShape dot;
};

void position_arrow(ConvexShape & arrow, float height, float width) 
{
	arrow.setPointCount(3);
	arrow.setPoint(0, sf::Vector2f(0, 0));
	arrow.setPoint(1, sf::Vector2f(width / 2, -height));
	arrow.setPoint(2, sf::Vector2f(width, 0));
	arrow.setPosition(float(START_X), float(START_Y));
	arrow.setOrigin(width / 2, -height / 8);
}

void position_shapes(Shapes & shape) 
{
	position_arrow(shape.hourArrow, 65, 4);
	shape.hourArrow.setFillColor(Color::Red);
	position_arrow(shape.minuteArrow, 80, 3);
	shape.minuteArrow.setFillColor(Color::White);
	position_arrow(shape.secondArrow, 95, 2);
	shape.secondArrow.setFillColor(Color::White);
	shape.backgroung.setSize(WINDOW_SIZE);
	shape.backgroung.setPosition(0, 0);
	shape.backgroung.setFillColor(Color::Black);
}

void coordinate_dots(Vector2f(& coordinatePoints)[AMOUNT_DOTS]) 
{
	Vector2f coordinatePoint;
	for (int i = 0; i < AMOUNT_DOTS; i++){
		coordinatePoint.x = START_X + SCALE * cos(i * 6 * float(M_PI) / 180);
		coordinatePoint.y = START_Y + SCALE * sin(i * 6 * float(M_PI) / 180);
		coordinatePoints[i] = { coordinatePoint.x, coordinatePoint.y };
	}
}

void draw_dots(RenderWindow & window, Shapes & shape, Vector2f(& coordinatePoints)[AMOUNT_DOTS])
{
	for (int i = 0; i < AMOUNT_DOTS; i++){
		if (i % 15 == 0) {
			shape.dot.setRadius(4);
			shape.dot.setOrigin(4 / 2, 4 / 2);
			shape.dot.setFillColor(sf::Color::White);
		}
		else if (i % 5 == 0){
			shape.dot.setRadius(2);
			shape.dot.setOrigin(2 / 2, 2 / 2);
			shape.dot.setFillColor(sf::Color::White);
		}
		else{
			shape.dot.setRadius(0.5);
			shape.dot.setOrigin(0.5 / 2, 0.5 / 2);
			shape.dot.setFillColor(sf::Color::White);
		}
		shape.dot.setPosition(coordinatePoints[i].x, coordinatePoints[i].y);
		window.draw(shape.dot);
	}
}


int main() 
{
	Shapes shape;
	position_shapes(shape);

	ContextSettings settings; 
	settings.antialiasingLevel = 8;

	RenderWindow window(VideoMode(unsigned int(WINDOW_SIZE.x), unsigned int(WINDOW_SIZE.y)), "Clock", Style::Default, settings);

	Vector2f coordinatePoints[AMOUNT_DOTS];
	SYSTEMTIME sysTime;
	coordinate_dots(coordinatePoints);
	while (window.isOpen()) {
		GetSystemTime(&sysTime);
		shape.secondArrow.setRotation(float(sysTime.wSecond * 6));
		shape.minuteArrow.setRotation(float(sysTime.wMinute * 6));
		shape.hourArrow.setRotation(float((sysTime.wHour + 3) * 30));
		cout << sysTime.wHour + 3 << " " << sysTime.wMinute << " " << sysTime.wSecond << endl;
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(shape.backgroung);
		window.draw(shape.hourArrow);
		window.draw(shape.minuteArrow);
		window.draw(shape.secondArrow);
		draw_dots(window, shape, coordinatePoints);
		window.display();
	}
	return 0;
}