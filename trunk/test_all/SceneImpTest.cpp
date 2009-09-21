#include "StdAfx.h"
#include "my_gtest.h"
#include "../core_billiard/my_render_imp.h"
namespace my_render_imp {

    class SceneImpTest : public testing::Test {
    protected:
        virtual void SetUp() {
            scene = new SceneImp();
        }
        virtual void TearDown() {
            delete scene;
        }

        SceneImp * scene;

        static wstring getFilename() {
            return L"../asset/duck.dae";
        }
    };

    TEST_F( SceneImpTest, Constructor ) {
        ASSERT_TRUE( scene );
    }

    TEST_F( SceneImpTest, LoadDAE ) {
        const bool succeed1 = scene->load( SceneImpTest::getFilename() );
        ASSERT_TRUE( succeed1 );
    }

}
