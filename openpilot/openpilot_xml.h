

void openpilot_save_xml_StabilizationSettings (FILE *fr, StabilizationSettingsData *data) {
	fprintf(fr, "  <StabilizationSettings>\n");
	fprintf(fr, "   <ManualRate_Roll>%f</ManualRate_Roll>\n", data->ManualRate[0]);
	fprintf(fr, "   <ManualRate_Pitch>%f</ManualRate_Pitch>\n", data->ManualRate[1]);
	fprintf(fr, "   <ManualRate_Yaw>%f</ManualRate_Yaw>\n", data->ManualRate[2]);
	fprintf(fr, "   <MaximumRate_Roll>%f</MaximumRate_Roll>\n", data->MaximumRate[0]);
	fprintf(fr, "   <MaximumRate_Pitch>%f</MaximumRate_Pitch>\n", data->MaximumRate[1]);
	fprintf(fr, "   <MaximumRate_Yaw>%f</MaximumRate_Yaw>\n", data->MaximumRate[2]);
	fprintf(fr, "   <RollRatePID_Kp>%f</RollRatePID_Kp>\n", data->RollRatePID[0]);
	fprintf(fr, "   <RollRatePID_Ki>%f</RollRatePID_Ki>\n", data->RollRatePID[1]);
	fprintf(fr, "   <RollRatePID_Kd>%f</RollRatePID_Kd>\n", data->RollRatePID[2]);
	fprintf(fr, "   <RollRatePID_ILimit>%f</RollRatePID_ILimit>\n", data->RollRatePID[3]);
	fprintf(fr, "   <PitchRatePID_Kp>%f</PitchRatePID_Kp>\n", data->PitchRatePID[0]);
	fprintf(fr, "   <PitchRatePID_Ki>%f</PitchRatePID_Ki>\n", data->PitchRatePID[1]);
	fprintf(fr, "   <PitchRatePID_Kd>%f</PitchRatePID_Kd>\n", data->PitchRatePID[2]);
	fprintf(fr, "   <PitchRatePID_ILimit>%f</PitchRatePID_ILimit>\n", data->PitchRatePID[3]);
	fprintf(fr, "   <YawRatePID_Kp>%f</YawRatePID_Kp>\n", data->YawRatePID[0]);
	fprintf(fr, "   <YawRatePID_Ki>%f</YawRatePID_Ki>\n", data->YawRatePID[1]);
	fprintf(fr, "   <YawRatePID_Kd>%f</YawRatePID_Kd>\n", data->YawRatePID[2]);
	fprintf(fr, "   <YawRatePID_ILimit>%f</YawRatePID_ILimit>\n", data->YawRatePID[3]);
	fprintf(fr, "   <RollPI_Kp>%f</RollPI_Kp>\n", data->RollPI[0]);
	fprintf(fr, "   <RollPI_Ki>%f</RollPI_Ki>\n", data->RollPI[1]);
	fprintf(fr, "   <RollPI_ILimit>%f</RollPI_ILimit>\n", data->RollPI[2]);
	fprintf(fr, "   <PitchPI_Kp>%f</PitchPI_Kp>\n", data->PitchPI[0]);
	fprintf(fr, "   <PitchPI_Ki>%f</PitchPI_Ki>\n", data->PitchPI[1]);
	fprintf(fr, "   <PitchPI_ILimit>%f</PitchPI_ILimit>\n", data->PitchPI[2]);
	fprintf(fr, "   <YawPI_Kp>%f</YawPI_Kp>\n", data->YawPI[0]);
	fprintf(fr, "   <YawPI_Ki>%f</YawPI_Ki>\n", data->YawPI[1]);
	fprintf(fr, "   <YawPI_ILimit>%f</YawPI_ILimit>\n", data->YawPI[2]);
	fprintf(fr, "   <VbarSensitivity_Roll>%f</VbarSensitivity_Roll>\n", data->VbarSensitivity[0]);
	fprintf(fr, "   <VbarSensitivity_Pitch>%f</VbarSensitivity_Pitch>\n", data->VbarSensitivity[1]);
	fprintf(fr, "   <VbarSensitivity_Yaw>%f</VbarSensitivity_Yaw>\n", data->VbarSensitivity[2]);
	fprintf(fr, "   <VbarRollPI_Kp>%f</VbarRollPI_Kp>\n", data->VbarRollPI[0]);
	fprintf(fr, "   <VbarRollPI_Ki>%f</VbarRollPI_Ki>\n", data->VbarRollPI[1]);
	fprintf(fr, "   <VbarPitchPI_Kp>%f</VbarPitchPI_Kp>\n", data->VbarPitchPI[0]);
	fprintf(fr, "   <VbarPitchPI_Ki>%f</VbarPitchPI_Ki>\n", data->VbarPitchPI[1]);
	fprintf(fr, "   <VbarYawPI_Kp>%f</VbarYawPI_Kp>\n", data->VbarYawPI[0]);
	fprintf(fr, "   <VbarYawPI_Ki>%f</VbarYawPI_Ki>\n", data->VbarYawPI[1]);
	fprintf(fr, "   <VbarTau>%f</VbarTau>\n", data->VbarTau);
	fprintf(fr, "   <GyroTau>%f</GyroTau>\n", data->GyroTau);
	fprintf(fr, "   <DerivativeGamma>%f</DerivativeGamma>\n", data->DerivativeGamma);
	fprintf(fr, "   <WeakLevelingKp>%f</WeakLevelingKp>\n", data->WeakLevelingKp);
	fprintf(fr, "   <RollMax>%i</RollMax>\n", data->RollMax);
	fprintf(fr, "   <PitchMax>%i</PitchMax>\n", data->PitchMax);
	fprintf(fr, "   <YawMax>%i</YawMax>\n", data->YawMax);
	fprintf(fr, "   <VbarGyroSuppress>%i</VbarGyroSuppress>\n", data->VbarGyroSuppress);
	fprintf(fr, "   <VbarMaxAngle>%i</VbarMaxAngle>\n", data->VbarMaxAngle);
	fprintf(fr, "   <DerivativeCutoff>%i</DerivativeCutoff>\n", data->DerivativeCutoff);
	fprintf(fr, "   <MaxAxisLock>%i</MaxAxisLock>\n", data->MaxAxisLock);
	fprintf(fr, "   <MaxAxisLockRate>%i</MaxAxisLockRate>\n", data->MaxAxisLockRate);
	fprintf(fr, "   <MaxWeakLevelingRate>%i</MaxWeakLevelingRate>\n", data->MaxWeakLevelingRate);
	fprintf(fr, "   <VbarPiroComp>%i</VbarPiroComp>\n", data->VbarPiroComp);
	fprintf(fr, "   <LowThrottleZeroIntegral>%i</LowThrottleZeroIntegral>\n", data->LowThrottleZeroIntegral);
	fprintf(fr, "  </StabilizationSettings>\n");
}


