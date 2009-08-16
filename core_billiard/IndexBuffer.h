#pragma once
namespace my_render {


MY_INTERFACE IndexBuffer {
    virtual ~IndexBuffer() {}

    virtual size_t getNumberOfIndex() = 0;

};


}
