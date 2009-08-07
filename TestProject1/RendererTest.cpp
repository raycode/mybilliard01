#include "stdafx.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

//namespace TestProject1
//{

[TestClass]
public ref class RendererTest
{
private:
	static TestContext^ testContext_;
    Render * render;

public: 
    [ClassInitialize()]
    static void MyClassInitialize(TestContext^ testContext)
    {
        testContext_ = testContext;
    };

    [TestInitialize()]
    void MyTestInitialize()
    {
        render = new RenderImp();
        setCurrentDirectory( testContext_ );
    };

    [TestCleanup()]
    void MyTestCleanup() {
        delete render;
    }

public:
	[TestMethod]
	void ConstructRenderer()
	{
        Assert::IsTrue( NULL != render );
	};

    [TestMethod]
    void WidthHeight() {
        render->setScreenWidth( 30 );
        Assert::AreEqual( 30, render->getScreenWidth() );

        render->setScreenHeight( 20 );
        Assert::AreEqual( 20, render->getScreenHeight() );
    }

    [TestMethod]
    void UpAxis() {
        domUpAxisType axises[] = { UPAXISTYPE_X_UP, UPAXISTYPE_Y_UP, UPAXISTYPE_Z_UP };

        for each( domUpAxisType axis in axises ) {
            render->setUpAxis( axis );
            Assert::AreEqual( (int) axis, (int) render->getUpAxis() );
        }
    }
};

//}
