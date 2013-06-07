//---------------------------------------------------------------------------
//
//   MQInit.cpp      Copyright(C) 1999-2013, tetraface Inc.
//
//     The initialization functions based on Metasequoia SDK Rev3.11 are 
//    defined in this file.
//     You do not need to modify this file.
//
//    　Metasequoia SDK Rev3.11の仕様に基づく初期化関数を定義している。
//    プラグイン開発者がこのファイルの内容を変更する必要はない。
//
//---------------------------------------------------------------------------

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "MQPlugin.h"


//
// global functions
//
HWND (__stdcall *MQ_GetWindowHandle)(void);
MQObject (__stdcall *MQ_CreateObject)(void);
MQMaterial (__stdcall *MQ_CreateMaterial)(void);
void (__stdcall *MQ_ShowFileDialog)(const char *title, MQFileDialogInfo *info);
void (__stdcall *MQ_ImportAxis)(MQFileDialogInfo *info, MQPoint *pts, int pts_count);
void (__stdcall *MQ_ExportAxis)(MQFileDialogInfo *info, MQPoint *pts, int pts_count);
#if MQPLUGIN_VERSION >= 0x210  // from Rev2.10
BOOL (__stdcall *MQ_LoadImage)(const char *filename, LPVOID *header, LPVOID *buffer, DWORD reserved);
BOOL (__stdcall *MQ_GetSystemPath)(char *buffer, int type);
#endif
#if MQPLUGIN_VERSION >= 0x230  // from Rev2.30
void (__stdcall *MQ_RefreshView)(void *reserved);
#endif
#if MQPLUGIN_VERSION >= 0x240  // from Rev2.40
void (__stdcall *MQ_StationCallback)(MQStationCallbackProc proc, void *option);
BOOL (__stdcall *MQ_SendMessage)(int message_type, MQSendMessageInfo *info);
#endif

