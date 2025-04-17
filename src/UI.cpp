#include "UI.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QGroupBox>
#include <QSpacerItem>
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    titleLabel = new QLabel("Analyze the Sentiment of your Message", this);
    titleLabel->setStyleSheet(
            "QLabel {"
            "   color: #6A5ACD;"
            "   font-size: 35pt;"
            "   font-weight: bold;"
            "}"
    );
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputEdit = new QLineEdit(this);
    inputEdit->setPlaceholderText("Enter your message here...");
    inputEdit->setStyleSheet(
            "QLineEdit {"
            "   border: 2px solid #FFC0CB;"
            "   border-radius: 12px;"
            "   padding: 6px;"
            "   font-size: 20pt;"
            "}"
    );
    goButton = new QPushButton("Go!", this);
    goButton->setStyleSheet(
            "QPushButton {"
            "   background-color: #FFB6C1;"
            "   border: 1px solid #ff9aa2;"
            "   border-radius: 12px;"
            "   padding: 8px 16px;"
            "   font-size: 20pt;"
            "}"
            "QPushButton:hover {"
            "   background-color: #FFA6B2;"
            "}"
    );
    inputLayout->addWidget(inputEdit);
    inputLayout->addWidget(goButton);
    mainLayout->addLayout(inputLayout);

    QVBoxLayout *sentimentLabelsLayout = new QVBoxLayout();
    sentimentLabelsLayout->setAlignment(Qt::AlignCenter);

    sentimentResultLabel = new QLabel("", this);
    sentimentResultLabel->setAlignment(Qt::AlignCenter);
    sentimentResultLabel->setVisible(false);
    sentimentResultLabel->setStyleSheet(
            "QLabel {"
            "   font-size: 28pt;"
            "   font-weight: bold;"
            "   color: #4B0082;"
            "}"
    );

    sentimentExplanationLabel = new QLabel("", this);
    sentimentExplanationLabel->setAlignment(Qt::AlignCenter);
    sentimentExplanationLabel->setVisible(false);
    sentimentExplanationLabel->setStyleSheet(
            "QLabel {"
            "   font-size: 28pt;"
            "   font-weight: bold;"
            "   color: #4B0082;"
            "}"
    );

    sentimentLabelsLayout->addWidget(sentimentResultLabel);
    sentimentLabelsLayout->addWidget(sentimentExplanationLabel);

    mainLayout->addLayout(sentimentLabelsLayout);


    mainLayout->addStretch();

    QHBoxLayout *bottomLayout = new QHBoxLayout();


    QVBoxLayout *leftColumn = new QVBoxLayout();
    openAddressingButton = new QPushButton("Open Addressing", this);
    openAddressingButton->setStyleSheet(
            "QPushButton {"
            "   background-color: #FFB6C1;"
            "   border: 1px solid #ff9aa2;"
            "   border-radius: 10px;"
            "   padding: 8px 16px;"
            "   font-size: 20pt;"
            "}"
            "QPushButton:hover {"
            "   background-color: #FFA6B2;"
            "}"
    );
    separateChainingButton = new QPushButton("Separate Chaining", this);
    separateChainingButton->setStyleSheet(
            "QPushButton {"
            "   background-color: #FFB6C1;"
            "   border: 1px solid #ff9aa2;"
            "   border-radius: 10px;"
            "   padding: 8px 16px;"
            "   font-size: 20pt;"
            "}"
            "QPushButton:hover {"
            "   background-color: #FFA6B2;"
            "}"
    );
    leftColumn->addWidget(openAddressingButton);
    leftColumn->addWidget(separateChainingButton);
    bottomLayout->addLayout(leftColumn);

    QVBoxLayout *rightColumn = new QVBoxLayout();
    metricsGroup = new QGroupBox("Metrics", this);
    QVBoxLayout *metricsLayout = new QVBoxLayout(metricsGroup);
    metricsLabel = new QLabel("", this);
    metricsLabel->setStyleSheet("font-size: 20pt;");
    metricsLayout->addWidget(metricsLabel);
    metricsGroup->setLayout(metricsLayout);
    metricsGroup->setVisible(false);
    rightColumn->addWidget(metricsGroup);
    bottomLayout->addLayout(rightColumn);

    bottomLayout->addStretch();
    mainLayout->addLayout(bottomLayout);

    //Doesnt really do anything right now
    connect(goButton, &QPushButton::clicked, this, &MainWindow::analyzeText);
    connect(openAddressingButton, &QPushButton::clicked, this, &MainWindow::selectOpenAddressing);
    connect(separateChainingButton, &QPushButton::clicked, this, &MainWindow::selectSeparateChaining);

    currentAlgorithm = "Open Addressing";

    setMinimumSize(500, 500);
}

void MainWindow::analyzeText()
{
    QString userText = inputEdit->text();

    //int sentimentScore = 0;
	std::string sentimentScore = "1";
    std::string sentimentExplantion = " ";

    sentimentResultLabel->setText(QString("The sentiment of your message is: %1").arg(sentimentScore));
    sentimentResultLabel->setVisible(true);

    sentimentExplanationLabel->setText(QString("Your text is %1").arg(QString::fromStdString(sentimentExplantion)));
    sentimentExplanationLabel->setVisible(true);

    if (currentAlgorithm == "Open Addressing")
    {
        metricsLabel->setText("Metrics!");
    }
    else if (currentAlgorithm == "Separate Chaining")
    {
        metricsLabel->setText("More Metrics!");
    }
    metricsGroup->setVisible(true);
}

void MainWindow::selectOpenAddressing()
{
    currentAlgorithm = "Open Addressing";
}

void MainWindow::selectSeparateChaining()
{
    currentAlgorithm = "Separate Chaining";
}
