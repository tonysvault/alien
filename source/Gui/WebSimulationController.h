#pragma once

#include <mutex>

#include <QObject>

#include "ModelBasic/Definitions.h"
#include "Web/Definitions.h"
#include "Web/Task.h"

#include "Definitions.h"

class WebSimulationController
    : public QObject
{
    Q_OBJECT
public:
    WebSimulationController(WebAccess* webAccess, QWidget* parent = nullptr);

    void init(SimulationAccess* access);

    bool onConnectToSimulation();
    bool onDisconnectToSimulation(string const& simulationId, string const& token);

    optional<string> getCurrentSimulationId() const;
    optional<string> getCurrentToken() const;

private:
    Q_SLOT void requestUnprocessedTasks() const;
    Q_SLOT void unprocessedTasksReceived(vector<Task> tasks);

    void processTasks();
    Q_SLOT void tasksProcessedStep1();
    Q_SLOT void tasksProcessedStep2();

    optional<string> _currentSimulationId;
    optional<string> _currentToken;

    map<string, Task> _taskById;
    optional<string> _processingTaskId;

    QByteArray _encodedImageData;
    QBuffer* _buffer = nullptr;

    QImagePtr _image;
    std::mutex _mutex;

    SimulationAccess* _simAccess = nullptr;
    QWidget* _parent = nullptr;
    WebAccess* _webAccess = nullptr;
    QTimer* _timer = nullptr;
};