//
// class MQDodument
//
int  (__stdcall *MQDoc_GetObjectCount)(MQDocument doc);
MQObject (__stdcall *MQDoc_GetObject)(MQDocument doc, int index);
#if MQPLUGIN_VERSION >= 0x0310
MQObject (__stdcall *MQDoc_GetObjectFromUniqueID)(MQDocument doc, int id);
#endif
int  (__stdcall *MQDoc_GetCurrentObjectIndex)(MQDocument doc);
void (__stdcall *MQDoc_SetCurrentObjectIndex)(MQDocument doc, int index);
int  (__stdcall *MQDoc_AddObject)(MQDocument doc, MQObject obj);
void (__stdcall *MQDoc_DeleteObject)(MQDocument doc, int index);
int  (__stdcall *MQDoc_GetObjectIndex)(MQDocument doc, MQObject obj);
#if MQPLUGIN_VERSION >= 0x0310
void (__stdcall *MQDoc_GetUnusedObjectName)(MQDocument doc, char *buffer, int buffer_size, const char *base_name);
#endif
int  (__stdcall *MQDoc_GetMaterialCount)(MQDocument doc);
MQMaterial (__stdcall *MQDoc_GetMaterial)(MQDocument doc, int index);
#if MQPLUGIN_VERSION >= 0x0310
MQMaterial (__stdcall *MQDoc_GetMaterialFromUniqueID)(MQDocument doc, int id);
#endif
int  (__stdcall *MQDoc_GetCurrentMaterialIndex)(MQDocument doc);
void (__stdcall *MQDoc_SetCurrentMaterialIndex)(MQDocument doc, int index);
int  (__stdcall *MQDoc_AddMaterial)(MQDocument doc, MQMaterial mat);
void (__stdcall *MQDoc_DeleteMaterial)(MQDocument doc, int index);
#if MQPLUGIN_VERSION >= 0x0310
void (__stdcall *MQDoc_GetUnusedMaterialName)(MQDocument doc, char *buffer, int buffer_size, const char *base_name);
#endif
BOOL (__stdcall *MQDoc_FindMappingFile)(MQDocument doc, char *out_path, const char *filename, DWORD map_type);
#if MQPLUGIN_VERSION >= 0x0310
BOOL (__stdcall *MQDoc_GetMappingImage)(MQDocument doc, const char *filename, DWORD map_type, void **array);
#endif
void (__stdcall *MQDoc_Compact)(MQDocument doc);
void (__stdcall *MQDoc_ClearSelect)(MQDocument doc, DWORD flag);
BOOL (__stdcall *MQDoc_AddSelectVertex)(MQDocument doc, int objindex, int vertindex);
BOOL (__stdcall *MQDoc_DeleteSelectVertex)(MQDocument doc, int objindex, int vertindex);
BOOL (__stdcall *MQDoc_IsSelectVertex)(MQDocument doc, int objindex, int vertindex);
BOOL (__stdcall *MQDoc_AddSelectLine)(MQDocument doc, int objindex, int faceindex, int lineindex);
BOOL (__stdcall *MQDoc_DeleteSelectLine)(MQDocument doc, int objindex, int faceindex, int lineindex);
BOOL (__stdcall *MQDoc_IsSelectLine)(MQDocument doc, int objindex, int faceindex, int lineindex);
BOOL (__stdcall *MQDoc_AddSelectFace)(MQDocument doc, int objindex, int faceindex);
BOOL (__stdcall *MQDoc_DeleteSelectFace)(MQDocument doc, int objindex, int faceindex);
BOOL (__stdcall *MQDoc_IsSelectFace)(MQDocument doc, int objindex, int faceindex);
#if MQPLUGIN_VERSION >= 0x230  // from Rev2.30
BOOL (__stdcall *MQDoc_AddSelectUVVertex)(MQDocument doc, int objindex, int faceindex, int vertindex);
BOOL (__stdcall *MQDoc_DeleteSelectUVVertex)(MQDocument doc, int objindex, int faceindex, int vertindex);
BOOL (__stdcall *MQDoc_IsSelectUVVertex)(MQDocument doc, int objindex, int faceindex, int vertindex);
#endif
#if MQPLUGIN_VERSION >= 0x210  // from Rev2.10
MQScene (__stdcall *MQDoc_GetScene)(MQDocument doc, int index);
#endif
#if MQPLUGIN_VERSION >= 0x240  // from Rev2.40
MQObject (__stdcall *MQDoc_GetParentObject)(MQDocument doc, MQObject obj);
int (__stdcall *MQDoc_GetChildObjectCount)(MQDocument doc, MQObject obj);
MQObject (__stdcall *MQDoc_GetChildObject)(MQDocument doc, MQObject obj, int index);
void (__stdcall *MQDoc_GetGlobalMatrix)(MQDocument doc, MQObject obj, float *matrix);
void (__stdcall *MQDoc_GetGlobalInverseMatrix)(MQDocument doc, MQObject obj, float *matrix);
#endif
#if MQPLUGIN_VERSION >= 0x0241
int  (__stdcall *MQDoc_InsertObject)(MQDocument doc, MQObject obj, MQObject before);
#endif
#if MQPLUGIN_VERSION >= 0x0310
int  (__stdcall *MQDoc_CreateUserData)(MQDocument doc, MQUserDataInfo *info);
void (__stdcall *MQDoc_DeleteUserData)(MQDocument doc, int userdata_type, int userdata_id);
#endif

//
// class MQScene
//
#if MQPLUGIN_VERSION >= 0x210  // from Rev2.10
void (__stdcall *MQScene_InitSize)(MQScene scene, int width, int height);
void (__stdcall *MQScene_GetProjMatrix)(MQScene scene, float *matrix);
void (__stdcall *MQScene_GetViewMatrix)(MQScene scene, float *matrix);
#endif
#if MQPLUGIN_VERSION >= 0x240  // from Rev2.40
void (__stdcall *MQScene_FloatValue)(MQScene scene, int type_id, float *values);
#endif
#if MQPLUGIN_VERSION >= 0x241  // from Rev2.41
BOOL (__stdcall *MQScene_GetVisibleFace)(MQScene scene, MQObject obj, BOOL *visible);
#endif
#if MQPLUGIN_VERSION >= 0x311  // from Rev3.11
void (__stdcall *MQScene_IntValue)(MQScene scene, int type_id, int *values);
#endif

