#include "structs.h"
#include <cmath>
#include <iostream>

using namespace std;

const double EPSILON = 1e-5;

bool areEqual(double a, double b) {
    return fabs(a - b) < EPSILON;
}

bool arePointsEqual(const Point& p1, const Point& p2) {
    return areEqual(p1.x, p2.x) && areEqual(p1.y, p2.y);
}

// Функции для точки
Point readPoint() {
    Point p;
    cout << "Введите координаты точки (x y): ";
    cin >> p.x >> p.y;
    return p;
}

void printPoint(const Point& p) {
    cout << "(" << p.x << ", " << p.y << ")";
}

// Функции для круга
Circle readCircle() {
    Circle c;
    cout << "Введите координаты центра круга (x y): ";
    cin >> c.center.x >> c.center.y;
    cout << "Введите радиус круга: ";
    cin >> c.radius;
    return c;
}

void printCircle(const Circle& c) {
    cout << "Круг: центр ";
    printPoint(c.center);
    cout << ", радиус = " << c.radius;
}

double circleCircumference(const Circle& c) {
    return 2 * 3.14 * c.radius;
}

double circleArea(const Circle& c) {
    return 3.14 * c.radius * c.radius;
}

// Функции для квадрата
Square readSquare() {
    Square s;
    cout << "Введите координаты левого верхнего угла квадрата (x y): ";
    cin >> s.topLeft.x >> s.topLeft.y;
    cout << "Введите длину стороны квадрата: ";
    cin >> s.side;
    return s;
}

void printSquare(const Square& s) {
    cout << "Квадрат: левый верхний угол ";
    printPoint(s.topLeft);
    cout << ", сторона = " << s.side;
}

double squarePerimeter(const Square& s) {
    return 4 * s.side;
}

double squareArea(const Square& s) {
    return s.side * s.side;
}

// Принадлежность точки фигуре
bool isPointInCircle(const Point& p, const Circle& c) {
    double dx = p.x - c.center.x;
    double dy = p.y - c.center.y;
    double distanceSquared = dx * dx + dy * dy;
    return distanceSquared < c.radius * c.radius - EPSILON;
}

bool isPointInSquare(const Point& p, const Square& s) {
    return (p.x > s.topLeft.x + EPSILON && 
            p.x < s.topLeft.x + s.side - EPSILON &&
            p.y < s.topLeft.y - EPSILON && 
            p.y > s.topLeft.y - s.side + EPSILON);
}

// Нахождение точки на контуре
bool isPointOnCircle(const Point& p, const Circle& c) {
    double dx = p.x - c.center.x;
    double dy = p.y - c.center.y;
    double distanceSquared = dx * dx + dy * dy;
    double radiusSquared = c.radius * c.radius;
    return areEqual(distanceSquared, radiusSquared);
}

bool isPointOnSquare(const Point& p, const Square& s) {
    bool onLeft = areEqual(p.x, s.topLeft.x) && (p.y <= s.topLeft.y && p.y >= s.topLeft.y - s.side);
    bool onRight = areEqual(p.x, s.topLeft.x + s.side) && (p.y <= s.topLeft.y && p.y >= s.topLeft.y - s.side);
    bool onTop = areEqual(p.y, s.topLeft.y) && (p.x >= s.topLeft.x && p.x <= s.topLeft.x + s.side);
    bool onBottom = areEqual(p.y, s.topLeft.y - s.side) && (p.x >= s.topLeft.x && p.x <= s.topLeft.x + s.side);
    
    return onLeft || onRight || onTop || onBottom;
}

// Пересечение фигур
bool doCirclesIntersect(const Circle& c1, const Circle& c2) {
    double dx = c1.center.x - c2.center.x;
    double dy = c1.center.y - c2.center.y;
    double distance = sqrt(dx * dx + dy * dy);
    double sumRadii = c1.radius + c2.radius;
    double diffRadii = fabs(c1.radius - c2.radius);
    
    return distance <= sumRadii + EPSILON && distance >= diffRadii - EPSILON;
}

bool doSquaresIntersect(const Square& s1, const Square& s2) {
    // Проверяем пересечение по осям X и Y
    bool xOverlap = !(s1.topLeft.x + s1.side < s2.topLeft.x - EPSILON || 
                     s2.topLeft.x + s2.side < s1.topLeft.x - EPSILON);
    bool yOverlap = !(s1.topLeft.y - s1.side > s2.topLeft.y + EPSILON || 
                     s2.topLeft.y - s2.side > s1.topLeft.y + EPSILON);
    
    return xOverlap && yOverlap;
}

bool doCircleAndSquareIntersect(const Circle& c, const Square& s) {
    // Находим ближайшую точку квадрата к центру круга
    double closestX = max(s.topLeft.x, min(c.center.x, s.topLeft.x + s.side));
    double closestY = min(s.topLeft.y, max(c.center.y, s.topLeft.y - s.side));
    
    // Проверяем, находится ли эта точка на окружности
    double dx = c.center.x - closestX;
    double dy = c.center.y - closestY;
    double distanceSquared = dx * dx + dy * dy;
    
    return distanceSquared <= c.radius * c.radius + EPSILON;
}

// Принадлежность фигуры
bool isCircleInCircle(const Circle& inner, const Circle& outer) {
    double dx = inner.center.x - outer.center.x;
    double dy = inner.center.y - outer.center.y;
    double distance = sqrt(dx * dx + dy * dy);
    return distance + inner.radius <= outer.radius + EPSILON;
}

bool isSquareInSquare(const Square& inner, const Square& outer) {
    return (inner.topLeft.x >= outer.topLeft.x - EPSILON &&
            inner.topLeft.y <= outer.topLeft.y + EPSILON &&
            inner.topLeft.x + inner.side <= outer.topLeft.x + outer.side + EPSILON &&
            inner.topLeft.y - inner.side >= outer.topLeft.y - outer.side - EPSILON);
}

bool isSquareInCircle(const Square& s, const Circle& c) {
    // Проверяем, что все углы квадрата находятся внутри круга
    Point corners[4] = {
        {s.topLeft.x, s.topLeft.y},
        {s.topLeft.x + s.side, s.topLeft.y},
        {s.topLeft.x, s.topLeft.y - s.side},
        {s.topLeft.x + s.side, s.topLeft.y - s.side}
    };
    
    for (int i = 0; i < 4; i++) {
        double dx = corners[i].x - c.center.x;
        double dy = corners[i].y - c.center.y;
        double distanceSquared = dx * dx + dy * dy;
        if (distanceSquared > c.radius * c.radius - EPSILON) {
            return false;
        }
    }
    return true;
}

bool isCircleInSquare(const Circle& c, const Square& s) {
    return (c.center.x - c.radius >= s.topLeft.x - EPSILON &&
            c.center.x + c.radius <= s.topLeft.x + s.side + EPSILON &&
            c.center.y + c.radius <= s.topLeft.y + EPSILON &&
            c.center.y - c.radius >= s.topLeft.y - s.side - EPSILON);
}