#include "dswf.h"

DSWF::DSWF(double elevationAngle, MatrixXd azimuthAngle, int losNum,int heightNum, MatrixXd losVelocity)
{
    vectorVelocity = MatrixXd::Zero(heightNum-1,3);

    Eigen::Matrix3d SiSum = MatrixXd::Zero(3,3);
    Eigen::MatrixXd Si = MatrixXd::Zero(3,losNum);
    for(int i=0;i<losNum;i++){
        Si(0,i) = sin(elevationAngle/180.0*PI);
        Si(1,i) = cos(elevationAngle/180.0*PI)*cos(azimuthAngle(i)/180.0*PI);
        Si(2,i) = cos(elevationAngle/180.0*PI)*sin(azimuthAngle(i)/180.0*PI);
    }
    SiSum = SiSum + Si*Si.transpose();

    for(int m=0;m<heightNum-1;m++) {
        Eigen::Vector3d SiVri(0,0,0);
        Eigen::Vector3d temp(0,0,0);
        for(int n=0;n<losNum;n++) {
            SiVri = SiVri + losVelocity(m,n)*Si.col(n);
            temp = SiSum.inverse()*SiVri;
            vectorVelocity.row(m) = temp;
        }
    }
}



//DSWF::DSWF(double elevationAngle, double azimuthAngle[], int losNum, MatrixXf losVelocity)
//{
//    Eigen::Matrix3d SiSum;
//    SiSum << 0,0,0,0,0,0,0,0,0;
//    Eigen::Vector3d SiVri(0,0,0);
//    for (int i=0; i<losNum; i++) {
//        qDebug() << "i = " << i;
//        Eigen::Vector3d Si;
//        Si(0) = sin(elevationAngle/180.0*PI);
//        qDebug() << "Si(0) = " << Si(0);
//        Si(1) = cos(elevationAngle/180.0*PI)*cos(azimuthAngle[i]/180.0*PI);
//        qDebug() << "Si(1) = " << Si(1);
//        Si(2) = cos(elevationAngle/180.0*PI)*sin(azimuthAngle[i]/180.0*PI);
//        qDebug() << "Si(2) = " << Si(2);
//        SiSum = SiSum + Si*Si.transpose();
//        SiVri = SiVri + losVelocity[i]*Si;
//    }
//    std::cout << "SiSum = \n" << SiSum << "\n";
//    std::cout << "SiSum-1 = \n" << SiSum.inverse() << "\n";
//    std::cout << "SiVri = \n" << SiVri << "\n";
//    Eigen::Vector3d temp = SiSum.inverse()*SiVri;
//    vectorVelocity[0] = temp(0);
//    vectorVelocity[1] = temp(1);
//    vectorVelocity[2] = temp(2);
//}

