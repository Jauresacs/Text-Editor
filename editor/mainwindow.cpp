#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "fileHandler.h"
#include "QTextEdit"
#include "QVBoxLayout"
#include "QMenuBar"
#include "QAction"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <qsystemtrayicon.h>
#include <QTabWidget>
#include <wchar.h>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QInputDialog>
#include "cppsyntaxhighlighter.h"


QString MainWindow::getPath(){
    return path;
}


/*bool printFile(wchar_t* path){
    std::ifstream file(path, std::ios::in);
    if (!file.is_open()){
        std::cout << "Error opening file: "<< path << std::endl;
        return 1;
    }

    std::string fileContent;
    file.seekg(0, std::ios::beg);
    file >> fileContent;

    std::cout << "File contents: " << fileContent << std::endl;

    //file.close();
}*/

void MainWindow::openFile(){
    QString filePath = QFileDialog::getOpenFileName(this, "ouvrir un fichier", "", "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
    if (filePath.isEmpty()) return;

    QFile file(filePath);
    QFileInfo fileInfo(filePath);
    if (!file.open(QFile::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier.");
        return;
    }

    newFile();

    QTextStream in(&file);
    textEdit->setPlainText(in.readAll());
    file.close();

    path = filePath;
    setWindowTitle(fileInfo.fileName());
    /*OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    wchar_t filePath[256] = L"";
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = filePath;
    ofn.nMaxFile = 256;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    if (GetOpenFileName(&ofn)){
        path = filePath;
    }

    if(path !=nullptr){
        printFile(path);
    }*/
}

void MainWindow::newFile(){
    //Créer une Zone pour la saisie de texte
    textEdit = new QTextEdit(this);
    CppSyntaxHighlighter *highlighter = new CppSyntaxHighlighter(textEdit->document());
    QFont font;
    font.setFamily("JetBrains Mono");
    font.setPointSize(12);
    textEdit->setFont(font);
    setCentralWidget(textEdit);
    setWindowTitle("New File");
}

void MainWindow::quit(){
    if(windowTitle() == "Editor Text"){
        close();
    }else{
        QFile file(path);
        file.open(QIODevice::ReadOnly | QIODevice::Text);

        QTextStream in(&file);
        QString fileContent = in.readAll();

        QString textEditContent = textEdit->toPlainText();

        if(fileContent == textEditContent){
            close();
        }else{
            QMessageBox::warning(this, "Erreur", "Enregistrer le fichier avant de fermer" + path);
        }
    }
}

void MainWindow::saveFile(){
    if (windowTitle()=="Editor Text"){
        QMessageBox::warning(this, "Ereur", "Vous deviez avoir un fichier d'ouvert avant de sauvegarder");
    }else if(windowTitle()=="New File"){
        QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer le fichier", QDir::homePath(), "Directories (*.*)");
        QFileDialog dirDialog(this, "Select Directory", "", "Directories (*.dir)");
        if (filePath.isEmpty()) {
            QMessageBox::warning(this, "Avertissement", "Aucun dossier sélectionné.");
            return;
        }
        if(!filePath.endsWith(".txt")){
            filePath += ".txt";
        }
        QFileInfo fileInfo(filePath);
        QFile file(filePath);
        if (file.open(QFile::WriteOnly | QIODevice::Text)){
            QTextStream out(&file);
            //qDebug() << textEdit->toPlainText();
            out << textEdit->toPlainText();
            file.close();
            QMessageBox::information(this, "Success", "Votre fichier a été sauvegardé avec succès!");
            setWindowTitle(fileInfo.fileName());
        }else{
            QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier.");
        }
        path = filePath;
    }else{
        QFile file(path);
        if (!file.open(QFile::WriteOnly | QIODevice::Text)){
            QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier.");
            return;
        }
        QTextStream out(&file);
        //qDebug() << textEdit->toPlainText();
        out << textEdit->toPlainText();
        file.close();
    }
    //QMessageBox::warning(this, "Error", "Impossible d'enregistrer le fichier");
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Editor Text");

    this->resize(800, 600);
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu *fileMenu = menuBar->addMenu(tr("&File"));
    QMenu *editMenu = menuBar->addMenu(tr("&Edit"));
    QMenu *helpMenu = menuBar->addMenu(tr("&Help"));

    QAction *newAction = new QAction(tr("&New"), this);
    newAction->setShortcut(Qt::Key_N);
    newAction->setShortcut(QKeySequence("Ctrl+N"));
    fileMenu->addAction(newAction);

    QAction *openAction = new QAction(tr("&Open"), this);
    openAction->setShortcut(Qt::Key_D);
    openAction->setShortcut(QKeySequence("Ctrl+O"));
    fileMenu->addAction(openAction);

    QAction *saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcut(Qt::Key_Save);
    saveAction->setShortcut(QKeySequence("Ctrl+S"));
    fileMenu->addAction(saveAction);

    QAction *quitAction = new QAction(tr("&Quit"), this);
    quitAction->setShortcut(Qt::Key_Q);
    quitAction->setShortcut(QKeySequence("Ctrl+Q"));
    fileMenu->addAction(quitAction);

    connect(newAction, &QAction::triggered, this, &MainWindow::newFile);
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(quitAction, &QAction::triggered, this, &MainWindow::quit);
    connect(quitAction, &QAction::triggered, this, &MainWindow::quit);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);

}

MainWindow::~MainWindow()
{
    delete ui;
}
