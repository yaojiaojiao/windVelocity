#include <losvelocity.h>
#include <readdata.h>

using namespace Eigen;
using namespace std;

LOSVelocity::LOSVelocity(double da[], int heightNum, int spectNumPerRan, int losVelocityBandPoints, double wavelength, double freqResol)
{
    data = MatrixXd::Zero(heightNum,spectNumPerRan);
    radialvelo =  MatrixXd::Zero(heightNum-1,1);
    FreqAxis = MatrixXd::Zero(1,spectNumPerRan);
    //频率轴FreqAxis
    for(int i=0;i<spectNumPerRan;i++)
        {
            FreqAxis(0,i) = freqResol*i;
        }

    //数据按heightNum*spectNumPerRan转换为二维数组
    for(int i=0;i<heightNum;i++) {
        for (int j=0; j<spectNumPerRan; j++)
        {
            data(i,j) = da[i*spectNumPerRan+j];
        }
    }

    //最接近AOM的频率
    double min = abs(FreqAxis(0,0) - AOM);
    int Index;                //最接近AOM频率下标
    int FreqDw;               //频率下标
    int FreqUp;               //频率上标
    for(int m = 0; m<spectNumPerRan; m++) {
        if(min > abs(FreqAxis(0,m) - AOM)) {
            min = abs(FreqAxis(0,m) - AOM);
            Index = m;
        }
    }

    FreqDw = Index-losVelocityBandPoints;
    FreqUp = Index+losVelocityBandPoints;
//    std::cout << "Index = \n" << Index << std::endl;

   DopplerFreq = MatrixXd::Zero(heightNum-1,1);          //DopplerFreq =43*1
    //功率谱减去最后一行噪声数据并找出最大值
    for(int row = 0; row<heightNum-1; row++)
    {
        int k = 0;
        double max = data(row,FreqDw) - data(43,FreqDw);
        for (int col=FreqDw; col<FreqUp; col++) {
            if (max<(data(row,col) - data(43,col))) {
                max = data(row,col) - data(43,col);
                k = col;
            }
        }
        DopplerFreq(row,0) = FreqAxis(0,k);
    }

    //径向速度计算
    for(int row=0;row<heightNum-1;row++) {
        radialvelo(row,0) = -(DopplerFreq(row,0) - AOM)*wavelength/2;
    }

}


