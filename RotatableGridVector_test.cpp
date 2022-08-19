#include <gtest/gtest.h>
#include "RotatableGridVector.hpp"

#define GEN                                                                                                             \
if (rows * cols > 26) {                                                                                                 \
    std::stringstream e;                                                                                                \
    e << "generation size must be less than 26, but " << rows << "(rows) * " << cols << "(columns) = " << rows * cols;  \
    throw std::out_of_range(e.str());                                                                                   \
}                                                                                                                       \
RotatableGridVector<unsigned char> r(rows, decltype(r)::value_type(cols))

RotatableGridVector<unsigned char> genActual(size_t rows, size_t cols) {
    GEN;

    unsigned char c = 'A';
    for ( decltype(r)::value_type &row : r )
        for ( unsigned char &v : row )
            v = c++;

    return r;
}

RotatableGridVector<unsigned char> genExpected(size_t cols, size_t rows) {
    GEN;

    unsigned char c = 'A';
    for (int col = (int)--cols; col >= 0; col--) {
        for (int row = 0; row < rows; row++) {
            r[row][col] = c++;
        }
    }

    return r;
}

#define TEST_(ROWS, COLS)                           \
TEST(RotatableGridVectorTest, ROWS ## x ## COLS) {  \
    auto actual = genActual(ROWS, COLS);            \
    actual.rotate();                                \
    ASSERT_EQ(actual, genExpected(ROWS, COLS));     \
} static_assert(true)

TEST_(5, 5);
TEST_(4, 4);
TEST_(3, 5);
TEST_(5, 3);
TEST_(4, 6);
TEST_(6, 4);