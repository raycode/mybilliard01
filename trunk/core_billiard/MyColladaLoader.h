#pragma once
#include "my_collada.h"
namespace core_billiard {


class MyColladaLoader {
public:
    MyColladaLoader( wstring filename );
    
private:
    wstring filename_;    
    DAEPtr dae_;
};


}