void openpilot_save_xml_HwSettings (FILE *fr, HwSettingsData *data) {
	fprintf(fr, "  <HwSettings>\n");
	fprintf(fr, "   <DSMxBind>%i</DSMxBind>\n", data->DSMxBind);
	fprintf(fr, "   <CC_RcvrPort>%i</CC_RcvrPort>\n", data->CC_RcvrPort);
	fprintf(fr, "   <CC_MainPort>%i</CC_MainPort>\n", data->CC_MainPort);
	fprintf(fr, "   <CC_FlexiPort>%i</CC_FlexiPort>\n", data->CC_FlexiPort);
	fprintf(fr, "   <RV_RcvrPort>%i</RV_RcvrPort>\n", data->RV_RcvrPort);
	fprintf(fr, "   <RV_AuxPort>%i</RV_AuxPort>\n", data->RV_AuxPort);
	fprintf(fr, "   <RV_AuxSBusPort>%i</RV_AuxSBusPort>\n", data->RV_AuxSBusPort);
	fprintf(fr, "   <RV_FlexiPort>%i</RV_FlexiPort>\n", data->RV_FlexiPort);
	fprintf(fr, "   <RV_TelemetryPort>%i</RV_TelemetryPort>\n", data->RV_TelemetryPort);
	fprintf(fr, "   <RV_GPSPort>%i</RV_GPSPort>\n", data->RV_GPSPort);
	fprintf(fr, "   <TelemetrySpeed>%i</TelemetrySpeed>\n", data->TelemetrySpeed);
	fprintf(fr, "   <GPSSpeed>%i</GPSSpeed>\n", data->GPSSpeed);
	fprintf(fr, "   <ComUsbBridgeSpeed>%i</ComUsbBridgeSpeed>\n", data->ComUsbBridgeSpeed);
	fprintf(fr, "   <USB_HIDPort>%i</USB_HIDPort>\n", data->USB_HIDPort);
	fprintf(fr, "   <USB_VCPPort>%i</USB_VCPPort>\n", data->USB_VCPPort);
	fprintf(fr, "   <OptionalModules_CameraStab>%i</OptionalModules_CameraStab>\n", data->OptionalModules[0]);
	fprintf(fr, "   <OptionalModules_GPS>%i</OptionalModules_GPS>\n", data->OptionalModules[1]);
	fprintf(fr, "   <OptionalModules_ComUsbBridge>%i</OptionalModules_ComUsbBridge>\n", data->OptionalModules[2]);
	fprintf(fr, "   <OptionalModules_Fault>%i</OptionalModules_Fault>\n", data->OptionalModules[3]);
	fprintf(fr, "   <OptionalModules_Altitude>%i</OptionalModules_Altitude>\n", data->OptionalModules[4]);
	fprintf(fr, "   <OptionalModules_TxPID>%i</OptionalModules_TxPID>\n", data->OptionalModules[5]);
	fprintf(fr, "   <OptionalModules_Autotune>%i</OptionalModules_Autotune>\n", data->OptionalModules[6]);
	fprintf(fr, "  </HwSettings>\n");
}


