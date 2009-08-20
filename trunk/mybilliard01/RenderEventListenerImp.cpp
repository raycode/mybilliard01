#include "StdAfx.h"
#include "my_app.h"


RenderEventListenerImp::RenderEventListenerImp( wstring sceneFile, wstring physX_File )
: scene_( new SceneImp() )
, phys_( new MyPhysX() )
, width_( 0.f )
, height_ ( 0.f )
, camera_( NULL )
, z_( 0.f )
{
    scene_->load( sceneFile );
    phys_->loadXMLFile( physX_File );

    //static NxMat34 posCamera( NxMat33( 
    //    NxVec3( 1.f, 0.f, 0.f ),
    //    NxVec3( 0.f, 1.f, 0.f ),
    //    NxVec3( 0.f, 0.f, 1.f ) ), NxVec3( -0.01f, 0.01f, -1.f ) );
    //camera_ = phys_->addCameraActor( posCamera );
}

void RenderEventListenerImp::init( RenderBufferFactory * renderFactory )
{
    scene_->setRenderFactory( renderFactory );
    initEffect( renderFactory );
    connectPhysicsToGraphics();
}

void RenderEventListenerImp::initEffect( RenderBufferFactory * renderFactory )
{
    effect_ = renderFactory->createEffectShader( L"..\\asset\\SimpleSample.fx" );
    assert( effect_ );

    tech_ = effect_->createTechniqueVariable( L"RenderScene" );
    assert( effect_->isValidTechnique( tech_ ) );

    world_ = effect_->createVariable( L"g_mWorld" );
    wvp_ = effect_->createVariable( L"g_mWorldViewProjection" );
}

void RenderEventListenerImp::connectPhysicsToGraphics()
{
    for( size_t i = 0; i < phys_->getNumberOfActors(); ++i ) {
        NxActor * const actor = phys_->getActor( i );
        const wstring name = convertString( actor->getName() );
        Node * const node = scene_->getNode( name );
        actor->userData = node;
    }
}

void RenderEventListenerImp::displayReset( int x, int y, int width, int height )
{
    width_ = (float) width;
    height_ = (float) height;
}

void RenderEventListenerImp::update( RenderBufferFactory * renderFactory, float elapsedTime ) {
    phys_->simulate( elapsedTime );
    updateObjects();
    phys_->fetchResult();

    z_ += elapsedTime;
}

void RenderEventListenerImp::updateObjects()
{
    toRender_.clear();

    for( size_t i = 0; i < phys_->getNumberOfActors(); ++i ) {
        NxActor * const actor = phys_->getActor( i );
        Node * const node = (Node *) (actor->userData);
        if( NULL == node ) continue;

        toRender_.push_back( node );

        float * matWorld = toRender_.rbegin()->matWorld_;
        actor->getGlobalPose().getColumnMajor44( matWorld );


        D3DXMATRIX Rz;
        D3DXMatrixRotationZ( &Rz, z_ );
        if( z_ >= 6.28f ) z_ = 0.f;
        D3DXMATRIX p = Rz;

        D3DXVECTOR3 position( 2.f, 0.5f, 1.f );
        D3DXVECTOR3 lookAt( 0.f, 0.f, 0.f );
        D3DXVECTOR3 up( 0.f, 0.f, 1.f );
        D3DXMATRIX view;
        D3DXMatrixLookAtLH( &view, &position, &lookAt, &up );

        D3DXMATRIX proj;
        D3DXMatrixPerspectiveFovLH(
            &proj,
            D3DX_PI * 0.5f, // 90 - degree
            width_ / height_,
            1.f,
            1000.f );

        memcpy( toRender_.rbegin()->matWVP_, (float*) (D3DXMATRIX( matWorld ) * p * view * proj), sizeof(float) * 16 );
    }
}

void RenderEventListenerImp::display( Render * render ) {
    render->clear_Color_Z( PixelColor( 0, 45, 50, 170 ), 1.0f );
    if( false == render->beginScene() ) return;

    DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"My Testing" ); // These events are to help PIX identify
    render->setRenderState()->setWireframe()->setSolid();
    render->setRenderState()->setCull()->setNone();
    MY_FOR_EACH( ToRender, iter, toRender_ )
    {
        iter_ = iter;
        effect_->setFloatArray( world_, iter_->matWorld_, 16 );
        effect_->setFloatArray( wvp_, iter_->matWVP_, 16 );
        render->renderWithEffectShader( effect_, tech_, this );
    }
    DXUT_EndPerfEvent();

    render->endScene();
}

void RenderEventListenerImp::display( Render * render, size_t pass ) {
    iter_->node_->display( render );
}

void RenderEventListenerImp::displayLost()
{
}

void RenderEventListenerImp::destroy() 
{
}

