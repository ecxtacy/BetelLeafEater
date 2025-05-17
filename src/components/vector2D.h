#pragma once
#include <iostream> 
#include <ostream>

class Vector2D {
  public:
    float x;
    float y;

    Vector2D();
    Vector2D(float, float);
    ~Vector2D();

    // float x() const;
    // float y() const;

    Vector2D operator+(Vector2D v);

    Vector2D operator-(Vector2D v);

    Vector2D operator*(float scalar);

    bool operator==(Vector2D v);

    Vector2D& operator+=(Vector2D v);

    friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec);

  private:
};