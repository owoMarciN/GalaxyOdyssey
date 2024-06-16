#ifndef BEZIER_PATH_H_
#define BEZIER_PATH_H_

#include "MathHelper.h"
#include <vector>

class BezierPath{
private:

    std::vector<BezierCurve> mCurves;
    std::vector<int> mSample;

public:

    BezierPath();
    ~BezierPath();

    void AddCurve(BezierCurve curve, int samples);
    void Sample(std::vector<Vector2>* samplePath);

};


#endif