#pragma once

#include <string_view>

namespace shapes {

/** Common interface for two-dimensional shapes. */
class Shape {
public:
    virtual ~Shape() = default;

    /** Return the shape's area in square units. */
    [[nodiscard]] virtual double area() const noexcept = 0;

    /** Return the shape's perimeter in linear units. */
    [[nodiscard]] virtual double perimeter() const noexcept = 0;

    /** Return the shape's type name. */
    [[nodiscard]] virtual std::string_view name() const noexcept = 0;
};

}  // namespace shapes