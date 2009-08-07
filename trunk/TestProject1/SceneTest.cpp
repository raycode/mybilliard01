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
        const bool succeed1 = scene->load( getFilename(), NULL );
        Assert::IsTrue( succeed1 );

        const bool succeed2 = scene->load( L"./" + getFilename(), NULL );
        Assert::IsTrue( succeed2 );

        const bool succeed3 = scene->load( L".\\" + getFilename(), NULL );
        Assert::IsTrue( succeed3 );

        const bool fail1 = scene->load( L"NoFile.dae", NULL );
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
        scene->load( getFilename(), NULL );

        Render * const render = new RenderImp();
        scene->setRender( render );

        Assert::IsTrue( UPAXISTYPE_Y_UP == render->getUpAxis() );
    }

    [TestMethod]
    void setRenderUpAxis_SetFirst() {
        Render * const render = new RenderImp();
        scene->setRender( render );

        scene->load( getFilename(), NULL );

        Assert::IsTrue( UPAXISTYPE_Y_UP == render->getUpAxis() );
    }
};
