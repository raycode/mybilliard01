#pragma once


namespace RenderMonkeySemantics {

#define MATRIX_SEMANTIC( NEW_SEMANTIC ) NEW_SEMANTIC, NEW_SEMANTIC##Transpose, NEW_SEMANTIC##Inverse, NEW_SEMANTIC##InverseTranspose

    enum { ViewPosition,
        ViewDirection,

        ViewportWidthInverse,
        ViewportHeightInverse,

        MATRIX_SEMANTIC( World ),
        MATRIX_SEMANTIC( View ),
        MATRIX_SEMANTIC( Projection ),
        MATRIX_SEMANTIC( ViewProjection ),
        MATRIX_SEMANTIC( WorldView ),
        MATRIX_SEMANTIC( WorldViewProjection ),
        SIZE_OF_SEMANTICS };

#undef MATRIX_SEMANTIC

};