#ifndef CELLFUNCTIONSCANNER_H
#define CELLFUNCTIONSCANNER_H

#include "model/features/cellfunction.h"

class CellFunctionScannerImpl : public CellFunction
{
public:
    CellFunctionScannerImpl (SimulationContext* context);

    Enums::CellFunction::Type getType () const { return Enums::CellFunction::SCANNER; }

protected:
    ProcessingResult processImpl (Token* token, Cell* cell, Cell* previousCell) override;
};

#endif // CELLFUNCTIONSCANNER_H