#include "FileLogger.h"

#include "Base/LoggingService.h"
#include "Base/ServiceLocator.h"

namespace
{
    auto const LogFilename = "log.txt";
}

FileLogger::FileLogger()
{
    auto loggingService = ServiceLocator::getInstance().getService<LoggingService>();
    loggingService->registerCallBack(this);

    std::remove(LogFilename);
    _outfile.open(LogFilename, std::ios_base::app);
}

FileLogger::~FileLogger()
{
    auto loggingService = ServiceLocator::getInstance().getService<LoggingService>();
    loggingService->unregisterCallBack(this);
}

void FileLogger::newLogMessage(Priority priority, std::string const& message)
{
    _outfile << message << std::endl;
}
