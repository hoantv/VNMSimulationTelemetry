#ifndef ACTELEMETRY_H
#define ACTELEMETRY_H

#include <QObject>
#include <QSharedMemory>

#include <QBuffer>
#include <QTimer>
#include <QDataStream>
#include "vnm_common.h"
#include "Hid/hid_report.h"
#include "Hid/hid_device.h"


#pragma once

typedef int AC_STATUS;

#define AC_OFF 0
#define AC_REPLAY 1
#define AC_LIVE 2
#define AC_PAUSE 3

typedef int AC_SESSION_TYPE;

#define AC_UNKNOWN -1
#define AC_PRACTICE 0
#define AC_QUALIFY 1
#define AC_RACE 2
#define AC_HOTLAP 3
#define AC_TIME_ATTACK 4
#define AC_DRIFT 5
#define AC_DRAG 6

typedef int AC_FLAG_TYPE;

#define AC_NO_FLAG 0
#define AC_BLUE_FLAG 1
#define AC_YELLOW_FLAG 2
#define AC_BLACK_FLAG 3
#define AC_WHITE_FLAG 4
#define AC_CHECKERED_FLAG 5
#define AC_PENALTY_FLAG 6

#pragma pack(push)
#pragma pack(4)

struct SPageFilePhysics
{
    int packetId = 0;
    float gas = 0;
    float brake = 0;
    float fuel = 0;
    int gear = 0;
    int rpm = 0;
    float steerAngle = 0;
    float speedKmh = 0;
    float velocity[3];
    float accG[3];
    float wheelSlip[4];
    float wheelLoad[4];
    float wheelPressure[4];
    float wheelAngularSpeed[4];
    float tyreWear[4];
    float tyreDirtyLevel[4];
    float TyreCoreTemp[4];
    float camberRAD[4];
    float suspensionTravel[4];
    float drs = 0;
    float tc = 0;
    float heading = 0;
    float pitch = 0;
    float roll = 0;
    float cgHeight = 0;
    float carDamage[5];
    int numberOfTyresOut = 0;
    int pitLimiterOn = 0;
    float abs = 0;
    float kersCharge = 0;
    float kersInput = 0;
    int autoshifterOn = 0;
    float rideHeight[2];
    float turboBoost;
    float ballast;
    float airDensity;
    float airTemp;
    float roadTemp;
    float localAngularVel[3];
    float finalForceFeedback;
    float performanceMeter;
    int engineBrake;
    int ersRecoveryLevel;
    int ersPowerLevel;
    int ersHeatCharging;
    int ersIsCharging;
    float kersCurrentKJ;
    int drsAvailable;
    int drsEnabled;
    float brakeTemp[4];
    float clutch;
    float tyreTempI[4];
    float tyreTempM[4];
    float tyreTempO[4];
    int isAIControlled;
    float tyreContactPoint[4][3];
    float tyreContactNormal[4][3];
    float tyreContactHeading[4][3];
    float brakeBias;
    float localVelocity[3];
    int P2PActivation;
    int P2PStatus;
    float currentMaxRpm;
    float mz[4];
    float fx[4];
    float fy[4];
    float slipRatio[4];
    float slipAngle[4];
    int tcinAction;
    int absInAction;
    float suspensionDamage[4];
    float tyreTemp[4];
    float waterTemp;
    float brakePressure[4];
    int frontBrakeCompound;
    int rearBrakeCompound;
    float padLife[4];
    float discLife[4];
};


