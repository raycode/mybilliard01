#include "StdAfx.h"
#include "my_render_imp.h"
namespace my_render_imp {


CameraFactoryImp::CameraFactoryImp( InstanceResolver * instanceResolver )
{
}

Camera * CameraFactoryImp::createCamera( domCameraRef cameraDom )
{
    const wstring id = convertString( cameraDom->getId() );
    const wstring name = convertString( cameraDom->getName() );
    const wstring uri = convertString( cameraDom->getDocumentURI()->getURI() );
    if( isAlreadyCreated( id ) ) return NULL;

    CameraImp * const newCamera = createCamera( id, name, uri );
    if( NULL == newCamera ) return NULL;

    domOpticsRef optics = cameraDom->getOptics();
    if( NULL == optics ) return NULL;

    domTechnique_commonRef tech = optics->getTechnique_common();
    if( NULL == tech ) return NULL;

    const bool succeedOrthographic = readCameraOrthographic( newCamera, tech->getOrthographic() );
    const bool succeedPerspective = readCameraPerspective( newCamera, tech->getPerspective() );

    if( false == succeedPerspective && false == succeedOrthographic ) {
        destroyCamera( newCamera );
        return NULL;
    }

    return newCamera;
}

bool CameraFactoryImp::readCameraPerspective( CameraImp * newCamera, domPerspectiveRef perspective )
{
    if( NULL == perspective ) return false;

    newCamera->setAsPerspective( true );
    CameraPerspective * const newPerspectiveCamera = newCamera->getPerspectiveCamera();

    if( perspective->getXfov() ) newPerspectiveCamera->setXFov( (float) perspective->getXfov()->getValue() );
    if( perspective->getYfov() ) newPerspectiveCamera->setYFov( (float) perspective->getYfov()->getValue() );
    if( perspective->getZnear() ) newPerspectiveCamera->setZNear( (float) perspective->getZnear()->getValue() );
    if( perspective->getZfar() ) newPerspectiveCamera->setZFar( (float) perspective->getZfar()->getValue() );
    if( perspective->getAspect_ratio() ) newPerspectiveCamera->setAspect( (float) perspective->getAspect_ratio()->getValue() );

    if( newPerspectiveCamera->getZNear() < 1.f) newPerspectiveCamera->setZNear( 1.f );
    return true;
}

bool CameraFactoryImp::readCameraOrthographic( CameraImp * newCamera, domOrthographicRef orthographic )
{
    if( NULL == orthographic ) return false;

    newCamera->setAsPerspective( false );
    CameraOrthographic * const newOrthographicCamera = newCamera->getOrthographicCamera();

    if( orthographic->getXmag() ) newOrthographicCamera->setXMag( (float) orthographic->getXmag()->getValue() );
    if( orthographic->getYmag() ) newOrthographicCamera->setYMag( (float) orthographic->getYmag()->getValue() );
    if( orthographic->getZnear() ) newOrthographicCamera->setZNear( (float) orthographic->getZnear()->getValue() );
    if( orthographic->getZfar() ) newOrthographicCamera->setZFar( (float) orthographic->getZfar()->getValue() );
    if( orthographic->getAspect_ratio() ) newOrthographicCamera->setAspect( (float) orthographic->getAspect_ratio()->getValue() );

    if( newOrthographicCamera->getZNear() < 1.f) newOrthographicCamera->setZNear( 1.f );
    return true;
}

Camera * CameraFactoryImp::find( wstring id ) {
    MY_FOR_EACH( Cameras, iter, cameras_ ) {
        if( (*iter)->getID() != id ) continue;
        return &**iter;
    }
    return NULL;
}

bool CameraFactoryImp::destroyCamera( Camera * camera ) {
    MY_FOR_EACH( Cameras, iter, cameras_ ) {
        if( (&**iter) != camera ) continue;
        cameras_.erase( iter );
        return true;
    }
    return false;
}

bool CameraFactoryImp::isAlreadyCreated( wstring id ) {
    return NULL != find( id );
}

CameraImp * CameraFactoryImp::createCamera( wstring id, wstring name, wstring uri )
{
    if( isAlreadyCreated( id ) ) return NULL;

    CameraImp * const newCamera = new CameraImp();
    if( NULL == newCamera ) return NULL;

    cameras_.push_back( CameraPtr( newCamera ) );

    newCamera->setID( id );
    newCamera->setName( name );
    newCamera->setURI( uri );

    return newCamera;
}

Camera * CameraFactoryImp::getDefaultCamera() {
    return & defaultCamera_;
}


}