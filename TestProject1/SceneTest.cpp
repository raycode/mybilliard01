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
        setCurrentDirectory( testContext_ );
        scene = new SceneImp();
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
        assertTrue( NULL != scene );
    }

    [TestMethod]
    void loadCollada() {
        const bool succeed1 = scene->load( getFilename() );
        assertTrue( succeed1 );
    }

    void loadCollada_wrongfile() {
        const bool fail1 = scene->load( L"NoFile.dae" );
        assertFalse( fail1 );
    }

    void loadCollada_severalTimes() {
        const bool succeed1 = scene->load( getFilename() );
        assertTrue( succeed1 );

        const bool succeed2 = scene->load( L"./" + getFilename() );
        assertTrue( succeed2 );

        const bool succeed3 = scene->load( L".\\" + getFilename() );
        assertTrue( succeed3 );

        const bool fail1 = scene->load( L"NoFile.dae" );
        assertFalse( fail1 );
    }

};
