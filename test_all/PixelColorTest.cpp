#include "StdAfx.h"
#include "my_gtest.h"
#include "../core_billiard/my_render_imp.h"
namespace my_render_imp {

    class PixelColorTest : public testing::Test {
    protected:
        virtual void SetUp() {}
        virtual void TearDown() {}
    };

    TEST_F( PixelColorTest, DefaultConstructor ) {
        PixelColor color;
        ASSERT_EQ( 0, color.getA() );
        ASSERT_EQ( 0, color.getR() );
        ASSERT_EQ( 0, color.getG() );
        ASSERT_EQ( 0, color.getB() );
        ASSERT_EQ( 0, color.getARGB() );
    }

    TEST_F( PixelColorTest, SetARGB ) {
        PixelColor color;
        color.setARGB( 0xff020304 );
        ASSERT_EQ( 0xff020304, color.getARGB() );
    }

    TEST_F( PixelColorTest, TypeCastingOperator ) {
        PixelColor color;
        color.setARGB( 0xff020304 );
        ASSERT_EQ( 0xff020304, (NxU32) color );
    }

    TEST_F( PixelColorTest, Constructor_Integer ) {
        PixelColor color( 255, 2, 3, 4 );
        ASSERT_EQ( 255u, color.getA() );
        ASSERT_EQ( 2u, color.getR() );
        ASSERT_EQ( 3u, color.getG() );
        ASSERT_EQ( 4u, color.getB() );
        ASSERT_EQ( 0xff020304, color.getARGB() );
    }

    TEST_F( PixelColorTest, Constructor_UnsignedInteger ) {
        PixelColor color( 255u, 2u, 3u, 4u );
        ASSERT_EQ( 255u, color.getA() );
        ASSERT_EQ( 2u, color.getR() );
        ASSERT_EQ( 3u, color.getG() );
        ASSERT_EQ( 4u, color.getB() );
        ASSERT_EQ( 0xff020304, color.getARGB() );
    }

    TEST_F( PixelColorTest, Constructor_Color256 ) {
        PixelColor color(
            (PixelColor::Color256) 255,
            (PixelColor::Color256) 2,
            (PixelColor::Color256) 3,
            (PixelColor::Color256) 4
        );
        ASSERT_EQ( (PixelColor::Color256) 255, color.getA() );
        ASSERT_EQ( (PixelColor::Color256) 2, color.getR() );
        ASSERT_EQ( (PixelColor::Color256) 3, color.getG() );
        ASSERT_EQ( (PixelColor::Color256) 4, color.getB() );
        ASSERT_EQ( 0xff020304, color.getARGB() );
    }

    TEST_F( PixelColorTest, Constructor_NxU32 ) {
        PixelColor color( 0xff020304 );
        ASSERT_EQ( 255u, color.getA() );
        ASSERT_EQ( 2u, color.getR() );
        ASSERT_EQ( 3u, color.getG() );
        ASSERT_EQ( 4u, color.getB() );
        ASSERT_EQ( 0xff020304, color.getARGB() );
    }

    TEST_F( PixelColorTest, Constructor_Float4 ) {
        PixelColor color( 1.f, 0.5f, 0.25f, 0.125f );
        ASSERT_EQ( (PixelColor::Color256) 255, color.getA() );
        ASSERT_EQ( (PixelColor::Color256) 127, color.getR() );
        ASSERT_EQ( (PixelColor::Color256) 63, color.getG() );
        ASSERT_EQ( (PixelColor::Color256) 31, color.getB() );
    }

    TEST_F( PixelColorTest, Constructor_NxVec3 ) {
        PixelColor color( 1.f, NxVec3( 0.5f, 0.25f, 0.125f ) );
        ASSERT_EQ( (PixelColor::Color256) 255, color.getA() );
        ASSERT_EQ( (PixelColor::Color256) 127, color.getR() );
        ASSERT_EQ( (PixelColor::Color256) 63, color.getG() );
        ASSERT_EQ( (PixelColor::Color256) 31, color.getB() );
    }

    TEST_F( PixelColorTest, SetEachColor ) {
        PixelColor color;

        color.setA( 255 );
        ASSERT_EQ( 255u, color.getA() );

        color.setR( 2 );
        ASSERT_EQ( 2u, color.getR() );

        color.setG( 3 );
        ASSERT_EQ( 3u, color.getG() );

        color.setB( 4 );
        ASSERT_EQ( 4u, color.getB() );

        ASSERT_EQ( 0xff020304, color.getARGB() );
    }

}

