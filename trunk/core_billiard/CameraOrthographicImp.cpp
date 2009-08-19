#include "Stdafx.h"
#include "my_render_imp.h"
namespace my_render_imp {


CameraOrthographicImp::CameraOrthographicImp()
{
    x_mag_ = y_mag_ = 50.f;
}

float	CameraOrthographicImp::getXMag()	{ return x_mag_;	 }
float	CameraOrthographicImp::getYMag()	{ return y_mag_;	 }

void	CameraOrthographicImp::setXMag(float magx)		{ x_mag_   = magx;  }
void 	CameraOrthographicImp::setYMag(float magy)		{ y_mag_   = magy;  }

}