
#include <iostream>
#include <memory>
#include <optional>
#include <utility>

namespace GEO
{
typedef long double               coord_type;  // type of coordinate axes step
typedef long double               param_type;  // type of parametr in c(t) function
typedef std::optional<param_type> deriv_type;  // result and success flag

// auxiliary class 1
class Point
{
private:
    coord_type _x{0};
    coord_type _y{0};
    coord_type _z{0};

public:
    Point(coord_type x = 0, coord_type y = 0, coord_type z = 0)
        : _x{x},
          _y{y},
          _z{z} {};
    Point(const Point&) = default;
    Point&
    operator=(const Point&) = default;

    // clang-format off
    auto&
    x() {return _x;};
    auto&
    y() {return _y;};
    auto&
    z() {return _z;};

    // clang-format on
};

// auxiliary class 2
class Vector
{
private:
    Point _tail{};
    Point _head{};

public:
    Vector(const Point& t = {}, const Point& h = {})
        : _tail{t},
          _head{h} {};
    Vector(const Vector&) = default;
    Vector&
    operator=(const Vector&) = default;

    operator coord_type(); // returns mod of vector

    // clang-format off
    Point&
    tail() {return _tail;}
    Point&
    head() {return _head;}

    // clang-format on
};

// abstract class for geometric objects
class Object
{
public:
    typedef std::shared_ptr<Object> Ptr;
    Object()              = default;
    Object(const Object&) = default;
    Object&
    operator=(const Object&) = default;

    virtual Point
    get3DPoint(const param_type t) = 0;
    virtual std::optional<Vector>
    get1stDerivative(const param_type t) = 0;
};

class Circle : public Object
{
private:
    Vector _radius;

public:
    Circle(const Vector& radius);
    Circle(const Circle&) = default;
    Circle&
    operator=(const Circle&) = default;

    operator Vector() { return _radius; };

    Point
    get3DPoint(const param_type t) override;

    std::optional<Vector>
    get1stDerivative(const param_type t) override;
};

class Ellipse : public Object
{
private:
    Vector _radius_x{};
    Vector _radius_y{};
    Point  _center{};

public:
    Ellipse(Vector rad_x, Vector rad_y, std::optional<Point> center = std::nullopt);

    Ellipse(const Ellipse&) = default;
    Ellipse&
    operator=(const Ellipse&) = default;

    Point
    get3DPoint(const param_type t) override;

    std::optional<Vector>
    get1stDerivative(const param_type t) override;
};

class Helix : public Object
{
private:
    Vector     _radius{};
    coord_type _step{};

public:
    Helix(Vector radius, coord_type step)
        : _radius{radius},
          _step{step} {};

    Point
    get3DPoint(const param_type t) override;

    std::optional<Vector>
    get1stDerivative(const param_type t) override;
};
}  // namespace GEO
