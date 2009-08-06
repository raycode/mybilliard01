#pragma once
namespace my_collada {

class MyColladaLoader {
public:
    MyColladaLoader( wstring filename );

    domCOLLADA * getCOLLADA();

private:
    const wstring filename_;    
    const DAEPtr dae_;
    domCOLLADA * collada_;
};


}
