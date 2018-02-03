#include "UmathTest.h"
#include <test_utils/approx.h>
#include <umath/Vec3.h>

using namespace UMath;

const float defaultApproxDelta = 0.000001f;

TEST_F(UmathTest, Vec3Constructors)
{
    UVec3f v1;
    ASSERT_TRUE(v1.x == 0);
    ASSERT_TRUE(v1.y == 0);
    ASSERT_TRUE(v1.z == 0);

    UVec3f v2(42);
    ASSERT_TRUE(v2.data[0] == 42);
    ASSERT_TRUE(v2.data[1] == 42);
    ASSERT_TRUE(v2.data[2] == 42);

    UVec3f v3(1, 2, 3);
    ASSERT_TRUE(v3.x       == 1);
    ASSERT_TRUE(v3.data[1] == 2);
    ASSERT_TRUE(v3.z       == 3);
}

TEST_F(UmathTest, Vec3ConstBinaryOperations)
{
    ASSERT_EQ(UVec3f(1, 2, 3) + UVec3f(3, 2, 1)   , UVec3f(4));
    ASSERT_EQ(UVec3f(3, 2, 1) - UVec3f(0, -1, -2) , UVec3f(3));
    ASSERT_EQ(UVec3f(1, 2, 3) * UVec3f(6, 3, 2)   , UVec3f(6));

    ASSERT_EQ(UVec3f(1, 2, 3) % UVec3f(6, 3, 2)   , 18);
    ASSERT_EQ(UVec3f(1, 2, 3) ^ UVec3f(3, 2, 1)   , UVec3f(-4, 8 , -4));

    ASSERT_EQ(UVec3f(1, 2, 3) * 2.0f             , UVec3f(2, 4, 6));
    ASSERT_EQ(2.0f * UVec3f(1, 2, 3)             , UVec3f(2, 4, 6));

    ASSERT_EQ(UVec3f(2, 4, 6) / 2                , UVec3f(1, 2, 3));

}

TEST_F(UmathTest, Vec3MutBinaryOperations)
{
    UVec3d v(1, 2, 3);

    v += UVec3d(2, 4, 6);
    ASSERT_EQ(v, UVec3d(3, 6, 9));

    v -= UVec3d(1, 2, 3);
    ASSERT_EQ(v, UVec3d(2, 4, 6));

    v *= UVec3d(0.5, 0.25, 1.5);
    ASSERT_EQ(v, UVec3d(1, 1, 9));

    v /= 0.5;
    ASSERT_EQ(v, UVec3d(2, 2, 18));

    v *= 0.5;
    ASSERT_EQ(v, UVec3d(1, 1, 9));

    v ^= UVec3d(2, 1, 3);
    ASSERT_EQ(v, UVec3d(-6, 15, -1));
}

TEST_F(UmathTest, Vec3ConstMethods)
{
    UVec3f v(1, 2, 3);
    ASSERT_EQ(v.x_axis() , UVec3f(1, 0, 0));
    ASSERT_EQ(v.y_axis() , UVec3f(0, 2, 0));
    ASSERT_EQ(v.z_axis() , UVec3f(0, 0, 3));
    ASSERT_EQ(v.len()    , static_cast<float>(sqrt(14.0f)));
    ASSERT_EQ(v.pow(2)   , UVec3f(1, 4, 9));
    ASSERT_EQ(v.mean()   , 2.0f);

    ASSERT_EQ(UVec3f(1, 2, 3).max_component(), 3.0f);
    ASSERT_EQ(UVec3f(1, 3, 2).max_component(), 3.0f);
    ASSERT_EQ(UVec3f(2, 1, 3).max_component(), 3.0f);
    ASSERT_EQ(UVec3f(2, 3, 1).max_component(), 3.0f);
}

TEST_F(UmathTest, UVec3MutMethods)
{
    UVec3f v(1, 2, 3);
    auto len = static_cast<float>(sqrt(14.0f));
    ASSERT_EQ(v.normalize()  , UVec3f(1.0f / len, 2.0f / len, 3.0f / len));
    ASSERT_TRUE(TestUtils::CompareApprox(v.len(), 1.0f, defaultApproxDelta));
}

TEST_F(UmathTest, UVec3CrossTest)
{
    UVec3f x(1, 0, 0);
    UVec3f y(0, 1, 0);
    UVec3f z(0, 0, 1);
    ASSERT_EQ(x ^ y, z);
}
