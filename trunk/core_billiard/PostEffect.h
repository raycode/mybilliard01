#pragma once
namespace my_render {


MY_INTERFACE PostEffect
    : EXTENDS_INTERFACE( RenderTarget )
    , EXTENDS_INTERFACE( RenderTargetCallBack )
{

};

}