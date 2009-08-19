#pragma once

struct ColladaFactoryImp::TestingBackdoor {

    PRIVATE_METHOD_1( wstring, ColladaFactoryImp, refineURL, wstring );

    PRIVATE_MEMBER( Instances, ColladaFactoryImp, instances_ );
    PRIVATE_MEMBER( NodeFactoryPtr, ColladaFactoryImp, nodeFactory_ );
    PRIVATE_MEMBER( GeometryFactoryPtr, ColladaFactoryImp, geometryFactory_ );

};
