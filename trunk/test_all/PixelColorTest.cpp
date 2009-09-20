#include "StdAfx.h"
#include "my_gtest.h"
#include "../core_billiard/my_render_imp.h"
namespace my_render_imp {

    class PixelColorTest : public testing::Test {
    protected:
        virtual void SetUp() {}
        virtual void TearDown() {}
    };

    TEST_F( PixelColorTest, One ) {
        PixelColor color;
        ASSERT_EQ( 0, color.getA() );
        ASSERT_EQ( 0, color.getR() );
        ASSERT_EQ( 0, color.getG() );
        ASSERT_EQ( 0, color.getB() );
    }

}

