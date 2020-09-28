// Copyright (c) 2017-2020, Lawrence Livermore National Security, LLC and
// other Axom Project Developers. See the top-level COPYRIGHT file for details.
//
// SPDX-License-Identifier: (BSD-3-Clause)

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "axom/klee/GeometryOperators.hpp"
#include "axom/klee/GeometryOperatorsIO.hpp"
#include "KleeMatchers.hpp"
#include "KleeTestUtils.hpp"

#include <array>
#include <memory>
#include <stdexcept>

namespace axom { namespace klee { namespace {

using test::AlmostEqPoint;
using test::AlmostEqMatrix;
using test::AlmostEqVector;
using test::MatchesSlice;
using test::affine;
using test::makePoint;
using test::makeVector;

using ::testing::HasSubstr;

/**
 * Read geometry operators from a string
 * \param startingDimensions the starting dimensions
 * \param input the operators expressed in yaml
 * \return the operators that were read.
 */
std::shared_ptr<const GeometryOperator> readOperators(int startingDimensions,
        const std::string &input) {
    conduit::Node node;
    node.parse(input, "yaml");
    return parseGeometryOperators(node, startingDimensions);
}

/**
 * Read a single operator.
 *
 * \tparam T the expected type of the operator
 * \param startingDimensions the starting dimensions
 * \param input the operator as yaml.
 * \return the read operator
 * \throws std::logic_error if there isn't excatly one operator of
 * the specified type.
 */
template<typename T>
T readSingleOperator(int startingDimensions, const std::string &input) {
    std::string wrappedInput{"-\n"};
    wrappedInput += input;
    std::shared_ptr<const GeometryOperator> genericOperator =
            readOperators(startingDimensions, wrappedInput);
    auto composite = dynamic_cast<const CompositeOperator *>(genericOperator.get());
    if (composite == nullptr) {
        throw std::logic_error("Did not get CompositeOperator");
    }
    if (composite->getOperators().size() != 1u) {
        throw std::logic_error("Did not have exactly one operator");
    }
    auto desired = dynamic_cast<const T *>(composite->getOperators()[0].get());
    if (desired == nullptr) {
        throw std::logic_error("Did not get expected type");
    }
    return *desired;
}

/**
 * Create a matcher to verify an object is a slice with the expected values
 * \param origin the expected origin
 * \param normal the expected normal vector
 * \param up the expected up vector
 * \return a matcher that verifies a SliceOperator is as specified
 */
test::MatchesSliceMatcherP<SliceOperator> isSlice(
        std::array<double, 3> origin, std::array<double, 3> normal,
        std::array<double, 3> up) {
    SliceOperator op{primal::Point3D{origin.data()},
                     primal::Vector3D{normal.data()},
                     primal::Vector3D{up.data()}};
    return MatchesSlice(op);
}

TEST(GeometryOperatorsIO, readTranslation_2D) {
    auto translation = readSingleOperator<Translation>(2, R"(
      translate: [10, 20]
    )");
    EXPECT_EQ(2, translation.startDims());
    EXPECT_EQ(2, translation.endDims());
    EXPECT_THAT(translation.getOffset(),
            AlmostEqVector(makeVector({10, 20, 0})));
}

TEST(GeometryOperatorsIO, readTranslation_3D) {
    auto translation = readSingleOperator<Translation>(3, R"(
      translate: [10, 20, 30]
    )");
    EXPECT_EQ(3, translation.startDims());
    EXPECT_EQ(3, translation.endDims());
    EXPECT_THAT(translation.getOffset(),
            AlmostEqVector(makeVector({10, 20, 30})));
}

TEST(GeometryOperatorsIO, readTranslation_unknownKeys) {
    try {
        readSingleOperator<Translation>(2, R"(
          translate: [10, 20]
          UNKNOWN_KEY: UNKNOWN_VALUE
        )");
        FAIL() << "Should have thrown an exception";
    } catch (const std::invalid_argument &ex) {
        EXPECT_THAT(ex.what(), HasSubstr("translate"));
        EXPECT_THAT(ex.what(), HasSubstr("UNKNOWN_KEY"));
    }
}

TEST(GeometryOperatorsIO, readRotation_2D_requiredOnly) {
    auto rotation = readSingleOperator<Rotation>(2, R"(
      rotate: 45
    )");
    EXPECT_EQ(2, rotation.startDims());
    EXPECT_EQ(2, rotation.endDims());
    EXPECT_DOUBLE_EQ(45, rotation.getAngle());
    EXPECT_THAT(rotation.getCenter(), AlmostEqPoint(makePoint({0, 0, 0})));
    EXPECT_THAT(rotation.getAxis(), AlmostEqVector(makeVector({0, 0, 1})));
}

TEST(GeometryOperatorsIO, readRotation_2D_optionalFields) {
    auto rotation = readSingleOperator<Rotation>(2, R"(
      rotate: 45
      center: [10, 20]
    )");
    EXPECT_EQ(2, rotation.startDims());
    EXPECT_EQ(2, rotation.endDims());
    EXPECT_DOUBLE_EQ(45, rotation.getAngle());
    EXPECT_THAT(rotation.getCenter(), AlmostEqPoint(makePoint({10, 20, 0})));
    EXPECT_THAT(rotation.getAxis(), AlmostEqVector(makeVector({0, 0, 1})));
}

TEST(GeometryOperatorsIO, readRotation_2D_axisNotAllowed) {
    try {
        readSingleOperator<Rotation>(2, R"(
            rotate: 45
            axis: [1, 2, 3]
        )");
        FAIL() << "Should have thrown an exception";
    } catch (const std::invalid_argument &ex) {
        EXPECT_THAT(ex.what(), HasSubstr("rotate"));
        EXPECT_THAT(ex.what(), HasSubstr("axis"));
    }
}

TEST(GeometryOperatorsIO, readRotation_3D_requiredOnly) {
    auto rotation = readSingleOperator<Rotation>(3, R"(
      rotate: 45
      axis: [1, 2, 3]
    )");
    EXPECT_EQ(3, rotation.startDims());
    EXPECT_EQ(3, rotation.endDims());
    EXPECT_DOUBLE_EQ(45, rotation.getAngle());
    EXPECT_THAT(rotation.getCenter(), AlmostEqPoint(makePoint({0, 0, 0})));
    EXPECT_THAT(rotation.getAxis(), AlmostEqVector(makeVector({1, 2, 3})));
}

TEST(GeometryOperatorsIO, readRotation_3D_optionalFields) {
    auto rotation = readSingleOperator<Rotation>(3, R"(
      rotate: 45
      axis: [1, 2, 3]
      center: [4, 5, 6]
    )");
    EXPECT_EQ(3, rotation.startDims());
    EXPECT_EQ(3, rotation.endDims());
    EXPECT_DOUBLE_EQ(45, rotation.getAngle());
    EXPECT_THAT(rotation.getCenter(), AlmostEqPoint(makePoint({4, 5, 6})));
    EXPECT_THAT(rotation.getAxis(), AlmostEqVector(makeVector({1, 2, 3})));
}

TEST(GeometryOperatorsIO, readScale_singleValue) {
    for (int dims = 2; dims <= 3; ++dims) {
        auto scale = readSingleOperator<Scale>(dims, R"(
          scale: 1.2
        )");
        EXPECT_EQ(dims, scale.startDims());
        EXPECT_EQ(dims, scale.endDims());
        EXPECT_DOUBLE_EQ(1.2, scale.getXFactor());
        EXPECT_DOUBLE_EQ(1.2, scale.getYFactor());
        EXPECT_DOUBLE_EQ(1.2, scale.getZFactor());
    }
}

TEST(GeometryOperatorsIO, readScale_2d_array) {
    auto scale = readSingleOperator<Scale>(2, R"(
      scale: [1.2, 3.4]
    )");
    EXPECT_EQ(2, scale.startDims());
    EXPECT_EQ(2, scale.endDims());
    EXPECT_DOUBLE_EQ(1.2, scale.getXFactor());
    EXPECT_DOUBLE_EQ(3.4, scale.getYFactor());
    EXPECT_DOUBLE_EQ(1.0, scale.getZFactor());
}

TEST(GeometryOperatorsIO, readScale_3d_array) {
    auto scale = readSingleOperator<Scale>(3, R"(
      scale: [1.2, 3.4, 5.6]
    )");
    EXPECT_EQ(3, scale.startDims());
    EXPECT_EQ(3, scale.endDims());
    EXPECT_DOUBLE_EQ(1.2, scale.getXFactor());
    EXPECT_DOUBLE_EQ(3.4, scale.getYFactor());
    EXPECT_DOUBLE_EQ(5.6, scale.getZFactor());
}

TEST(GeometryOperatorsIO, readArbitraryMatrix_2D) {
    auto matrixOp = readSingleOperator<ArbitraryMatrixOperator>(2, R"(
      matrix: [10, 20, 30, 40, 50, 60]
    )");
    EXPECT_EQ(2, matrixOp.startDims());
    EXPECT_EQ(2, matrixOp.endDims());
    EXPECT_THAT(matrixOp.toMatrix(), AlmostEqMatrix(affine({
            10, 20, 0, 30,
            40, 50, 0, 60,
            0, 0, 1, 0
    })));
}

TEST(GeometryOperatorsIO, readArbitraryMatrix_3D) {
    auto matrixOp = readSingleOperator<ArbitraryMatrixOperator>(3, R"(
      matrix: [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120]
    )");
    EXPECT_EQ(3, matrixOp.startDims());
    EXPECT_EQ(3, matrixOp.endDims());
    EXPECT_THAT(matrixOp.toMatrix(), AlmostEqMatrix(affine({
            10, 20, 30, 40,
            50, 60, 70, 80,
            90, 100, 110, 120
    })));
}

TEST(GeometryOperatorsIO, readSlice_specifyAll) {
    auto slice = readSingleOperator<SliceOperator>(3, R"(
      slice:
        origin: [1, 2, 3]
        normal: [4, 5, 6]
        up: [-5, 4, 0]
    )");
    EXPECT_THAT(slice, isSlice({1, 2, 3}, {4, 5, 6}, {-5, 4, 0}));
}

TEST(GeometryOperatorsIO, readSlice_x_defaults) {
    auto slice = readSingleOperator<SliceOperator>(3, R"(
      slice:
        x: 10
    )");
    EXPECT_THAT(slice, isSlice({10, 0, 0}, {1, 0, 0}, {0, 0, 1}));
}

TEST(GeometryOperatorsIO, readSlice_x_optionals) {
    auto slice = readSingleOperator<SliceOperator>(3, R"(
      slice:
        x: 10
        origin: [10, 20, 30]
        normal: [40, 0, 0]
        up: [0, -50, 60]
    )");
    EXPECT_THAT(slice, isSlice({10, 20, 30}, {40, 0, 0}, {0, -50, 60}));
}

TEST(GeometryOperatorsIO, readSlice_y_defaults) {
    auto slice = readSingleOperator<SliceOperator>(3, R"(
      slice:
        y: 20
    )");
    EXPECT_THAT(slice, isSlice({0, 20, 0}, {0, 1, 0}, {1, 0, 0}));
}

TEST(GeometryOperatorsIO, readSlice_y_optionals) {
    auto slice = readSingleOperator<SliceOperator>(3, R"(
      slice:
        y: 20
        origin: [10, 20, 30]
        normal: [0, 40, 0]
        up: [-50, 0, 60]
    )");
    EXPECT_THAT(slice, isSlice({10, 20, 30}, {0, 40, 0}, {-50, 0, 60}));
}

TEST(GeometryOperatorsIO, readSlice_z_defaults) {
    auto slice = readSingleOperator<SliceOperator>(3, R"(
      slice:
        z: 30
    )");
    EXPECT_THAT(slice, isSlice({0, 0, 30}, {0, 0, 1}, {0, 1, 0}));
}

TEST(GeometryOperatorsIO, readSlice_z_optionals) {
    auto slice = readSingleOperator<SliceOperator>(3, R"(
      slice:
        z: 30
        origin: [10, 20, 30]
        normal: [0, 0, 40]
        up: [-50, 60, 0]
    )");
    EXPECT_THAT(slice, isSlice({10, 20, 30}, {0, 0, 40}, {-50, 60, 0}));
}

TEST(GeometryOperatorsIO, readSlice_zeroNormal) {
    try {
        readSingleOperator<SliceOperator>(3, R"(
          slice:
            origin: [10, 20, 30]
            normal: [0, 0, 0]
            up: [0, -50, 60]
        )");
        FAIL() << "Should have thrown a message about the normal being zero";
    } catch (std::invalid_argument &ex) {
        EXPECT_THAT(ex.what(), HasSubstr("normal"));
        EXPECT_THAT(ex.what(), HasSubstr("zero"));
    }
}

TEST(GeometryOperatorsIO, readSlice_upAndNormalNotNormal) {
    try {
        readSingleOperator<SliceOperator>(3, R"(
          slice:
            origin: [10, 20, 30]
            normal: [10, 20, 30]
            up: [10, 0, 0]
        )");
        FAIL() << "Should have thrown a message about the normal and up "
                  "vectors not being perpendicular";
    } catch (std::invalid_argument &ex) {
        EXPECT_THAT(ex.what(), HasSubstr("normal"));
        EXPECT_THAT(ex.what(), HasSubstr("up"));
    }
}

TEST(GeometryOperatorsIO, readSlice_badPlaneValues) {
    EXPECT_THROW(readSingleOperator<SliceOperator>(3, R"(
      slice:
        x: 10
        origin: [20, 0, 0]
    )"), std::invalid_argument) << "Bad origin";

    EXPECT_THROW(readSingleOperator<SliceOperator>(3, R"(
      slice:
        x: 10
        normal: [1, 2, 3]
    )"), std::invalid_argument) << "Bad normal";

    EXPECT_THROW(readSingleOperator<SliceOperator>(3, R"(
      slice:
        x: 10
        up: [1, 2, 3]
    )"), std::invalid_argument) << "Bad up";
}

TEST(GeometryOperatorsIO, readMultiple_matchingDimensions) {
    auto op = readOperators(3, R"(
      - translate: [10, 20, 30]
      - translate: [40, 50, 60]
    )");
    auto composite = std::dynamic_pointer_cast<const CompositeOperator>(op);
    ASSERT_TRUE(composite);
    EXPECT_EQ(2u, composite->getOperators().size());
}

TEST(GeometryOperatorsIO, readMultiple_nonMatchingDimensions) {
    EXPECT_THROW(readOperators(3, R"(
      - translate: [10, 20, 30]
      - translate: [40, 50]
    )"), std::invalid_argument);
}

TEST(GeometryOperatorsIO, readMultiple_unknownOperator) {
    try {
        readOperators(3, R"(
          - UNKNOWN_OPERATOR: [10, 20, 30]
         )");
        FAIL() << "Should have thrown";
    } catch (const std::invalid_argument &ex) {
        EXPECT_THAT(ex.what(), HasSubstr("UNKNOWN_OPERATOR"));
    }
}

}}}