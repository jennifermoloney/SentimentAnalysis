//
// Created by Jennifer Moloney on 4/8/25.
//

#ifndef SENTIMENTANALYSIS_UI_H
#define SENTIMENTANALYSIS_UI_H


#include <QMainWindow>
#include <QString>

class QLabel;
class QLineEdit;
class QPushButton;
class QGroupBox;

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void analyzeText();
    void selectOpenAddressing();
    void selectSeparateChaining();

private:
    // UI components
    QLabel *titleLabel;
    QLineEdit *inputEdit;
    QPushButton *goButton;

    QPushButton *openAddressingButton;
    QPushButton *separateChainingButton;

    QLabel *sentimentResultLabel; // Hidden initially, appears after Go! is pressed.
    QLabel *sentimentExplanationLabel;
    QGroupBox *metricsGroup;         // Hidden initially.
    QLabel *metricsLabel;            // Contents of the metrics group.

    // Track which algorithm is selected.
    QString currentAlgorithm;
};



#endif //SENTIMENTANALYSIS_UI_H
