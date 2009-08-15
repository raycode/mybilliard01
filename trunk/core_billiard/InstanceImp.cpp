#include "stdafx.h"
#include "my_render_imp.h"
namespace my_render_imp {


Base * InstanceImp::getInstanceOwner() {
    return instanceOwner_;
}

wstring InstanceImp::getUrl() {
    return url_;
}

Base * InstanceImp::getResolvedReferrence() {
    return resolver_->resolveInstanceUrl( getUrl() );
}

InstanceImp::InstanceImp( InstanceResolver * resolver )
: resolver_( resolver ), instanceOwner_( NULL )
{
}

void InstanceImp::setInstanceOwner( Base * owner ) {
    instanceOwner_ = owner;
}

void InstanceImp::setUrl( wstring url ) {
    url_ = url;
}

}
