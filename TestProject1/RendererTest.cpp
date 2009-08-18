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
        render = new RenderWin32DX9Imp();
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
        assertTrue( NULL != render );
	};

};

//}
