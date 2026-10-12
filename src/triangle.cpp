#include "shapes/triangle.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace shapes {

Triangle::Triangle(const double side_a, const double side_b, const double side_c)
    : side_a_(side_a), side_b_(side_b), side_c_(side_c) {
    if (!std::isfinite(side_a_) || !std::isfinite(side_b_) || !std::isfinite(side_c_) ||
        side_a_ <= 0.0 || side_b_ <= 0.0 || side_c_ <= 0.0) {
        throw std::invalid_argument("triangle sides must be positive and finite");
    }

    const double longest = std::max({side_a_, side_b_, side_c_});
    const double side_sum = side_a_ + side_b_ + side_c_;
    if (longest >= side_sum - longest) {
        throw std::invalid_argument("triangle sides must satisfy the triangle inequality");
    }
}

double Triangle::area() const noexcept {
    const double semiperimeter = perimeter() / 2.0;
    return std::sqrt(semiperimeter * (semiperimeter - side_a_) *
                     (semiperimeter - side_b_) * (semiperimeter - side_c_));
}

double Triangle::perimeter() const noexcept {
    return side_a_ + side_b_ + side_c_;
}

std::string_view Triangle::name() const noexcept {
    return "Triangle";
}

}  // namespace shapes