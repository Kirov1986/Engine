#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QTextStream>
#include <QPoint>
#include <QVector>
#include <QString>
#include <qmath.h>

bool IsInRect(QPoint Point, QPoint S, QPoint E);
int CountDistance(QPoint X1, QPoint X2);
double CountAngle(QPointF X1, QPointF X2);
QString GenerateID(int &ID1, int &ID2, int &ID3, int &ID4);
QString StreamRead(QTextStream &TStream);
QPoint Rotate(QPoint RP, QPoint CP, double Angle);

#endif // FUNCTIONS_H

