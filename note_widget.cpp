#include "note_widget.hpp"

#include <QFileInfo>

Ui::NoteWidget::NoteWidget(QWidget* parent, QString fp, Graph* graph) : QWidget(parent)
{
    gridLayout = new QGridLayout(this);
    saveButton = new QPushButton("save", this);
    saveButton->setShortcut(Qt::CTRL + Qt::Key_S);
    blackButton = new QPushButton("black", this);
    redButton = new QPushButton("red", this);
    greenButton = new QPushButton("green", this);
    blueButton = new QPushButton("blue", this);
    thinButton = new QPushButton("thin", this);
    mediumButton = new QPushButton("medium", this);
    thickButton = new QPushButton("thick", this);
    eraserButton = new QPushButton("eraser", this);
    clearAllButton = new QPushButton("clear all", this);
    undoButton = new QPushButton("undo", this);
    redoButton = new QPushButton("redo", this);
    outboundLinksList = new QListWidget(this);
    inboundLinksList = new QListWidget(this);
    outboundHeaderLabel = new QLabel("outbound links", this);
    inboundHeaderLabel = new QLabel("inbound links", this);
    drawArea = new Ui::DrawWidget(this);
    filename = fp;
    g = graph;

    outboundLinksList->setMaximumWidth(400);
    outboundHeaderLabel->setMaximumWidth(400);
    inboundLinksList->setMaximumWidth(400);
    inboundHeaderLabel->setMaximumWidth(400);

    updateLists();

    setLayout(gridLayout);
    gridLayout->addWidget(saveButton, 0, 0);
    gridLayout->addWidget(blackButton, 0, 1);
    gridLayout->addWidget(redButton, 0, 2);
    gridLayout->addWidget(greenButton, 0, 3);
    gridLayout->addWidget(blueButton, 0, 4);
    gridLayout->addWidget(thinButton, 0, 5);
    gridLayout->addWidget(mediumButton, 0, 6);
    gridLayout->addWidget(thickButton, 0, 7);
    gridLayout->addWidget(eraserButton, 0, 8);
    gridLayout->addWidget(clearAllButton, 0, 9);
    gridLayout->addWidget(undoButton, 0, 10);
    gridLayout->addWidget(redoButton, 0, 11);
    gridLayout->addWidget(drawArea, 1, 0, 5, 12);
    gridLayout->addWidget(outboundHeaderLabel, 2, 13);
    gridLayout->addWidget(outboundLinksList, 3, 13);
    gridLayout->addWidget(inboundHeaderLabel, 4, 13);
    gridLayout->addWidget(inboundLinksList, 5, 13);

    // connect signals (event) to slots (methods)
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveNote()));
    connect(blackButton, SIGNAL(clicked()), this, SLOT(setColourBlack()));
    connect(redButton, SIGNAL(clicked()), this, SLOT(setColourRed()));
    connect(greenButton, SIGNAL(clicked()), this, SLOT(setColourGreen()));
    connect(blueButton, SIGNAL(clicked()), this, SLOT(setColourBlue()));
    connect(thinButton, SIGNAL(clicked()), this, SLOT(setWidthThin()));
    connect(mediumButton, SIGNAL(clicked()), this, SLOT(setWidthMedium()));
    connect(thickButton, SIGNAL(clicked()), this, SLOT(setWidthThick()));
    connect(eraserButton, SIGNAL(clicked()), this, SLOT(setEraser()));
    connect(clearAllButton, SIGNAL(clicked()), this->drawArea, SLOT(clearImage()));
    connect(undoButton, SIGNAL(clicked()), this->drawArea, SLOT(undo()));
    connect(redoButton, SIGNAL(clicked()), this->drawArea, SLOT(redo()));
}

QString Ui::NoteWidget::getFilename() { return filename; }

void Ui::NoteWidget::saveNote() { drawArea->saveImage(filename); }
void Ui::NoteWidget::openNote(bool exists) { drawArea->openImage(filename, exists); }

void Ui::NoteWidget::setColourBlack() { drawArea->setPenColour(Qt::black); }
void Ui::NoteWidget::setColourRed() { drawArea->setPenColour(Qt::red); }
void Ui::NoteWidget::setColourGreen() { drawArea->setPenColour(Qt::green); }
void Ui::NoteWidget::setColourBlue() { drawArea->setPenColour(Qt::blue); }
void Ui::NoteWidget::setEraser() { drawArea->setPenColour(Qt::white); }

void Ui::NoteWidget::setWidthThin() { drawArea->setPenWidth(4); }
void Ui::NoteWidget::setWidthMedium() { drawArea->setPenWidth(8); }
void Ui::NoteWidget::setWidthThick() { drawArea->setPenWidth(12); }

void Ui::NoteWidget::updateLists()
{
    int id = g->findId(filename.toStdString());
    inboundLinksList->clear();
    for (auto n : g->inboundLinks(id)) {
        QFileInfo file(QString::fromStdString(n.data));
        QListWidgetItem* newItem = new QListWidgetItem;
        newItem->setData(Qt::UserRole, file.absoluteFilePath());
        newItem->setText(file.baseName());
        inboundLinksList->addItem(newItem);
    }
    outboundLinksList->clear();
    for (auto n : g->outboundLinks(id)) {
        QFileInfo file(QString::fromStdString(n.data));
        QListWidgetItem* newItem = new QListWidgetItem;
        newItem->setData(Qt::UserRole, file.absoluteFilePath());
        newItem->setText(file.baseName());
        outboundLinksList->addItem(newItem);
    }
}
