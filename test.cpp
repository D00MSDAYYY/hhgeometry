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
    auto  PI{std::numbers::pi_v<param_type>};
    Point p1{0, 0, 0};
    Point p2{10, 0, 0};
    Point p3{0, 30, 0};

   

    std::cout << "\n####################################################### "
                 "CIRCLE: ###########################################";
    std::cout << "\n########################################################"
                 "###################################################";
    Circle circle{
        Vector{p1, p2}
    };

    std::cout << "\n############## 3D POINTS:\n";
    for(coord_type path{0.0}; path < 4; path += 1)
        std::cout << "rad = " << path << "\t" << circle.get3DPoint(path) << "\t|\t"
                  << "rad + 2*PI = " << circle.get3DPoint(path + 2 * PI) << "\n";

    std::cout << "\n############## DERIVATIVES:\n";
    for(coord_type path{0.0}; path < 4; path += 1)
        std::cout << "rad = " << std::setw(4) << std::setprecision(5) << path << "\t\t"
                  << std::setw(4) << std::setprecision(5) << *circle.get1stDerivative(path)
                  << "\t|\t"
                  << "rad + 2*PI = " << std::setw(4) << std::setprecision(5) << path + 2.0 * PI
                  << std::setw(4) << std::setprecision(5) << "\t"
                  << *circle.get1stDerivative(path + 2.0 * PI) << std::endl;

    std::cout << "\n####################################################### ELLIPSE: "
                 "###########################################";
    std::cout << "\n########################################################"
                 "####################################################";
    Ellipse ellipse{
        {p1, p2},
        {p1, p3}
    };

    std::cout << "\n############## 3D POINTS:\n";
    for(coord_type path{0.0}; path < 4; path += 1)
        std::cout << "rad = " << path << "\t" << ellipse.get3DPoint(path) << "\t|\t"
                  << "rad + 2*PI = " << ellipse.get3DPoint(path + 2 * PI) << "\n";

    std::cout << "\n############## DERIVATIVES:\n";
    for(coord_type path{0.0}; path < 4; path += 1)
        std::cout << "rad = " << std::setw(4) << std::setprecision(5) << path << "\t\t"
                  << std::setw(4) << std::setprecision(5) << *ellipse.get1stDerivative(path)
                  << "\t|\t"
                  << "rad + 2*PI = " << std::setw(4) << std::setprecision(5) << path + 2.0 * PI
                  << std::setw(4) << std::setprecision(5) << "\t"
                  << *ellipse.get1stDerivative(path + 2.0 * PI) << std::endl;

    std::cout << "\n####################################################### HELIX: "
                 "############################################";
    std::cout << "\n#########################################################"
                 "##################################################";
    coord_type step{1.0f};
    Helix      helix{
             {p1, p2},
        step
    };

    std::cout << "\n############## 3D POINTS:\n";
    for(coord_type path{0.0}; path < 4; path += 1)
        std::cout << "rad = " << path << "\t" << helix.get3DPoint(path) << "\t|\t"
                  << "rad + 2*PI = " << helix.get3DPoint(path + 2 * PI) << "\n";

    std::cout << "\n############## DERIVATIVES:\n";
    for(coord_type path{0.0}; path < 4; path += 1)
        std::cout << "rad = " << std::setw(4) << std::setprecision(5) << path << "\t\t"
                  << std::setw(4) << std::setprecision(5) << *helix.get1stDerivative(path)
                  << "\t|\t"
                  << "rad + 2*PI = " << std::setw(4) << std::setprecision(5) << path + 2.0 * PI
                  << std::setw(4) << std::setprecision(5) << "\t"
                  << *helix.get1stDerivative(path + 2.0 * PI) << "\n";
}
