#ifndef NOTE_WIDGET_H
#define NOTE_WIDGET_H

#include "draw_widget.hpp"
#include "graph.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QWidget>

namespace Ui
{
class NoteWidget : public QWidget
{
    Q_OBJECT

public:
    NoteWidget(QWidget*, QString, Graph*);  // constructor
    ~NoteWidget() = default;  // destructor
    QString getFilename();
    QListWidget* outboundLinksList;
    QListWidget* inboundLinksList;

public slots:
    void saveNote();
    void openNote(bool);
    void setColourBlack();
    void setColourRed();
    void setColourGreen();
    void setColourBlue();
    void setEraser();
    void setWidthThin();
    void setWidthMedium();
    void setWidthThick();
    void updateLists();

private:
    Ui::DrawWidget* drawArea;  // area for drawing on note
    Graph* g;  // reference to graph for database which is open, to update lists
    QString filename;  // used for saves/loads
    QGridLayout* gridLayout;
    QPushButton* saveButton;  // write note to file
    QPushButton* blackButton;  // change pen colour
    QPushButton* redButton;
    QPushButton* greenButton;
    QPushButton* blueButton;
    QPushButton* thinButton;  // change pen width
    QPushButton* mediumButton;
    QPushButton* thickButton;
    QPushButton* eraserButton;
    QPushButton* clearAllButton;
    QPushButton* undoButton;
    QPushButton* redoButton;
    QLabel* outboundHeaderLabel;
    QLabel* inboundHeaderLabel;
};
}  // namespace Ui

#endif  // NOTE_WIDGET_H
