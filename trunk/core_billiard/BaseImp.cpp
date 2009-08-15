#include "stdafx.h"
#include "my_render_imp.h"
namespace my_render_imp {


const wchar_t * BaseImp::getID() {
    return id_.c_str();
}

const wchar_t * BaseImp::getName() {
    return name_.c_str();
}

const wchar_t * BaseImp::getURI() {
    return uri_.c_str();
}

void BaseImp::setID( wstring id ) {
    id_ = id;
}

void BaseImp::setName( wstring name ) {
    name_ = name;
}

void BaseImp::setURI( wstring uri ) {
    uri_ = uri;
}


}
