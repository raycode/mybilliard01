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
        static wstring effectFilenameByNodeName( wstring nodeName );
    };

}