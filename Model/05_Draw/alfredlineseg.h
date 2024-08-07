#ifndef ALFREDLINE_H
#define ALFREDLINE_H

class PointEx{
public:
    double x;
    double y;
    PointEx(double xp=0,double yp=0){
        x=xp;
        y=yp;
    };
};

class LineSegment {
public:
    PointEx startPoint;
    PointEx endPoint;
    LineSegment(PointEx start,PointEx end){
        startPoint=start;
        endPoint=end;
    };
    LineSegment(){

    }
};

class AlfredLineSeg
{
public:
    bool bDraw; // 是否绘制
    bool bSelLine; // 是否选中线
    bool bSelStartPt;   // 是否选中的是线段的起始点
    bool bSelEndPt;

    LineSegment *seg;

public:
    AlfredLineSeg();
};

#endif // ALFREDLINE_H
