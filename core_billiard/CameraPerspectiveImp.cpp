#include "StdAfx.h"
#include "my_render_imp.h"
namespace my_render_imp {


CameraPerspectiveImp::CameraPerspectiveImp()  {
    x_fov_ = y_fov_ = 36.0f;
}

float	CameraPerspectiveImp::getXFov()	{
    return x_fov_;	 
}
float	CameraPerspectiveImp::getYFov()	{
    return y_fov_;	 
}
void	CameraPerspectiveImp::setXFov(float fovx) {
    x_fov_   = fovx;  
}
void 	CameraPerspectiveImp::setYFov(float fovf) { 
    y_fov_   = fovf;  
}

void CameraPerspectiveImp::getProjectionMatrix44( float * returnMatrix44, bool bRightHand, bool bRowMajor )
{
    float columnMajor[16];

    columnMajor[ 1 ] = columnMajor[ 2 ] = columnMajor[ 3 ]
    = columnMajor[ 4 ] = columnMajor[ 6 ] = columnMajor[ 7 ]
    = columnMajor[ 8 ] = columnMajor[ 9 ]
    = columnMajor[ 12 ] = columnMajor[ 13 ] = columnMajor[ 15 ] = 0.f;

    if( 0.f == getAspect() ) throw exception();

    const float yScale = 1.f / tan( getYFov() / 180.f * 3.141592f / 2.f );
    const float xScale = yScale / getAspect();

    columnMajor[ 0 ] = xScale;
    columnMajor[ 5 ] = yScale;

    const float denominator = getZNear() - getZFar();
    if( 0.f == denominator ) throw exception();

    if( bRightHand ) {
        columnMajor[ 10 ] = getZFar() / denominator;
        columnMajor[ 11 ] = -1.f;
        columnMajor[ 14 ] = getZNear() * getZFar() / denominator;

    } else {
        columnMajor[ 10 ] = getZFar() / - denominator;
        columnMajor[ 11 ] = 1.f;
        columnMajor[ 14 ] = - getZNear() * getZFar() / - denominator;

    }

    assert( sizeof( columnMajor ) == sizeof(float) * 16 );
    memcpy( (unsigned char *) returnMatrix44, (unsigned char *) columnMajor, sizeof( columnMajor ) );

    if( bRowMajor ) {
        returnMatrix44[ 11 ] = columnMajor[ 14 ];
        returnMatrix44[ 14 ] = columnMajor[ 11 ];
    }

}


}