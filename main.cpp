#include "graph_notes.hpp"

#include <QApplication>

int main(int argc, char* argv[])
{
    // start up the application
    QApplication graphNotes(argc, argv);
    Ui::MainWindow window;
    window.show();
    return graphNotes.exec();
}
