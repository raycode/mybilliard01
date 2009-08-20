#pragma once
namespace my_render_imp {


class CameraCommonImp : IMPLEMENTS_INTERFACE( CameraCommon ) {
public:
    virtual float	getZNear() OVERRIDE;
    virtual float	getZFar() OVERRIDE;
    virtual float	getAspect() OVERRIDE;

    virtual void 	setZNear(float nearf) OVERRIDE;
    virtual void	setZFar(float farf) OVERRIDE;
    virtual void	setAspect(float aspect) OVERRIDE;

public:
    CameraCommonImp();

private:
    float		aspect_;
    float		zNear_;
    float		zFar_;

};

}