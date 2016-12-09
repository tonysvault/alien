#ifndef SIMULATIONCONTEXTIMPL_H
#define SIMULATIONCONTEXTIMPL_H

#include "model/simulationcontext.h"
#include "model/topology.h"
#include <QMutex>

class SimulationContextImpl : public SimulationContext
{
public:
    SimulationContextImpl ();
    ~SimulationContextImpl ();

    void lock ();
    void unlock ();

    void init (IntVector2D size);

    Topology getTopology () const;
    EnergyParticleMap* getEnergyParticleMap () const;
    CellMap* getCellMap () const;
    QList<CellCluster*>& getClustersRef ();
    QList<EnergyParticle*>& getEnergyParticlesRef ();

	void serialize(QDataStream& stream) const;
	void build(QDataStream& stream);

private:
    QMutex _mutex;
    QList<CellCluster*> _clusters;
    QList<EnergyParticle*> _energyParticles;
    Topology _topology;
    EnergyParticleMap* _energyParticleMap;
    CellMap* _cellMap;

};

#endif // SIMULATIONCONTEXTIMPL_H
