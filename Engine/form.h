#ifndef FORM_H
#define FORM_H

#include <QVector>
#include "button.h"

class Form : public BaseTextureModule {
private:
    QPoint Pos;
    QVector<Button> Buttons;
    int Size;

    bool Dynamic;
    bool Visible;

public:
    Form();
    ~Form();

    QSize GetTextureSize(int i);
    QPoint GetEndPos();
    QPixmap& GetTexture(int i) { return TextureContainer[0][i]; }
    QPoint& GetPos() { return Pos; }
    QVector<Button>& GetButtons() { return Buttons; }
    Button& GetButton(int i) { return Buttons[i]; }
    int GetSize() { return Size; }
    bool IsDynamic() { return Dynamic; }
    bool IsVisible() { return Visible; }

    Form& SetPos(const QPoint _Pos);
    Form& AddButton(const Button _B);
    Form& SetSize(const int _Size);
    Form& SetDynamic(const bool _Val);
    Form& SetVisible(const bool _Val);
};

#endif // FORM_H
