#include "shapes/circle.hpp"
#include "shapes/shape.hpp"
#include "shapes/triangle.hpp"

#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <memory>
#include <stdexcept>

namespace {

TEST(CircleTest, ComputesAreaAndPerimeter) {
    const shapes::Circle circle(2.0);

    EXPECT_NEAR(circle.area(), 4.0 * std::acos(-1.0), 1e-12);
    EXPECT_NEAR(circle.perimeter(), 4.0 * std::acos(-1.0), 1e-12);
    EXPECT_EQ(circle.name(), "Circle");
    EXPECT_DOUBLE_EQ(circle.radius(), 2.0);
}

TEST(CircleTest, RejectsNonPositiveOrNonFiniteRadius) {
    EXPECT_THROW(shapes::Circle(0.0), std::invalid_argument);
    EXPECT_THROW(shapes::Circle(-1.0), std::invalid_argument);
    EXPECT_THROW(shapes::Circle(std::numeric_limits<double>::infinity()), std::invalid_argument);
    EXPECT_THROW(shapes::Circle(std::numeric_limits<double>::quiet_NaN()), std::invalid_argument);
}

TEST(TriangleTest, ComputesAreaAndPerimeter) {
    const shapes::Triangle triangle(3.0, 4.0, 5.0);

    EXPECT_DOUBLE_EQ(triangle.area(), 6.0);
    EXPECT_DOUBLE_EQ(triangle.perimeter(), 12.0);
    EXPECT_EQ(triangle.name(), "Triangle");
}

TEST(TriangleTest, RejectsInvalidSideLengths) {
    EXPECT_THROW(shapes::Triangle(0.0, 4.0, 5.0), std::invalid_argument);
    EXPECT_THROW(shapes::Triangle(-1.0, 4.0, 5.0), std::invalid_argument);
    EXPECT_THROW(shapes::Triangle(1.0, 2.0, 3.0), std::invalid_argument);
    EXPECT_THROW(shapes::Triangle(1.0, 2.0, 4.0), std::invalid_argument);
    EXPECT_THROW(
        shapes::Triangle(std::numeric_limits<double>::infinity(), 4.0, 5.0),
        std::invalid_argument);
}

TEST(ShapeTest, SupportsPolymorphicOwnership) {
    const std::unique_ptr<shapes::Shape> circle = std::make_unique<shapes::Circle>(1.0);
    const std::unique_ptr<shapes::Shape> triangle = std::make_unique<shapes::Triangle>(3.0, 4.0, 5.0);

    EXPECT_EQ(circle->name(), "Circle");
    EXPECT_EQ(triangle->name(), "Triangle");
    EXPECT_GT(circle->area(), 0.0);
    EXPECT_GT(triangle->area(), 0.0);
}

}  // namespace