#pragma once
namespace my_render_imp {


class CameraImp : public BaseImp, IMPLEMENTS_INTERFACE( Camera ) {
public: // from Camera
    virtual bool isPerspective() OVERRIDE;
    virtual bool isOrthographic() OVERRIDE;

    virtual CameraPerspective * getPerspectiveCamera() OVERRIDE;
    virtual CameraOrthographic * getOrthographicCamera() OVERRIDE;

public:
    CameraImp();

private:
    CameraPerspective * perspectiveCamera_;
    CameraOrthographic * orthographicCamera_;
};


}
