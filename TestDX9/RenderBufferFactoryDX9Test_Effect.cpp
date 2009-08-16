#include "stdafx.h"
#include "RenderBufferFactoryDX9Test_Backdoor.hpp"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;


const static float positions[] = {
    150.0f,  50.0f, 0.5f,
    250.0f, 250.0f, 0.5f,
    50.0f, 250.0f, 0.5f
};

const static NxU32 diffuses[] = {
    0xffff0000, 0xff00ff00, 0xff00ffff
};


class VertexRenderingListener : public RenderEventListenerNull {
public:
    static wstring getFilename() {
        return getDeployedFilename( L"asset\\SimpleSample.fx" );
    }

    virtual void init( RenderBufferFactory * factory ) OVERRIDE {
        effect_ = factory->createEffectShader( getFilename() );
        tech_ = effect_->createTechniqueVariable( L"RenderScene" );
        vb_ = factory->createVertexBuffer_static( 3, positions );
        vb_->appendNormal_Array( positions, 0 );
        vb_->appendColor_Array( diffuses, 0 );
        effectRender_ = new EffectRenderListener( vb_ );
    }

    virtual void display( Render * render ) OVERRIDE {
        render->setRenderState()->setWireframe()->setSolid();
        render->beginScene();
        render->renderWithEffectShader( effect_, tech_, effectRender_ );
        render->endScene();
    }


    class EffectRenderListener : public RenderEffectShader {
    public:
        EffectRenderListener( VertexBuffer * vb )
            : vb_( vb )
        {}

        virtual void display( Render * render, size_t pass ) OVERRIDE {
            render->drawPrimitive_TRIANGLELIST( vb_, 0, 1 );
        }

    private:
        VertexBuffer * vb_;
    };

private:
    EffectRenderListener * effectRender_;
    EffectShader * effect_;
    ShaderVariable * tech_;
    VertexBuffer * vb_;
};

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
            assertTrue( factory->releaseEffectShader( effect ) );
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

            assertTrue( factory->releaseEffectShader( effectDX9 ) );
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
