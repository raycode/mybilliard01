#pragma once

struct SceneImp::TestingBackdoor
{
    PRIVATE_METHOD_1_VOID( SceneImp, storeFilename, wstring );

    PRIVATE_MEMBER( wstring, SceneImp, filename_ );
    PRIVATE_MEMBER( wstring, SceneImp, pathname_ );
    PRIVATE_MEMBER( ColladaFactory *, SceneImp, colladaFactory_ );
    PRIVATE_MEMBER( RenderBufferFactory *, SceneImp, renderFactory_ );
    PRIVATE_MEMBER( Node *, SceneImp, currentScene_ );
    PRIVATE_MEMBER( DAEPtr, SceneImp, dae_ );
    PRIVATE_MEMBER( domCOLLADARef, SceneImp, collada_ );
    PRIVATE_MEMBER( Camera *, SceneImp, currentCamera_ );
};

