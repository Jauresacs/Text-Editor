#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H


class TextEditor {
public:
    void insertText(const std::string& text, size_t position);
    void deleteText(size_t position, size_t length);
    string searchText(const std::string& pattern);
    string getText() const;
    void setText(const std::string& text);

private:
    std::string content;
};

#endif // TEXTEDITOR_H
