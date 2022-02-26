#include "note_widget.hpp"

Ui::NoteWidget::NoteWidget(QWidget* parent, QString fp) : QWidget(parent)
{
    gridLayout = new QGridLayout(this);
    saveButton = new QPushButton("save", this);
    blackButton = new QPushButton("black", this);
    redButton = new QPushButton("red", this);
    greenButton = new QPushButton("green", this);
    blueButton = new QPushButton("blue", this);
    drawArea = new Ui::DrawWidget(this);
    filename = fp;
    // pen width modifiers TODO

    setLayout(gridLayout);
    gridLayout->addWidget(saveButton, 0, 0);
    gridLayout->addWidget(blackButton, 0, 1);
    gridLayout->addWidget(redButton, 0, 2);
    gridLayout->addWidget(greenButton, 0, 3);
    gridLayout->addWidget(blueButton, 0, 4);
    gridLayout->addWidget(drawArea, 1, 0, 1, 5);

    // connect signals (event) to slots (methods)
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveNote()));
    connect(blackButton, SIGNAL(clicked()), this, SLOT(setColourBlack()));
    connect(redButton, SIGNAL(clicked()), this, SLOT(setColourRed()));
    connect(greenButton, SIGNAL(clicked()), this, SLOT(setColourGreen()));
    connect(blueButton, SIGNAL(clicked()), this, SLOT(setColourBlue()));
}

void Ui::NoteWidget::saveNote()
{
    // TODO
}

void Ui::NoteWidget::setColourBlack() { drawArea->setPenColour(Qt::black); }
void Ui::NoteWidget::setColourRed() { drawArea->setPenColour(Qt::red); }
void Ui::NoteWidget::setColourGreen() { drawArea->setPenColour(Qt::green); }
void Ui::NoteWidget::setColourBlue() { drawArea->setPenColour(Qt::blue); }
