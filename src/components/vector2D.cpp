#include "vector2D.h"

Vector2D::Vector2D() 
{
  x = 0;
  y = 0;
};

Vector2D::Vector2D(float x, float y) 
{
  this->x = x;
  this->y = y;
};

Vector2D::~Vector2D() 
{};

Vector2D Vector2D::operator+(Vector2D v) {
  return Vector2D(x + v.x, y + v.y);
}

Vector2D Vector2D::operator-(Vector2D v) {
  return Vector2D(x - v.x, y - v.y);
}

Vector2D Vector2D::operator*(float scalar) {
  return Vector2D(x * scalar, y * scalar);
}

bool Vector2D::operator==(Vector2D v) {
  return x == v.x && y == v.y;
}

Vector2D& Vector2D::operator+=(Vector2D v) 
{
  x += v.x;
  y += v.y;
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Vector2D& vec)
{
  os << "(" << vec.x << ", " << vec.y << ")";
  return os;
}