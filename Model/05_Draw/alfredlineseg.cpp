#include "alfredlineseg.h"

AlfredLineSeg::AlfredLineSeg()
{
    bDraw=false;
    bSelLine=false;
    bSelStartPt=false;
    bSelEndPt=false;
    seg=new LineSegment;
}
