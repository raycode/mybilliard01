#include "stdafx.h"
#include "MyTestFramework.h"
#include "RenderForDX9.h"
namespace billiard {

class MyColladaLoaderTest : public testing::Test  {
protected:

    virtual void SetUp() {}
    virtual void TearDown() {}

};

TEST_F( MyColladaLoaderTest, One ) {
    const wstring filename = ConstString::colladaVisualAssetFilename();
    MyColladaLoader loader( filename );
    ASSERT_STREQ( filename.c_str(), loader.filename_.c_str() );
}


}