//
// class MQObject
//
void (__stdcall *MQObj_Delete)(MQObject obj);
MQObject (__stdcall *MQObj_Clone)(MQObject obj);
void (__stdcall *MQObj_Merge)(MQObject dest, MQObject source);
void (__stdcall *MQObj_Freeze)(MQObject obj, DWORD flag);
void (__stdcall *MQObj_GetName)(MQObject obj, char *buffer, int size);
int  (__stdcall *MQObj_GetVertexCount)(MQObject obj);
void (__stdcall *MQObj_GetVertex)(MQObject obj, int index, MQPoint *pts);
void (__stdcall *MQObj_SetVertex)(MQObject obj, int index, MQPoint *pts);
void (__stdcall *MQObj_GetVertexArray)(MQObject obj, MQPoint *ptsarray);
int  (__stdcall *MQObj_GetFaceCount)(MQObject obj);
int  (__stdcall *MQObj_GetFacePointCount)(MQObject obj, int face);
void (__stdcall *MQObj_GetFacePointArray)(MQObject obj, int face, int *vertex);
void (__stdcall *MQObj_GetFaceCoordinateArray)(MQObject obj, int face, MQCoordinate *uvarray);
int  (__stdcall *MQObj_GetFaceMaterial)(MQObject obj, int face);
#if MQPLUGIN_VERSION >= 0x240  // from Rev2.40
UINT (__stdcall *MQObj_GetFaceUniqueID)(MQObject obj, int face);
int (__stdcall *MQObj_GetFaceIndexFromUniqueID)(MQObject obj, UINT unique_id);
#endif
void (__stdcall *MQObj_SetName)(MQObject obj, const char *buffer);
int  (__stdcall *MQObj_AddVertex)(MQObject obj, MQPoint *p);
BOOL (__stdcall *MQObj_DeleteVertex)(MQObject obj, int index, BOOL del_vert);
int  (__stdcall *MQObj_GetVertexRefCount)(MQObject obj, int index);
#if MQPLUGIN_VERSION >= 0x240  // from Rev2.40
UINT (__stdcall *MQObj_GetVertexUniqueID)(MQObject obj, int index);
int (__stdcall *MQObj_GetVertexIndexFromUniqueID)(MQObject obj, UINT unique_id);
#endif
#if MQPLUGIN_VERSION >= 0x300  // from Rev3.00
int  (__stdcall *MQObj_GetVertexRelatedFaces)(MQObject obj, int vertex, int *faces);
#endif
//DWORD (__stdcall *MQObj_GetVertexColor)(MQObject obj, int index); // OBSOLUTE
//void (__stdcall *MQObj_SetVertexColor)(MQObject obj, int index, DWORD color); // OBSOLUTE
float (__stdcall *MQObj_GetVertexWeight)(MQObject obj, int index);
void (__stdcall *MQObj_SetVertexWeight)(MQObject obj, int index, float value);
void (__stdcall *MQObj_CopyVertexAttribute)(MQObject obj, int vert1, MQObject obj2, int vert2);
int  (__stdcall *MQObj_AddFace)(MQObject obj, int count, int *index);
BOOL (__stdcall *MQObj_DeleteFace)(MQObject obj, int index, BOOL del_vert);
BOOL (__stdcall *MQObj_InvertFace)(MQObject obj, int index);
void (__stdcall *MQObj_SetFaceMaterial)(MQObject obj, int face, int material);
void (__stdcall *MQObj_SetFaceCoordinateArray)(MQObject obj, int face, MQCoordinate *uvarray);
#if MQPLUGIN_VERSION >= 0x230  // from Rev2.30
DWORD (__stdcall *MQObj_GetFaceVertexColor)(MQObject obj, int face, int vertex);
void (__stdcall *MQObj_SetFaceVertexColor)(MQObject obj, int face, int vertex, DWORD color);
#endif
#if MQPLUGIN_VERSION >= 0x310  // from Rev3.10
float (__stdcall *MQObj_GetFaceEdgeCrease)(MQObject obj, int face, int line);
void (__stdcall *MQObj_SetFaceEdgeCrease)(MQObject obj, int face, int line, float crease);
#endif
#if MQPLUGIN_VERSION >= 0x300  // from Rev3.00
BOOL (__stdcall *MQObj_GetFaceVisible)(MQObject obj, int face);
void (__stdcall *MQObj_SetFaceVisible)(MQObject obj, int face, BOOL flag);
#endif
void (__stdcall *MQObj_OptimizeVertex)(MQObject obj, float distance, MQBool *apply);
void (__stdcall *MQObj_Compact)(MQObject obj);
DWORD (__stdcall *MQObj_GetVisible)(MQObject obj);
void (__stdcall *MQObj_SetVisible)(MQObject obj, DWORD visible);
DWORD (__stdcall *MQObj_GetPatchType)(MQObject obj);
void (__stdcall *MQObj_SetPatchType)(MQObject obj, DWORD type);
int  (__stdcall *MQObj_GetPatchSegment)(MQObject obj);
void (__stdcall *MQObj_SetPatchSegment)(MQObject obj, int segment);
#if MQPLUGIN_VERSION >= 0x210  // from Rev2.10
int  (__stdcall *MQObj_GetShading)(MQObject obj);
void (__stdcall *MQObj_SetShading)(MQObject obj, int type);
float (__stdcall *MQObj_GetSmoothAngle)(MQObject obj);
void (__stdcall *MQObj_SetSmoothAngle)(MQObject obj, float degree);
int  (__stdcall *MQObj_GetMirrorType)(MQObject obj);
void (__stdcall *MQObj_SetMirrorType)(MQObject obj, int type);
DWORD (__stdcall *MQObj_GetMirrorAxis)(MQObject obj);
void (__stdcall *MQObj_SetMirrorAxis)(MQObject obj, DWORD axis);
float (__stdcall *MQObj_GetMirrorDistance)(MQObject obj);
void (__stdcall *MQObj_SetMirrorDistance)(MQObject obj, float dis);
int  (__stdcall *MQObj_GetLatheType)(MQObject obj);
void (__stdcall *MQObj_SetLatheType)(MQObject obj, int type);
DWORD (__stdcall *MQObj_GetLatheAxis)(MQObject obj);
void (__stdcall *MQObj_SetLatheAxis)(MQObject obj, DWORD axis);
int  (__stdcall *MQObj_GetLatheSegment)(MQObject obj);
void (__stdcall *MQObj_SetLatheSegment)(MQObject obj, int segment);
#endif
#if MQPLUGIN_VERSION >= 0x240  // from Rev2.40
int (__stdcall *MQObj_GetIntValue)(MQObject obj, int type_id);
void (__stdcall *MQObj_GetFloatArray)(MQObject obj, int type_id, float *array);
void (__stdcall *MQObj_SetIntValue)(MQObject obj, int type_id, int value);
void (__stdcall *MQObj_SetFloatArray)(MQObject obj, int type_id, const float *array);
#endif
#if MQPLUGIN_VERSION >= 0x0310
BOOL (__stdcall *MQObj_AllocUserData)(MQObject obj, int userdata_id);
void (__stdcall *MQObj_FreeUserData)(MQObject obj, int userdata_id);
BOOL (__stdcall *MQObj_GetUserData)(MQObject obj, int userdata_id, int offset, int copy_bytes, void *buffer);
BOOL (__stdcall *MQObj_SetUserData)(MQObject obj, int userdata_id, int offset, int copy_bytes, const void *buffer);
BOOL (__stdcall *MQObj_AllocVertexUserData)(MQObject obj, int userdata_id);
void (__stdcall *MQObj_FreeVertexUserData)(MQObject obj, int userdata_id);
BOOL (__stdcall *MQObj_GetVertexUserData)(MQObject obj, int userdata_id, int vertex_start_index, int copy_vertex_num, int offset, int copy_bytes, void *buffer);
BOOL (__stdcall *MQObj_SetVertexUserData)(MQObject obj, int userdata_id, int vertex_start_index, int copy_vertex_num, int offset, int copy_bytes, const void *buffer);
BOOL (__stdcall *MQObj_AllocFaceUserData)(MQObject obj, int userdata_id);
void (__stdcall *MQObj_FreeFaceUserData)(MQObject obj, int userdata_id);
BOOL (__stdcall *MQObj_GetFaceUserData)(MQObject obj, int userdata_id, int face_start_index, int copy_face_num, int offset, int copy_bytes, void *buffer);
BOOL (__stdcall *MQObj_SetFaceUserData)(MQObject obj, int userdata_id, int face_start_index, int copy_face_num, int offset, int copy_bytes, const void *buffer);
#endif

