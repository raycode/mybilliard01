#include "Stdafx.h"
#include "my_render_imp.h"
namespace my_render_imp {


CameraOrthographicImp::CameraOrthographicImp()
{
    x_mag_ = y_mag_ = 50.f;
}

float	CameraOrthographicImp::getXMag()	{ return x_mag_;	 }
float	CameraOrthographicImp::getYMag()	{ return y_mag_;	 }

void	CameraOrthographicImp::setXMag(float magx)		{
    x_mag_   = magx;
}

void 	CameraOrthographicImp::setYMag(float magy)		{
    y_mag_   = magy;
}

void CameraOrthographicImp::getProjectionMatrix44( float * returnMatrix44, bool bRightHand, bool bRowMajor )
{
    float columnMajor[16];

    columnMajor[ 1 ] = columnMajor[ 2 ] = columnMajor[ 3 ]
    = columnMajor[ 4 ] = columnMajor[ 6 ] = columnMajor[ 7 ]
    = columnMajor[ 8 ] = columnMajor[ 9 ] = columnMajor[ 11 ]
    = columnMajor[ 12 ] = columnMajor[ 13 ] = 0.f;

    columnMajor[ 0 ] = 2.f / getXMag();
    columnMajor[ 5 ] = 2.f / getYMag();
    columnMajor[ 15 ] = 1.f;

    if( bRightHand ) {
        columnMajor[ 10 ] = 1.f / ( getZNear() - getZFar() );
        columnMajor[ 14 ] = getZNear() / ( getZNear() - getZFar() );

    } else {
        columnMajor[ 10 ] = 1.f / ( getZFar() - getZNear() );
        columnMajor[ 14 ] = -getZNear() / ( getZFar() - getZNear() );
 
    }

    memcpy( returnMatrix44, columnMajor, sizeof( columnMajor ) );
    
    if( bRowMajor ) {
        returnMatrix44[ 11 ] = columnMajor[ 14 ];
        returnMatrix44[ 14 ] = columnMajor[ 11 ];
    }
}


}