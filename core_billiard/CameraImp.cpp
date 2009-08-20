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

void CameraImp::getProjectionMatrix44( float * returnMatrix44, bool bRightHand, bool bRowMajor )
{
    if( isPerspective() ) getPerspectiveCamera()->getProjectionMatrix44( returnMatrix44, bRightHand, bRowMajor );
    else getOrthographicCamera()->getProjectionMatrix44( returnMatrix44, bRightHand, bRowMajor );
}


}