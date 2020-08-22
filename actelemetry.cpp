#include "actelemetry.h"

ACTelemetry::ACTelemetry(QObject *parent) : QObject(parent)
{
   acTelemetryTimer = new QTimer(this);
   connect(acTelemetryTimer, SIGNAL(timeout()), this, SLOT(updateTelemetry()));
   telemetryFeatureReport = new TelemetryFeatureReport;
}

ACTelemetry::~ACTelemetry()
{
    stop();
}

void ACTelemetry::stop(void) {
    if (acTelemetryTimer->isActive()) {
        acTelemetryTimer->stop();
        telemetryFeatureReport = new TelemetryFeatureReport;
        sharedMemoryVNMSimulationTelemetry.lock();
        TelemetryFeatureReport *to = (TelemetryFeatureReport*)sharedMemoryVNMSimulationTelemetry.data();
        memcpy(to, telemetryFeatureReport, sharedMemoryVNMSimulationTelemetry.size());
        sharedMemoryVNMSimulationTelemetry.unlock();
        sharedMemorySPageFilePhysics.detach();
        sharedMemorySPageFileGraphics.detach();
        sharedMemorySPageFileStatic.detach();
        sharedMemoryVNMSimulationTelemetry.detach();
        writeLog(logInfo, "ACTelemetry was stoped successfully");
    }
}
void ACTelemetry::start(void) {
    sharedMemorySPageFilePhysics.setNativeKey("Local\\acpmf_physics");
    sharedMemorySPageFilePhysicsStatus = sharedMemorySPageFilePhysics.attach();
    if (sharedMemorySPageFilePhysics.attach()) {
        writeLog(logInfo, "Attached to sharedMemorySPageFilePhysics");
    } else {
        writeLog(logError,  "Can not attach to sharedMemorySPageFilePhysics");
    }

    sharedMemorySPageFileGraphics.setNativeKey("Local\\acpmf_graphics");
    sharedMemorySPageFileGraphicsStatus = sharedMemorySPageFileGraphics.attach();
    if (sharedMemorySPageFileGraphics.attach()) {
        writeLog(logInfo, "Attached to sharedMemorySPageFileGraphics");
    } else {
        writeLog(logError, "Can not attach to sharedMemorySPageFileGraphics");
    }

    sharedMemorySPageFileStatic.setNativeKey("Local\\acpmf_static");
    sharedMemorySPageFileStaticStatus = sharedMemorySPageFileStatic.attach();
    if (sharedMemorySPageFileStatic.attach()) {
        writeLog(logInfo, "Attached to sharedMemorySPageFileStatic");
    } else {
        writeLog(logError, "Can not attach to sharedMemorySPageFileStatic");
    }
    sharedMemoryVNMSimulationTelemetry.setNativeKey("vnm_simulation_telemetry");
    sharedMemoryVNMSimulationTelemetryStatus = sharedMemoryVNMSimulationTelemetry.attach();
    if (sharedMemoryVNMSimulationTelemetry.attach()) {
        writeLog(logInfo, "Attached to sharedMemoryVNMSimulationTelemetry");
    } else {
        writeLog(logError, "Can not attach to sharedMemoryVNMSimulationTelemetry");
    }
     acTelemetryTimer->start(interval);
}
void ACTelemetry::updateTelemetry(){
    if (sharedMemorySPageFilePhysicsStatus) {
        sharedMemorySPageFilePhysics.lock();
        sPageFilePhysics = static_cast<SPageFilePhysics*>(sharedMemorySPageFilePhysics.data());
        sharedMemorySPageFilePhysics.unlock();
        telemetryFeatureReport->gas =  sPageFilePhysics->gas;
        telemetryFeatureReport->brake =  sPageFilePhysics->brake;
        telemetryFeatureReport->fuel = sPageFilePhysics->fuel;
        telemetryFeatureReport->gear = sPageFilePhysics->gear;
        telemetryFeatureReport->rpm =  sPageFilePhysics->rpm;
        telemetryFeatureReport->steerAngle =  sPageFilePhysics->steerAngle;
        telemetryFeatureReport->speedKmh = sPageFilePhysics->speedKmh;
        telemetryFeatureReport->tc = sPageFilePhysics->tc;
        telemetryFeatureReport->abs = sPageFilePhysics->abs;
        telemetryFeatureReport->turboBoost = sPageFilePhysics->turboBoost;
        telemetryFeatureReport->drsEnabled = sPageFilePhysics->drsEnabled;
        telemetryFeatureReport->clutch = sPageFilePhysics->clutch;
        telemetryFeatureReport->brakeBias = sPageFilePhysics->brakeBias;
        telemetryFeatureReport->frontBrakeCompound = sPageFilePhysics->frontBrakeCompound;
        telemetryFeatureReport->rearBrakeCompound = sPageFilePhysics->rearBrakeCompound;
        telemetryFeatureReport->finalForceFeedback =  sPageFilePhysics->finalForceFeedback;
    }
    if (sharedMemorySPageFileGraphicsStatus) {
        sharedMemorySPageFileGraphics.lock();
        sPageFileGraphic = static_cast<SPageFileGraphic*>(sharedMemorySPageFileGraphics.data());
        sharedMemorySPageFileGraphics.unlock();
        // add paramters here
    }
    if (sharedMemorySPageFileStaticStatus) {
        sharedMemorySPageFileStatic.lock();
        sPageFileStatic = static_cast<SPageFileStatic*>(sharedMemorySPageFileStatic.data());
        sharedMemorySPageFileStatic.unlock();
        telemetryFeatureReport->maxTorque = sPageFileStatic->maxTorque;
        telemetryFeatureReport->maxPower = sPageFileStatic->maxPower;
        telemetryFeatureReport->maxRpm = sPageFileStatic->maxRpm;
        telemetryFeatureReport->maxFuel = sPageFileStatic->maxFuel;
        telemetryFeatureReport->maxTurboBoost = sPageFileStatic->maxTurboBoost;
    }
    if (sharedMemoryVNMSimulationTelemetryStatus){
        sharedMemoryVNMSimulationTelemetry.lock();
        TelemetryFeatureReport *to = (TelemetryFeatureReport*)sharedMemoryVNMSimulationTelemetry.data();
        memcpy(to, telemetryFeatureReport, sharedMemoryVNMSimulationTelemetry.size());

        sharedMemoryVNMSimulationTelemetry.unlock();
    }

}
