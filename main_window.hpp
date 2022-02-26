#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

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
    void newNoteButtonClicked();
    void allFilesListItemClicked(QListWidgetItem*);
    void openDB(QString);
    void openNote(QString);

protected:
private:
    QPushButton* openFileButton;
    QPushButton* newNoteButton;
    QPushButton* saveNoteButton;
    QListWidget* allFilesList;
    QTabWidget*  notesTabs;
    QGridLayout* gridLayout;
    QWidget*     layoutWidget;  // placeholder, to set layout
};
}  // namespace Ui

#endif  // MAIN_WINDOW_H_
