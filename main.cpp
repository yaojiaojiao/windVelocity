#include <QCoreApplication>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <iostream>
#include <math.h>
#include <qmath.h>
#include <QDebug>
#include <dswf.h>
#include <losvelocity.h>
#include <readdata.h>

const double wavelength = 1.55e-6;
const double freqResol = 550e6/1024;
const int losVelocityBandPoints = 40;
int heightNum = 44;
int spectNumPerRan = 513;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString ch[4] = {
        "E://QtProjects//0904//windVelocity//data//ChA00dat_1.txt",
        "E://QtProjects//0904//windVelocity//data//ChA00dat_2.txt",
        "E://QtProjects//0904//windVelocity//data//ChA00dat_3.txt",
        "E://QtProjects//0904//windVelocity//data//ChA00dat_4.txt"
    };

    ReadData *rd;
    LOSVelocity *los;

    MatrixXd losV = MatrixXd::Zero(heightNum-1,4);

    //径向风速
    for(int i=0;i<4;i++) {
        rd = new ReadData(ch[i]);
        los = new LOSVelocity(rd->data, heightNum, spectNumPerRan, losVelocityBandPoints, wavelength, freqResol);
        losV.col(i) = los->radialvelo;
    }
    std::cout << losV << endl;

    MatrixXd azimuthAngle(1,4);
    azimuthAngle << 90,180,270,360;
    double elevationAngle =60.0;
    int losNum = azimuthAngle.cols();
    std::cout << "col=" << losNum << endl;

    DSWF *vect;
    vect = new DSWF(elevationAngle,azimuthAngle,losNum,heightNum,losV);
    std::cout << "Vect=\n" << vect->vectorVelocity;


    return a.exec();
}