void openpilot_save_xml_SystemSettings (FILE *fr, SystemSettingsData *data) {
	fprintf(fr, "  <SystemSettings>\n");
	fprintf(fr, "   <GUIConfigData>%i</GUIConfigData>\n", data->GUIConfigData);
	fprintf(fr, "   <AirframeType>%i</AirframeType>\n", data->AirframeType);
	fprintf(fr, "  </SystemSettings>\n");
}


static void model_save_xml_OpenPilot (FILE *fr) {
	fprintf(fr, " <OpenPilot>\n");
	openpilot_save_xml_StabilizationSettings(fr, &OpenpilotStabilizationSettings);
	openpilot_save_xml_HwSettings(fr, &OpenpilotHwSettings);
	openpilot_save_xml_SystemSettings(fr, &OpenpilotSystemSettings);
	fprintf(fr, " </OpenPilot>\n");
	return;
}



static void model_parseOpenPilot_StabilizationSettings (xmlDocPtr doc, xmlNodePtr cur, StabilizationSettingsData *data) {
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if (1 == 2) {
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"ManualRate_Roll"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->ManualRate[0] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"ManualRate_Pitch"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->ManualRate[1] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"ManualRate_Yaw"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->ManualRate[2] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"MaximumRate_Roll"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->MaximumRate[0] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"MaximumRate_Pitch"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->MaximumRate[1] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"MaximumRate_Yaw"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->MaximumRate[2] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"RollRatePID_Kp"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->RollRatePID[0] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"RollRatePID_Ki"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->RollRatePID[1] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"RollRatePID_Kd"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->RollRatePID[2] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"RollRatePID_ILimit"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->RollRatePID[3] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"PitchRatePID_Kp"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->PitchRatePID[0] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"PitchRatePID_Ki"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->PitchRatePID[1] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"PitchRatePID_Kd"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->PitchRatePID[2] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"PitchRatePID_ILimit"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->PitchRatePID[3] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"YawRatePID_Kp"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->YawRatePID[0] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"YawRatePID_Ki"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->YawRatePID[1] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"YawRatePID_Kd"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->YawRatePID[2] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"YawRatePID_ILimit"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->YawRatePID[3] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"RollPI_Kp"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->RollPI[0] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"RollPI_Ki"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->RollPI[1] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"RollPI_ILimit"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->RollPI[2] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"PitchPI_Kp"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->PitchPI[0] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"PitchPI_Ki"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->PitchPI[1] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"PitchPI_ILimit"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->PitchPI[2] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"YawPI_Kp"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->YawPI[0] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"YawPI_Ki"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->YawPI[1] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"YawPI_ILimit"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->YawPI[2] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"VbarSensitivity_Roll"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->VbarSensitivity[0] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"VbarSensitivity_Pitch"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->VbarSensitivity[1] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"VbarSensitivity_Yaw"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->VbarSensitivity[2] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"VbarRollPI_Kp"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->VbarRollPI[0] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"VbarRollPI_Ki"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->VbarRollPI[1] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"VbarPitchPI_Kp"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->VbarPitchPI[0] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"VbarPitchPI_Ki"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->VbarPitchPI[1] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"VbarYawPI_Kp"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->VbarYawPI[0] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"VbarYawPI_Ki"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->VbarYawPI[1] = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"VbarTau"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->VbarTau = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"GyroTau"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->GyroTau = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"DerivativeGamma"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->DerivativeGamma = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"WeakLevelingKp"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->WeakLevelingKp = atof((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"RollMax"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->RollMax = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"PitchMax"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->PitchMax = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"YawMax"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->YawMax = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"VbarGyroSuppress"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->VbarGyroSuppress = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"VbarMaxAngle"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->VbarMaxAngle = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"DerivativeCutoff"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->DerivativeCutoff = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"MaxAxisLock"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->MaxAxisLock = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"MaxAxisLockRate"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->MaxAxisLockRate = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"MaxWeakLevelingRate"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->MaxWeakLevelingRate = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"VbarPiroComp"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->VbarPiroComp = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"LowThrottleZeroIntegral"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->LowThrottleZeroIntegral = atoi((char *)key);
			}
			xmlFree(key);
		}
		cur = cur->next;
	}
	return;
}


