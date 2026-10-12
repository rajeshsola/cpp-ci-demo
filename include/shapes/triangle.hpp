#pragma once

#include "shapes/shape.hpp"

namespace shapes {

/** A triangle described by the lengths of its three sides. */
class Triangle final : public Shape {
public:
    /** Create a triangle; throws std::invalid_argument unless the sides form a valid triangle. */
    Triangle(double side_a, double side_b, double side_c);

    [[nodiscard]] double area() const noexcept override;
    [[nodiscard]] double perimeter() const noexcept override;
    [[nodiscard]] std::string_view name() const noexcept override;

private:
    double side_a_;
    double side_b_;
    double side_c_;
};

}  // namespace shapes