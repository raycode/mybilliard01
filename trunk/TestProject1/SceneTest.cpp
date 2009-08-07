#include "stdafx.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

[TestClass]
public ref class SceneTest
{
private:
    static TestContext^ testContext_;

private:
    Scene * scene;

public: 
    [ClassInitialize()]
    static void MyClassInitialize(TestContext^ testContext)
    {
        testContext_ = testContext;
    };

    [TestInitialize()]
    void MyTestInitialize()
    {
        scene = new SceneImp();
        setCurrentDirectory( testContext_ );
    };

    [TestCleanup()]
    void MyTestCleanup() {
        delete scene;
    };

    static wstring getFilename() {
        return getDeployedFilename( L"asset\\1ball1box.dae" );
    }

public:
    [TestMethod]
    void ConstructorScene() {
        Assert::IsTrue( NULL != scene );
    }

    [TestMethod]
    void loadCollada() {
        DAEPtr dae;
        dae = DAEPtr( new DAE() );
        domCOLLADA * const collada = dae->open( convertString< string >( getFilename() ).c_str() );
        Assert::IsTrue( NULL != collada );

        Scene * const scene_ = new SceneImp();
        scene_->load( getFilename() );
        /*Assert::IsTrue( succeed1 );*/

        //const bool succeed2 = scene->load( L"./" + getFilename() );
        //Assert::IsTrue( succeed2 );

        //const bool succeed3 = scene->load( L".\\" + getFilename() );
        //Assert::IsTrue( succeed3 );

        //const bool fail1 = scene->load( L"NoFile.dae" );
        //Assert::IsFalse( fail1 );
    }
};
