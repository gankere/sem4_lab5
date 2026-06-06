#pragma once
#include <QWidget>
#include <QPixmap>
#include "domain.h"

class QtCanvasWidget : public QWidget {
    Q_OBJECT
public:
    explicit QtCanvasWidget(ICanvas& canvas, QWidget* parent = nullptr);
    ~QtCanvasWidget();

    void updateFactory(IToolFactory* factory);
    void clearCanvas();

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

signals:
    void pixelClicked(int x, int y);

private:
    ICanvas& canvas;
    IToolFactory* currentFactory;
    ITool* activeTool;
    bool isDrawing;
    QPoint lastPos;
    int pixelSize;

    // Кэш отрисовки в видеопамяти
    QPixmap canvasCache;
    bool cacheDirty;
    void updateCache();  // Пересоздаёт кэш из данных canvas

    void drawAtPosition(const QPoint& pos);
    void drawLine(const QPoint& from, const QPoint& to);
};