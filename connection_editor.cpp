#include "connection_editor.hpp"

#include <QFileInfo>
#include <algorithm>

Ui::ConnectionEditor::ConnectionEditor(QWidget* parent, std::vector<std::string> files)
  : QWidget(parent)
{
    gridLayout = new QGridLayout(this);
    sourcesList = new QListWidget(this);
    targetsList = new QListWidget(this);
    addEdgeButton = new QPushButton("Add Edge", this);
    removeEdgeButton = new QPushButton("Remove Edge", this);
    allFiles = files;

    updateLists();

    setLayout(gridLayout);
    gridLayout->addWidget(sourcesList, 0, 0);
    gridLayout->addWidget(targetsList, 0, 1);
    gridLayout->addWidget(addEdgeButton, 1, 0);
    gridLayout->addWidget(removeEdgeButton, 1, 1);

    connect(addEdgeButton, SIGNAL(clicked()), this, SLOT(requestAddEdge()));
    connect(removeEdgeButton, SIGNAL(clicked()), this, SLOT(requestRemoveEdge()));
    // button signals are connected in Ui::MainWindow to Ui::NoteWidget
}

void Ui::ConnectionEditor::requestAddEdge()
{
    QString from, to;
    if (sourcesList->currentItem() && targetsList->currentItem()) {
        from = sourcesList->currentItem()->data(Qt::UserRole).toString();
        to = targetsList->currentItem()->data(Qt::UserRole).toString();
        emit addEdgeRequested(from, to);
    }
}

void Ui::ConnectionEditor::requestRemoveEdge()
{
    QString from, to;
    if (sourcesList->currentItem() && targetsList->currentItem()) {
        from = sourcesList->currentItem()->data(Qt::UserRole).toString();
        to = targetsList->currentItem()->data(Qt::UserRole).toString();
        emit removeEdgeRequested(from, to);
    }
}

void Ui::ConnectionEditor::removeFile(std::string filename)
{
    std::remove_if(allFiles.begin(), allFiles.end(),
      [filename](const std::string f) { return f == filename; });
    updateLists();
}

void Ui::ConnectionEditor::addFile(std::string filename)
{
    bool exists = false;
    for (auto file : allFiles)
        if (file == filename) exists = true;
    if (!exists) {
        allFiles.push_back(filename);
        updateLists();
    }
}

void Ui::ConnectionEditor::updateLists()
{
    sourcesList->clear();
    targetsList->clear();
    for (auto file : allFiles) {
        QFileInfo        f(QString::fromStdString(file));
        QListWidgetItem* sourceItem = new QListWidgetItem;
        QListWidgetItem* targetItem = new QListWidgetItem;
        sourceItem->setData(Qt::UserRole, f.absoluteFilePath());
        targetItem->setData(Qt::UserRole, f.absoluteFilePath());
        sourceItem->setText(f.baseName());
        targetItem->setText(f.baseName());
        sourcesList->addItem(sourceItem);
        targetsList->addItem(targetItem);
    }
}
