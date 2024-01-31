// #include "pch.h" Uncomment for Visual Studio 2017 and earlier
#include "curve_dll\include\Circle.h"
#include "curve_dll\include\Helix3d.h"
#include "curve_dll\include\Ellipse.h"

#include <iostream>
#include <random>
#include <memory>
#include <execution>
#include "numbers"

using std::numbers::pi;
using namespace std::string_view_literals;

void PrintPoint3D(std::ostream& out, const Point3D& p) {
    out << "Point at pi/4: x = "sv << p.x 
        << ", y = "sv << p.y 
        << ", z = "sv << p.z 
        << ".\n"sv;
}
void PrintVector3D(std::ostream& out, const Vector3D& v) {
    out << "Vector at pi/4: x = "sv << v.x 
        << ", y = "sv << v.y 
        << ", z = "sv << v.z 
        << ".\n"sv;
}

void PrintCoordinates(std::ostream& out, std::vector<std::shared_ptr<Curve>>& curves, double phi) {
    for(auto& curve : curves) {
        PrintPoint3D(out, curve->GetPoint3D(phi));
        PrintVector3D(out, curve->GetVector3D(phi));
    }
}

void FillContainers(std::vector<std::shared_ptr<Curve>>& curves, std::vector<std::shared_ptr<Curve>>& circles) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(0., 1000.);

    auto fill_curves = [&gen, &distrib](std::shared_ptr<Curve>& curve) {
        int curve_type = static_cast<int>(distrib(gen)) % 3;
        switch(curve_type) {
        case 0:
            curve = std::make_shared<Ellipse>(distrib(gen), distrib(gen));
            break;
        case 1:
            curve = std::make_shared<Helix3D>(distrib(gen), distrib(gen));
            break;
        case 2:
            curve = std::make_shared<Circle>(distrib(gen));
            break;
        default:
            break;
        }
    };

    //заполняем массив кривых
    for_each(std::execution::par, curves.begin(), curves.end(), fill_curves);

    for(auto& curve : curves) {
        if(curve->IsCircle()) {
            circles.emplace_back(curve);
        }
    }
}

void SortCircles(std::vector<std::shared_ptr<Curve>>& circles) {

    auto comparator = [](std::shared_ptr<Curve>& circle_left, std::shared_ptr<Curve>& circle_right) {
        return circle_left->GetRadius() < circle_right->GetRadius();
    };
    std::sort(std::execution::par, circles.begin(), circles.end(), comparator);
}

double GetCirclesRadiiSum(std::vector<std::shared_ptr<Curve>>& circles) {
    double total_sum_of_radii = 0;
    std::mutex m;
    auto summarize_radii = [&total_sum_of_radii, &m](std::shared_ptr<Curve>& curve) {
        std::lock_guard<std::mutex> guard(m);
        total_sum_of_radii += curve->GetRadius();
    };
    for_each(std::execution::par, circles.begin(), circles.end(), summarize_radii);
    return total_sum_of_radii;
}

int main() {
    int size = 10000;
    std::cout << "Set the amount of curves: "sv;
    std::cin >> size;

    std::vector<std::shared_ptr<Curve>> curves(size);
    std::vector<std::shared_ptr<Curve>> circles; //круг это элипс у которого два радиуса равны или спираль, у которой шаг равен 0
    circles.reserve(size / 3); //здесь мы не знаем размер, но можем предполагать, что он не меньше 1/3 общего размера

    FillContainers(curves, circles);

    PrintCoordinates(std::cout, curves, pi/4);

    SortCircles(circles);

    std::cout << "\nTotal sum of circles radii: "sv << GetCirclesRadiiSum(circles) << std::endl;
    
    system("pause");
}