#include "hhgeometry.hpp"

#include <cmath>
#include <iomanip>
#include <functional>
#include <iostream>
#include <limits>

using namespace GEO;

auto
distanse(Point p1, Point p2)
{
    return std::sqrt(std::pow(p2.x() - p1.x(), 2) + std::pow(p2.y() - p1.y(), 2)
                     + std::pow(p2.z() - p1.z(), 2));
}

auto
mod(Vector vec)
{
    return distanse(vec.tail(), vec.head());
}

auto
derivative1st(std::function<Point(param_type)> func, param_type t)
{
    bool                        is_ok{true};
    decltype(deriv_type::first) res{};
    try
    {
        auto epsilon{std::numeric_limits<param_type>::epsilon()};
        auto dy{func(t + epsilon).y() - func(t).y()};
        auto dx{func(t + epsilon).x() - func(t).x()};
        for(auto d{epsilon}; dx == 0.0f; d +=epsilon)
        {
            dy = func(t + d).y() - func(t).y();
            dx = func(t + d).x() - func(t).x();
        }
        res = dy / dx;
    }
    catch(const std::exception& e)
    {
        is_ok = false;
    }
    return deriv_type{res, is_ok};
}

Point
circle_func(param_type t, Vector radius)
{
    auto radius_mod{mod(radius)};
    return {radius_mod * std::cos(t) + radius.tail().x(),
            radius_mod * std::sin(t) + radius.tail().y()};
}

Circle::Circle(const Vector& radius)
    : _radius{radius}
{
    _radius.tail().z() = 0.0f;
    _radius.head().z() = 0.0f;
}

Point
Circle::get3DPoint(const param_type t)
{
    return circle_func(t, _radius);
}

deriv_type
Circle::get1stDerivative(const param_type t)
{
    return derivative1st([this](param_type arg) { return circle_func(arg, _radius); }, t);
}

Point
ellipse_func(param_type t, Vector radius_x, Vector radius_y, Point center)
{
    auto x_mod{mod(radius_x)};
    auto y_mod{mod(radius_y)};
    return {x_mod * std::cos(t) + center.x(), y_mod * std::sin(t) + center.y()};
}

Ellipse::Ellipse(Vector rad_x, Vector rad_y, std::optional<Point> center)
{
    _radius_x.tail()     = rad_x.tail();
    _radius_x.head().x() = rad_x.head().x();
    _radius_x.head().y() = _radius_x.tail().y();  //!

    _radius_y.tail()     = rad_y.tail();
    _radius_y.head().x() = _radius_y.tail().x();  //!
    _radius_y.head().y() = rad_y.head().y();

    if(center)
        _center = *center;
    else
        _center = _radius_x.tail();
}

Point
Ellipse::get3DPoint(const param_type t)
{
    return ellipse_func(t, _radius_x, _radius_y, _center);
}

deriv_type
Ellipse::get1stDerivative(const param_type t)
{
    return derivative1st([this](param_type arg)
                         { return ellipse_func(arg, _radius_x, _radius_y, _center); },
                         t);
}

Point
helix_func(param_type t, Vector radius, coord_type step)
{
    auto radius_mod{mod(radius)};

    return {radius_mod * std::cos(t) + radius.tail().x(),
            radius_mod * std::sin(t) + radius.tail().y(),
            step * t};
}

Point
Helix::get3DPoint(const param_type t)
{
    return helix_func(t, _radius, _step);
}

deriv_type
Helix::get1stDerivative(const param_type t)
{
    return derivative1st([this](param_type arg) { return helix_func(arg, _radius, _step); },
                         t);
}
