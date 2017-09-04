#ifndef DSWF_H
#define DSWF_H
#include <eigen/Eigen>
#include <Eigen/Dense>
#include <math.h>
#include <iostream>
#include <QDebug>

const double PI = 3.1415926;
using namespace Eigen;
using namespace std;

class DSWF
{
public:
    DSWF(double elevationAngle, MatrixXd azimuthAngle, int losNum, int heightNum, MatrixXd losVelocity);
    MatrixXd vectorVelocity;
};
#endif // DSWF_H
