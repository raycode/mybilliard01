#include "stdafx.h"
#include "my_render_imp.h"
namespace my_render_imp {


InstanceImp::InstanceImp( InstanceResolver * resolver, wstring url )
    : resolver_( resolver ), url_( url ), resolvedReference_( NULL )
{
}

wstring InstanceImp::getURL() {
    return url_;
}

Base * InstanceImp::getResolvedReference() {
    if( NULL == resolvedReference_ )
        resolvedReference_ = resolver_->resolveInstanceURL( getURL() );
    return resolvedReference_;
}


}
