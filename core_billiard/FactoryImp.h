#pragma once
namespace my_render_imp {


// template policy style for sub-factories is possible
// but I don't want to expose implementations on a header file.
class FactoryImp : IMPLEMENTS_( Factory ), IMPLEMENTS_( InstanceResolver ) {
public: // from Factory
    virtual Node * createVisualScene( domVisual_sceneRef );
    virtual Geometry * createGeometry( domGeometryRef );

    virtual void release( Base * );

public: // from InstanceResolver
    virtual Base * resolveInstanceUrl( wstring id );
    virtual Instance * createInstance( wstring url, Base * owner );
    virtual void releaseInstance( Instance * );

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
