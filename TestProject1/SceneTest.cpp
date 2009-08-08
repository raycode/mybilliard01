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
    Factory * baseFactory;

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
        baseFactory = new DummyBaseFactory();
        setCurrentDirectory( testContext_ );
    };

    [TestCleanup()]
    void MyTestCleanup() {
        delete baseFactory;
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
        const bool succeed1 = scene->load( getFilename(), baseFactory );
        Assert::IsTrue( succeed1 );

        const bool succeed2 = scene->load( L"./" + getFilename(), baseFactory );
        Assert::IsTrue( succeed2 );

        const bool succeed3 = scene->load( L".\\" + getFilename(), baseFactory );
        Assert::IsTrue( succeed3 );

        const bool fail1 = scene->load( L"NoFile.dae", baseFactory );
        Assert::IsFalse( fail1 );
    }

    [TestMethod]
    void setRender() {
        Render * const render = new RenderImp();
        scene->setRender( render );
        Assert::IsTrue( render == scene->getRender() );
    }

    [TestMethod]
    void setRenderUpAxis_LoadFirst() {
        scene->load( getFilename(), baseFactory );

        Render * const render = new RenderImp();
        scene->setRender( render );

        Assert::IsTrue( UPAXISTYPE_Y_UP == render->getUpAxis() );
    }

    [TestMethod]
    void setRenderUpAxis_SetFirst() {
        Render * const render = new RenderImp();
        scene->setRender( render );

        scene->load( getFilename(), baseFactory );

        Assert::IsTrue( UPAXISTYPE_Y_UP == render->getUpAxis() );
    }
};
