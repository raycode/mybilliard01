#pragma once
namespace my_render {


INTERFACE_ IndexBuffer {
public:
    virtual size_t getNumberOfIndex() = 0;
    virtual size_t getNumberOfByteForEach() = 0; // 2 or 4

public: virtual ~IndexBuffer() {}
};


}
