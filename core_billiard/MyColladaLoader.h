#pragma once
#include <string>
namespace billiard {
using namespace std;


class MyColladaLoader {
public:
    MyColladaLoader( wstring filename );
    
private:
    wstring filename_;    
    DAE dae_;
};


}
