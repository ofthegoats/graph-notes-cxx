#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include "graph.hpp"

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

public:
    MainWindow(QWidget* parent = 0);  // constructor, default toplevel
    ~MainWindow() = default;          // default destructor

public slots:
    void openDBButtonClicked();
    void newDBButtonClicked();
    void openNoteButtonClicked();
    void newNoteButtonClicked();
    void listItemClicked(QListWidgetItem*);
    void openDB(QString);
    void openNoteTab(QString, bool);
    void closeTab(int);

protected:
private:
    Graph        g;
    int          currentId;
    bool         dbIsOpen;        // whether there is an open database
    QString      dbFilepath;      // where that database is
    QPushButton* openDBButton;    // open database
    QPushButton* newDBButton;     // open database
    QPushButton* openNoteButton;  // open standalone note
    QPushButton* newNoteButton;   // create a new note
    QListWidget* allFilesList;    // list of all files in db
    QTabWidget*  notesTabs;       // tabs of open files
    QGridLayout* gridLayout;
    QWidget*     layoutWidget;  // placeholder, to set layout
};
}  // namespace Ui

#endif  // MAIN_WINDOW_H_
