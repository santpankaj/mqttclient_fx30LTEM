/*
 * AUTO-GENERATED _componentMain.c for the mqttclient_fx30ltemComponent component.

 * Don't bother hand-editing this file.
 */

#include "legato.h"
#include "../liblegato/eventLoop.h"
#include "../liblegato/log.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const char* _mqttclient_fx30ltemComponent_le_data_ServiceInstanceName;
const char** le_data_ServiceInstanceNamePtr = &_mqttclient_fx30ltemComponent_le_data_ServiceInstanceName;
void le_data_ConnectService(void);
// Component log session variables.
le_log_SessionRef_t mqttclient_fx30ltemComponent_LogSession;
le_log_Level_t* mqttclient_fx30ltemComponent_LogLevelFilterPtr;

// Component initialization function (COMPONENT_INIT).
void _mqttclient_fx30ltemComponent_COMPONENT_INIT(void);

// Library initialization function.
// Will be called by the dynamic linker loader when the library is loaded.
__attribute__((constructor)) void _mqttclient_fx30ltemComponent_Init(void)
{
    LE_DEBUG("Initializing mqttclient_fx30ltemComponent component library.");

    // Connect client-side IPC interfaces.
    le_data_ConnectService();

    // Register the component with the Log Daemon.
    mqttclient_fx30ltemComponent_LogSession = log_RegComponent("mqttclient_fx30ltemComponent", &mqttclient_fx30ltemComponent_LogLevelFilterPtr);

    //Queue the COMPONENT_INIT function to be called by the event loop
    event_QueueComponentInit(_mqttclient_fx30ltemComponent_COMPONENT_INIT);
}


#ifdef __cplusplus
}
#endif
