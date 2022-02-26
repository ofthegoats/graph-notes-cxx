#ifndef NOTE_WIDGET_H
#define NOTE_WIDGET_H

#include "draw_widget.hpp"

#include <QGridLayout>
#include <QPushButton>
#include <QWidget>

namespace Ui
{
class NoteWidget : public QWidget
{
    Q_OBJECT

public:
    NoteWidget(QWidget*, QString);  // constructor
    ~NoteWidget() = default;        // destructor

public slots:
    void saveNote();
    void setColourBlack();
    void setColourRed();
    void setColourGreen();
    void setColourBlue();

private:
    Ui::DrawWidget* drawArea;
    QString         filename;
    QGridLayout*    gridLayout;
    QPushButton*    saveButton;
    QPushButton*    blackButton;
    QPushButton*    redButton;
    QPushButton*    greenButton;
    QPushButton*    blueButton;
};
}  // namespace Ui

#endif  // NOTE_WIDGET_H
