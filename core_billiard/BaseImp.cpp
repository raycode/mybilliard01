#include "my_render_imp.h"
namespace my_render_imp {


wstring BaseImp::getID() {
    return id_;
}

wstring BaseImp::getName() {
    return name_;
}

void BaseImp::setID( wstring id ) {
    id_ = id;
}

void BaseImp::setName( wstring name ) {
    name_ = name;
}

}
