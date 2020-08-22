# VNMSimulationTelemetry
This is opensource to get statistics of the games
here are parameters what i think "must have" in Assetto Corsa

    // SPageFilePhysics
    
    float gas = 0;
    
    float brake = 0;
    
    float fuel = 0;
    
    int gear = 0;
    
    int rpm = 0;
    
    float steerAngle = 0;
    
    float speedKmh = 0;
    
    float tc = 0;
    
    float abs = 0;
    
    float turboBoost;
    
    int drsEnabled;
    
    float clutch;
    
    float brakeBias;
    
    int frontBrakeCompound;
    
    int rearBrakeCompound;
    
    float finalForceFeedback;
    
    // SPageFileGraphic

    //SPageFileStatic
    
    float maxTorque = 0;
    
    float maxPower = 0;
    
    int maxRpm = 0;
    
    float maxFuel = 0;
    
    float maxTurboBoost = 0;
	
all this value must be convert to  2 byte to easy transmission
so struct will like this

struct TelemetryFeatureReport {

    uint8_t gameID = 0;
 
    // SPageFilePhysics
    
    int16_t gas = 0;
    
    int16_t brake = 0;
    
    int16_t fuel = 0;
    
    int16_t gear = 0;
    
    int16_t rpm = 0;
    
    int16_t steerAngle = 0;
    
    int16_t speedKmh = 0;
    
    int16_t tc = 0;
    
    int16_t abs = 0;
    
    int16_t turboBoost;
    
    int16_t drsEnabled;
    
    int16_t clutch;
    
    int16_t brakeBias;
    
    int16_t frontBrakeCompound;
    
    int16_t rearBrakeCompound;
    
    int16_t finalForceFeedback;
    
    // SPageFileGraphic

    //SPageFileStatic
    
    int16_t maxTorque = 0;
    
    int16_t maxPower = 0;
    
    int16_t maxRpm = 0;
    
    int16_t maxFuel = 0;
    
    int16_t maxTurboBoost = 0;
};
some parameters are true/false, value < 255 can be use uint8_t or int8_t like gear, fuel, drsEnable.

If parameters's value is (-1.0 to 1.0), muliply with 10000, for example: steerAngle, finalForceFeedback is [-1.0, -0.9999...0.9999, 1.0] =>new value is [-10000, 10000]

class AcTelemetry is wrote on QT5 C++.
	
