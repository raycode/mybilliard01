#include "StdAfx.h"
#include "my_render_imp.h"
namespace my_render_imp {


CameraImp::CameraImp() 
: perspectiveCamera_( NULL )
, orthographicCamera_( NULL )
{
}

bool CameraImp::isPerspective() {
    return NULL != getPerspectiveCamera();
}

bool CameraImp::isOrthographic() {
    return NULL != getOrthographicCamera();
}

CameraPerspective * CameraImp::getPerspectiveCamera() {
    return perspectiveCamera_;
}
CameraOrthographic * CameraImp::getOrthographicCamera() {
    return orthographicCamera_;
}

}