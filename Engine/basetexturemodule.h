#ifndef BASETEXTUREMODULE_H
#define BASETEXTUREMODULE_H

#include <QString>
#include <QVector>
#include <QPixmap>
#include <QSize>

class BaseTextureModule {
protected:
    QString Name;
    QVector<QVector<QPixmap> > TextureContainer;
    QVector<int> MSecVector;
    QVector<int> StateVector;
public:
    BaseTextureModule();
    BaseTextureModule(QString _Name, QPixmap _Texture);
    BaseTextureModule(QString _Name, QVector<QPixmap> _TextureVector, int _MSecPerA = 0);
    BaseTextureModule(QString _Name, QVector<QVector<QPixmap> > _TextureContainer, int _MSecPerA = 0);
    BaseTextureModule(QString _Name, QVector<QVector<QPixmap> > _TextureContainer, QVector<int> _MSecVector, QVector<int> _StateVector);
    BaseTextureModule(const BaseTextureModule &B);
    ~BaseTextureModule();

    QString& GetName() { return Name; }
    QVector<QVector<QPixmap> >& GetTextureContainer() { return TextureContainer; }
    QVector<int>& GetMSecVector() { return MSecVector; }
    QVector<int>& GetStateVector() { return StateVector; }
    virtual QSize GetTextureSize() { return TextureContainer[0][0].size(); }
    virtual QPoint GetTextureCenter() { return QPoint(TextureContainer[0][0].size().width() / 2, TextureContainer[0][0].size().height() / 2); }

    BaseTextureModule& SetName(const QString _Name);
    BaseTextureModule& SetTexture(const QPixmap _Texture);
    BaseTextureModule& SetTextureVector(const QVector<QPixmap> _TextureVector);
    BaseTextureModule& SetTextureContainer(const QVector<QVector<QPixmap> > _TextureContainer);
    BaseTextureModule& SetMSecVector(const QVector<int> _MSecVector);
    BaseTextureModule& SetStateVector(const QVector<int> _StateVector);
    BaseTextureModule& SetTextureSize(const QSize _Size);
};

BaseTextureModule FindByNameBTM(QVector<BaseTextureModule> &V, QString Name);

#endif // BASETEXTUREMODULE_H
