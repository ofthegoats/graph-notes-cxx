#include "note_widget.hpp"

#include <QFileInfo>

void setButtonIcon(QString path, QPushButton* button)
{
    QPixmap pixmap(path);
    QIcon bIcon(pixmap);
    button->setIcon(bIcon);
    button->setIconSize(pixmap.rect().size());
}

// constructor, return a new note widget
Ui::NoteWidget::NoteWidget(QWidget* parent, QString fp, Graph* graph) : QWidget(parent)
{
    // instances of elements: buttons with shortcuts, drawing area, layout
    gridLayout = new QGridLayout(this);
    saveButton = new QPushButton("save", this);
    saveButton->setShortcut(Qt::CTRL + Qt::Key_S);
    blackButton = new QPushButton(this);
    redButton = new QPushButton(this);
    greenButton = new QPushButton(this);
    blueButton = new QPushButton(this);
    thinButton = new QPushButton("thin", this);
    mediumButton = new QPushButton("medium", this);
    thickButton = new QPushButton("thick", this);
    eraserButton = new QPushButton("eraser", this);
    clearAllButton = new QPushButton("clear all", this);
    undoButton = new QPushButton("undo", this);
    undoButton->setShortcut(Qt::CTRL + Qt::Key_Z);
    redoButton = new QPushButton("redo", this);
    redoButton->setShortcut(Qt::CTRL + Qt::Key_Y);
    outboundLinksList = new QListWidget(this);
    inboundLinksList = new QListWidget(this);
    outboundHeaderLabel = new QLabel("outbound links", this);
    inboundHeaderLabel = new QLabel("inbound links", this);
    drawArea = new Ui::DrawWidget(this);
    filename = fp;
    g = graph;

    setButtonIcon(
      "/usr/share/icons/Adwaita/24x24/actions/document-save-symbolic.symbolic.png", saveButton);
    setButtonIcon("/usr/share/icons/Adwaita/24x24/actions/edit-clear-all-symbolic.symbolic.png",
      clearAllButton);
    setButtonIcon(
      "/usr/share/icons/Adwaita/24x24/actions/edit-undo-symbolic.symbolic.png", undoButton);
    setButtonIcon(
      "/usr/share/icons/Adwaita/24x24/actions/edit-redo-symbolic.symbolic.png", redoButton);

    blackButton->setStyleSheet("background-color: black");
    redButton->setStyleSheet("background-color: red");
    greenButton->setStyleSheet("background-color: green");
    blueButton->setStyleSheet("background-color: blue");

    // graphical settings to lists do not become too wide
    outboundLinksList->setMaximumWidth(400);
    outboundHeaderLabel->setMaximumWidth(400);
    inboundLinksList->setMaximumWidth(400);
    inboundHeaderLabel->setMaximumWidth(400);

    updateLists();

    // layout all the widgets
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

    // connect buttons to appropriate methods
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

// simple file management procedures
void Ui::NoteWidget::saveNote() { drawArea->saveImage(filename); }
void Ui::NoteWidget::openNote(bool exists) { drawArea->openImage(filename, exists); }

// simple colour management procedures
void Ui::NoteWidget::setColourBlack() { drawArea->setPenColour(Qt::black); }
void Ui::NoteWidget::setColourRed() { drawArea->setPenColour(Qt::red); }
void Ui::NoteWidget::setColourGreen() { drawArea->setPenColour(Qt::green); }
void Ui::NoteWidget::setColourBlue() { drawArea->setPenColour(Qt::blue); }
void Ui::NoteWidget::setEraser() { drawArea->setPenColour(Qt::white); }

// simple width management procedures
void Ui::NoteWidget::setWidthThin() { drawArea->setPenWidth(4); }
void Ui::NoteWidget::setWidthMedium() { drawArea->setPenWidth(8); }
void Ui::NoteWidget::setWidthThick() { drawArea->setPenWidth(12); }

// update lists of connected notes to match the new graph
void Ui::NoteWidget::updateLists()
{
    // need id to find connected nodes
    int id = g->findId(filename.toStdString());
    // clear list and readd new values
    inboundLinksList->clear();
    for (auto n : g->inboundLinks(id)) {
        QFileInfo file(QString::fromStdString(n.data));
        QListWidgetItem* newItem = new QListWidgetItem;
        // store full path but only show base filename to user
        newItem->setData(Qt::UserRole, file.absoluteFilePath());
        newItem->setText(file.baseName());
        inboundLinksList->addItem(newItem);
    }
    outboundLinksList->clear();
    for (auto n : g->outboundLinks(id)) {
        QFileInfo file(QString::fromStdString(n.data));
        QListWidgetItem* newItem = new QListWidgetItem;
        // store full path but only show base filename to user
        newItem->setData(Qt::UserRole, file.absoluteFilePath());
        newItem->setText(file.baseName());
        outboundLinksList->addItem(newItem);
    }
}
