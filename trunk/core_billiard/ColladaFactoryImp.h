#pragma once
namespace my_render_imp {


class ColladaFactoryImp : IMPLEMENTS_INTERFACE( ColladaFactory ), IMPLEMENTS_INTERFACE( InstanceResolver ) {
public: // from ColladaFactory
    virtual Node * createVisualScene( domVisual_sceneRef ) OVERRIDE;
    virtual Geometry * createGeometry( domGeometryRef ) OVERRIDE;

    virtual bool destroy( Base * ) OVERRIDE;

public: // from InstanceResolver
    virtual Instance * createInstance( wstring url ) OVERRIDE;
    virtual bool destroyInstance( Instance * ) OVERRIDE;

    virtual Base * resolveInstanceURL( wstring id ) OVERRIDE;

public:
    ColladaFactoryImp();

private:
    wstring refineURL( wstring url );

private: // instances
    typedef list< InstanceImpPtr > Instances;
    Instances instances_;

private: // sub-factories
    NodeFactoryPtr nodeFactory_;
    GeometryFactoryPtr geometryFactory_;

    MY_UNIT_TEST_BACKDOOR;
};


}
