#include "hhgeometry.hpp"

#include <iomanip>
#include <iostream>
#include <limits>
#include <numbers>
using namespace GEO;

std::ostream&
operator<<(std::ostream& os, const Point& cp)
{
    auto p{cp};
    os << "x = " << std::setw(4) << std::setprecision(5) << p.x() << "\t y = " << std::setw(4)
       << std::setprecision(5) << p.y() << "\t z = " << std::setw(4) << std::setprecision(5)
       << p.z();
    return os;
}

std::ostream&
operator<<(std::ostream& os, const Vector& cv)
{
    auto v{cv};
    os << "tail : x = " << v.tail().x() << "\t y = " << v.tail().y()
       << "\t z = " << v.tail().z() << "\nhead : x = " << v.head().x()
       << "\t y = " << v.head().y() << "\t z = " << v.head().z() << "\n";
    return os;
}

int
main()
{
    auto PI{std::numbers::pi_v<param_type>};

    // std::cout << "CIRCLE:\n";
    Point  p1{0, 0, 0};
    Point  p2{10, 0, 0};

    // Circle circle{
    //     Vector{p1, p2}
    // };

    // std::cout << "\t3D POINTS:\n";
    // for(double path{0.0}; path < 4; path += 1)
    //     std::cout << "rad = " << path << "\t" << circle.get3DPoint(path) << "\t|\t"
    //               << "rad + 2*PI = " << circle.get3DPoint(path + 2 * PI) << "\n";

    // std::cout << "\tDERIVATIVES:\n";
    // for(double path{0.0}; path < 8; path += 1)
    //     std::cout << "rad = " << std::setw(4) << std::setprecision(5) << path << "\t\t"
    //               << std::setw(4) << std::setprecision(5)
    //               << circle.get1stDerivative(path).first << "\t|\t"
    //               << "rad + 2*PI = " << std::setw(4) << std::setprecision(5) << path + 2.0 * PI
    //               << std::setw(4) << std::setprecision(5) << "\t"
    //               << circle.get1stDerivative(path + 2.0 * PI).first << "\n";

    std::cout << "ELLIPSE:\n";
    Point   p3{0, 30, 0};

    Ellipse ellipse{
        {p1, p2},
        {p1, p3}
    };
    std::cout << Vector{p1, p2} << " " << Vector{p1, p3};
    std::cout << "\t3D POINTS:\n";
    for(double path{0.0}; path < 4; path += 1)
        std::cout << "rad = " << path << "\t" << ellipse.get3DPoint(path) << "\t|\t"
                  << "rad + 2*PI = " << ellipse.get3DPoint(path + 2 * PI) << "\n";

    std::cout << "\tDERIVATIVES:\n";
    for(double path{0.0}; path < 8; path += 1)
        std::cout << "rad = " << std::setw(4) << std::setprecision(5) << path << "\t\t"
                  << std::setw(4) << std::setprecision(5)
                  << ellipse.get1stDerivative(path).first << "\t|\t"
                  << "rad + 2*PI = " << std::setw(4) << std::setprecision(5) << path + 2.0 * PI
                  << std::setw(4) << std::setprecision(5) << "\t"
                  << ellipse.get1stDerivative(path + 2.0 * PI).first << "\n";
}
