#include "main_window.hpp"

#include "database.hpp"
#include "note_widget.hpp"

#include <QFileDialog>

Ui::MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    gridLayout = new QGridLayout(this);
    layoutWidget = new QWidget;  // placeholder, to set layout
    openDBButton = new QPushButton("open database", this);
    newDBButton = new QPushButton("new database", this);
    openNoteButton = new QPushButton("open note", this);
    newNoteButton = new QPushButton("new note", this);
    notesTabs = new QTabWidget(this);
    allFilesList = new QListWidget(this);
    dbIsOpen = false;  // no db open by default
    dbFilepath = "";

    layoutWidget->setLayout(gridLayout);
    setCentralWidget(layoutWidget);  // set grid layout for mainwindow
    gridLayout->addWidget(openDBButton, 0, 0);
    gridLayout->addWidget(newDBButton, 0, 1);
    gridLayout->addWidget(openNoteButton, 1, 0);
    gridLayout->addWidget(newNoteButton, 1, 1);
    gridLayout->addWidget(allFilesList, 2, 0, 1, 2);
    gridLayout->addWidget(notesTabs, 0, 2, 3, 1);

    // connect signals (events) to slots (methods)
    connect(openDBButton, SIGNAL(clicked()), this, SLOT(openDBButtonClicked()));
    connect(newDBButton, SIGNAL(clicked()), this, SLOT(newDBButtonClicked()));
    connect(openNoteButton, SIGNAL(clicked()), this, SLOT(openNoteButtonClicked()));
    connect(newNoteButton, SIGNAL(clicked()), this, SLOT(newNoteButtonClicked()));
    connect(allFilesList, SIGNAL(itemClicked(QListWidgetItem*)), this,
      SLOT(allFilesListItemClicked(QListWidgetItem*)));
}

void Ui::MainWindow::openDBButtonClicked()
{
    QString fp =
      QFileDialog::getOpenFileName(this, "open db", ".", "graph db files(*.db)");
    db_prepare(fp.toLocal8Bit().data());
    openDB(fp);
}

void Ui::MainWindow::newDBButtonClicked()
{
    QString fp =
      QFileDialog::getSaveFileName(this, "open db", ".", "graph db files(*.db)");
    db_prepare(fp.toLocal8Bit().data());
    openDB(fp);
}

void Ui::MainWindow::openNoteButtonClicked()
{
    QString fp =
      QFileDialog::getOpenFileName(this, "open note", ".", "note files(*.png)");
    // when db is open, new notes join the graph and db
    if (dbIsOpen && g.findId(fp.toStdString()) == -1) {
        int id = g.addNode(fp.toStdString());
        db_add_node(dbFilepath.toLocal8Bit().data(), id, fp.toLocal8Bit().data());
        allFilesList->addItem(QString::fromStdString(fp.toStdString()));
    }
    openNoteTab(fp);
}

void Ui::MainWindow::newNoteButtonClicked()
{
    QString fp =
      QFileDialog::getSaveFileName(this, "open note", ".", "note files(*.png)");
    // when db is open, new notes join the graph and db
    if (dbIsOpen && g.findId(fp.toStdString()) == -1) {
        int id = g.addNode(fp.toStdString());
        db_add_node(dbFilepath.toLocal8Bit().data(), id, fp.toLocal8Bit().data());
        allFilesList->addItem(QString::fromStdString(fp.toStdString()));
    }
    openNoteTab(fp);
}

void Ui::MainWindow::allFilesListItemClicked(QListWidgetItem* item)
{
    openNoteTab(item->text());
}

void Ui::MainWindow::openDB(QString filename)
{
    g = db_get_graph(filename.toLocal8Bit().data());
    dbIsOpen = true;
    dbFilepath = filename;
    for (auto node : g.getNodes())
        allFilesList->addItem(QString::fromStdString(node.data));
}

void Ui::MainWindow::openNoteTab(QString filename)
{
    NoteWidget* note = new NoteWidget(notesTabs, filename);
    note->openNote();
    notesTabs->addTab(note, filename);
}
