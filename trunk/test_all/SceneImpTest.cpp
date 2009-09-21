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

    TEST_F( SceneImpTest, Load ) {
        const bool succeed1 = scene->load( getFilename() );
        ASSERT_TRUE( succeed1 );
    }

    TEST_F( SceneImpTest, Load_wrongfile ) {
        const bool fail1 = scene->load( L"NoFile.dae" );
        ASSERT_FALSE( fail1 );
    }

    TEST_F( SceneImpTest, Unload ) {
        ASSERT_TRUE( scene->load( getFilename() ) );

        ASSERT_NE( 0u, scene->getNumberOfVisualScene() );
        ASSERT_NE( 0u, scene->getNumberOfNode() );
        scene->unload();

        ASSERT_EQ( 0u, scene->getNumberOfVisualScene() );
        ASSERT_EQ( 0u, scene->getNumberOfNode() );
    }

    //TEST_F( SceneImpTest, VisualSceneIDs ) {
    //    ASSERT_TRUE( scene->load( getFilename() ) );

    //    vector< wstring > id_array = scene->getVisualSceneIDs();
    //    ASSERT_EQ( 1u, id_array.size() );
    //    ASSERT_EQ( wstring( L"VisualSceneNode" ), id_array[0] );
    //}
}
