#ifndef CPPSYNTAXHIGHLIGHTER_H
#define CPPSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

class CppSyntaxHighlighter : public QSyntaxHighlighter {
    Q_OBJECT

public:
    explicit CppSyntaxHighlighter(QTextDocument *parent = nullptr)
        : QSyntaxHighlighter(parent) {
        setupHighlightingRules();
    }

protected:
    void highlightBlock(const QString &text) override {
        // Applique les règles de coloration sur chaque ligne de texte
        for (const HighlightingRule &rule : highlightingRules) {
            QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
            while (matchIterator.hasNext()) {
                QRegularExpressionMatch match = matchIterator.next();
                setFormat(match.capturedStart(), match.capturedLength(), rule.format);
            }
        }
    }

private:
    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    QVector<HighlightingRule> highlightingRules;

    void setupHighlightingRules() {
        // Mots-clés de C++
        QStringList keywordPatterns = {
            "\\bif\\b", "\\belse\\b", "\\bfor\\b", "\\bwhile\\b",
            "\\bclass\\b", "\\bstruct\\b", "\\breturn\\b", "\\bvoid\\b",
            "\\bint\\b", "\\bfloat\\b", "\\bdouble\\b"
        };

        QTextCharFormat keywordFormat;
        keywordFormat.setForeground(Qt::red);
        keywordFormat.setFontWeight(QFont::Bold);

        for (const QString &pattern : keywordPatterns) {
            HighlightingRule rule;
            rule.pattern = QRegularExpression(pattern);
            rule.format = keywordFormat;
            highlightingRules.append(rule);
        }

        // Commentaires (ligne et bloc)
        QTextCharFormat commentFormat;
        commentFormat.setForeground(Qt::gray);
        HighlightingRule singleLineCommentRule;
        singleLineCommentRule.pattern = QRegularExpression("//[^\n]*");
        singleLineCommentRule.format = commentFormat;
        highlightingRules.append(singleLineCommentRule);

        HighlightingRule multiLineCommentRule;
        multiLineCommentRule.pattern = QRegularExpression("/\\*.*\\*/");
        multiLineCommentRule.format = commentFormat;
        highlightingRules.append(multiLineCommentRule);

        // Littéraux de chaîne
        QTextCharFormat stringFormat;
        stringFormat.setForeground(Qt::darkGreen);
        HighlightingRule stringRule;
        stringRule.pattern = QRegularExpression("\".*\"");
        stringRule.format = stringFormat;
        highlightingRules.append(stringRule);
    }
};


#endif // CPPSYNTAXHIGHLIGHTER_H
