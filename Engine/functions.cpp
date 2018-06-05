#include "functions.h"

bool IsInRect(QPoint Point, QPoint S, QPoint E) {
    bool Res = 0;
    if (E.x() > S.x() && E.y() > S.y())
        { if (Point.x() > S.x() && Point.y() > S.y() && Point.x() < E.x() && Point.y() < E.y()) Res = 1; }
    else if (E.x() > S.x() && E.y() < S.y())
        { if (Point.x() > S.x() && Point.y() < S.y() && Point.x() < E.x() && Point.y() > E.y()) Res = 1; }
    else if (E.x() < S.x() && E.y() > S.y())
        { if (Point.x() < S.x() && Point.y() > S.y() && Point.x() > E.x() && Point.y() < E.y()) Res = 1; }
    else if (E.x() < S.x() && E.y() < S.y())
        { if (Point.x() < S.x() && Point.y() < S.y() && Point.x() > E.x() && Point.y() > E.y()) Res = 1; }
    return Res;
}

int CountDistance(QPoint X1, QPoint X2) {
    return sqrt(pow(X1.x() - X2.x(), 2) + pow(X1.y() - X2.y(), 2));
}

double CountAngle(QPointF X1, QPointF X2) {
    double Angle = 0;
    Angle = atan(fabs(X2.x() - X1.x()) / fabs(X2.y() - X1.y())) * 180 / M_PI;
    if (X2.x() >= X1.x() && X2.y() >= X1.y()) Angle = 180 - Angle;
    else if (X2.x() <= X1.x() && X2.y() >= X1.y()) Angle = 180 + Angle;
    else if (X2.x() <= X1.x() && X2.y() <= X1.y()) Angle = 360 - Angle;
    return Angle;
}

QString GenerateID(int &ID1, int &ID2, int &ID3, int &ID4) {
    QString Res;

    Res.append(char(ID1));
    Res.append(char(ID2));
    Res.append(char(ID3));
    Res.append(char(ID4)); ++ID4;

    if (ID4 > 57) {
        ID4 = 48;
        ++ID3;
        if (ID3 > 57) {
            ID3 = 48;
            ++ID2;
            if (ID2 > 90) {
                ID2 = 65;
                ++ID1;
            }
        }
    }

    return Res;
}

QString StreamRead(QTextStream &TStream) {
    QString Res = ";";
    while ((Res.size() > 1 && Res[0] == '/' && Res[1] == '/') || (Res[Res.size() - 1] == ':') || (Res[0] == ';')) TStream >> Res;
    return Res;
}

QPoint Rotate(QPoint RP, QPoint CP, double Angle) {
    double A = CountAngle(CP, RP) + 270;
    double Fi = A + Angle; while (Fi >= 360) Fi -= 360; Fi = Fi * M_PI / 180;
    int D = CountDistance(CP, RP);
    return QPoint(D * cos(Fi), D * sin(Fi));
}
