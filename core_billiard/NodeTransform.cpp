#include "my_render_imp.h"
namespace my_render_imp {

NodeTransform::NodeTransform()
: type_( ENodeTransformUnknown )
, rotationAngle_( 0.f )
, animation_(NULL)
{
}

NodeTransformType NodeTransform::getType( wstring nameType ) {
    if( nameType == L"rotate" )
        return (ENodeTransformRotate); 
    else if( nameType == L"translate" )
        return (ENodeTransformTranslate); 
    else if( nameType == L"matrix" ) 
        return (ENodeTransformMatrix); 
    else if( nameType == L"scale" ) 
        return (ENodeTransformScale); 
    else if( nameType == L"lookat" ) 
        return (ENodeTransformLookAt); 
    else if( nameType == L"skew" ) 
        return (ENodeTransformSkew);

    return (ENodeTransformUnknown); 
}

void NodeTransform::setTranslate( NxVec3 ) {

}

void NodeTransform::setRotate( NxVec3 dir, NxReal angle ) {

}

void NodeTransform::setScale( NxVec3 ) {

}

void NodeTransform::setLookAt( NxVec3 v[] ) {

}

void NodeTransform::setMatrix( NxMat34 m ) {

}

void NodeTransform::setSid( wstring sid ) {

}

}