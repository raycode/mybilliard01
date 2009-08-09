#include "my_render_imp.h"
namespace my_render_imp {


wstring BaseImp::getID() {
    return id_;
}

wstring BaseImp::getName() {
    return name_;
}

wstring BaseImp::getURI() {
    return uri_;
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
