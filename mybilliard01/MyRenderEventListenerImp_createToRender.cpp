#include "stdafx.h"
#include "my_app.h"


ToRender * MyRenderEventListenerImp::createToRender( Node * node, RenderBufferFactory * renderFactory )
{
    if( NULL == node ) return & nullToRender_;
    const wstring nodeName = node->getName();

    const wstring effectFilename = ConstEffectFilename::getEffectFilenameByNodeName( nodeName );
    EffectShader * const effect = renderFactory->createEffectShader( effectFilename );
    assert( effect );
    if( NULL == effect ) return & nullToRender_;

    ToRender * newToRender = NULL;
    if( nodeName == L"CUE_BALL" ) {
        newToRender = new ToRenderImp_RenderMonkey( node, effect );
    } else {
        newToRender = new ToRenderImp( node, effect );
    }
    
    toRenders_.push_back( ToRenderPtr( newToRender ) );

    findLights( effect );

    return newToRender;
}

void MyRenderEventListenerImp::findLights( EffectShader * effect ) {

    const wchar_t * names[] = {
        L"Light0_Position",
        L"Light1_Position" };

    for( size_t i = 0; i < sizeof( names ) / sizeof( wchar_t * ); ++i )
    {
        const wstring name = names[ i ];
        if( false == effect->hasVariableByName( name ) ) continue;
        if( sharedLights_.find( name ) != sharedLights_.end() ) continue;

        ShaderVariable * const newLight = effect->createVariableByName( name );
        sharedLights_.insert( SharedLights::value_type( name, newLight ) );
    }
}

ShaderVariable * MyRenderEventListenerImp::getLight( wstring name ) {
    SharedLights::const_iterator iter = sharedLights_.find( name );
    if( sharedLights_.end() == iter ) {
        assert( L"light not found." && false );
        return NULL;
    }
    return iter->second;
}

