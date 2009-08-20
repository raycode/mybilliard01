#include "stdafx.h"
#include "my_render_imp.h"
namespace my_render_imp {


CameraCommonImp::CameraCommonImp()
{
    aspect_ = 16.0f / 9.0f;
    zNear_ = 0.01f;
    zFar_ = 10.0f * 100.f;		
}

float	CameraCommonImp::getZNear()	{ return zNear_;  }
float	CameraCommonImp::getZFar()	{ return zFar_;	 }
float	CameraCommonImp::getAspect()	{ return aspect_; }

void 	CameraCommonImp::setZNear(float nearf)	{ zNear_  = nearf; }
void	CameraCommonImp::setZFar(float farf)		{ zFar_	 = farf;  }
void	CameraCommonImp::setAspect(float aspect)	{ aspect_ = aspect;}


}

