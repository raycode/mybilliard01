#pragma once
namespace my_render_d3d9_imp {


class RenderErrorNotifyImp : IMPLEMENTS_( RenderErrorNotify ) {
public:
    virtual void openWindow( wstring );

};


}
