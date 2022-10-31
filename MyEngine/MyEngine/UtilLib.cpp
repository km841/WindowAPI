#include "pch.h"
#include "UtilLib.h"

HPEN		WindowGDI::hPens[(UINT)PEN_TYPE::END] = {};
HBRUSH		WindowGDI::hBrushes[(UINT)BRUSH_TYPE::END] = {};