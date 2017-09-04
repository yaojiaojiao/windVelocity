#include "readdata.h"

ReadData::ReadData(QString FileName)
{
    QFile file(FileName);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"file wrong";
    }
    QTextStream in(&file);
    QString line;
    QStringList str_list;
    while (!in.atEnd())
    {
        line = in.readLine();
        str_list= line.split(" ");
        for(int i=0; i<22572; i++) {
            data[i] = str_list[i].toDouble();
        }
    }

    file.close();

//    return data1;
}
