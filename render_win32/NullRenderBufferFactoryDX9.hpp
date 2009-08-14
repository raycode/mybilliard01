#pragma once
namespace my_render_win32_dx9 {


class NullRenderBufferFactoryDX9
    : public NullRenderBufferFactory
    , public NullRenderEventListener
    , IMPLEMENTS_( RenderBufferFactoryDX9 )
{
public:
};


}