//
// class MQMaterial
//
void (__stdcall *MQMat_Delete)(MQMaterial mat);
#if MQPLUGIN_VERSION >= 0x230  // from Rev2.30
int (__stdcall *MQMat_GetIntValue)(MQMaterial mat, int type_id);
void (__stdcall *MQMat_GetFloatArray)(MQMaterial mat, int type_id, float *array);
#endif
void (__stdcall *MQMat_GetName)(MQMaterial mat, char *buffer, int size);
void (__stdcall *MQMat_GetColor)(MQMaterial mat, MQColor *color);
float (__stdcall *MQMat_GetAlpha)(MQMaterial mat);
float (__stdcall *MQMat_GetDiffuse)(MQMaterial mat);
float (__stdcall *MQMat_GetAmbient)(MQMaterial mat);
float (__stdcall *MQMat_GetEmission)(MQMaterial mat);
float (__stdcall *MQMat_GetSpecular)(MQMaterial mat);
float (__stdcall *MQMat_GetPower)(MQMaterial mat);
void (__stdcall *MQMat_GetTextureName)(MQMaterial mat, char *buffer, int size);
void (__stdcall *MQMat_GetAlphaName)(MQMaterial mat, char *buffer, int size);
void (__stdcall *MQMat_GetBumpName)(MQMaterial mat, char *buffer, int size);
#if MQPLUGIN_VERSION >= 0x230  // from Rev2.30
void (__stdcall *MQMat_SetIntValue)(MQMaterial mat, int type_id, int value);
void (__stdcall *MQMat_SetFloatArray)(MQMaterial mat, int type_id, const float *array);
#endif
void (__stdcall *MQMat_SetName)(MQMaterial mat, const char *name);
void (__stdcall *MQMat_SetColor)(MQMaterial mat, MQColor *color);
void (__stdcall *MQMat_SetAlpha)(MQMaterial mat, float value);
void (__stdcall *MQMat_SetDiffuse)(MQMaterial mat, float value);
void (__stdcall *MQMat_SetAmbient)(MQMaterial mat, float value);
void (__stdcall *MQMat_SetEmission)(MQMaterial mat, float value);
void (__stdcall *MQMat_SetSpecular)(MQMaterial mat, float value);
void (__stdcall *MQMat_SetPower)(MQMaterial mat, float value);
void (__stdcall *MQMat_SetTextureName)(MQMaterial mat, const char *name);
void (__stdcall *MQMat_SetAlphaName)(MQMaterial mat, const char *name);
void (__stdcall *MQMat_SetBumpName)(MQMaterial mat, const char *name);
#if MQPLUGIN_VERSION >= 0x0310
BOOL (__stdcall *MQMat_AllocUserData)(MQMaterial mat, int userdata_id);
void (__stdcall *MQMat_FreeUserData)(MQMaterial mat, int userdata_id);
BOOL (__stdcall *MQMat_GetUserData)(MQMaterial mat, int userdata_id, int offset, int copy_bytes, void *buffer);
BOOL (__stdcall *MQMat_SetUserData)(MQMaterial mat, int userdata_id, int offset, int copy_bytes, const void *buffer);
#endif

