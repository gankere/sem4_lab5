#pragma once
#include <QMainWindow>
#include "qtcanvaswidget.h"
#include "logger.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(ICanvas& canvas, ILogger* logger, QWidget* parent = nullptr);

private slots:
    void onBrushClicked();
    void onEraserClicked();
    void onClearClicked();

private:
    QtCanvasWidget* canvasWidget;
    ILogger* logger;
};