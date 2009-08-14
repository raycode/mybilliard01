#pragma once
namespace my_render {


INTERFACE_ IndexBuffer {
public:
    virtual size_t getNumberOfIndex() = 0;

public: virtual ~IndexBuffer() {}
};


}
