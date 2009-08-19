#include "StdAfx.h"
#include "my_render_imp.h"
namespace my_render_imp {


CameraImp::CameraImp() 
: isPerspective_( true )
{
}

bool CameraImp::isPerspective() {
    return isPerspective_;
}

bool CameraImp::isOrthographic() {
    return false == isPerspective();
}

CameraPerspective * CameraImp::getPerspectiveCamera() {
    return & perspectiveCamera_;
}

CameraOrthographic * CameraImp::getOrthographicCamera() {
    return & orthographicCamera_;
}

void CameraImp::setAsPerspective( bool val ) {
    isPerspective_ = val;
}


}