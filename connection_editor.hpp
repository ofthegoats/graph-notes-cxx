#ifndef CONNECTION_EDITOR_H_
#define CONNECTION_EDITOR_H_

#include <QGridLayout>
#include <QListWidget>
#include <QPushButton>
#include <QWidget>

namespace Ui
{
class ConnectionEditor : public QWidget
{
    Q_OBJECT

signals:
    void addEdgeRequested(QString, QString);
    void removeEdgeRequested(QString, QString);

private slots:
    void requestAddEdge();
    void requestRemoveEdge();

public:
    ConnectionEditor(QWidget* parent = nullptr, std::vector<std::string> files = {});
    ~ConnectionEditor() = default;
    QPushButton* addEdgeButton;
    QPushButton* removeEdgeButton;
    void         removeFile(std::string);
    void         addFile(std::string);

private:
    QGridLayout* gridLayout;
    QListWidget* sourcesList;
    QListWidget* targetsList;
    // main window will link button signals to notes
    std::vector<std::string> allFiles;

    void updateLists();
};
}  // namespace Ui

#endif  // CONNECTION_EDITOR_H_
