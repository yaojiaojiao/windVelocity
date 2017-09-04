#ifndef READDATA_H
#define READDATA_H
#include "QFile"
#include <eigen/Eigen>
#include <Eigen/Dense>
#include <math.h>
#include <iostream>
#include <QDebug>
using namespace std;
using namespace Eigen;

class ReadData
{
public:
    ReadData(QString FileName);
    double data[22572] = {0};
};

#endif // READDATA_H
