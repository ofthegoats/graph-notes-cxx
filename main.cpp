#include "graph_notes.hpp"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication   graphNotes(argc, argv);
    Ui::MainWindow window;
    window.show();
    return graphNotes.exec();
}
