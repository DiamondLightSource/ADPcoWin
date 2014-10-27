/*
 * SimulationApi.h
 *
 * Revamped PCO area detector driver.
 *
 * A simulation of the PCO API library and hardware
 *
 * Author:  Giles Knap
 *          Jonathan Thompson
 *
 */

#ifndef SIMULATIONAPI_H_
#define SIMULATIONAPI_H_

#include <string>
#include "epicsMessageQueue.h"
#include "StateMachine.h"
#include "DllApi.h"
#include "IntegerParam.h"
#include "StringParam.h"
class Pco;
class TraceStream;
class TakeLock;

class SimulationApi: public DllApi, public StateMachine::User
{
// Construction
public:
    SimulationApi(Pco* pco, TraceStream* trace);
    virtual ~SimulationApi();

// Overrides of DllApi
protected:
    virtual int doOpenCamera(Handle* handle, unsigned short camNum);
    virtual int doCloseCamera(Handle handle);
    virtual int doRebootCamera(Handle handle);
    virtual int doGetGeneral(Handle handle);
    virtual int doGetCameraType(Handle handle, unsigned short* camType);
    virtual int doGetSensorStruct(Handle handle);
    virtual int doGetCameraDescription(Handle handle, Description* description);
    virtual int doGetStorageStruct(Handle handle, unsigned long* ramSize, unsigned int* pageSize);
    virtual int doGetRecordingStruct(Handle handle);
    virtual int doResetSettingsToDefault(Handle handle);
    virtual int doGetTransferParameters(Handle handle, Transfer* transfer);
    virtual int doSetTransferParameters(Handle handle, Transfer* transfer);
    virtual int doGetSizes(Handle handle, Sizes* sizes);
    virtual int doSetDateTime(Handle handle, struct tm* currentTime);
    virtual int doGetTemperature(Handle handle, short* ccd, short* camera, short* psu);
    virtual int doSetCoolingSetpoint(Handle handle, short setPoint);
    virtual int doGetCoolingSetpoint(Handle handle, short* setPoint);
    virtual int doSetPixelRate(Handle handle, unsigned long pixRate);
    virtual int doGetPixelRate(Handle handle, unsigned long* pixRate);
    virtual int doGetBitAlignment(Handle handle, unsigned short* bitAlignment);
    virtual int doSetBitAlignment(Handle handle, unsigned short bitAlignment);
    virtual int doGetCameraSetup(Handle handle, unsigned short* setupType,
            unsigned long* setupData, unsigned short* setupDataLen);
    virtual int doSetBinning(Handle handle, unsigned short binHorz, unsigned short binVert);
    virtual int doGetBinning(Handle handle, unsigned short* binHorz, unsigned short* binVert);
    virtual int doSetRoi(Handle handle, unsigned short x0, unsigned short y0,
            unsigned short x1, unsigned short y1);
    virtual int doGetRoi(Handle handle, unsigned short* x0, unsigned short* y0,
            unsigned short* x1, unsigned short* y1);
    virtual int doSetTriggerMode(Handle handle, unsigned short mode);
    virtual int doGetTriggerMode(Handle handle, unsigned short* mode);
    virtual int doSetStorageMode(Handle handle, unsigned short mode);
    virtual int doGetStorageMode(Handle handle, unsigned short* mode);
    virtual int doSetTimestampMode(Handle handle, unsigned short mode);
    virtual int doGetTimestampMode(Handle handle, unsigned short* mode);
    virtual int doSetAcquireMode(Handle handle, unsigned short mode);
    virtual int doGetAcquireMode(Handle handle, unsigned short* mode);
    virtual int doSetDelayExposureTime(Handle handle, unsigned long delay,
            unsigned long exposure, unsigned short timeBaseDelay,
            unsigned short timeBaseExposure);
    virtual int doGetDelayExposureTime(Handle handle, unsigned long* delay,
            unsigned long* exposure, unsigned short* timeBaseDelay,
            unsigned short* timeBaseExposure);
    virtual int doSetConversionFactor(Handle handle, unsigned short factor);
    virtual int doSetAdcOperation(Handle handle, unsigned short mode);
    virtual int doGetAdcOperation(Handle handle, unsigned short* mode);
    virtual int doGetRecordingState(Handle handle, unsigned short* state);
    virtual int doSetRecordingState(Handle handle, unsigned short state);
    virtual int doGetRecorderSubmode(Handle handle, unsigned short* mode);
    virtual int doAllocateBuffer(Handle handle, short* bufferNumber, unsigned long size,
            unsigned short** buffer, Handle* event);
    virtual int doCancelImages(Handle handle);
    virtual int doCamlinkSetImageParameters(Handle handle, unsigned short xRes, unsigned short yRes);
    virtual int doArm(Handle handle);
    virtual int doAddBufferEx(Handle handle, unsigned long firstImage, unsigned long lastImage, 
        short bufferNumber, unsigned short xRes, unsigned short yRes, unsigned short bitRes);
    virtual int doGetBufferStatus(Handle handle, short bufferNumber, unsigned long* statusDll,
        unsigned long* statusDrv);
    virtual int doForceTrigger(Handle handle, unsigned short* triggered);
    virtual int doFreeBuffer(Handle handle, short bufferNumber);
    virtual int doGetActiveRamSegment(Handle handle, unsigned short* segment);
    virtual int doGetNumberOfImagesInSegment(Handle handle, unsigned short segment,
            unsigned long* validImageCount, unsigned long* maxImageCount);
    virtual int doSetActiveLookupTable(Handle handle, unsigned short identifier);
    virtual int doSetTimeouts(Handle handle, unsigned int commandTimeout,
    		unsigned int imageTimeout, unsigned int transferTimeout);

// Override of StateMachine::User
public:
    virtual int doTransition(StateMachine* machine, int state, int event);

// Parameters
private:
	IntegerParam paramConnected;
	IntegerParam paramOpen;;
	IntegerParam paramCameraType;
	IntegerParam paramMaxHorzRes;
	IntegerParam paramMaxVertRes;
	IntegerParam paramDynResolution;
	IntegerParam paramMaxBinHorz;
	IntegerParam paramMaxBinVert;
	IntegerParam paramBinHorzStepping;
	IntegerParam paramBinVertStepping;
	IntegerParam paramRoiHorSteps;
	IntegerParam paramRoiVertSteps;
	IntegerParam paramPixelRate;
	IntegerParam paramConvFact;
	IntegerParam paramGeneralCaps;
	IntegerParam paramRamSize;
	IntegerParam paramPageSize;
	IntegerParam paramBaudRate;
	IntegerParam paramClockFrequency;
	IntegerParam paramCamlinkLines;
	IntegerParam paramDataFormat;
	IntegerParam paramTransmit;
	IntegerParam paramActualHorzRes;
	IntegerParam paramActualVertRes;
	IntegerParam paramTimeYear;
	IntegerParam paramTimeMonth;
	IntegerParam paramTimeDay;
	IntegerParam paramTimeHour;
	IntegerParam paramTimeMinute;
	IntegerParam paramTimeSecond;
	IntegerParam paramTempCcd;
	IntegerParam paramTempCamera;
	IntegerParam paramTempPsu;
	IntegerParam paramBitAlignment;
	IntegerParam paramEdgeGlobalShutter;
	IntegerParam paramActualHorzBin;
	IntegerParam paramActualVertBin;
	IntegerParam paramActualRoiX0;
	IntegerParam paramActualRoiY0;
	IntegerParam paramActualRoiX1;
	IntegerParam paramActualRoiY1;
	IntegerParam paramTriggerMode;
	IntegerParam paramStorageMode;
	IntegerParam paramTimestampMode;
	IntegerParam paramAcquireMode;
	IntegerParam paramDelayTime;
	IntegerParam paramDelayTimebase;
	IntegerParam paramExposureTime;
	IntegerParam paramExposureTimebase;
	IntegerParam paramActualConvFact;
	IntegerParam paramAdcOperation;
	IntegerParam paramRecordingState;
	IntegerParam paramRecorderSubmode;
	IntegerParam paramCamlinkHorzRes;
	IntegerParam paramCamlinkVertRes;
	IntegerParam paramArmed;
	IntegerParam paramClearStateRecord;
	IntegerParam paramExternalTrigger;
	StringParam paramStateRecord;

// Types
public:
    enum Request {requestConnectionUp=0, requestConnectionDown, requestOpen,
        requestClose, requestStartRecording, requestStopRecording,
        requestTrigger, requestArm, requestCancelImages};
    enum State {stateConnected=0, stateOpen, stateDisconnected, stateArmed,
        stateRecording};

// Constants
protected:
    static const int edgeSetupDataLength;
    static const int edgeSetupDataType;
    static const char* stateNames[];
    static const char* eventNames[];

// Members
protected:
    struct
    {
        unsigned short* buffer;
        unsigned long status;
    } buffers[DllApi::maxNumBuffers];
    epicsMessageQueue bufferQueue;
    StateMachine* stateMachine;
    int frameNumber;

// Functions
protected:
    void post(Request req);
    void generateFrame();
    void startTriggerTimer();
    void onConnected(TakeLock& takeLock);
    void onExternalTrigger(TakeLock& takeLock);
};

#endif /* SIMULATIONAPI_H_ */