//
// class MQMatrix
//
#if MQPLUGIN_VERSION >= 0x240  // from Rev2.40
void (__stdcall *MQMatrix_FloatValue)(float *mtx, int type_id, float *values);
#endif

//
// class MQXmlElement
//
#if MQPLUGIN_VERSION >= 0x240  // from Rev2.40
void (__stdcall *MQXmlElem_Value)(MQXmlElement elem, int type_id, void *values);
#endif


//---------------------------------------------------------------------------
//  MQCheckVersion
//---------------------------------------------------------------------------
MQPLUGIN_EXPORT DWORD MQCheckVersion(DWORD exe_version)
{
#if MQPLUGIN_VERSION == 0x200
	// exeのバージョンは2.0.0.0(Ver2.0)以上必要
	if(exe_version < 0x2000)
		return 0;
#elif MQPLUGIN_VERSION == 0x210
	// exeのバージョンは2.1.0.0(Ver2.1)以上必要
	if(exe_version < 0x2100)
		return 0;
#elif MQPLUGIN_VERSION == 0x230
	// exeのバージョンは2.3.1.0(Ver2.3.1)以上必要
	if(exe_version < 0x2310)
		return 0;
#elif MQPLUGIN_VERSION == 0x240
	// exeのバージョンは2.4.0.0(Ver2.4.0)以上必要
	if(exe_version < 0x2400)
		return 0;
#elif MQPLUGIN_VERSION == 0x241
	// exeのバージョンは2.4.1.0(Ver2.4.1)以上必要
	if(exe_version < 0x2410)
		return 0;
#elif MQPLUGIN_VERSION == 0x246
	// exeのバージョンは2.4.6.0(Ver2.4.6)以上必要
	if(exe_version < 0x2460)
		return 0;
#elif MQPLUGIN_VERSION == 0x249
	// exeのバージョンは2.4.9.0(Ver2.4.9)以上必要
	if(exe_version < 0x2490)
		return 0;
#elif MQPLUGIN_VERSION == 0x300
	// exeのバージョンは3.0.0.0(Ver3.0.0)以上必要
	if(exe_version < 0x3000)
		return 0;
#elif MQPLUGIN_VERSION == 0x310
	// exeのバージョンは3.1.0.0(Ver3.1.0)以上必要
	if(exe_version < 0x3100)
		return 0;
#elif MQPLUGIN_VERSION == 0x311
	// exeのバージョンは3.1.1.0(Ver3.1.1)以上必要
	if(exe_version < 0x3101)
		return 0;
#endif

	// This plug-in is based on the latest version of the specification
	// このプラグインは最新版に基づく仕様
	return MQPLUGIN_VERSION;
}


