#include "StdAfx.h"
#include "my_app.h"

#include "MyCameraModeSMC.h"
#include "MyCameraTopViewSMC.h"
#include "MyCameraAimViewSMC.h"
#include "MyCameraMoveViewMoveSMC.h"
#include "MyCameraMoveViewRotateSMC.h"
#include "MouseStateSMC.h"

#define _versID _versID_Mode
#include "autogenerated/MyCameraModeSMC_AutoGenerated.cpp"
#undef _versID

#define _versID _versID_TopView
#include "autogenerated/MyCameraTopViewSMC_AutoGenerated.cpp"
#undef _versID

#define _versID _versID_AimView
#include "autogenerated/MyCameraAimViewSMC_AutoGenerated.cpp"
#undef _versID

#define _versID _versID_MoveViewMove
#include "autogenerated/MyCameraMoveViewMoveSMC_AutoGenerated.cpp"
#undef _versID

#define _versID _versID_MoveViewRotate
#include "autogenerated/MyCameraMoveViewRotateSMC_AutoGenerated.cpp"
#undef _versID

#define _versID _versID_MouseState
#include "autogenerated/MouseStateSMC_AutoGenerated.cpp"
#undef _versID

