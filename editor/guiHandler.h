#ifndef GUIHANDLER_H
#define GUIHANDLER_H

#include <QMainWindow>
class GUIHandler{

public:
    void initialize();
    void updateTextDisplay(const std::string& text);
    void connectEvents();

private:
    //GUI-specific component (e.g, Qt Widgets or GTK+ elements);
};

#endif // GUIHANDLER_H
