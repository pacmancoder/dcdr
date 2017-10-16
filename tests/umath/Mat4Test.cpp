#include <UmathTest.h>
#include <umath/Mat4.h>

using namespace UMath;

TEST_F(UmathTest, Mat4Constructors)
{
    Mat4f mz = Mat4f::zero();
    for (int i = 0; i < Mat4f::ROW_ELEMENTS; ++i)
        for (int j = 0; j < Mat4f::COL_ELEMENTS; ++j)
            ASSERT_EQ(mz.data[i][j], 0);

    Mat4f mi = Mat4f::identity();
    for (int i = 0; i < Mat4f::ROW_ELEMENTS; ++i)
        for (int j = 0; j < Mat4f::COL_ELEMENTS; ++j)
            ASSERT_EQ(mi.data[i][j], (i == j) ? 1 : 0);

    float buffer[Mat4f::ELEMENTS];
    for (int i = 0; i < Mat4f::ELEMENTS; i++) buffer[i] = i;

    Mat4f mb = Mat4f::from_buffer(buffer);
    for (int i = 0; i < Mat4f::ELEMENTS; ++i)
        ASSERT_EQ(*((float*)mb.data + i), i);

    ASSERT_EQ(mb.a11, 0); ASSERT_EQ(mb.a21, 4); ASSERT_EQ(mb.a31,  8); ASSERT_EQ(mb.a41, 12);
    ASSERT_EQ(mb.a12, 1); ASSERT_EQ(mb.a22, 5); ASSERT_EQ(mb.a32,  9); ASSERT_EQ(mb.a42, 13);
    ASSERT_EQ(mb.a13, 2); ASSERT_EQ(mb.a23, 6); ASSERT_EQ(mb.a33, 10); ASSERT_EQ(mb.a43, 14);
    ASSERT_EQ(mb.a14, 3); ASSERT_EQ(mb.a24, 7); ASSERT_EQ(mb.a34, 11); ASSERT_EQ(mb.a44, 15);
}

TEST_F(UmathTest, MatOperator)
{
    float buffer[] = {
            1, 2, 3, 4,
            5, 6, 7, 8,
            1, 2, 3, 4,
            5, 6, 7, 8,
    };

    float buffer2[] = {
            1, 5, 1, 5,
            2, 6, 2, 6,
            3, 7, 3, 7,
            4, 8, 4, 8,
    };

    float expected_mul[] = {
            30,  70,  30,  70,
            70, 174,  70, 174,
            30,  70,  30,  70,
            70, 174, 70,  174,
    };

    Mat4f m1  = Mat4f::from_buffer(buffer);

    Mat4f mt(m1);
    mt.transpose();
    ASSERT_EQ(mt, Mat4f::from_buffer(buffer2));

    Mat4f m2  = Mat4f::from_buffer(buffer2);

    Mat4f mm = m2 * m1;
    ASSERT_EQ(mm, Mat4f::from_buffer(expected_mul));

    ASSERT_EQ(m2.transform_point(Vec3f(1, 2, 3)), Vec3f(18.0f / 46, 1, 18.0f / 46));
    ASSERT_EQ(m2.transform_direction(Vec3f(1, 2, 3)), Vec3f(14, 38, 14));
}