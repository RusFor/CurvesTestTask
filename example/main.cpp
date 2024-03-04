// #include "pch.h" Uncomment for Visual Studio 2017 and earlier
#include "..\curve_dll\include\Circle.h"
#include "..\curve_dll\include\Helix3d.h"
#include "..\curve_dll\include\Ellipse.h"

#include <iostream>
#include <random>
#include <memory>
#include <execution>
#include <numbers>

using std::numbers::pi;
using std::numbers::e;
using namespace std::string_view_literals;


void PrintPoint3D(std::ostream& out, const curve::Point3D& p) {
	out << "Point at pi/4: x = "sv << p.x
		<< ", y = "sv << p.y
		<< ", z = "sv << p.z
		<< ".\n"sv;
}
void PrintVector3D(std::ostream& out, const curve::Vector3D& v) {
	out << "Vector at pi/4: x = "sv << v.x
		<< ", y = "sv << v.y
		<< ", z = "sv << v.z
		<< ".\n"sv;
}

void PrintCoordinates(std::ostream& out, std::vector<std::shared_ptr<curve::Curve>>& curves, double phi) {
	for(auto& curve : curves) {
		if(curve != nullptr) {
			PrintPoint3D(out, curve->GetPoint3D(phi));
			PrintVector3D(out, curve->GetVector3D(phi));
		}
	}
}

void FillContainer(std::vector<std::shared_ptr<curve::Curve>>& curves) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distrib(-1000., 1000.);

	auto fill_curves = [&gen, &distrib](std::shared_ptr<curve::Curve>& curve) {
		try {
			int curve_type = static_cast<int>(distrib(gen)) % 3;
			switch(curve_type) {
			case 0:
				curve = std::make_shared<curve::Ellipse>(distrib(gen), distrib(gen));
				break;
			case 1:
				curve = std::make_shared<curve::Helix3D>(distrib(gen), distrib(gen));
				break;
			case 2:
				curve = std::make_shared<curve::Circle>(distrib(gen));
				break;
			default:
				break;
			}
		} catch(const std::exception& e) {
			std::cerr << "Error : " << e.what() << std::endl;
		}
	};
	//заполняем массив кривых
	for_each(std::execution::par, curves.begin(), curves.end(), fill_curves);
}

void FillCirclesContainer(std::vector<std::shared_ptr<curve::Curve>>& curves,
						  std::vector<std::shared_ptr<curve::Circle>>& circles) {
	for(const auto& curve : curves) {
		if(curve != nullptr && curve->GetType() == curve::Type::Circle) {
			circles.emplace_back(dynamic_cast<curve::Circle*>(curve.get()));
		}
	}
}

void SortCircles(std::vector<std::shared_ptr<curve::Circle>>& circles) {

	auto comparator = [](std::shared_ptr<curve::Circle>& circle_left, std::shared_ptr<curve::Circle>& circle_right) {
		return circle_left->GetRadius() < circle_right->GetRadius();
	};
	std::sort(std::execution::par, circles.begin(), circles.end(), comparator);
}

double GetCirclesRadiiSum(std::vector<std::shared_ptr<curve::Circle>>& circles) {
	double total_sum_of_radii = 0;
	std::mutex m;
	auto summarize_radii = [&total_sum_of_radii, &m](std::shared_ptr<curve::Circle>& circle) {
		std::lock_guard<std::mutex> guard(m);
		total_sum_of_radii += circle->GetRadius();
	};
	for_each(std::execution::par, circles.begin(), circles.end(), summarize_radii);
	return total_sum_of_radii;
}

int main() {
	size_t size;

	std::cout << "Set the amount of curves: "sv;
	std::cin >> size;

	std::vector<std::shared_ptr<curve::Curve>> curves(size);
	std::vector<std::shared_ptr<curve::Circle>> circles;
	circles.reserve(size / 3); //здесь мы не знаем размер, но можем предполагать, что он не меньше 1/3 общего размера

	FillContainer(curves);

	FillCirclesContainer(curves, circles);

	PrintCoordinates(std::cout, curves, pi / 4);

	SortCircles(circles);

	std::cout << "\nTotal sum of circles radii: "sv << GetCirclesRadiiSum(circles) << std::endl;


	system("pause");
}