#define GPA(proc) \
	*(FARPROC *)&proc = GetProcAddress(hModule, #proc); \
	if(proc == NULL) goto MQINIT_EXIT;


//---------------------------------------------------------------------------
//  MQInit
//---------------------------------------------------------------------------
MQPLUGIN_EXPORT BOOL MQInit(const char *exe_name)
{
	HMODULE hModule = LoadLibrary(exe_name);
	if(hModule == NULL)
		return FALSE;

	BOOL result = FALSE;

	// ***** Global ***** 
	GPA(MQ_GetWindowHandle);
	GPA(MQ_CreateObject);
	GPA(MQ_CreateMaterial);
	GPA(MQ_ShowFileDialog);
	GPA(MQ_ImportAxis);
	GPA(MQ_ExportAxis);
#if MQPLUGIN_VERSION >= 0x210  // from Rev2.10
	GPA(MQ_LoadImage);
	GPA(MQ_GetSystemPath);
#endif
#if MQPLUGIN_VERSION >= 0x230  // from Rev2.30
	GPA(MQ_RefreshView);
	GPA(MQ_GetSystemPath);
#endif
#if MQPLUGIN_VERSION >= 0x240  // from Rev2.40
	GPA(MQ_StationCallback);
	GPA(MQ_SendMessage);
#endif

	// ***** MQDocument *****
	GPA(MQDoc_GetObjectCount);
	GPA(MQDoc_GetObject);
#if MQPLUGIN_VERSION >= 0x310  // from Rev3.10
	GPA(MQDoc_GetObjectFromUniqueID);
#endif
	GPA(MQDoc_GetCurrentObjectIndex);
	GPA(MQDoc_SetCurrentObjectIndex);
	GPA(MQDoc_AddObject);
	GPA(MQDoc_DeleteObject);
	GPA(MQDoc_GetObjectIndex);
#if MQPLUGIN_VERSION >= 0x310  // from Rev3.10
	GPA(MQDoc_GetUnusedObjectName);
#endif
	GPA(MQDoc_GetMaterialCount);
	GPA(MQDoc_GetMaterial);
#if MQPLUGIN_VERSION >= 0x310  // from Rev3.10
	GPA(MQDoc_GetMaterialFromUniqueID);
#endif
	GPA(MQDoc_GetCurrentMaterialIndex);
	GPA(MQDoc_SetCurrentMaterialIndex);
	GPA(MQDoc_AddMaterial);
	GPA(MQDoc_DeleteMaterial);
#if MQPLUGIN_VERSION >= 0x310  // from Rev3.10
	GPA(MQDoc_GetUnusedMaterialName);
#endif
	GPA(MQDoc_Compact);
	GPA(MQDoc_ClearSelect);
	GPA(MQDoc_AddSelectVertex);
	GPA(MQDoc_DeleteSelectVertex);
	GPA(MQDoc_IsSelectVertex);
	GPA(MQDoc_AddSelectLine);
	GPA(MQDoc_DeleteSelectLine);
	GPA(MQDoc_IsSelectLine);
	GPA(MQDoc_AddSelectFace);
	GPA(MQDoc_DeleteSelectFace);
	GPA(MQDoc_IsSelectFace);
#if MQPLUGIN_VERSION >= 0x230  // from Rev2.30
	GPA(MQDoc_AddSelectUVVertex);
	GPA(MQDoc_DeleteSelectUVVertex);
	GPA(MQDoc_IsSelectUVVertex);
#endif
#if MQPLUGIN_VERSION >= 0x210  // from Rev2.10
	GPA(MQDoc_FindMappingFile);
	GPA(MQDoc_GetScene);
#endif
#if MQPLUGIN_VERSION >= 0x310  // from Rev3.10
	GPA(MQDoc_GetMappingImage);
#endif
#if MQPLUGIN_VERSION >= 0x240  // from Rev2.40
	GPA(MQDoc_GetParentObject);
	GPA(MQDoc_GetChildObjectCount);
	GPA(MQDoc_GetChildObject);
	GPA(MQDoc_GetGlobalMatrix);
	GPA(MQDoc_GetGlobalInverseMatrix);
#endif
#if MQPLUGIN_VERSION >= 0x241  // from Rev2.41
	GPA(MQDoc_InsertObject);
#endif
#if MQPLUGIN_VERSION >= 0x310  // from Rev3.10
	GPA(MQDoc_CreateUserData);
	GPA(MQDoc_DeleteUserData);
#endif

	// ***** MQScene *****
#if MQPLUGIN_VERSION >= 0x210  // from Rev2.10
	GPA(MQScene_InitSize);
	GPA(MQScene_GetProjMatrix);
	GPA(MQScene_GetViewMatrix);
#endif
#if MQPLUGIN_VERSION >= 0x240  // from Rev2.40
	GPA(MQScene_FloatValue);
#endif
#if MQPLUGIN_VERSION >= 0x241  // from Rev2.41
	GPA(MQScene_GetVisibleFace);
#endif
#if MQPLUGIN_VERSION >= 0x311  // from Rev3.11
	GPA(MQScene_IntValue);
#endif

	// ***** MQObject *****
	GPA(MQObj_Delete);
	GPA(MQObj_Clone);
	GPA(MQObj_Merge);
	GPA(MQObj_Freeze);
	GPA(MQObj_GetName);
	GPA(MQObj_GetVertexCount);
	GPA(MQObj_GetVertex);
	GPA(MQObj_SetVertex);
	GPA(MQObj_GetVertexArray);
	GPA(MQObj_GetFaceCount);
	GPA(MQObj_GetFacePointCount);
	GPA(MQObj_GetFacePointArray);
	GPA(MQObj_GetFaceCoordinateArray);
	GPA(MQObj_GetFaceMaterial);
#if MQPLUGIN_VERSION >= 0x240  // from Rev2.40
	GPA(MQObj_GetFaceUniqueID);
	GPA(MQObj_GetFaceIndexFromUniqueID);
#endif
	GPA(MQObj_SetName);
	GPA(MQObj_AddVertex);
	GPA(MQObj_DeleteVertex);
	GPA(MQObj_GetVertexRefCount);
#if MQPLUGIN_VERSION >= 0x240  // from Rev2.40
	GPA(MQObj_GetVertexUniqueID);
	GPA(MQObj_GetVertexIndexFromUniqueID);
#endif
#if MQPLUGIN_VERSION >= 0x300  // from Rev3.00
	GPA(MQObj_GetVertexRelatedFaces);
#endif
	//GPA(MQObj_GetVertexColor); // OBSOLUTE
	//GPA(MQObj_SetVertexColor); // OBSOLUTE
	GPA(MQObj_GetVertexWeight);
	GPA(MQObj_SetVertexWeight);
	GPA(MQObj_CopyVertexAttribute);
	GPA(MQObj_AddFace);
	GPA(MQObj_DeleteFace);
	GPA(MQObj_InvertFace);
	GPA(MQObj_SetFaceMaterial);
	GPA(MQObj_SetFaceCoordinateArray);
#if MQPLUGIN_VERSION >= 0x230  // from Rev2.30
	GPA(MQObj_GetFaceVertexColor);
	GPA(MQObj_SetFaceVertexColor);
#endif
#if MQPLUGIN_VERSION >= 0x310  // from Rev3.10
	GPA(MQObj_GetFaceEdgeCrease);
	GPA(MQObj_SetFaceEdgeCrease);
#endif
#if MQPLUGIN_VERSION >= 0x300  // from Rev3.00
	GPA(MQObj_GetFaceVisible);
	GPA(MQObj_SetFaceVisible);
#endif
	GPA(MQObj_OptimizeVertex);
	GPA(MQObj_Compact);
	GPA(MQObj_GetVisible);
	GPA(MQObj_SetVisible);
	GPA(MQObj_GetPatchType);
	GPA(MQObj_SetPatchType);
	GPA(MQObj_GetPatchSegment);
	GPA(MQObj_SetPatchSegment);
#if MQPLUGIN_VERSION >= 0x210  // from Rev2.10
	GPA(MQObj_GetShading);
	GPA(MQObj_SetShading);
	GPA(MQObj_GetSmoothAngle);
	GPA(MQObj_SetSmoothAngle);
	GPA(MQObj_GetMirrorType);
	GPA(MQObj_SetMirrorType);
	GPA(MQObj_GetMirrorAxis);
	GPA(MQObj_SetMirrorAxis);
	GPA(MQObj_GetMirrorDistance);
	GPA(MQObj_SetMirrorDistance);
	GPA(MQObj_GetLatheType);
	GPA(MQObj_SetLatheType);
	GPA(MQObj_GetLatheAxis);
	GPA(MQObj_SetLatheAxis);
	GPA(MQObj_GetLatheSegment);
	GPA(MQObj_SetLatheSegment);
#endif
#if MQPLUGIN_VERSION >= 0x240  // from Rev2.40
	GPA(MQObj_GetIntValue);
	GPA(MQObj_GetFloatArray);
	GPA(MQObj_SetIntValue);
	GPA(MQObj_SetFloatArray);
#endif
#if MQPLUGIN_VERSION >= 0x310  // from Rev3.10
	GPA(MQObj_AllocUserData);
	GPA(MQObj_FreeUserData);
	GPA(MQObj_GetUserData);
	GPA(MQObj_SetUserData);
	GPA(MQObj_AllocVertexUserData);
	GPA(MQObj_FreeVertexUserData);
	GPA(MQObj_GetVertexUserData);
	GPA(MQObj_SetVertexUserData);
	GPA(MQObj_AllocFaceUserData);
	GPA(MQObj_FreeFaceUserData);
	GPA(MQObj_GetFaceUserData);
	GPA(MQObj_SetFaceUserData);
#endif

	// ***** MQMaterial ***** 
	GPA(MQMat_Delete);
#if MQPLUGIN_VERSION >= 0x230  // from Rev2.30
	GPA(MQMat_GetIntValue);
	GPA(MQMat_GetFloatArray);
#endif
	GPA(MQMat_GetName);
	GPA(MQMat_GetColor);
	GPA(MQMat_GetAlpha);
	GPA(MQMat_GetDiffuse);
	GPA(MQMat_GetAmbient);
	GPA(MQMat_GetEmission);
	GPA(MQMat_GetSpecular);
	GPA(MQMat_GetPower);
	GPA(MQMat_GetTextureName);
	GPA(MQMat_GetAlphaName);
	GPA(MQMat_GetBumpName);
#if MQPLUGIN_VERSION >= 0x230  // from Rev2.30
	GPA(MQMat_SetIntValue);
	GPA(MQMat_SetFloatArray);
#endif
	GPA(MQMat_SetName);
	GPA(MQMat_SetColor);
	GPA(MQMat_SetAlpha);
	GPA(MQMat_SetDiffuse);
	GPA(MQMat_SetAmbient);
	GPA(MQMat_SetEmission);
	GPA(MQMat_SetSpecular);
	GPA(MQMat_SetPower);
	GPA(MQMat_SetTextureName);
	GPA(MQMat_SetAlphaName);
	GPA(MQMat_SetBumpName);
#if MQPLUGIN_VERSION >= 0x0310
	GPA(MQMat_AllocUserData);
	GPA(MQMat_FreeUserData);
	GPA(MQMat_GetUserData);
	GPA(MQMat_SetUserData);
#endif

#if MQPLUGIN_VERSION >= 0x240  // from Rev2.40
	GPA(MQMatrix_FloatValue);
#endif

#if MQPLUGIN_VERSION >= 0x240  // from Rev2.40
	GPA(MQXmlElem_Value);
#endif

	result = TRUE;

MQINIT_EXIT:
	FreeLibrary(hModule);
	return result;
}


