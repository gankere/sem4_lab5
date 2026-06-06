#include "presentation.h"
#include <iostream>
#include <limits>
#include <cstdlib>

void ConsoleUI::drawCanvas(const ICanvas& canvas) {
    std::cout << " Canvas " << canvas.getWidth() << "x" << canvas.getHeight();

    std::cout << "\n==================================================\n";
    for (int y = 0; y < canvas.getHeight(); ++y) {
        for (int x = 0; x < canvas.getWidth(); ++x) {
            Pixel p = canvas.getPixel(x, y);
            if (p.filled) 
                std::cout << "#";
            else 
                std::cout << ".";
        }
        std::cout << "\n";
    }
    std::cout << "==================================================\n";
}

void ConsoleUI::printMenu(const std::string& toolName) {
    std::string tool;
    if (toolName == "Draw") {
        tool = "Draw";
    } else {
        tool = "Erase";
    }
    std::cout << "\n1. " <<  tool << " 2. Change Tool  3. Clear  0. Exit\n> ";
}

int ConsoleUI::getChoice() {
    int c; 
    std::cin >> c;
    return c;
}

void ConsoleUI::getCoords(int& x, int& y) {
    std::cout << "Enter X Y: ";
    std::cin >> x >> y;
}

AppController::AppController(ICanvas& canvas, ILogger* log) 
    : canvas(canvas), currentFactory(new BrushFactory()), logger(log) {
    logger->log("Controller initialized");
}

AppController::~AppController() {
    delete currentFactory;
    logger->log("Controller destroyed");
}

void AppController::setFactory(IToolFactory* factory) {
    delete currentFactory;
    currentFactory = factory;
    logger->log("Tool changed");
}

void AppController::run() {
    logger->log("Application started");
    
    while (true) {
        ui.drawCanvas(canvas);
        std::string currentToolName = currentFactory->getToolName();
        ui.printMenu(currentToolName);
        
        int choice = ui.getChoice();
        
        if (choice == 0) break;
        
        if (choice == 1) {
            int x, y;
            ui.getCoords(x, y);
            
            ITool* tool = currentFactory->create();
            tool->use(canvas, x, y);
            delete tool;
            
            logger->log("Draw at " + std::to_string(x) + "," + std::to_string(y));
        }
        
        if (choice == 2) {
            int t; 
            std::cout << "1.Brush 2.Eraser: "; 
            std::cin >> t;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            if (t == 1) {setFactory(new BrushFactory());
            } else {setFactory(new EraserFactory());}
        }

        if (choice == 3) {
            canvas.clear();
            logger->log("Canvas cleared");
            continue;
        }
    }
    logger->log("Application stopped");
}