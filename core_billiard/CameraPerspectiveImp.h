#pragma once
namespace my_render_imp {


class CameraPerspectiveImp : public CameraCommonImp, IMPLEMENTS_INTERFACE( CameraPerspective ) {
public: // from CameraPerspective
    virtual float	getXFov() OVERRIDE;
    virtual float	getYFov() OVERRIDE;

    virtual void	setXFov(float fovx) OVERRIDE;
    virtual void 	setYFov(float fovf) OVERRIDE;

public:
    CameraPerspectiveImp();

private:
    float		x_fov_;
    float		y_fov_;

};


}
