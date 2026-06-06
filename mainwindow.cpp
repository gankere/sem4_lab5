#include "mainwindow.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(ICanvas& canvas, ILogger* logger, QWidget* parent)
    : QMainWindow(parent), logger(logger) {

    canvasWidget = new QtCanvasWidget(canvas, this);
    canvasWidget->setMinimumSize(400, 400); //виджет холста
        //кнопки
    auto* brushBtn = new QPushButton("Кисть");
    auto* eraserBtn = new QPushButton("Ластик");
    auto* clearBtn = new QPushButton("Очистить");

    connect(brushBtn, &QPushButton::clicked, this, &MainWindow::onBrushClicked);
    connect(eraserBtn, &QPushButton::clicked, this, &MainWindow::onEraserClicked);
    connect(clearBtn, &QPushButton::clicked, this, &MainWindow::onClearClicked);
        //кнопки в ряд
    auto* btnLayout = new QHBoxLayout;
    btnLayout->addWidget(brushBtn);
    btnLayout->addWidget(eraserBtn);
    btnLayout->addWidget(clearBtn);

    auto* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(canvasWidget);
    mainLayout->addLayout(btnLayout);

    auto* central = new QWidget;
    central->setLayout(mainLayout);
    setCentralWidget(central);

    logger->log("Qt UI initialized");
}

void MainWindow::onBrushClicked() {
    canvasWidget->updateFactory(new BrushFactory());
    logger->log("Tool changed to Brush");
}

void MainWindow::onEraserClicked() {
    canvasWidget->updateFactory(new EraserFactory());
    logger->log("Tool changed to Eraser");
}

void MainWindow::onClearClicked() {
    canvasWidget->clearCanvas();
    logger->log("Canvas cleared");
}