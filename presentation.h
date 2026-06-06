#pragma once
#include "domain.h"
#include "logger.h"

class ConsoleUI {
public:
    void drawCanvas(const ICanvas& canvas);
    void printMenu(const std::string& toolName); 
    int getChoice();
    void getCoords(int& x, int& y);
};

class AppController {
    ConsoleUI ui;
    ICanvas& canvas;
    IToolFactory* currentFactory;
    ILogger* logger;
public:
    AppController(ICanvas& canvas, ILogger* log);
    ~AppController();
    
    void setFactory(IToolFactory* factory);
    void run();
};