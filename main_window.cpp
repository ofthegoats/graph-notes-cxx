#include "main_window.hpp"

#include "note_widget.hpp"

#include <QFileDialog>

Ui::MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    gridLayout = new QGridLayout(this);
    layoutWidget = new QWidget;  // placeholder, to set layout
    openFileButton = new QPushButton("open file", this);
    newNoteButton = new QPushButton("new note", this);
    notesTabs = new QTabWidget(this);
    allFilesList = new QListWidget(this);

    layoutWidget->setLayout(gridLayout);
    setCentralWidget(layoutWidget);  // set grid layout for mainwindow
    gridLayout->addWidget(openFileButton, 0, 0);
    gridLayout->addWidget(newNoteButton, 0, 1);
    gridLayout->addWidget(allFilesList, 1, 0);
    gridLayout->addWidget(notesTabs, 1, 1);

    // connect signals (events) to slots (methods)
    connect(openFileButton, SIGNAL(clicked()), this, SLOT(openDBButtonClicked()));
    connect(newNoteButton, SIGNAL(clicked()), this, SLOT(newNoteButtonClicked()));
    connect(allFilesList, SIGNAL(itemClicked(QListWidgetItem*)), this,
      SLOT(allFilesListItemClicked(QListWidgetItem*)));
}

void Ui::MainWindow::openDBButtonClicked()
{
    QString fp =
      QFileDialog::getOpenFileName(this, "open db", ".", "graph db files(*.db)");
    openDB(fp);
}

void Ui::MainWindow::newNoteButtonClicked()
{
    QString fp =
      QFileDialog::getSaveFileName(this, "open note", ".", "note files(*.png)");
    openNote(fp);
}

void Ui::MainWindow::allFilesListItemClicked(QListWidgetItem* item)
{
    openNote(item->text());
}

void Ui::MainWindow::openDB(QString filename)
{
    // TODO
}

void Ui::MainWindow::openNote(QString filename)
{
    // TODO, will use NoteWidget
    NoteWidget* note = new NoteWidget(notesTabs, filename);
    notesTabs->addTab(note, filename);
}
