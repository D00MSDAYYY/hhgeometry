#include "hhgeometry.hpp"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numbers>
#include <random>
#include <vector>

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
    auto                       PI{std::numbers::pi_v<param_type>};

    std::default_random_engine dre{
        uint32_t(std::chrono::system_clock::now().time_since_epoch().count())};
    std::uniform_real_distribution<coord_type> distr_real(0, 100.0f);
    std::uniform_int_distribution<int>         distr_int(1, 3);

    int                                        size{10};
    std::vector<Object::Ptr>                   geo_objects{};
    for(int i{0}; i < size; ++i)
    {
        auto choice{distr_int(dre)};
        if(choice == 1)  // circle
        {
            Point  p0{distr_real(dre)};
            Point  p1{distr_real(dre)};
            Vector vec0{p0, p1};
            geo_objects.push_back(std::move(Object::Ptr{new Circle{vec0}}));
        }
        if(choice == 2)  // ellipse
        {
            Point  p0{distr_real(dre)};
            Point  p1{distr_real(dre)};
            Vector vec0{p0, p1};
            Point  p2{distr_real(dre)};
            Point  p3{distr_real(dre)};
            Vector vec1{p2, p3};
            geo_objects.push_back(std::move(Object::Ptr{
                new Ellipse{vec0, vec1}
            }));
        }
        if(choice == 3)  // helix
        {
            Point      p0{distr_real(dre)};
            Point      p1{distr_real(dre)};
            Vector     vec0{p0, p1};
            coord_type step{distr_real(dre)};
            geo_objects.push_back(std::move(Object::Ptr{
                new Helix{vec0, step}
            }));
        }
    }

    for(auto point{PI / 4.0f}; auto& object: geo_objects)
        std::cout << object->get3DPoint(point)
                  << "\t derivative = " << *object->get1stDerivative(point) << "\n";
    std::vector<std::reference_wrapper<Object::Ptr>> ref_cirles{};

    for(auto& object: geo_objects)
    {
        auto is_circle{dynamic_cast<Circle*>(object.get())};
        if(is_circle) ref_cirles.push_back(object);
    }

    std::sort(ref_cirles.begin(),
              ref_cirles.end(),
              [](const auto& l, const auto& r)
              {
                  auto   circle_l{*static_cast<Circle*>(l.get().get())};
                  Vector v_l{circle_l};
                  auto   circle_r{*static_cast<Circle*>(r.get().get())};
                  Vector v_r{circle_r};

                  return v_l < v_r;
              });


              for(auto& elem : ref_cirles)
              {
                  auto   circle_l{*static_cast<Circle*>(elem.get().get())};
                  Vector v_l{circle_l};

                  std::cout << ">> " << coord_type(v_l) << std::endl;
              }
}
