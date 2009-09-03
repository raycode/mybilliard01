#pragma once
#include <string>
namespace my_utility {

    using namespace std;

    class ConstString {
    public:
        static wstring dllDirectory();
	    static wstring windowTitle();
	    static wstring colladaPhysXFilename();
	    static wstring colladaVisualAssetFilename();

    public: // effect
        static wstring effectFilenameByNodeName( wstring nodeName );
        static wstring shadowMapEffectShaderFilename();
        static wstring effectFilename_Blur();
        static wstring effectFilename_HDR();
        static wstring effectFilename_SSAO();

    public: // sound
        static wstring soundFilename_BallStrong( size_t index );
        static wstring soundFilename_BallWeak( size_t index );
        static wstring soundFilename_BallBreak( size_t index );
        static wstring soundFilename_Chalk( size_t index );
        static wstring soundFilename_Pocket( size_t index );
        static wstring soundFilename_CueStrong( size_t index );
        static wstring soundFilename_CueWeak( size_t index );
        static wstring soundFilename_BounceOnRail( size_t index );
    };

}