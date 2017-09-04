#ifndef LOSVELOCITY_H
#define LOSVELOCITY_H
#include <eigen/Eigen>
#include <Eigen/Dense>
#include <math.h>
#include <iostream>
#include <QDebug>
#include "qtextstream.h"
#include <QFile>
#include <QVector>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;
using namespace Eigen;
const double AOM = 56396484.375;

class LOSVelocity
{
public:
    LOSVelocity(double da[], int heightNum, int spectNumPerRan, int losVelocityBandPoints, double wavelength, double freqResol);
    MatrixXd data;
    MatrixXd FreqAxis;
    MatrixXd DopplerFreq;
    MatrixXd radialvelo;

};



#endif // LOSVELOCITY_H
