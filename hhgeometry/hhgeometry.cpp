#include "hhgeometry.hpp"

#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>

using namespace GEO;

// finds the distance (mod) between 2 points
auto
distanse(Point p1, Point p2)
{
    return std::sqrt(std::pow(p2.x() - p1.x(), 2) + std::pow(p2.y() - p1.y(), 2)
                     + std::pow(p2.z() - p1.z(), 2));
}

// finds the mod of vector
auto
mod(Vector vec)
{
    return distanse(vec.tail(), vec.head());
}

// find the 1st derivative of function c(t)
// which includes x(t) and y(t)
auto
derivative1st(std::function<Point(param_type)> func, param_type t)
{
    //
    // FOR X
    //

    // ########################################
    // find limit of x(t) from the LEFT side :
    // ########################################
    auto l_dt_x{std::numeric_limits<param_type>::epsilon()};
    auto l_dx{func(t + l_dt_x).x() - func(t).x()};

    while(l_dx == 0.0f && l_dt_x < 1.0f)  // find dt for x (aproximately)
    {
        l_dt_x *= 10.0f;
        l_dx    = func(t + l_dt_x).x() - func(t).x();
    }

    auto part_l_dt_x{l_dt_x / 10.0f};
    while(l_dx != 0.0f && l_dt_x > 0.0f)  // find dt for x (more precisely)
    {
        l_dt_x -= part_l_dt_x;
        l_dx    = func(t + l_dt_x).x() - func(t).x();
    }
    l_dt_x += part_l_dt_x;
    l_dx    = func(t + l_dt_x).x() - func(t).x();
    // ########################################
    // find limit of x(t) from the RIGHT side :
    // ########################################
    auto r_dt_x{std::numeric_limits<param_type>::epsilon()};
    auto r_dx{func(t).x() - func(t - r_dt_x).x()};

    while(r_dx == 0.0f && r_dt_x < 1.0f)  // find dt for x (aproximately)
    {
        r_dt_x *= 10.0f;
        r_dx    = func(t).x() - func(t - r_dt_x).x();
    }

    auto part_r_dt_x{r_dt_x / 10.0f};
    while(r_dx != 0.0f && r_dt_x > 0.0f)  // find dt for x (more precisely)
    {
        r_dt_x -= part_r_dt_x;
        r_dx    = func(t).x() - func(t - r_dt_x).x();
    }
    r_dt_x += part_r_dt_x;
    r_dx    = func(t).x() - func(t - r_dt_x).x();

    //
    // FOR Y
    //

    // ########################################
    // find limit of y(t) from the LEFT side :
    // ########################################
    auto l_dt_y{std::numeric_limits<param_type>::epsilon()};
    auto l_dy{func(t + l_dt_y).y() - func(t).y()};

    while(l_dy == 0.0f && l_dt_y < 1.0f)  // find dt for y (aproximately)
    {
        l_dt_y *= 10.0f;
        l_dy    = func(t + l_dt_y).y() - func(t).y();
    }

    auto part_l_dt_y{l_dt_y / 10.0f};
    while(l_dy != 0.0f && l_dt_y > 0.0f)  // find dt for y (more precisely)
    {
        l_dt_y -= part_l_dt_y;
        l_dy    = func(t + l_dt_y).y() - func(t).y();
    }
    l_dt_y += part_l_dt_y;
    l_dy    = func(t + l_dt_y).y() - func(t).y();
    // ########################################
    // find limit of y(t) from the RIGHT side :
    // ########################################
    auto r_dt_y{std::numeric_limits<param_type>::epsilon()};
    auto r_dy{func(t).y() - func(t - r_dt_y).y()};

    while(r_dy == 0.0f && r_dt_y < 1.0f)  // find dt for y (aproximately)
    {
        r_dt_y *= 10.0f;
        r_dy    = func(t).y() - func(t - r_dt_y).y();
    }
    auto part_r_dt_y{r_dt_y / 10.0f};
    while(r_dy != 0.0f && r_dt_y > 0.0f)  // find dt for y (more precisely)
    {
        r_dt_y -= part_r_dt_y;
        r_dy    = func(t).y() - func(t - r_dt_y).y();
    }
    r_dt_y += part_r_dt_y;
    r_dy    = func(t).y() - func(t - r_dt_y).y();
    // std::cout << "l_dx " << l_dx << " r_dx " << r_dx << std::endl;
    // std::cout << "l_dy " << l_dy << " r_dy " << r_dy << std::endl;
    std::optional<Vector>  res{};  // default is std::nullopt(no derivative)
    deriv_type::value_type aproximation{
        1e-5};                     // acceptable difference between left and right limits
    if(std::abs(l_dy - r_dy) < aproximation && abs(l_dx - r_dx) < aproximation)
    {
        auto avrg_dx{(l_dx + r_dx) / 2.0f};
        auto avrg_dt_x{(l_dt_x + r_dt_x) / 2.0f};
        auto deriv_x{avrg_dx / avrg_dt_x};

        auto avrg_dy{(l_dy + r_dy) / 2.0f};
        auto avrg_dt_y{(l_dt_y + r_dt_y) / 2.0f};
        auto deriv_y{avrg_dy / avrg_dt_y};
        
        res = {
            {0,       0,       0},
            {deriv_x, deriv_y, 0}  // derivative like 3D vector
        };
    }
    return res;
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

std::optional<Vector>
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

std::optional<Vector>
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

std::optional<Vector>
Helix::get1stDerivative(const param_type t)
{
    return derivative1st([this](param_type arg) { return helix_func(arg, _radius, _step); },
                         t);
}

GEO::Vector::operator coord_type() { return mod(*this); }
