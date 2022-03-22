#include "main_window.hpp"

#include "database.hpp"
#include "note_widget.hpp"

#include <QAction>
#include <QFileDialog>
#include <QMenuBar>

Ui::MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    gridLayout = new QGridLayout(this);
    layoutWidget = new QWidget;  // placeholder, to set layout
    notesTabs = new QTabWidget(this);
    allFilesList = new QListWidget(this);
    connectionEditor = new Ui::ConnectionEditor(nullptr, {});
    dbIsOpen = false;  // no db open by default
    dbFilepath = "";

    openDBAction = new QAction(tr("&Open DB"), this);
    openDBAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_O);
    newDBAction = new QAction(tr("&New DB"), this);
    newDBAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_N);
    openNoteAction = new QAction(tr("&Open Note"), this);
    openNoteAction->setShortcut(Qt::CTRL + Qt::Key_O);
    newNoteAction = new QAction(tr("&New Note"), this);
    newNoteAction->setShortcut(Qt::CTRL + Qt::Key_N);
    connectionEditorAction = new QAction(tr("&Connection Editor"), this);
    connectionEditorAction->setShortcut(Qt::CTRL + Qt::Key_E);

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openDBAction);
    fileMenu->addAction(newDBAction);
    fileMenu->addAction(openNoteAction);
    fileMenu->addAction(newNoteAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(connectionEditorAction);

    connect(openDBAction, SIGNAL(triggered()), this, SLOT(openDBButtonClicked()));
    connect(newDBAction, SIGNAL(triggered()), this, SLOT(newDBButtonClicked()));
    connect(openNoteAction, SIGNAL(triggered()), this, SLOT(openNoteButtonClicked()));
    connect(newNoteAction, SIGNAL(triggered()), this, SLOT(newNoteButtonClicked()));
    connect(
      connectionEditorAction, SIGNAL(triggered()), this, SLOT(openConnectionEditor()));

    // settings for a tab widget
    notesTabs->setMovable(true);
    notesTabs->setTabsClosable(true);
    connect(notesTabs, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));

    layoutWidget->setLayout(gridLayout);
    setCentralWidget(layoutWidget);  // set grid layout for mainwindow
    gridLayout->addWidget(allFilesList, 0, 0, 1, 2);
    gridLayout->addWidget(notesTabs, 0, 2, 1, 1);

    // connect signals (events) to slots (methods)
    connect(allFilesList, SIGNAL(itemClicked(QListWidgetItem*)), this,
      SLOT(listItemClicked(QListWidgetItem*)));
    connect(connectionEditor, SIGNAL(addEdgeRequested(QString, QString)), this,
      SLOT(addEdgeHandler(QString, QString)));
    connect(connectionEditor, SIGNAL(removeEdgeRequested(QString, QString)), this,
      SLOT(removeEdgeHandler(QString, QString)));
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
    emit graphChanged();
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
