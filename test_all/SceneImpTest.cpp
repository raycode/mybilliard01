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

    TEST_F( SceneImpTest, GetNumberOfVisualScene ) {
        ASSERT_TRUE( scene->load( getFilename() ) );
        ASSERT_EQ( 1u, scene->getNumberOfVisualScene() );
    }
    TEST_F( SceneImpTest, GetVisualSceneByIndex ) {
        ASSERT_TRUE( scene->load( getFilename() ) );
    }
    TEST_F( SceneImpTest, GetVisualSceneByID ) {
        ASSERT_TRUE( scene->load( getFilename() ) );
    }
    TEST_F( SceneImpTest, GetDefaultVisualScene ) {
        ASSERT_TRUE( scene->load( getFilename() ) );
    }
    TEST_F( SceneImpTest, GetCurrentVisualScene ) {
        ASSERT_TRUE( scene->load( getFilename() ) );
    }
    TEST_F( SceneImpTest, SetCurrentVisualScene ) {
        ASSERT_TRUE( scene->load( getFilename() ) );
    }

    TEST_F( SceneImpTest, GetNumberOfNode ) {
        ASSERT_TRUE( scene->load( getFilename() ) );
    }
    TEST_F( SceneImpTest, GetNodeByIndex ) {
        ASSERT_TRUE( scene->load( getFilename() ) );
    }
    TEST_F( SceneImpTest, GetNodeByID ) {
        ASSERT_TRUE( scene->load( getFilename() ) );
    }

    TEST_F( SceneImpTest, GetNumberOfGeometry ) {
        ASSERT_TRUE( scene->load( getFilename() ) );
    }
    TEST_F( SceneImpTest, GetGeometryByIndex ) {
        ASSERT_TRUE( scene->load( getFilename() ) );
    }
    TEST_F( SceneImpTest, GetGeometryByID ) {
        ASSERT_TRUE( scene->load( getFilename() ) );
    }
    TEST_F( SceneImpTest, GetGeometryByName ) {
        ASSERT_TRUE( scene->load( getFilename() ) );
    }

    TEST_F( SceneImpTest, GetNumberOfCamera ) {
        ASSERT_TRUE( scene->load( getFilename() ) );
    }
    TEST_F( SceneImpTest, GetCameraByIndex ) {
        ASSERT_TRUE( scene->load( getFilename() ) );
    }
    TEST_F( SceneImpTest, GetCameraByID ) {
        ASSERT_TRUE( scene->load( getFilename() ) );
    }
    TEST_F( SceneImpTest, GetCameraByName ) {
        ASSERT_TRUE( scene->load( getFilename() ) );
    }

    TEST_F( SceneImpTest, IsUpAxisXYZ ) {
        ASSERT_TRUE( scene->load( getFilename() ) );
        ASSERT_FALSE( scene->isUpAxisX() );
        ASSERT_TRUE( scene->isUpAxisY() );
        ASSERT_FALSE( scene->isUpAxisZ() );
    }

}
