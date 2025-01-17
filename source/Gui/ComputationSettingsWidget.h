﻿#pragma once

#include <QWidget>

#include "EngineGpuKernels/CudaConstants.h"

#include "Definitions.h"
#include "ui_ComputationSettingsWidget.h"


class ComputationSettingsWidget : public QWidget {
	Q_OBJECT

public:
	ComputationSettingsWidget(QWidget * parent = nullptr);
	~ComputationSettingsWidget() = default;

    boost::optional<IntVector2D> getUniverseSize() const;
    void setUniverseSize(IntVector2D const& value) const;

    boost::optional<CudaConstants> getCudaConstants() const;
    void setCudaConstants(CudaConstants const& value);

    void saveSettings();

private:
	Ui::ComputationSettingsWidget ui;
};
