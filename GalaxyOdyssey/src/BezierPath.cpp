 #include "BezierPath.h"

BezierPath::BezierPath(){

}

BezierPath::~BezierPath(){

}

void BezierPath::AddCurve(BezierCurve curve, int samples){
    mCurves.push_back(curve);
    mSample.push_back(samples);
}

void BezierPath::Sample(std::vector<Vector2> * samplePath){
    for(unsigned int i = 0; i < mCurves.size(); i++){
        for(float t = 0; t <= 1.0f; t += 1.0f/mSample[i]){
            samplePath->push_back(mCurves[i].calculateCurvePoint(t));
        }
    }
}