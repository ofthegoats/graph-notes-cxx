#ifndef CONNECTION_EDITOR_H_
#define CONNECTION_EDITOR_H_

#include <QGridLayout>
#include <QListWidget>
#include <QPushButton>
#include <QWidget>

namespace Ui
{
class ConnectionEditor : public QWidget  // inherits from QWidget
{
    Q_OBJECT

signals:
    // signals sent from this widget to the main window
    void addEdgeRequested(QString, QString);
    void removeEdgeRequested(QString, QString);

private slots:
    // methods called to add and remove edges
    void requestAddEdge();
    void requestRemoveEdge();

public:
    ConnectionEditor(QWidget* parent = nullptr, std::vector<std::string> files = {});
    ~ConnectionEditor() = default;
    QPushButton* addEdgeButton;
    QPushButton* removeEdgeButton;
    void removeFile(std::string);
    void addFile(std::string);

private:
    QGridLayout* gridLayout;
    QListWidget* sourcesList;
    QListWidget* targetsList;
    // main window will link button signals to notes
    std::vector<std::string> allFiles;
    void updateLists();  // update the lists which the user can see
};
}  // namespace Ui

#endif  // CONNECTION_EDITOR_H_
