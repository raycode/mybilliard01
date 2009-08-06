#pragma once
namespace my_collada {

class MyColladaLoader {
public:
    MyColladaLoader( wstring filename );

    domCOLLADA * getCOLLADA();
    DAE * getDAE();

    daeElement * idLookup( wstring id );

    domVisual_scene * getInstancedVisualScene();
    vector< domMesh * > getMeshByNodeID( wstring nodeId );

private:
    const wstring filename_;    
    const DAEPtr dae_;
    domCOLLADA * collada_;
};


template < typename T1 >
static T1 * daeDowncast( daeElement * elem ) {
    if( NULL == elem ) return NULL;
    if( T1::ID() != elem->typeID() ) return NULL;
    return (T1*) elem;
}


}