static void model_parseOpenPilot_HwSettings (xmlDocPtr doc, xmlNodePtr cur, HwSettingsData *data) {
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if (1 == 2) {
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"DSMxBind"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->DSMxBind = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"CC_RcvrPort"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->CC_RcvrPort = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"CC_MainPort"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->CC_MainPort = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"CC_FlexiPort"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->CC_FlexiPort = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"RV_RcvrPort"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->RV_RcvrPort = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"RV_AuxPort"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->RV_AuxPort = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"RV_AuxSBusPort"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->RV_AuxSBusPort = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"RV_FlexiPort"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->RV_FlexiPort = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"RV_TelemetryPort"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->RV_TelemetryPort = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"RV_GPSPort"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->RV_GPSPort = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"TelemetrySpeed"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->TelemetrySpeed = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"GPSSpeed"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->GPSSpeed = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"ComUsbBridgeSpeed"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->ComUsbBridgeSpeed = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"USB_HIDPort"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->USB_HIDPort = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"USB_VCPPort"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->USB_VCPPort = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"OptionalModules_CameraStab"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->OptionalModules[0] = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"OptionalModules_GPS"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->OptionalModules[1] = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"OptionalModules_ComUsbBridge"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->OptionalModules[2] = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"OptionalModules_Fault"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->OptionalModules[3] = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"OptionalModules_Altitude"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->OptionalModules[4] = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"OptionalModules_TxPID"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->OptionalModules[5] = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"OptionalModules_Autotune"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->OptionalModules[6] = atoi((char *)key);
			}
			xmlFree(key);
		}
		cur = cur->next;
	}
	return;
}


static void model_parseOpenPilot_SystemSettings (xmlDocPtr doc, xmlNodePtr cur, SystemSettingsData *data) {
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if (1 == 2) {
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"GUIConfigData"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->GUIConfigData = atoi((char *)key);
			}
			xmlFree(key);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"AirframeType"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				data->AirframeType = atoi((char *)key);
			}
			xmlFree(key);
		}
		cur = cur->next;
	}
	return;
}


static void model_parseOpenPilot (xmlDocPtr doc, xmlNodePtr cur) {
	cur = cur->xmlChildrenNode;
	openpilot_defaults_StabilizationSettings(&OpenpilotStabilizationSettings);
	openpilot_defaults_HwSettings(&OpenpilotHwSettings);
	openpilot_defaults_SystemSettings(&OpenpilotSystemSettings);
	while (cur != NULL) {
		if (1 == 2) {
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"StabilizationSettings"))) {
			model_parseOpenPilot_StabilizationSettings(doc, cur, &OpenpilotStabilizationSettings);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"HwSettings"))) {
			model_parseOpenPilot_HwSettings(doc, cur, &OpenpilotHwSettings);
		} else if ((!xmlStrcmp(cur->name, (const xmlChar *)"SystemSettings"))) {
			model_parseOpenPilot_SystemSettings(doc, cur, &OpenpilotSystemSettings);
		}
		cur = cur->next;
	}
	return;
}


