#pragma once
namespace my_render_imp {

class FactoryImp : IMPLEMENTS_ Factory, IMPLEMENTS_ InstanceResolver {
public: // from Factory
    virtual Node * createVisualScene( domVisual_sceneRef );
    virtual Geometry * createGeometry( domGeometryRef );

    virtual void release( Base * );

public: // from InstanceResolver
    virtual Base * resolveInstanceUrl( wstring id );
    virtual Instance * createInstance( string url );
    virtual void releaseInstance( Instance * );

public:
    FactoryImp();

private: // instances
    typedef list< InstancePtr > Instances;
    Instances instances_;

private: // sub-factories
    NodeFactoryPtr nodeFactory_;
    GeometryFactoryPtr geometryFactory_;
};

}
