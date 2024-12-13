#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <fstream>
#include <string>
#include <QString>
#include <QTextEdit>
#include <QCloseEvent>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void initialize();
    void updateTextDisplay(const std::string& text);
    void connectEvents();
    void openFile();
    void saveFile();
    void quit();
    void newFile();
    QString getPath();
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override {
        if(windowTitle() =="Editor Text"){
            event->accept();
        }else{
            QFile file(path);
            file.open(QIODevice::ReadOnly | QIODevice::Text);

            QTextStream in(&file);
            QString fileContent = in.readAll();

            QString textEditContent = textEdit->toPlainText();
            if (fileContent == textEditContent){
                event->accept();
            }else{
                QMessageBox::warning(this, "Erreur", "Enregistrer le fichier avant de fermer" + path);
                event->ignore();
            }
        }
    }

private:
    Ui::MainWindow *ui;
    QTextEdit *textEdit;
    QString path;
};
#endif // MAINWINDOW_H
