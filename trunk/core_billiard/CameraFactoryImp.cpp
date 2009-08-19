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

    const bool bPerspectiveCamera = (NULL != tech->getPerspective());
    const bool bOrthographicCamera = ( NULL != tech->getOrthographic() );

    bool succeed = false;
    if( bPerspectiveCamera ) {
        domPerspectiveRef pers = tech->getPerspective();
        succeed = readCameraPerspective( newCamera, pers );

    } else if( bOrthographicCamera ) {
        domOrthographicRef ortho = tech->getOrthographic();
        succeed = readCameraOrthographic( newCamera, ortho );

    } else
        succeed = false;

    if( false == succeed ) {
        destroyCamera( newCamera );
        return NULL;
    }

    return newCamera;
}

Camera * CameraFactoryImp::find( wstring id )
{
    return NULL;
}

bool CameraFactoryImp::destroyCamera( Camera * )
{
    return false;
}

bool CameraFactoryImp::readCameraPerspective( CameraImp * newCamera, domPerspectiveRef )
{
    return false;
}

bool CameraFactoryImp::readCameraOrthographic( CameraImp * newCamera, domOrthographicRef )
{
    return false;
}

bool CameraFactoryImp::isAlreadyCreated( wstring id )
{
    return false;
}

CameraImp * CameraFactoryImp::createCamera( wstring id, wstring name, wstring uri )
{
    return NULL;
}


}