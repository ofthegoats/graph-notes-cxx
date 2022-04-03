#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include "connection_editor.hpp"
#include "graph.hpp"
#include "qwidget.h"

#include <QGridLayout>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QTabWidget>

namespace Ui
{
class MainWindow : public QMainWindow  // inherits from QMainWindow
{
    Q_OBJECT

signals:
    // signal used to tell other widgets when to update graphs
    void graphChanged();

public:
    MainWindow(QWidget* parent = 0);  // constructor, default toplevel
    ~MainWindow() = default;  // default destructor

public slots:
    // public functions to connect to signals
    void openDBButtonClicked();
    void newDBButtonClicked();
    void openNoteButtonClicked();
    void newNoteButtonClicked();
    void listItemClicked(QListWidgetItem*);
    void openDB(QString);
    void openNoteTab(QString, bool);
    void closeTab(int);
    void addEdgeHandler(QString, QString);
    void removeEdgeHandler(QString, QString);
    void openConnectionEditor();

private:
    QMenu* fileMenu;  // menus and actions therein
    QMenu* editMenu;
    QAction* openDBAction;
    QAction* newDBAction;
    QAction* openNoteAction;
    QAction* newNoteAction;
    QAction* connectionEditorAction;
    QWidget* layoutWidget;  // placeholder, to set layout
    QListWidget* allFilesList;  // list of all files in db
    QTabWidget* notesTabs;  // tabs of open files
    QGridLayout* gridLayout;
    Graph g;  // graph storing structure of user notes
    bool dbIsOpen;  // whether there is an open database
    QString dbFilepath;  // where the database is stored
    Ui::ConnectionEditor* connectionEditor;  // widget used to manage edges
};
}  // namespace Ui

#endif  // MAIN_WINDOW_H_
