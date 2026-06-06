#pragma once
#include <vector>
#include <string>
#include <stack>

// ============================================
// Шаг отката
// ============================================
struct UndoStep {
    int x, y;
    bool previousState;
    bool isBatchMarker;
    
    UndoStep(int x_ = 0, int y_ = 0, bool prev = false, bool marker = false)
        : x(x_), y(y_), previousState(prev), isBatchMarker(marker) {}
};

// ============================================
// Пиксель
// ============================================
struct Pixel {
    bool filled;
    Pixel() : filled(false) {}
    Pixel(bool f) : filled(f) {}
};

// ============================================
// Интерфейс холста
// ============================================
class ICanvas {
public:
    virtual ~ICanvas() = default;
    virtual void setPixel(int x, int y, Pixel p) = 0;
    virtual Pixel getPixel(int x, int y) const = 0;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual void clear() = 0;
    virtual void undo() = 0;
    virtual void startBatch() = 0;
    virtual void endBatch() = 0;
};

// ============================================
// Реализация холста
// ============================================
class Canvas : public ICanvas {
private:
    std::vector<Pixel> data;
    int w, h;
    std::stack<UndoStep> undoHistory;
    bool isUndoing;
    bool isBatching;
    
public:
    Canvas(int width, int height);
    
    void setPixel(int x, int y, Pixel p) override;
    Pixel getPixel(int x, int y) const override;
    int getWidth() const override;
    int getHeight() const override;
    void clear() override;
    void undo() override;
    void startBatch() override;
    void endBatch() override;
};

// ============================================
// Инструменты
// ============================================
class ITool {
public:
    virtual ~ITool() = default;
    virtual void use(ICanvas& canvas, int x, int y) = 0;
    virtual std::string getToolName() const = 0;
};

class BrushTool : public ITool {
public:
    void use(ICanvas& canvas, int x, int y) override;
    std::string getToolName() const override;
};

class EraserTool : public ITool {
public:
    void use(ICanvas& canvas, int x, int y) override;
    std::string getToolName() const override;
};

// ============================================
// Фабрики
// ============================================
class IToolFactory {
public:
    virtual ~IToolFactory() = default;
    virtual ITool* create() = 0;
    virtual std::string getToolName() const = 0;
};

class BrushFactory : public IToolFactory {
public:
    ITool* create() override;
    std::string getToolName() const override;
};

class EraserFactory : public IToolFactory {
public:
    ITool* create() override;
    std::string getToolName() const override;
};