#include "stdafx.h"
#include "my_app.h"

MyCamera::MyCamera( Camera * cameraCollada, NxActor * cameraPhysX )
: cameraCollada_( cameraCollada )
, cameraPhysX_( cameraPhysX )
{
}


void MyCamera::getViewMatrix44( float * returnMatrix44, bool bRightHand, bool bRowMajor )
{
    D3DXVECTOR3 position( 2.f, 0.5f, 1.f );
    D3DXVECTOR3 lookAt( 0.f, 0.f, 0.f );
    D3DXVECTOR3 up( 0.f, 0.f, 1.f );
    D3DXMATRIX view;
    D3DXMatrixLookAtLH( &view, &position, &lookAt, &up );

    if( bRowMajor ) {
        RowMajorMatrix44f rst( (float*) (view.m), false );
        memcpy( returnMatrix44, &rst, sizeof( rst ) );

    } else {
        memcpy( returnMatrix44, &view, sizeof( view ) );

    }

}