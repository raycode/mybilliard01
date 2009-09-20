#include "StdAfx.h"
#include "my_gtest.h"
#include "../render_win32/my_render_win32_imp.h"
namespace my_render_win32_imp {

    class ApplicationWin32ImpTest : public testing::Test {
    protected:
        virtual void SetUp() {}
        virtual void TearDown() {}
    };

    TEST_F( ApplicationWin32ImpTest, One )
    {
        ApplicationWin32 * const app = new ApplicationWin32Imp();
        delete app;
    }
}
