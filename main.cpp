#include <QApplication>
#include "domain.h"
#include "logger.h"
#include "mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Canvas canvas(1024, 1024); // размер сетки
    ILogger* logger = LoggerFactory::createLogger(false);

    MainWindow window(canvas, logger);
    window.setWindowTitle("Pixel Editor Qt");
    window.resize(600, 650);
    window.show();

    logger->log("Application started");
    int result = app.exec();

    logger->log("Application stopped");
    delete logger;
    return result;
}