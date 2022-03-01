#include "note_widget.hpp"

Ui::NoteWidget::NoteWidget(QWidget* parent, QString fp) : QWidget(parent)
{
    gridLayout = new QGridLayout(this);
    saveButton = new QPushButton("save", this);
    blackButton = new QPushButton("black", this);
    redButton = new QPushButton("red", this);
    greenButton = new QPushButton("green", this);
    blueButton = new QPushButton("blue", this);
    thinButton = new QPushButton("thin", this);
    mediumButton = new QPushButton("medium", this);
    thickButton = new QPushButton("thick", this);
    drawArea = new Ui::DrawWidget(this);
    filename = fp;

    setLayout(gridLayout);
    gridLayout->addWidget(saveButton, 0, 0);
    gridLayout->addWidget(blackButton, 0, 1);
    gridLayout->addWidget(redButton, 0, 2);
    gridLayout->addWidget(greenButton, 0, 3);
    gridLayout->addWidget(blueButton, 0, 4);
    gridLayout->addWidget(thinButton, 0, 5);
    gridLayout->addWidget(mediumButton, 0, 6);
    gridLayout->addWidget(thickButton, 0, 7);
    gridLayout->addWidget(drawArea, 1, 0, 1, 8);

    // connect signals (event) to slots (methods)
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveNote()));
    connect(blackButton, SIGNAL(clicked()), this, SLOT(setColourBlack()));
    connect(redButton, SIGNAL(clicked()), this, SLOT(setColourRed()));
    connect(greenButton, SIGNAL(clicked()), this, SLOT(setColourGreen()));
    connect(blueButton, SIGNAL(clicked()), this, SLOT(setColourBlue()));
    connect(thinButton, SIGNAL(clicked()), this, SLOT(setWidthThin()));
    connect(mediumButton, SIGNAL(clicked()), this, SLOT(setWidthMedium()));
    connect(thickButton, SIGNAL(clicked()), this, SLOT(setWidthThick()));
}

void Ui::NoteWidget::saveNote()
{
    // TODO
}

void Ui::NoteWidget::setColourBlack() { drawArea->setPenColour(Qt::black); }
void Ui::NoteWidget::setColourRed() { drawArea->setPenColour(Qt::red); }
void Ui::NoteWidget::setColourGreen() { drawArea->setPenColour(Qt::green); }
void Ui::NoteWidget::setColourBlue() { drawArea->setPenColour(Qt::blue); }

void Ui::NoteWidget::setWidthThin() { drawArea->setPenWidth(2); }
void Ui::NoteWidget::setWidthMedium() { drawArea->setPenWidth(4); }
void Ui::NoteWidget::setWidthThick() { drawArea->setPenWidth(6); }
