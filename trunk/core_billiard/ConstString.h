#pragma once
#include <string>
namespace my_utility {

    using namespace std;

    class ConstString {
    public:
	    static wstring windowTitle();
	    static wstring effectFilename();
	    static wstring colladaPhysXFilename();
	    static wstring colladaVisualAssetFilename();
        static wstring dllDirectoryForColladaDOM();
    };

}