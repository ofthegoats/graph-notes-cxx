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
    QString getFilename() { return filename; };

public slots:
    void saveNote();
    void openNote();
    void setColourBlack();
    void setColourRed();
    void setColourGreen();
    void setColourBlue();
    void setEraser();
    void setWidthThin();
    void setWidthMedium();
    void setWidthThick();

private:
    Ui::DrawWidget* drawArea;  // area for drawing on note
    QString         filename;  // used for saves/loads
    QGridLayout*    gridLayout;
    QPushButton*    saveButton;   // write note to file
    QPushButton*    blackButton;  // change pen colour
    QPushButton*    redButton;
    QPushButton*    greenButton;
    QPushButton*    blueButton;
    QPushButton*    thinButton;  // change pen width
    QPushButton*    mediumButton;
    QPushButton*    thickButton;
    QPushButton*    eraserButton;
};
}  // namespace Ui

#endif  // NOTE_WIDGET_H
