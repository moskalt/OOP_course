#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
const int windowWidth = 1000;
const int windowHeight = 1000;
const float Radius = 60.f;

class tFigure {
protected:
	float angle = 0;
public:
	//methods
	//virtual void circleRotation() = 0;
	virtual void aroundRotaion(sf::Vector2f v, sf::Transform* t) = 0;
	virtual void centerRotation(sf::Transform* t) = 0;
	virtual sf::CircleShape getObject() = 0;
};

class Circle :public tFigure {
private:
	sf::CircleShape circle;
	float m_x;
	float m_y;
	sf::Color color;
	float circleRadius;
public:
	Circle(float x, float y, sf::Color t_color = sf::Color::Magenta) :
		m_x(x), m_y(y), color(t_color)
	{
		circleRadius =1.29* Radius;
		circle.setFillColor(color);
		circle.setRadius(circleRadius);
		circle.setPosition(m_x, m_y);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
	}

	void aroundRotaion(sf::Vector2f v, sf::Transform* t) override {
		angle = 1;
		circle.rotate(angle);
	}
	void centerRotation(sf::Transform* t) override {
		angle = 0.3;
		t->rotate(angle, { (float)windowWidth / 2, (float)windowHeight / 2 });
	}
	sf::CircleShape getObject() override {
		return this->circle;
	}
};

class Triangle : public tFigure {
private:
	sf::CircleShape triangle;
	float m_x;
	float m_y;
	sf::Color color;
	float triangleRadius;
	float t_angle;
public:
	Triangle(float x, float y, float angle = 0, sf::Color t_color = sf::Color::Magenta) :
		m_x(x), m_y(y), color(t_color), t_angle(angle)
	{
		triangleRadius = Radius;
		triangle.setRadius(triangleRadius);
		triangle.setFillColor(color);
		triangle.setPointCount(3);
		triangle.setRotation(t_angle);
		triangle.setOrigin(triangle.getRadius(), triangle.getRadius());
		triangle.setPosition(m_x, m_y);
	}
	void aroundRotaion(sf::Vector2f v, sf::Transform* t) override {
		angle = 1;
		t->rotate(angle,v);
	}

	void centerRotation(sf::Transform* t) override {
		angle = 0.3;
		t->rotate(angle, { (float)windowWidth / 2, (float)windowHeight / 2 });
	}

	sf::CircleShape getObject() override {
		return this->triangle;
	}
};

class Star {
private:
	sf::Transform t;
	sf::Transform midrota;
	sf::RenderWindow* localWindow;
	float m_x;
	float m_y;
	std::vector<tFigure*> figures;
public:
	Star(sf::RenderWindow* window)
	{
		localWindow = window;
		m_y = windowHeight - Radius * 2.5;
		m_x = windowWidth / 2;
		figures.push_back(new Circle(m_x, m_y));
		figures.push_back(new Triangle(m_x, m_y - 1.5 * Radius));
		figures.push_back(new Triangle(m_x - 1.5 * Radius, m_y, -90));
		figures.push_back(new Triangle(m_x, m_y + 1.5 * Radius, 180));
		figures.push_back(new Triangle(m_x + 1.5 * Radius, m_y, 90));
	}

	void aroundRotaion() {
		for (size_t i = 1; i < figures.size(); i++) {
			figures[i]->aroundRotaion(figures[0]->getObject().getPosition(), &t);
		}
	}
	void centerRotation() {
		for (auto &item : figures) {
			item->centerRotation(&midrota);
		}
	}
	void drawStar() {
		for (auto& item : figures) {
			localWindow->draw(item->getObject(), t);
			localWindow->draw(item->getObject(), midrota);
		}
	}
};