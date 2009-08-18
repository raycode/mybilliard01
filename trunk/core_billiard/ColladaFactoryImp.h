#pragma once
namespace my_render_imp {


class ColladaFactoryImp : IMPLEMENTS_INTERFACE( ColladaFactory ), IMPLEMENTS_INTERFACE( InstanceResolver ) {
public: // from ColladaFactory
    virtual Node * createVisualScene( domVisual_sceneRef ) OVERRIDE;
    virtual Geometry * createGeometry( domGeometryRef ) OVERRIDE;

    virtual bool destroy( Base * ) OVERRIDE;

public: // from InstanceResolver
    virtual Base * resolveInstanceUrl( wstring id ) OVERRIDE;
    virtual Instance * createInstance( wstring url, Base * owner ) OVERRIDE;
    virtual bool destroyInstance( Instance * ) OVERRIDE;

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
};


}
