#pragma once
namespace my_render_win32_dx9_imp {


template< typename ResourceType_ >
class SharedResource {
public:
    SharedResource( ResourceType_ res )
        : resource( res )
    {}

    ~SharedResource() {
        SAFE_RELEASE( resource );
    }

    ResourceType_ resource;
};


}