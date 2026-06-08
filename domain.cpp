#include "domain.h"
#include <stdexcept>
#include <algorithm>

// === Canvas ===
Canvas::Canvas(int width, int height) 
    : w(width), h(height), isUndoing(false), isBatching(false) {
    if (w <= 0 || h <= 0) throw std::invalid_argument("Size must be positive");
    data.resize(w * h, Pixel(false));
}

void Canvas::setPixel(int x, int y, Pixel p) {
    if (x >= 0 && x < w && y >= 0 && y < h) {
        if (!isUndoing) {
            undoHistory.push(UndoStep(x, y, data[y * w + x].filled, false));
        }
        data[y * w + x] = p;
    }
}

Pixel Canvas::getPixel(int x, int y) const {
    if (x >= 0 && x < w && y >= 0 && y < h)
        return data[y * w + x];
    return Pixel(false);
}

int Canvas::getWidth() const { return w; }
int Canvas::getHeight() const { return h; }

void Canvas::startBatch() {
    isBatching = true;
    undoHistory.push(UndoStep(-1, -1, false, true));
}

void Canvas::endBatch() {
    isBatching = false;
}

void Canvas::undo() {
    if (undoHistory.empty()) return;
    isUndoing = true;
    while (!undoHistory.empty()) {
        UndoStep step = undoHistory.top();
        undoHistory.pop();
        if (step.isBatchMarker) break;
        if (step.x >= 0 && step.x < w && step.y >= 0 && step.y < h) {
            data[step.y * w + step.x] = Pixel(step.previousState);
        }
    }
    isUndoing = false;
}

void Canvas::clear() {
    startBatch();
    
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (data[y * w + x].filled) {
                setPixel(x, y, Pixel(false));
            }
        }
    }
    
    endBatch();
}

// === Tools ===
void BrushTool::use(ICanvas& canvas, int x, int y) {
    canvas.setPixel(x, y, Pixel(true));
}
std::string BrushTool::getToolName() const { return "Draw"; }

void EraserTool::use(ICanvas& canvas, int x, int y) {
    canvas.setPixel(x, y, Pixel(false));
}
std::string EraserTool::getToolName() const { return "Erase"; }

// === Factories ===
ITool* BrushFactory::create() { return new BrushTool(); }
std::string BrushFactory::getToolName() const { return "Draw"; }

ITool* EraserFactory::create() { return new EraserTool(); }
std::string EraserFactory::getToolName() const { return "Erase"; }
