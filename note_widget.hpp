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
    void openNote();
    void setColourBlack();
    void setColourRed();
    void setColourGreen();
    void setColourBlue();
    void setWidthThin();
    void setWidthMedium();
    void setWidthThick();

private:
    Ui::DrawWidget* drawArea;  // area for drawing on note
    QString         filename;  // used for graphs
    QGridLayout*    gridLayout;
    QPushButton*    saveButton;   // write note to file
    QPushButton*    blackButton;  // change pen colour
    QPushButton*    redButton;
    QPushButton*    greenButton;
    QPushButton*    blueButton;
    QPushButton*    thinButton;  // change pen width
    QPushButton*    mediumButton;
    QPushButton*    thickButton;
};
}  // namespace Ui

#endif  // NOTE_WIDGET_H
