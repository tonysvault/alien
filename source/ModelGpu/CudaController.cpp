#include "CudaWorker.h"
#include "CudaJob.h"

#include "CudaController.h"

namespace
{
	const string ThreadControllerId = "ThreadControllerId";
}

CudaController::CudaController(QObject* parent /*= nullptr*/)
	: QObject(parent)
{
	_worker = new CudaWorker();
	_worker->moveToThread(&_thread);
	connect(_worker, &CudaWorker::timestepCalculated, this, &CudaController::timestepCalculatedWithGpu);
	connect(this, &CudaController::runWorker, _worker, &CudaWorker::run);
	_thread.start();
	Q_EMIT runWorker();
}

CudaController::~CudaController()
{
	_worker->terminateWorker();
	_thread.quit();
	if (!_thread.wait(2000)) {
		_thread.terminate();
		_thread.wait();
	}
	delete _worker;
}

void CudaController::init(SpaceProperties *metric)
{
	_worker->init(metric);
}

CudaWorker * CudaController::getCudaWorker() const
{
	return _worker;
}

void CudaController::calculate(RunningMode mode)
{
	if (mode == RunningMode::CalcSingleTimestep) {
		CudaJob job = boost::make_shared<_CalcSingleTimestepJob>(ThreadControllerId, false);
		_worker->addJob(job);
	}
	if (mode == RunningMode::OpenEndedSimulation) {
		CudaJob job = boost::make_shared<_RunSimulationJob>(ThreadControllerId, false);
		_worker->addJob(job);
	}
	if (mode == RunningMode::DoNothing) {
		CudaJob job = boost::make_shared<_StopSimulationJob>(ThreadControllerId, false);
		_worker->addJob(job);
	}
}

void CudaController::restrictTimestepsPerSecond(optional<int> tps)
{
//TODO
//	_worker->restrictTimestepsPerSecond(tps);
}

void CudaController::timestepCalculatedWithGpu()
{
	Q_EMIT timestepCalculated();
}
