#pragma once
namespace my_render_imp {


class CameraOrthographicImp : public CameraCommonImp, IMPLEMENTS_INTERFACE( CameraOrthographic ) {
public:
    virtual float	getXMag() OVERRIDE;
    virtual float	getYMag() OVERRIDE;

    virtual void	setXMag( float magx ) OVERRIDE;
    virtual void 	setYMag( float magy ) OVERRIDE;

    virtual void getProjectionMatrix44( float * returnMatrix44, bool bRightHand, bool bRowMajor ) OVERRIDE;

public:
    CameraOrthographicImp();

private:
    float		x_mag_;
    float		y_mag_;

};


}