#
# AUTO-GENERATED Makefile; do not edit, changes will be lost
#

# Define target type
TARGET:=wp77xx

# Custom makefile include: initialization
-include ../customInit.mk

# Only when not cleaning
ifneq ($(MAKECMDGOALS),clean)
endif

# Target artifact.*
TARGET_ARTIFACT:=mqttclient_fx30ltem.$(TARGET).update

# Clean command
CLEANCOMMAND:=find -maxdepth 1 -mindepth 1 ! -name Makefile ! -name .rsync-rules -exec rm -R {} \;

# MK command
MKCOMMAND:=cd ..;mkapp -t $(TARGET) -o Target_Legato_Debug -w Target_Legato_Debug -i "$(LEGATO_ROOT)/interfaces/logDaemon" -i "$(LEGATO_ROOT)/interfaces/atServices" -i "$(LEGATO_ROOT)/interfaces/airVantage" -i "$(LEGATO_ROOT)/interfaces/airVantage/legacy" -i "$(LEGATO_ROOT)/interfaces/portService" -i "$(LEGATO_ROOT)/interfaces/modemServices" -i "$(LEGATO_ROOT)/interfaces/watchdog" -i "$(LEGATO_ROOT)/interfaces/positioning" -i "$(LEGATO_ROOT)/interfaces/wifi" -i "$(LEGATO_ROOT)/interfaces/supervisor" -i "$(LEGATO_ROOT)/interfaces" -i "$(LEGATO_ROOT)/interfaces/secureStorage" -i "mqttclient_fx30ltemComponent/mqtt-inc" -s "$(LEGATO_ROOT)/apps/platformServices/airVantageConnector/apps/test/assetDataTest" -s "$(LEGATO_ROOT)/components/dataConnectionService/platformAdaptor/default" -s "$(LEGATO_ROOT)/apps/platformServices/airVantageConnector/apps/test/suspendResume" -s "$(LEGATO_ROOT)/apps/platformServices/airVantageConnector/apps/test/timeseries" -s "$(LEGATO_ROOT)/apps/platformServices/airVantageConnector" -s "$(LEGATO_ROOT)/components/airVantage" -s "$(LEGATO_ROOT)/modules/WiFi/apps/tools/wifi" -s "$(LEGATO_ROOT)/components/positioning" -s "$(LEGATO_ROOT)/components/secStore" -s "$(LEGATO_ROOT)/components/portService" -s "$(LEGATO_ROOT)/components/uartMode/platformAdaptor/default" -s "$(LEGATO_ROOT)/components/modemServices/platformAdaptor/default" -s "$(LEGATO_ROOT)/apps/platformServices/airVantageConnector/apps/test/avcIntegrationTest" -s "$(LEGATO_ROOT)/apps/proprietary/atAirVantage/src" -s "$(LEGATO_ROOT)/components/audio/platformAdaptor/default" -s "$(LEGATO_ROOT)/apps/tools" -s "$(LEGATO_ROOT)/components/3rdParty" -s "$(LEGATO_ROOT)/apps/platformServices/airVantageConnector/apps/test" -s "$(LEGATO_ROOT)/components/fwupdate/platformAdaptor/default" -s "$(LEGATO_ROOT)/apps/platformServices/airVantageConnector/apps/test/assetPush" -s "$(LEGATO_ROOT)/apps/platformServices/airVantageConnector/apps/test/airVantageConnectorUnitTest" -s "$(LEGATO_ROOT)/modules/WiFi/service" -s "$(LEGATO_ROOT)/components/dataConnectionService" -s "$(LEGATO_ROOT)/components/airVantage/platformAdaptor/default" -s "." -s "$(LEGATO_ROOT)/apps/platformServices/airVantageConnector/apps/test/session" -s "$(LEGATO_ROOT)/components/fwupdate" -s "$(LEGATO_ROOT)/apps/proprietary/atQmiLinker/src" -s "$(LEGATO_ROOT)/components/positioning/platformAdaptor/default" -s "$(LEGATO_ROOT)/apps/platformServices/airVantageConnector/apps/test/avDataUnitTest" -s "$(LEGATO_ROOT)/components/devMode" -s "$(LEGATO_ROOT)/components/secStore/platformAdaptor/default" -s "$(LEGATO_ROOT)/components/modemServices" -s "$(LEGATO_ROOT)/components/atServices" -s "$(LEGATO_ROOT)/components" -s "$(LEGATO_ROOT)/components/uartMode" -s "$(LEGATO_ROOT)/apps/proprietary/qmiAirVantage/src" -s "$(LEGATO_ROOT)/apps/platformServices/airVantageConnector/apps/test/packageDownloadHost" -C -g -X -g -L -g mqttclient_fx30ltem.adef

# Custom makefile include: definitions
-include ../customDefs.mk

.PHONY: all target clean codegen mkCodegen  airvantage

all: target

codegen: mkCodegen

mkCodegen:
	$(MKCOMMAND) --generate-code

target:
	$(MKCOMMAND)



clean:
	$(CLEANCOMMAND)


# Custom makefile include: targets
-include ../customTargets.mk
