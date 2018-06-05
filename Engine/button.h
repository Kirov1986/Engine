#ifndef BUTTON_H
#define BUTTON_H

#include <QPoint>
#include "basetexturemodule.h"

class Button : public BaseTextureModule {
private:
    QPoint Pos;
    int State, OpenForm;
    bool Visible;

public:
    Button();
    ~Button();

    QPixmap& GetTexture();
    QPoint GetEndPos();
    QPoint& GetPos() { return Pos; }
    int GetState() { return State; }
    int GetOpenForm() { return OpenForm; }
    bool IsVisible() { return Visible; }

    Button& SetPos(const QPoint _Pos);
    Button& SetState(const int _State);
    Button& SetOpenForm(const int _OpenForm);
    Button& SetVisible(const bool _Val);
};

#endif // BUTTON_H
