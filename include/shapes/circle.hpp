#pragma once

#include "shapes/shape.hpp"

namespace shapes {

/** A circle described by its radius. */
class Circle final : public Shape {
public:
    /** Create a circle; throws std::invalid_argument unless radius is positive and finite. */
    explicit Circle(double radius);

    [[nodiscard]] double area() const noexcept override;
    [[nodiscard]] double perimeter() const noexcept override;
    [[nodiscard]] std::string_view name() const noexcept override;

    /** Return the circle's radius. */
    [[nodiscard]] double radius() const noexcept;

private:
    double radius_;
};

}  // namespace shapes