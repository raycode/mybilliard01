#pragma once
namespace my_render_imp {


class CameraFactoryImp : IMPLEMENTS_INTERFACE( CameraFactory ) {
public: // from CameraFactory
    virtual Camera * createCamera( domCameraRef ) OVERRIDE;
    virtual Camera * find( wstring id ) OVERRIDE;
    virtual bool destroyCamera( Camera * ) OVERRIDE;

public:
    CameraFactoryImp( InstanceResolver * instanceResolver );

private: // typedef
    typedef domCamera::domOptics domOptics;
    typedef domCamera::domOpticsRef domOpticsRef;
    typedef domOptics::domTechnique_common domTechnique_common;
    typedef domOptics::domTechnique_commonRef domTechnique_commonRef;
    typedef domTechnique_common::domPerspectiveRef domPerspectiveRef;
    typedef domTechnique_common::domOrthographicRef domOrthographicRef;

private: // read dom
    bool readCameraPerspective( CameraImp * newCamera, domPerspectiveRef );
    bool readCameraOrthographic( CameraImp * newCamera, domOrthographicRef );

private:
    bool isAlreadyCreated( wstring id );
    CameraImp * createCamera( wstring id, wstring name, wstring uri );

private:
    typedef list< CameraPtr > Cameras;
    Cameras cameras_;

};


}