#pragma once
namespace my_render {


INTERFACE_ InstanceGeometry: public Instance {
public:
    virtual Geometry * getGeometry() = 0;

public: virtual ~InstanceGeometry() {}
};


typedef vector< InstanceGeometry * > InstanceGeometries;
MY_ITERATOR_DECL( InstanceGeometries );


}
