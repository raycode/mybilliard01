#pragma once
namespace my_render {


MY_INTERFACE RenderTargetChain
    : EXTENDS_INTERFACE( RenderTarget )
    , EXTENDS_INTERFACE( RenderTargetCallBack )
{

};

}