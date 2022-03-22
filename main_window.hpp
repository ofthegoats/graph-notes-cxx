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
    void graphChanged();

public:
    MainWindow(QWidget* parent = 0);  // constructor, default toplevel
    ~MainWindow() = default;  // default destructor

public slots:
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

protected:
private:
    Graph g;
    int currentId;
    bool dbIsOpen;  // whether there is an open database
    QMenu* fileMenu;
    QMenu* editMenu;
    QAction* openDBAction;
    QAction* newDBAction;
    QAction* openNoteAction;
    QAction* newNoteAction;
    QAction* connectionEditorAction;
    QString dbFilepath;  // where that database is
    QListWidget* allFilesList;  // list of all files in db
    QTabWidget* notesTabs;  // tabs of open files
    QGridLayout* gridLayout;
    QWidget* layoutWidget;  // placeholder, to set layout
    Ui::ConnectionEditor* connectionEditor;
};
}  // namespace Ui

#endif  // MAIN_WINDOW_H_
