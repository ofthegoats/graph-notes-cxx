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
    connectionEditorButton = new QPushButton("edit connections", this);
    notesTabs = new QTabWidget(this);
    allFilesList = new QListWidget(this);
    connectionEditor = new Ui::ConnectionEditor(nullptr, {});
    dbIsOpen = false;  // no db open by default
    dbFilepath = "";

    // settings for a tab widget
    notesTabs->setMovable(true);
    notesTabs->setTabsClosable(true);
    connect(notesTabs, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));

    layoutWidget->setLayout(gridLayout);
    setCentralWidget(layoutWidget);  // set grid layout for mainwindow
    gridLayout->addWidget(openDBButton, 0, 0);
    gridLayout->addWidget(newDBButton, 0, 1);
    gridLayout->addWidget(openNoteButton, 1, 0);
    gridLayout->addWidget(newNoteButton, 1, 1);
    gridLayout->addWidget(connectionEditorButton, 2, 0, 1, 2);
    gridLayout->addWidget(allFilesList, 3, 0, 1, 2);
    gridLayout->addWidget(notesTabs, 0, 2, 4, 1);

    // connect signals (events) to slots (methods)
    connect(openDBButton, SIGNAL(clicked()), this, SLOT(openDBButtonClicked()));
    connect(newDBButton, SIGNAL(clicked()), this, SLOT(newDBButtonClicked()));
    connect(openNoteButton, SIGNAL(clicked()), this, SLOT(openNoteButtonClicked()));
    connect(newNoteButton, SIGNAL(clicked()), this, SLOT(newNoteButtonClicked()));
    connect(allFilesList, SIGNAL(itemClicked(QListWidgetItem*)), this,
      SLOT(listItemClicked(QListWidgetItem*)));
    connect(connectionEditor, SIGNAL(addEdgeRequested(QString, QString)), this,
      SLOT(addEdgeHandler(QString, QString)));
    connect(connectionEditor, SIGNAL(removeEdgeRequested(QString, QString)), this,
      SLOT(removeEdgeHandler(QString, QString)));
    connect(
      connectionEditorButton, SIGNAL(clicked()), this, SLOT(openConnectionEditor()));
}

void Ui::MainWindow::openDBButtonClicked()
{
    QString fp =
      QFileDialog::getOpenFileName(this, "open db", ".", "graph db files(*.db)");
    if (fp == "") return;
    db_prepare(fp.toLocal8Bit().data());
    openDB(fp);
}

void Ui::MainWindow::newDBButtonClicked()
{
    QString fp =
      QFileDialog::getSaveFileName(this, "open db", ".", "graph db files(*.db)");
    if (fp == "") return;
    db_prepare(fp.toLocal8Bit().data());
    openDB(fp);
}

void Ui::MainWindow::openNoteButtonClicked()
{
    QString fp =
      QFileDialog::getOpenFileName(this, "open note", ".", "note files(*.png)");
    if (fp == "") return;
    // when db is open, new notes join the graph and db
    if (dbIsOpen && g.findId(fp.toStdString()) == -1) {
        QFileInfo file(fp);
        int id = g.addNode(fp.toStdString());
        emit graphChanged();  // node was added
        QListWidgetItem* newItem = new QListWidgetItem;
        db_add_node(dbFilepath.toLocal8Bit().data(), id, fp.toLocal8Bit().data());
        newItem->setData(Qt::UserRole, fp);
        newItem->setText(file.baseName());
        allFilesList->addItem(newItem);
    }
    openNoteTab(fp, true);
}

void Ui::MainWindow::newNoteButtonClicked()
{
    QString fp =
      QFileDialog::getSaveFileName(this, "open note", ".", "note files(*.png)");
    if (fp == "") return;
    // when db is open, new notes join the graph and db
    if (dbIsOpen && g.findId(fp.toStdString()) == -1) {
        QFileInfo file(fp);
        int id = g.addNode(fp.toStdString());
        emit graphChanged();  // node was added
        QListWidgetItem* newItem = new QListWidgetItem;
        db_add_node(dbFilepath.toLocal8Bit().data(), id, fp.toLocal8Bit().data());
        newItem->setData(Qt::UserRole, fp);
        newItem->setText(file.baseName());
        allFilesList->addItem(newItem);
    }
    openNoteTab(fp, false);
}

void Ui::MainWindow::listItemClicked(QListWidgetItem* item)
{
    openNoteTab(item->data(Qt::UserRole).toString(), true);
}

void Ui::MainWindow::openDB(QString filename)
{
    g = db_get_graph(filename.toLocal8Bit().data());
    dbIsOpen = true;
    dbFilepath = filename;
    for (auto node : g.getNodes()) {
        QFileInfo file(QString::fromStdString(node.data));
        QListWidgetItem* newItem = new QListWidgetItem;
        connectionEditor->addFile(node.data);  // add files to lists
        newItem->setData(Qt::UserRole, file.absoluteFilePath());
        newItem->setText(file.baseName());
        allFilesList->addItem(newItem);
    }
}

void Ui::MainWindow::openNoteTab(QString filename, bool exists)
{
    NoteWidget* note = new NoteWidget(notesTabs, filename, &g);
    connect(note->outboundLinksList, SIGNAL(itemClicked(QListWidgetItem*)), this,
      SLOT(listItemClicked(QListWidgetItem*)));
    connect(note->inboundLinksList, SIGNAL(itemClicked(QListWidgetItem*)), this,
      SLOT(listItemClicked(QListWidgetItem*)));
    // when changes are finished, update lists
    connect(this, SIGNAL(graphChanged()), note, SLOT(updateLists()));
    connectionEditor->addFile(filename.toStdString());
    if (exists) note->openNote();
    notesTabs->addTab(note, QFileInfo(filename).baseName());
    notesTabs->setCurrentWidget(note);
}

void Ui::MainWindow::closeTab(int index) { notesTabs->removeTab(index); }

void Ui::MainWindow::addEdgeHandler(QString from, QString to)
{
    if (dbIsOpen) {
        int fromId = g.findId(from.toStdString());
        int toId = g.findId(to.toStdString());
        g.addEdge(fromId, toId);
        db_add_edge(dbFilepath.toLocal8Bit().data(), fromId, toId);
        emit graphChanged();
    }
}

void Ui::MainWindow::removeEdgeHandler(QString from, QString to)
{
    if (dbIsOpen) {
        int fromId = g.findId(from.toStdString());
        int toId = g.findId(to.toStdString());
        g.removeEdge(fromId, toId);
        db_remove_edge(dbFilepath.toLocal8Bit().data(), fromId, toId);
        emit graphChanged();
    }
}

void Ui::MainWindow::openConnectionEditor() { connectionEditor->show(); }
