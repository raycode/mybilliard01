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
    return newToRender;
}

