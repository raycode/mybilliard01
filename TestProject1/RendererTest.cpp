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
    };

	[TestMethod]
	void ConstructRenderer()
	{
        Render * const renderer = new RenderImp();
        Assert::IsTrue( NULL != renderer );
	};

    [TestMethod]
    void WidthHeight() {
        Render * const render = new RenderImp();

        render->setScreenWidth( 30 );
        Assert::AreEqual( 30, render->getScreenWidth() );

        render->setScreenHeight( 20 );
        Assert::AreEqual( 20, render->getScreenHeight() );
    }
};

//}
