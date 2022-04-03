#include "connection_editor.hpp"

#include <QFileInfo>
#include <algorithm>

// constructor, create an instance of a connection editor
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

    // connect buttons to appropriate methods to handle user request for editing edges
    connect(addEdgeButton, SIGNAL(clicked()), this, SLOT(requestAddEdge()));
    connect(removeEdgeButton, SIGNAL(clicked()), this, SLOT(requestRemoveEdge()));
}

// called when the user presses the button to add an edge
void Ui::ConnectionEditor::requestAddEdge()
{
    QString from, to;
    // take the notes selected in both lists
    // make sure any notes have been selected
    if (sourcesList->currentItem() && targetsList->currentItem()) {
        from = sourcesList->currentItem()->data(Qt::UserRole).toString();
        to = targetsList->currentItem()->data(Qt::UserRole).toString();
        // tell the main window to add an edge
        emit addEdgeRequested(from, to);
    }
}

// called when the user presses the button to remove an edge
void Ui::ConnectionEditor::requestRemoveEdge()
{
    QString from, to;
    // take the notes selected in both lists
    // make sure any notes have been selected
    if (sourcesList->currentItem() && targetsList->currentItem()) {
        from = sourcesList->currentItem()->data(Qt::UserRole).toString();
        to = targetsList->currentItem()->data(Qt::UserRole).toString();
        emit removeEdgeRequested(from, to);
    }
}

// called to remove a file from the list of all files
void Ui::ConnectionEditor::removeFile(std::string filename)
{
    std::remove_if(
      allFiles.begin(), allFiles.end(), [filename](const std::string f) { return f == filename; });
    updateLists();
}

// called to add a file to the list of all files
void Ui::ConnectionEditor::addFile(std::string filename)
{
    // only add the file if it is not already present
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
    // clear both lists, and fill both back up using the list stored
    sourcesList->clear();
    targetsList->clear();
    for (auto file : allFiles) {
        QFileInfo f(QString::fromStdString(file));
        QListWidgetItem* sourceItem = new QListWidgetItem;
        QListWidgetItem* targetItem = new QListWidgetItem;
        // store the full path in the item
        sourceItem->setData(Qt::UserRole, f.absoluteFilePath());
        targetItem->setData(Qt::UserRole, f.absoluteFilePath());
        // do not show the full path to the user
        sourceItem->setText(f.baseName());
        targetItem->setText(f.baseName());
        // add the item to the lists
        sourcesList->addItem(sourceItem);
        targetsList->addItem(targetItem);
    }
}
