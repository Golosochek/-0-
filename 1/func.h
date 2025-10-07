#ifndef FUNC_H
#define FUNC_H

#include "structs.h"

// Функции для точки
Point readPoint();
void printPoint(const Point& p);

// Функции для круга
Circle readCircle();
void printCircle(const Circle& c);
double circleCircumference(const Circle& c);
double circleArea(const Circle& c);

// Функции для квадрата
Square readSquare();
void printSquare(const Square& s);
double squarePerimeter(const Square& s);
double squareArea(const Square& s);

// Принадлежность точки фигуре
bool isPointInCircle(const Point& p, const Circle& c);
bool isPointInSquare(const Point& p, const Square& s);

// Нахождение точки на контуре
bool isPointOnCircle(const Point& p, const Circle& c);
bool isPointOnSquare(const Point& p, const Square& s);

// Пересечение фигур
bool doCirclesIntersect(const Circle& c1, const Circle& c2);
bool doSquaresIntersect(const Square& s1, const Square& s2);
bool doCircleAndSquareIntersect(const Circle& c, const Square& s);

// Принадлежность фигуры
bool isCircleInCircle(const Circle& inner, const Circle& outer);
bool isSquareInSquare(const Square& inner, const Square& outer);
bool isSquareInCircle(const Square& s, const Circle& c);
bool isCircleInSquare(const Circle& c, const Square& s);

#endif