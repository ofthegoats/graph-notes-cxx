#include "note_widget.hpp"

Ui::NoteWidget::NoteWidget(QWidget* parent, QString fp) : QWidget(parent)
{
    gridLayout = new QGridLayout(this);
    saveButton = new QPushButton("save", this);
    drawArea = new Ui::DrawWidget(this);
    filename = fp;
    // pen modifiers TODO

    setLayout(gridLayout);
    gridLayout->addWidget(saveButton, 0, 0);
    gridLayout->addWidget(drawArea, 1, 0);
}

void Ui::NoteWidget::saveNote()
{
    // TODO
}
