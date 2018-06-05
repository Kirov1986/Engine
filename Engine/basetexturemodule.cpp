#include "basetexturemodule.h"

BaseTextureModule::BaseTextureModule() {
    Name = "noname";
}

BaseTextureModule::BaseTextureModule(QString _Name, QPixmap _Texture) {
    QVector<QPixmap> Temp;
    Name = _Name;
    Temp.push_back(_Texture);
    TextureContainer.push_back(Temp);
}

BaseTextureModule::BaseTextureModule(QString _Name, QVector<QPixmap> _TextureVector, int _MSecPerA) {
    Name = _Name;
    TextureContainer.push_back(_TextureVector);
    MSecVector.push_back(_MSecPerA);
}

BaseTextureModule::BaseTextureModule(QString _Name, QVector<QVector<QPixmap> > _TextureContainer, int _MSecPerA) {
    Name = _Name;
    TextureContainer = _TextureContainer;
    MSecVector.push_back(_MSecPerA);
}

BaseTextureModule::BaseTextureModule(QString _Name, QVector<QVector<QPixmap> > _TextureContainer, QVector<int> _MSecVector, QVector<int> _StateVector) {
    Name = _Name;
    TextureContainer = _TextureContainer;
    MSecVector = _MSecVector;
    StateVector = _StateVector;
}

BaseTextureModule::BaseTextureModule(const BaseTextureModule &B) {
    Name = B.Name;
    TextureContainer = B.TextureContainer;
    MSecVector = B.MSecVector;
    StateVector = B.StateVector;
}

BaseTextureModule::~BaseTextureModule() {

}

BaseTextureModule& BaseTextureModule::SetName(const QString _Name) {
    Name = _Name;
    return *this;
}

BaseTextureModule& BaseTextureModule::SetTexture(const QPixmap _Texture) {
    QVector<QPixmap> Temp;
    Temp.push_back(_Texture);
    TextureContainer.clear();
    TextureContainer.push_back(Temp);
    return *this;
}

BaseTextureModule& BaseTextureModule::SetTextureVector(const QVector<QPixmap> _TextureVector) {
    TextureContainer.clear();
    TextureContainer.push_back(_TextureVector);
    return *this;
}

BaseTextureModule& BaseTextureModule::SetTextureContainer(const QVector<QVector<QPixmap> > _TextureContainer) {
    TextureContainer = _TextureContainer;
    return *this;
}

BaseTextureModule& BaseTextureModule::SetMSecVector(const QVector<int> _MSecVector) {
    MSecVector = _MSecVector;
    return *this;
}

BaseTextureModule& BaseTextureModule::SetStateVector(const QVector<int> _StateVector) {
    StateVector = _StateVector;
    return *this;
}

BaseTextureModule& BaseTextureModule::SetTextureSize(const QSize _Size) {
    for (int i = 0; i < TextureContainer.size(); i++) for (int j = 0; j < TextureContainer[i].size(); j++) TextureContainer[i][j] = TextureContainer[i][j].scaled(_Size);
    return *this;
}

BaseTextureModule FindByNameBTM(QVector<BaseTextureModule> &V, QString Name) {
    BaseTextureModule Res;
    for (int i = 0; i < V.size(); i++) if (V[i].GetName() == Name) {
        Res = V[i];
        break;
    }
    return Res;
}
