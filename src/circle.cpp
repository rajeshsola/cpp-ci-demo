#include "shapes/circle.hpp"

#include <cmath>
#include <numbers>
#include <stdexcept>

namespace shapes {

Circle::Circle(const double radius) : radius_(radius) {
    if (!std::isfinite(radius_) || radius_ <= 0.0) {
        throw std::invalid_argument("circle radius must be positive and finite");
    }
}

double Circle::area() const noexcept {
    return std::numbers::pi_v<double> * radius_ * radius_;
}

double Circle::perimeter() const noexcept {
    return 2.0 * std::numbers::pi_v<double> * radius_;
}

std::string_view Circle::name() const noexcept {
    return "Circle";
}

double Circle::radius() const noexcept {
    return radius_;
}

}  // namespace shapes