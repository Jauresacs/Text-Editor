#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <string>
#include <fstream>
#include <QObject>

class FileHandler : public QObject{

    Q_OBJECT

    public:
        explicit FileHandler(QObject *parent = nullptr);
        bool openFile(const std::string& filePath);
        bool saveFile(const std::string& filePath, const std::string& content);
        bool quit();
        bool newFile();

    private:
        std::fstream file;
        std::string path;
};

#endif // FILEHANDLER_H
