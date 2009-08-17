#pragma once
namespace my_render_imp {


// template policy style for sub-factories is possible
// but I don't want to expose implementations on a header file.
class FactoryImp : IMPLEMENTS_INTERFACE( Factory ), IMPLEMENTS_INTERFACE( InstanceResolver ) {
public: // from Factory
    virtual Node * createVisualScene( domVisual_sceneRef ) OVERRIDE;
    virtual Geometry * createGeometry( domGeometryRef ) OVERRIDE;

    virtual void release( Base * ) OVERRIDE;

public: // from InstanceResolver
    virtual Base * resolveInstanceUrl( wstring id ) OVERRIDE;
    virtual Instance * createInstance( wstring url, Base * owner ) OVERRIDE;
    virtual void releaseInstance( Instance * ) OVERRIDE;

public:
    FactoryImp();

private: // instances
    typedef list< InstanceImpPtr > Instances;
    Instances instances_;

private: // sub-factories
    NodeFactoryPtr nodeFactory_;
    GeometryFactoryPtr geometryFactory_;
};


}
