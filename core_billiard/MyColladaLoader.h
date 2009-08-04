#pragma once
namespace my_collada {

class MyColladaLoader {
public:
    MyColladaLoader( wstring filename );
    
private:
    wstring filename_;    
    DAEPtr dae_;
};


}
