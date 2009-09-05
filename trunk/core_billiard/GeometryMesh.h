#pragma once
namespace my_render {


MY_INTERFACE GeometryMesh : EXTENDS_INTERFACE( Displayable ) {

    virtual void appendPrimitive( GeometryMeshPrimitive * primitive ) PURE;
    virtual size_t getNumberOfPrimitives() PURE;
    virtual GeometryMeshPrimitive * getPrimitive( size_t index ) PURE;

};


}
