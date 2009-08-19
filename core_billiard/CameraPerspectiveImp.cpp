#include "StdAfx.h"
#include "my_render_imp.h"
namespace my_render_imp {


CameraPerspectiveImp::CameraPerspectiveImp() 
{
    x_fov_ = y_fov_ = 36.0f;
}

float	CameraPerspectiveImp::getXFov()	{ return x_fov_;	 }
float	CameraPerspectiveImp::getYFov()	{ return y_fov_;	 }
void	CameraPerspectiveImp::setXFov(float fovx)		{ x_fov_   = fovx;  }
void 	CameraPerspectiveImp::setYFov(float fovf)		{ y_fov_   = fovf;  }

}