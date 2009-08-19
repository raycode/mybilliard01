#include "stdafx.h"
#include "RenderBufferFactoryDX9Imp_Backdoor.hpp"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;



namespace TestDX9
{
	[TestClass]
	public ref class RenderBufferFactoryDX9Test_Effect
	{
    private:
        static TestContext^ testContext_;
        RenderWin32DX9Imp * dx9Imp;
        RenderBufferFactoryDX9 * factory;

        static wstring getFilename() {
            return getDeployedFilename( L"asset\\SimpleSample.fx" );
        }

    public: 
        [ClassInitialize()]
        static void MyClassInitialize(TestContext^ testContext) {
            testContext_ = testContext;
        };

        [TestInitialize()]
        void MyTestInitialize() {
            setCurrentDirectory( testContext_ );
            dx9Imp = new RenderWin32DX9Imp();
            dx9Imp->setBackbufferLockable( true );
        };

        [TestCleanup()]
        void MyTestCleanup() {
            delete dx9Imp;
        };

    public:
        [TestMethod]
        void FixtureOnly() {}

		[TestMethod]
		void CreateEffect()
		{
            assertTrue( dx9Imp->createDevice( true, 30, 30 ) );
            factory = PRIVATE_METHOD( RenderWin32DX9Imp, getBufferFactory )( dx9Imp );
 
            EffectShader * const effect = factory->createEffectShader( getFilename() );
            assertNotNull( effect );
            assertTrue( factory->destroyEffectShader( effect ) );
		};

        [TestMethod]
        void SetTechnique() {
            assertTrue( dx9Imp->createDevice( true, 30, 30 ) );
            factory = PRIVATE_METHOD( RenderWin32DX9Imp, getBufferFactory )( dx9Imp );
            EffectShaderDX9 * const effectDX9 = static_cast< EffectShaderDX9 *>( factory->createEffectShader( getFilename() ) );
            assertNotNull( effectDX9 );

            ShaderVariable * const tech = effectDX9->createTechniqueVariable( L"RenderScene" );
            assertNotNull( tech );

            assertTrue( effectDX9->isValidTechnique( tech ) );

            effectDX9->setTechnique( tech );
            assertEquals( 1u, effectDX9->begin() );
            effectDX9->end();

            assertTrue( factory->destroyEffectShader( effectDX9 ) );
        }

        [TestMethod]
        void RenderEffect() {
            //RenderEventListener * const renderListener = new VertexRenderingListener();
            //assertNotNull( renderListener );
            //dx9Imp->addRenderEventListener( renderListener );

            //assertTrue( dx9Imp->createDevice( false, 0, 0 ) );
            //factory = PRIVATE_METHOD( RenderWin32DX9Imp, getBufferFactory )( dx9Imp );
            //for( size_t i = 0; i < 60*100; ++i )
            //    dx9Imp->renderOneFrame();
            //dx9Imp->destroyDevice();

            //delete renderListener;
        }
    };
}