struct SPageFileGraphic
{
int packetId = 0;
AC_STATUS status = AC_OFF;
AC_SESSION_TYPE session = AC_PRACTICE;
wchar_t currentTime[15];
wchar_t lastTime[15];
wchar_t bestTime[15];
wchar_t split[15];
int completedLaps = 0;
int position = 0;
int iCurrentTime = 0;
int iLastTime = 0;
int iBestTime = 0;
float sessionTimeLeft = 0;
float distanceTraveled = 0;
int isInPit = 0;
int currentSectorIndex = 0;
int lastSectorTime = 0;
int numberOfLaps = 0;
wchar_t tyreCompound[33];

float replayTimeMultiplier = 0;
float normalizedCarPosition = 0;
float carCoordinates[3];
float penaltyTime = 0;
AC_FLAG_TYPE flag = AC_NO_FLAG;
int idealLineOn = 0;
int isInPitLane = 0;
float surfaceGrip = 0;

int mandatoryPitDone = 0;
float windSpeed = 0;
float windDirection = 0;
int isSetupMenuVisible = 0;
int mainDisplayIndex = 0;
int secondaryDisplyIndex = 0;
int TC = 0;
int TCCUT = 0;
int EngineMap = 0;
int ABS = 0;
float fuelXLap = 0;
int rainLights = 0;
int flashingLights = 0;
int lightsStage = 0;
float exhaustTemperature = 0;
int wiperLV = 0;
int driverStintTotalTimeLeft = 0;
int driverStintTimeLeft = 0;
int rainTyres = 0;
int sessionIndex = 0;
float usedFuel = 0;
wchar_t deltaLapTime[15];
int iDeltaLapTime = 0;
wchar_t estimatedLapTime = 0;
int iEstimatedLapTime = 0;
int isDeltaPositive = 0;
int iSplit = 0;
int isValidLap = 0;
float fuelEstimatedLaps = 0;
wchar_t trackStatus[33];
int missingMandatoryPits = 0;

};


struct SPageFileStatic
{
wchar_t smVersion[15];
wchar_t acVersion[15];
// session static info
int numberOfSessions = 0;
int numCars = 0;
wchar_t carModel[33];
wchar_t track[33];
wchar_t playerName[33];
wchar_t playerSurname[33];
wchar_t playerNick[33];
int sectorCount = 0;

// car static info
float maxTorque = 0;
float maxPower = 0;
int maxRpm = 0;
float maxFuel = 0;
float suspensionMaxTravel[4];
float tyreRadius[4];
float maxTurboBoost = 0;

float airTemp = 0;
float roadTemp = 0;
bool penaltiesEnabled = false;

float aidFuelRate = 0;
float aidTireRate = 0;
float aidMechanicalDamage = 0;
bool aidAllowTyreBlankets = false;
float aidStability = 0;
bool aidAutoClutch = false;
bool aidAutoBlip = false;

int hasDRS = 0;
int hasERS = 0;
int hasKERS = 0;
float kersMaxJ = 0;
int engineBrakeSettingsCount = 0;
int ersPowerControllerCount = 0;
float trackSplineLength = 0;
wchar_t trackConfiguration = 0;
float ersMaxJ = 0;
int isTimedRace = 0;
int hasExtraLap = 0;
wchar_t carSkin[33];
int reversedGridPositions = 0;
int PitWindowStart = 0;
int PitWindowEnd = 0;
int isOnline = 0;
};

#pragma pack(pop)

class ACTelemetry : public QObject
{
    Q_OBJECT
public:
    explicit ACTelemetry(QObject *parent = nullptr);
    ~ACTelemetry();
    void start(void);
    void stop(void);

signals:
private slots:
    void updateTelemetry();
private:
    QTimer *acTelemetryTimer;
    uint8_t interval = 10;
    SPageFilePhysics* sPageFilePhysics;
    SPageFileGraphic* sPageFileGraphic;
    SPageFileStatic* sPageFileStatic;
    TelemetryFeatureReport* telemetryFeatureReport;
    QSharedMemory sharedMemorySPageFilePhysics;
    QSharedMemory sharedMemorySPageFileGraphics;
    QSharedMemory sharedMemorySPageFileStatic;
    QSharedMemory sharedMemoryVNMSimulationTelemetry;
    bool sharedMemorySPageFilePhysicsStatus = false;
    bool sharedMemorySPageFileGraphicsStatus = false;
    bool sharedMemorySPageFileStaticStatus = false;
    bool sharedMemoryVNMSimulationTelemetryStatus = false;
};

#endif // ACTELEMETRY_H
