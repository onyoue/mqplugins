//---------------------------------------------------------------------------
//
//   MQPlugin.h      Copyright(C) 1999-2013, tetraface Inc.
//
//     This is an include file based on Metasequoia SDK Rev3.11
//    specification. You do not need to modify this file.
//
//    　Metasequoia SDK Rev3.11の仕様に基づくインクルードファイル。
//    プラグイン開発者がこのファイルの内容を変更する必要はない。
//
//---------------------------------------------------------------------------

#ifndef MQPluginH
#define MQPluginH

#include <math.h>
#include <string>

// It treats as Rev3.11 if MQPLUGIN_VERSION is not defined in preprocessor.
// プリプロセッサでMQPLUGIN_VERSIONが定義されていなければRev3.11として扱う
#ifndef MQPLUGIN_VERSION
#define MQPLUGIN_VERSION  0x0311
#endif


#ifndef MQPLUGIN_EXPORTS
#define MQPLUGIN_API extern "C"
#endif

#define MQPLUGIN_EXPORT extern "C" __declspec(dllexport)


#define MQPLUGIN_TYPE_IMPORT   1
#define MQPLUGIN_TYPE_EXPORT   2
#define MQPLUGIN_TYPE_CREATE   3
#define MQPLUGIN_TYPE_OBJECT   4
#define MQPLUGIN_TYPE_SELECT   5
#define MQPLUGIN_TYPE_STATION  6
#define MQPLUGIN_TYPE_COMMAND  7

// MQOnEvent
#define MQEVENT_INITIALIZE			1
#define MQEVENT_EXIT				2
#define MQEVENT_ACTIVATE			100
#define MQEVENT_IS_ACTIVATED		101
#define MQEVENT_MINIMIZE			102
#define MQEVENT_USER_MESSAGE		103
#define MQEVENT_DRAW				110
#define MQEVENT_LBUTTON_DOWN		120
#define MQEVENT_LBUTTON_MOVE		121
#define MQEVENT_LBUTTON_UP			122
#define MQEVENT_MBUTTON_DOWN		123
#define MQEVENT_MBUTTON_MOVE		124
#define MQEVENT_MBUTTON_UP			125
#define MQEVENT_RBUTTON_DOWN		126
#define MQEVENT_RBUTTON_MOVE		127
#define MQEVENT_RBUTTON_UP			128
#define MQEVENT_MOUSE_MOVE			129
#define MQEVENT_MOUSE_WHEEL			130
#define MQEVENT_KEY_DOWN			140
#define MQEVENT_KEY_UP				141
#define MQEVENT_NEW_DOCUMENT		200
#define MQEVENT_END_DOCUMENT		201
#define MQEVENT_SAVE_DOCUMENT		202
#define MQEVENT_UNDO				210
#define MQEVENT_REDO				211
#define MQEVENT_UNDO_UPDATED		212
#define MQEVENT_OBJECT_LIST			220
#define MQEVENT_OBJECT_MODIFIED		221
#define MQEVENT_OBJECT_SELECTED		222
#define MQEVENT_MATERIAL_LIST		230
#define MQEVENT_MATERIAL_MODIFIED	231
#define MQEVENT_SCENE				240

// MQ_SendMessage
#define MQMESSAGE_ACTIVATE 				100
#define MQMESSAGE_USER_MESSAGE			101
#define MQMESSAGE_NEW_DRAW_OBJECT		200
#define MQMESSAGE_NEW_DRAW_MATERIAL		201
#define MQMESSAGE_DELETE_DRAW_OBJECT	210
#define MQMESSAGE_DELETE_DRAW_MATERIAL	211
#define MQMESSAGE_GET_UNDO_STATE		300
#define MQMESSAGE_UPDATE_UNDO			301
#define MQMESSAGE_REDRAW_SCENE			400
#define MQMESSAGE_REDRAW_ALL_SCENE		401
#define MQMESSAGE_GET_SCENE_OPTION		410
#define MQMESSAGE_HIT_TEST				411		// new in Rev2.49
#define MQMESSAGE_GET_EDIT_OPTION		500
#define MQMESSAGE_GET_SNAPPED_POS		501
#define MQMESSAGE_GET_RESOURCE_CURSOR	502
#define MQMESSAGE_SET_MOUSE_CURSOR		603
#define MQMESSAGE_SET_STATUS_STRING		604		// new in Rev2.49

// MQ_ShowFileDialog
#define MQFILE_TYPE_LEFT       0
#define MQFILE_TYPE_RIGHT      1
#define MQFILE_TYPE_UP         2
#define MQFILE_TYPE_DOWN       3
#define MQFILE_TYPE_FRONT      4
#define MQFILE_TYPE_BACK       5

// MQ_GetSystemPath
#define MQFOLDER_ROOT          1
#define MQFOLDER_METASEQ_EXE   2
#define MQFOLDER_METASEQ_INI   3
#define MQFOLDER_DATA          4
#define MQFOLDER_PLUGINS       5

// MQDoc_ClearSelect
#define MQDOC_CLEARSELECT_VERTEX  1
#define MQDOC_CLEARSELECT_LINE    2
#define MQDOC_CLEARSELECT_FACE    4
#define MQDOC_CLEARSELECT_ALL     7

// MQDoc_FindMappingFile
#define MQMAPPING_TEXTURE   1
#define MQMAPPING_ALPHA     2
#define MQMAPPING_BUMP      3

// MQDoc_CreateUserData
#define MQUSERDATA_OBJECT	1
#define MQUSERDATA_MATERIAL 2
#define MQUSERDATA_VERTEX   3
#define MQUSERDATA_FACE     4

// MQScene_IntValue/MQScene_FloatValue
#define MQSCENE_GET_CAMERA_POS   		0x101
#define MQSCENE_GET_CAMERA_ANGLE 		0x102
#define MQSCENE_GET_LOOK_AT_POS   		0x103
#define MQSCENE_GET_ROTATION_CENTER		0x104
#define MQSCENE_GET_FOV					0x105
#define MQSCENE_GET_DIRECTIONAL_LIGHT	0x106
#define MQSCENE_GET_AMBIENT_COLOR		0x107
#define MQSCENE_SET_CAMERA_POS   		0x201
#define MQSCENE_SET_CAMERA_ANGLE 		0x202
#define MQSCENE_SET_LOOK_AT_POS   		0x203
#define MQSCENE_SET_ROTATION_CENTER		0x204
#define MQSCENE_SET_FOV					0x205
#define MQSCENE_SET_DIRECTIONAL_LIGHT	0x206
#define MQSCENE_SET_AMBIENT_COLOR		0x207
#define MQSCENE_CONVERT_3D_TO_SCREEN	0x300
#define MQSCENE_CONVERT_SCREEN_TO_3D	0x301
#define MQSCENE_ADD_MULTILIGHT			0x400 // new in Rev3.11
#define MQSCENE_DELETE_MULTILIGHT		0x401 // new in Rev3.11
#define MQSCENE_GET_MULTILIGHT_NUMBER	0x402 // new in Rev3.11
#define MQSCENE_SET_MULTILIGHT_INDEX	0x403 // new in Rev3.11
#define MQSCENE_GET_MULTILIGHT_DIR		0x404 // new in Rev3.11
#define MQSCENE_SET_MULTILIGHT_DIR		0x405 // new in Rev3.11
#define MQSCENE_GET_MULTILIGHT_COLOR	0x406 // new in Rev3.11
#define MQSCENE_SET_MULTILIGHT_COLOR	0x407 // new in Rev3.11

// MQObj_GetType
#define MQOBJECT_TYPE_NORMAL              0
#define MQOBJECT_TYPE_POINT_LIGHT         1
#define MQOBJECT_TYPE_DIRECTIONAL_LIGHT   2

// MQObj_Freeze
#define MQOBJECT_FREEZE_PATCH    0x00000001
#define MQOBJECT_FREEZE_MIRROR   0x00000002
#define MQOBJECT_FREEZE_LATHE    0x00000004
#define MQOBJECT_FREEZE_ALL      0x7FFFFFFF

// MQObj_GetPatchType, MQObj_SetPatchType
#define MQOBJECT_PATCH_MAX       3
#define MQOBJECT_PATCH_NONE      0
#define MQOBJECT_PATCH_SPLINE1   1
#define MQOBJECT_PATCH_SPLINE2   2
#define MQOBJECT_PATCH_CATMULL   3

// MQObj_GetShading, MQObj_SetShading
#define MQOBJECT_SHADE_MAX       1
#define MQOBJECT_SHADE_FLAT      0
#define MQOBJECT_SHADE_GOURAUD   1

// MQObj_GetMirrorType, MQObj_SetMirrorType
#define MQOBJECT_MIRROR_MAX      2
#define MQOBJECT_MIRROR_NONE     0
#define MQOBJECT_MIRROR_NORMAL   1
#define MQOBJECT_MIRROR_JOIN     2

// MQObj_GetMirrorAxis, MQObj_SetMirrorAxis
#define MQOBJECT_MIRROR_AXIS_X   1
#define MQOBJECT_MIRROR_AXIS_Y   2
#define MQOBJECT_MIRROR_AXIS_Z   4

// MQObj_GetLatheType, MQObj_SetLatheType
#define MQOBJECT_LATHE_MAX       3
#define MQOBJECT_LATHE_NONE      0
#define MQOBJECT_LATHE_FRONT     1
#define MQOBJECT_LATHE_BACK      2
#define MQOBJECT_LATHE_BOTH      3

// MQObj_GetLatheAxis, MQObj_SetLatheAxis
#define MQOBJECT_LATHE_X         0
#define MQOBJECT_LATHE_Y         1
#define MQOBJECT_LATHE_Z         2


// MQMat_GetShader, MQMat_SetShader
#define MQMATERIAL_SHADER_CLASSIC      0
#define MQMATERIAL_SHADER_CONSTANT     1
#define MQMATERIAL_SHADER_LAMBERT      2
#define MQMATERIAL_SHADER_PHONG        3
#define MQMATERIAL_SHADER_BLINN        4

// MQMat_GetVertexColor, MQMat_SetVertexColor
#define MQMATERIAL_VERTEXCOLOR_DISABLE		0
#define MQMATERIAL_VERTEXCOLOR_DIFFUSE		1

// MQMat_GetMappingType, MQMat_SetMappingType
#define MQMATERIAL_PROJECTION_UV			0
#define MQMATERIAL_PROJECTION_FLAT			1
#define MQMATERIAL_PROJECTION_CYLINDER		2
#define MQMATERIAL_PROJECTION_SPHERE		3


// MQObj_GetIntValue, MQObj_SetIntValue
// MQObj_GetFloatArray, MQObj_SetFloatArray
#define MQOBJ_ID_DEPTH	 				0x101  // Int Value
#define MQOBJ_ID_FOLDING 				0x102  // Int Value
#define MQOBJ_ID_LOCKING				0x103  // Int Value
#define MQOBJ_ID_UNIQUE_ID 				0x104  // Int Value
#define MQOBJ_ID_TYPE	 				0x105  // Int Value : new in Rev3.00
#define MQOBJ_ID_SELECTED				0x106  // Int Value : new in Rev3.10
#define MQOBJ_ID_PATCH_TRIANGLE			0x107  // Int Value : new in Rev3.10
#define MQOBJ_ID_COLOR	 				0x201  // Float Array
#define MQOBJ_ID_COLOR_VALID			0x201  // Int Value
#define MQOBJ_ID_SCALING 				0x301  // Float Array
#define MQOBJ_ID_ROTATION				0x302  // Float Array
#define MQOBJ_ID_TRANSLATION 			0x303  // Float Array
#define MQOBJ_ID_LOCAL_MATRIX 			0x304  // Float Array
#define MQOBJ_ID_LOCAL_INVERSE_MATRIX 	0x305  // Float Array (get only)
#define MQOBJ_ID_LIGHT_VALUE			0x401  // Float Value : new in Rev3.00
#define MQOBJ_ID_LIGHT_ATTENUATION		0x402  // Int Value   : new in Rev3.00
#define MQOBJ_ID_LIGHT_FALLOFF_END		0x403  // Float Value : new in Rev3.00
#define MQOBJ_ID_LIGHT_FALLOFF_HALF		0x404  // Float Value : new in Rev3.00

// MQMat_GetIntValue, MQMat_SetIntValue
// MQMat_GetFloatArray, MQMat_SetFloatArray
#define MQMAT_ID_SHADER 				0x101  // Int Value
#define MQMAT_ID_VERTEXCOLOR    		0x102  // Int Value
#define MQMAT_ID_UNIQUE_ID 				0x103  // Int Value
#define MQMAT_ID_DOUBLESIDED			0x104  // Int Value : new in Rev3.10
#define MQMAT_ID_SELECTED				0x106  // Int Value : new in Rev3.10
#define MQMAT_ID_MAPPROJ 				0x301  // Int Value
#define MQMAT_ID_MAPPROJ_POSITION 		0x302  // Float Array
#define MQMAT_ID_MAPPROJ_SCALING		0x303  // Float Array
#define MQMAT_ID_MAPPROJ_ANGLE 			0x304  // Float Array

// MQMatrix_FloatValue
#define MQMATRIX_GET_SCALING			0x101
#define MQMATRIX_GET_ROTATION			0x102
#define MQMATRIX_GET_TRANSLATION		0x103
#define MQMATRIX_GET_INVERSE_TRANSFORM	0x105
#define MQMATRIX_SET_TRANSFORM			0x204
#define MQMATRIX_SET_INVERSE_TRANSFORM	0x205

// MQXmlElem_Value
#define MQXMLELEM_ADD_CHILD_ELEMENT		0x101
#define MQXMLELEM_REMOVE_CHILD_ELEMENT	0x102
#define MQXMLELEM_FIRST_CHILD_ELEMENT	0x201
#define MQXMLELEM_NEXT_CHILD_ELEMENT 	0x202
#define MQXMLELEM_GET_PARENT_ELEMENT 	0x203
#define MQXMLELEM_GET_NAME				0x301
#define MQXMLELEM_GET_TEXT		 		0x302
#define MQXMLELEM_GET_ATTRIBUTE			0x303
#define MQXMLELEM_SET_TEXT				0x402
#define MQXMLELEM_SET_ATTRIBUTE			0x403



typedef BYTE MQBool;

//
// struct MQPoint
//
typedef struct MQPoint
{
public:
	float x,y,z;

	// constructor
	inline MQPoint() { }
	inline MQPoint(float nx, float ny, float nz) {x=nx; y=ny; z=nz;}

	// operator
	inline MQPoint& operator = (const MQPoint& p)
		{x=p.x; y=p.y; z=p.z; return *this;}
	inline MQPoint& operator = (const float& s)
		{x=y=z=s; return *this;}
	inline MQPoint& operator += (const MQPoint& p)
		{x+=p.x; y+=p.y; z+=p.z; return *this;}
	inline MQPoint& operator += (const float& s)
		{x+=s; y+=s; z+=s; return *this;}
	inline MQPoint& operator -= (const MQPoint& p)
		{x-=p.x; y-=p.y; z-=p.z; return *this;}
	inline MQPoint& operator -= (const float& s)
		{x-=s; y-=s; z-=s; return *this;}
	inline MQPoint& operator *= (const MQPoint& p)
		{x*=p.x; y*=p.y; z*=p.z; return *this;}
	inline MQPoint& operator *= (float s)
		{x*=s; y*=s; z*=s; return *this;}
	inline MQPoint& operator /= (float s)
		{x/=s; y/=s; z/=s; return *this;}
	inline MQPoint operator + () const {return *this;}
	inline MQPoint operator - () const {return MQPoint(-x,-y,-z);}
	friend inline MQPoint operator + (const MQPoint& p1, const MQPoint& p2)
		{return MQPoint(p1.x+p2.x, p1.y+p2.y, p1.z+p2.z);}
	friend inline MQPoint operator + (const MQPoint& p, const float& s)
		{return MQPoint(p.x+s, p.y+s, p.z+s);}
	friend inline MQPoint operator + (const float& s, const MQPoint& p)
		{return MQPoint(p.x+s, p.y+s, p.z+s);}
	friend inline MQPoint operator - (const MQPoint& p1, const MQPoint& p2)
		{return MQPoint(p1.x-p2.x, p1.y-p2.y, p1.z-p2.z);}
	friend inline MQPoint operator - (const MQPoint& p, const float& s)
		{return MQPoint(p.x-s, p.y-s, p.z-s);}
	friend inline MQPoint operator - (const float& s, const MQPoint& p)
		{return MQPoint(s-p.x, s-p.y, s-p.z);}
	friend inline MQPoint operator * (const MQPoint& p1, const MQPoint& p2)
		{return MQPoint(p1.x*p2.x, p1.y*p2.y, p1.z*p2.z);}
	friend inline MQPoint operator * (const MQPoint& p, const float& s)
		{return MQPoint(p.x*s, p.y*s, p.z*s);}
	friend inline MQPoint operator * (const float& s, const MQPoint& p)
		{return MQPoint(p.x*s, p.y*s, p.z*s);}
	friend inline MQPoint operator / (const MQPoint& p, const float& s)
		{return MQPoint(p.x/s, p.y/s, p.z/s);}
	friend inline bool operator == (const MQPoint& p1, const MQPoint& p2)
		{return (p1.x==p2.x && p1.y==p2.y && p1.z==p2.z);}
	friend inline bool operator != (const MQPoint& p1, const MQPoint& p2)
		{return (p1.x!=p2.x || p1.y!=p2.y || p1.z!=p2.z);}

	inline void zero() { x=y=z=0.0f; }
	inline void one() { x=y=z=1.0f; }
	inline float norm() const { return x*x + y*y + z*z; }
	inline float abs() const { return (float)sqrt(norm()); }
	inline void normalize() {
		float a = abs();
		if(a > 0.0f) *this /= a;
		else zero();
	}
} MQPoint;


//
// struct MQColor
//
typedef struct MQColor
{
	float r,g,b;
public:
	inline MQColor() {}
	inline MQColor(float value) { r=g=b=value; }
	inline MQColor(float nr, float ng, float nb) { r=nr; g=ng; b=nb; }

	friend inline MQColor operator + (const MQColor& c1, const MQColor& c2)
		{return MQColor(c1.r+c2.r, c1.g+c2.g, c1.b+c2.b);}
	friend inline MQColor operator + (const MQColor& c, const float& s)
		{return MQColor(c.r+s, c.g+s, c.b+s);}
	friend inline MQColor operator + (const float& s, const MQColor& c)
		{return MQColor(c.r+s, c.g+s, c.b+s);}
	friend inline MQColor operator - (const MQColor& c1, const MQColor& c2)
		{return MQColor(c1.r-c2.r, c1.g-c2.g, c1.b-c2.b);}
	friend inline MQColor operator - (const MQColor& c, const float& s)
		{return MQColor(c.r-s, c.g-s, c.b-s);}
	friend inline MQColor operator - (const float& s, const MQColor& c)
		{return MQColor(s-c.r, s-c.g, s-c.b);}
	friend inline MQColor operator * (const MQColor& c1, const MQColor& c2)
		{return MQColor(c1.r*c2.r, c1.g*c2.g, c1.b*c2.b);}
	friend inline MQColor operator * (const MQColor& c, const float& s)
		{return MQColor(c.r*s, c.g*s, c.b*s);}
	friend inline MQColor operator * (const float& s, const MQColor& c)
		{return MQColor(c.r*s, c.g*s, c.b*s);}
	friend inline bool operator == (const MQColor& c1, const MQColor& c2)
		{return (c1.r==c2.r && c1.g==c2.g && c1.b==c2.b);}
	friend inline bool operator != (const MQColor& c1, const MQColor& c2)
		{return (c1.r!=c2.r || c1.g!=c2.g || c1.b!=c2.b);}
} MQColor;


//
// struct MQCoordinate
//
typedef struct MQCoordinate
{
	float u,v;
public:
	inline MQCoordinate() {}
	inline MQCoordinate(float nu, float nv) { u=nu; v=nv; }

	inline MQCoordinate& operator += (const MQCoordinate& p)
		{u+=p.u; v+=p.v; return *this;}
	inline MQCoordinate& operator += (const float& s)
		{u+=s; v+=s; return *this;}
	inline MQCoordinate& operator -= (const MQCoordinate& p)
		{u-=p.u; v-=p.v; return *this;}
	inline MQCoordinate& operator -= (const float& s)
		{u-=s; v-=s; return *this;}
	inline MQCoordinate& operator *= (const MQCoordinate& p)
		{u*=p.u; v*=p.v; return *this;}
	inline MQCoordinate& operator *= (float s)
		{u*=s; v*=s; return *this;}
	inline MQCoordinate& operator /= (float s)
		{u/=s; v/=s; return *this;}
	inline MQCoordinate operator + () const {return *this;}
	inline MQCoordinate operator - () const {return MQCoordinate(-u,-v);}
	friend inline MQCoordinate operator + (const MQCoordinate& p1, const MQCoordinate& p2)
		{return MQCoordinate(p1.u+p2.u, p1.v+p2.v);}
	friend inline MQCoordinate operator + (const MQCoordinate& p, const float& s)
		{return MQCoordinate(p.u+s, p.v+s);}
	friend inline MQCoordinate operator + (const float& s, const MQCoordinate& p)
		{return MQCoordinate(p.u+s, p.v+s);}
	friend inline MQCoordinate operator - (const MQCoordinate& p1, const MQCoordinate& p2)
		{return MQCoordinate(p1.u-p2.u, p1.v-p2.v);}
	friend inline MQCoordinate operator - (const MQCoordinate& p, const float& s)
		{return MQCoordinate(p.u-s, p.v-s);}
	friend inline MQCoordinate operator - (const float& s, const MQCoordinate& p)
		{return MQCoordinate(s-p.u, s-p.v);}
	friend inline MQCoordinate operator * (const MQCoordinate& p1, const MQCoordinate& p2)
		{return MQCoordinate(p1.u*p2.u, p1.v*p2.v);}
	friend inline MQCoordinate operator * (const MQCoordinate& p, const float& s)
		{return MQCoordinate(p.u*s, p.v*s);}
	friend inline MQCoordinate operator * (const float& s, const MQCoordinate& p)
		{return MQCoordinate(p.u*s, p.v*s);}
	friend inline MQCoordinate operator / (const MQCoordinate& p, const float& s)
		{return MQCoordinate(p.u/s, p.v/s);}
	friend inline MQCoordinate operator / (const MQCoordinate& p1, const MQCoordinate& p2)
		{return MQCoordinate(p1.u/p2.u, p1.v/p2.v);}
	friend inline bool operator == (const MQCoordinate& p1, const MQCoordinate& p2)
		{return (p1.u==p2.u && p1.v==p2.v);}
	friend inline bool operator != (const MQCoordinate& p1, const MQCoordinate& p2)
		{return (p1.u!=p2.u || p1.v!=p2.v);}

	inline void zero() { u=v=0.0f; }
	inline void one() { u=v=1.0f; }
} MQCoordinate;


//
// struct MQAngle
//
typedef struct MQAngle
{
	float head;
	union {
		float pich;
		float pitch;
	};
	float bank;

	inline MQAngle() {}
	inline MQAngle(float h, float p, float b) { head=h; pich=p; bank=b; }
} MQAngle;


//
// class MQMatrix
//
class MQMatrix
{
public:
	union {
		float t[16];
		float d[4][4];
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
	};

	// operator
	friend inline MQMatrix operator + (const MQMatrix& m1, const MQMatrix& m2)
	{
		MQMatrix m0;
		for(int i=0; i<16; i++) m0.t[i] = m1.t[i] + m2.t[i];
		return m0;
	}
	friend inline MQMatrix operator * (const MQMatrix& m1, const MQMatrix& m2)
	{
		MQMatrix m0;
		for(int i=0; i<4; i++)
			for(int j=0; j<4; j++)
				m0.d[i][j] =
					m1.d[i][0]*m2.d[0][j] + m1.d[i][1]*m2.d[1][j] +
					m1.d[i][2]*m2.d[2][j] + m1.d[i][3]*m2.d[3][j];
		return m0;
	}
	friend inline MQPoint operator * (const MQPoint& qp, const MQMatrix& m)
	{
		return MQPoint(
			qp.x*m._11 + qp.y*m._21 + qp.z*m._31 + m._41,
			qp.x*m._12 + qp.y*m._22 + qp.z*m._32 + m._42,
			qp.x*m._13 + qp.y*m._23 + qp.z*m._33 + m._43 );
	}
	inline MQMatrix& operator *= (const MQMatrix mat) { *this = (*this * mat); return *this; }

	inline MQMatrix() {}
	inline MQMatrix(const float *value){
		for (int i=0; i<16; i++)
			t[i] = value[i];
	}

	void Identify(void)
	{
		for (int i=0; i<4; i++){
			for (int j=0; j<4; j++){
				d[i][j] = (i == j) ? 1.0f : 0.0f;
			}
		}
	}
	MQPoint Mult3(const MQPoint& p) const
	{
		return MQPoint(
			p.x*_11 + p.y*_21 + p.z*_31,
			p.x*_12 + p.y*_22 + p.z*_32,
			p.x*_13 + p.y*_23 + p.z*_33 );
	}
	void Transpose3(void)
	{
		float v12 = _12;
		float v13 = _13;
		float v21 = _21;
		float v23 = _23;
		float v31 = _31;
		float v32 = _32;
		_12 = v21;
		_13 = v31;
		_21 = v12;
		_23 = v32;
		_31 = v13;
		_32 = v23;
	}
	MQPoint GetRow3(int r) const
	{
		return MQPoint(d[r][0], d[r][1], d[r][2]);
	}
	MQPoint GetColumn3(int c) const
	{
		return MQPoint(d[0][c], d[1][c], d[2][c]);
	}
	void SetRow3(int r, const MQPoint& p)
	{
		d[r][0] = p.x;
		d[r][1] = p.y;
		d[r][2] = p.z;
	}
	void SetColumn3(int c, const MQPoint& p)
	{
		d[0][c] = p.x;
		d[1][c] = p.y;
		d[2][c] = p.z;
	}

#if MQPLUGIN_VERSION >= 0x0240
	MQPoint GetScaling() const;
	MQAngle GetRotation() const;
	MQPoint GetTranslation() const;
	void SetTransform(const MQPoint *scaling, const MQAngle *rotation, const MQPoint *trans);
	void SetInverseTransform(const MQPoint *scaling, const MQAngle *rotation, const MQPoint *trans);
#endif
};


//
// struct MQFileDialogInfo
//
typedef struct {
	DWORD dwSize;
	int type;
	float scale;
	const char *softname;
	int axis_x;
	int axis_y;
	int axis_z;
} MQFileDialogInfo;


//
// struct MQUserDataInfo
//
struct MQUserDataInfo {
	DWORD dwSize;
	DWORD productID;
	DWORD pluginID;
	char identifier[16];
	int userdata_type;
	int bytes_per_element;
	bool create;

	MQUserDataInfo(){
		memset(this, 0, sizeof(MQUserDataInfo));
		dwSize = sizeof(MQUserDataInfo);
	}
};

//
// struct MQSendMessageInfo
//
struct MQSendMessageInfo {
	DWORD Product;
	DWORD ID;
	int index;
	void *option;

	MQSendMessageInfo(){
		Product = 0;
		ID = 0;
		index = 0;
		option = NULL;
	}
};


//
// struct MQSelectVertex
//
typedef struct MQSelectVertex
{
	int object; // index of object
	int vertex; // index of vertex

	inline MQSelectVertex() {}
	inline MQSelectVertex(int i, int j) { object=i; vertex=j; }
	friend inline bool operator == (const MQSelectVertex& l1, const MQSelectVertex& l2)
		{return (l1.object==l2.object && l1.vertex==l2.vertex);}
	friend inline bool operator != (const MQSelectVertex& l1, const MQSelectVertex& l2)
		{return (l1.object!=l2.object || l1.vertex!=l2.vertex);}
} MQSelectVertex;


//
// struct MQSelectLine
//
typedef struct MQSelectLine
{
	int object; // index of object
	int face;   // index of face
	int line;   // index of line

	inline MQSelectLine() {}
	inline MQSelectLine(int i, int j, int k) { object=i; face=j; line=k; }
	friend inline bool operator == (const MQSelectLine& l1, const MQSelectLine& l2)
		{return (l1.object==l2.object && l1.face==l2.face && l1.line==l2.line);}
	friend inline bool operator != (const MQSelectLine& l1, const MQSelectLine& l2)
		{return (l1.object!=l2.object || l1.face!=l2.face || l1.line!=l2.line);}
} MQSelectLine;


//
// struct MQSelectFace
//
typedef struct MQSelectFace
{
	int object; // index of object
	int face;   // index of face

	inline MQSelectFace() {}
	inline MQSelectFace(int i, int j) { object=i; face=j; }
	friend inline bool operator == (const MQSelectFace& l1, const MQSelectFace& l2)
		{return (l1.object==l2.object && l1.face==l2.face);}
	friend inline bool operator != (const MQSelectFace& l1, const MQSelectFace& l2)
		{return (l1.object!=l2.object || l1.face!=l2.face);}
} MQSelectFace;



class MQCDocument;
#if MQPLUGIN_VERSION >= 0x0210
class MQCScene;
#endif
class MQCObject;
class MQCMaterial;
#if MQPLUGIN_VERSION >= 0x0210
class MQCXmlElement;
#endif

typedef MQCDocument *MQDocument;
#if MQPLUGIN_VERSION >= 0x0210
typedef MQCScene *MQScene;
#endif
typedef MQCObject *MQObject;
typedef MQCMaterial *MQMaterial;
#if MQPLUGIN_VERSION >= 0x0240
typedef MQCXmlElement *MQXmlElement;
#endif


typedef BOOL (__stdcall *MQStationCallbackProc)(MQDocument doc, void *option);


#ifndef MQPLUGIN_EXPORTS

//
// plugin interface
//
MQPLUGIN_EXPORT DWORD MQCheckVersion(DWORD exe_version);
MQPLUGIN_EXPORT BOOL MQInit(const char *exe_name);
MQPLUGIN_EXPORT const char *MQGetPlugInName(void);
MQPLUGIN_EXPORT void MQGetPlugInID(DWORD *Product, DWORD *ID);
MQPLUGIN_EXPORT int MQGetPlugInType(void);
MQPLUGIN_EXPORT const char *MQEnumString(int index);
MQPLUGIN_EXPORT const char *MQEnumFileType(int index);
MQPLUGIN_EXPORT const char *MQEnumFileExt(int index);
MQPLUGIN_EXPORT BOOL MQExportFile(int index, const char *filename, MQDocument doc);
MQPLUGIN_EXPORT BOOL MQImportFile(int index, const char *filename, MQDocument doc);
MQPLUGIN_EXPORT BOOL MQCreate(int index, MQDocument doc);
MQPLUGIN_EXPORT BOOL MQModifyObject(int index, MQDocument doc);
MQPLUGIN_EXPORT BOOL MQModifySelect(int index, MQDocument doc);
MQPLUGIN_EXPORT BOOL MQOnEvent(MQDocument doc, int event_type, void *option);

//
// global function
//
extern HWND (__stdcall *MQ_GetWindowHandle)(void);
extern MQObject (__stdcall *MQ_CreateObject)(void);
extern MQMaterial (__stdcall *MQ_CreateMaterial)(void);
extern void (__stdcall *MQ_ShowFileDialog)(const char *title, MQFileDialogInfo *info);
extern void (__stdcall *MQ_ImportAxis)(MQFileDialogInfo *info, MQPoint *pts, int pts_count);
extern void (__stdcall *MQ_ExportAxis)(MQFileDialogInfo *info, MQPoint *pts, int pts_count);
#if MQPLUGIN_VERSION >= 0x0210
extern BOOL (__stdcall *MQ_LoadImage)(const char *filename, LPVOID *header, LPVOID *buffer, DWORD reserved);
extern BOOL (__stdcall *MQ_GetSystemPath)(char *buffer, int type);
#endif
#if MQPLUGIN_VERSION >= 0x0230
extern void (__stdcall *MQ_RefreshView)(void *reserved);
#endif
#if MQPLUGIN_VERSION >= 0x0240
extern void (__stdcall *MQ_StationCallback)(MQStationCallbackProc proc, void *option);
extern BOOL (__stdcall *MQ_SendMessage)(int message_type, MQSendMessageInfo *info);
#endif

//
// class MQDocument
//
extern int  (__stdcall *MQDoc_GetObjectCount)(MQDocument doc);
extern MQObject (__stdcall *MQDoc_GetObject)(MQDocument doc, int index);
#if MQPLUGIN_VERSION >= 0x0310
extern MQObject (__stdcall *MQDoc_GetObjectFromUniqueID)(MQDocument doc, int id);
#endif
extern int  (__stdcall *MQDoc_GetCurrentObjectIndex)(MQDocument doc);
extern void (__stdcall *MQDoc_SetCurrentObjectIndex)(MQDocument doc, int index);
extern int  (__stdcall *MQDoc_AddObject)(MQDocument doc, MQObject obj);
extern void (__stdcall *MQDoc_DeleteObject)(MQDocument doc, int index);
extern int  (__stdcall *MQDoc_GetObjectIndex)(MQDocument doc, MQObject obj);
#if MQPLUGIN_VERSION >= 0x0310
extern void (__stdcall *MQDoc_GetUnusedObjectName)(MQDocument doc, char *buffer, int buffer_size, const char *base_name);
#endif
extern int  (__stdcall *MQDoc_GetMaterialCount)(MQDocument doc);
extern MQMaterial (__stdcall *MQDoc_GetMaterial)(MQDocument doc, int index);
#if MQPLUGIN_VERSION >= 0x0310
extern MQMaterial (__stdcall *MQDoc_GetMaterialFromUniqueID)(MQDocument doc, int id);
#endif
extern int  (__stdcall *MQDoc_GetCurrentMaterialIndex)(MQDocument doc);
extern void (__stdcall *MQDoc_SetCurrentMaterialIndex)(MQDocument doc, int index);
extern int  (__stdcall *MQDoc_AddMaterial)(MQDocument doc, MQMaterial mat);
extern void (__stdcall *MQDoc_DeleteMaterial)(MQDocument doc, int index);
#if MQPLUGIN_VERSION >= 0x0310
extern void (__stdcall *MQDoc_GetUnusedMaterialName)(MQDocument doc, char *buffer, int buffer_size, const char *base_name);
#endif
extern void (__stdcall *MQDoc_Compact)(MQDocument doc);
extern void (__stdcall *MQDoc_ClearSelect)(MQDocument doc, DWORD flag);
extern BOOL (__stdcall *MQDoc_AddSelectVertex)(MQDocument doc, int objindex, int vertindex);
extern BOOL (__stdcall *MQDoc_DeleteSelectVertex)(MQDocument doc, int objindex, int vertindex);
extern BOOL (__stdcall *MQDoc_IsSelectVertex)(MQDocument doc, int objindex, int vertindex);
extern BOOL (__stdcall *MQDoc_AddSelectLine)(MQDocument doc, int objindex, int faceindex, int lineindex);
extern BOOL (__stdcall *MQDoc_DeleteSelectLine)(MQDocument doc, int objindex, int faceindex, int lineindex);
extern BOOL (__stdcall *MQDoc_IsSelectLine)(MQDocument doc, int objindex, int faceindex, int lineindex);
extern BOOL (__stdcall *MQDoc_AddSelectFace)(MQDocument doc, int objindex, int faceindex);
extern BOOL (__stdcall *MQDoc_DeleteSelectFace)(MQDocument doc, int objindex, int faceindex);
extern BOOL (__stdcall *MQDoc_IsSelectFace)(MQDocument doc, int objindex, int faceindex);
#if MQPLUGIN_VERSION >= 0x0230
extern BOOL (__stdcall *MQDoc_AddSelectUVVertex)(MQDocument doc, int objindex, int faceindex, int vertindex);
extern BOOL (__stdcall *MQDoc_DeleteSelectUVVertex)(MQDocument doc, int objindex, int faceindex, int vertindex);
extern BOOL (__stdcall *MQDoc_IsSelectUVVertex)(MQDocument doc, int objindex, int faceindex, int vertindex);
#endif
#if MQPLUGIN_VERSION >= 0x0210
extern BOOL (__stdcall *MQDoc_FindMappingFile)(MQDocument doc, char *out_path, const char *filename, DWORD map_type);
extern MQScene (__stdcall *MQDoc_GetScene)(MQDocument doc, int index);
#endif
#if MQPLUGIN_VERSION >= 0x0310
extern BOOL (__stdcall *MQDoc_GetMappingImage)(MQDocument doc, const char *filename, DWORD map_type, void **array);
#endif
#if MQPLUGIN_VERSION >= 0x0240
extern MQObject (__stdcall *MQDoc_GetParentObject)(MQDocument doc, MQObject obj);
extern int (__stdcall *MQDoc_GetChildObjectCount)(MQDocument doc, MQObject obj);
extern MQObject (__stdcall *MQDoc_GetChildObject)(MQDocument doc, MQObject obj, int index);
extern void (__stdcall *MQDoc_GetGlobalMatrix)(MQDocument doc, MQObject obj, float *matrix);
extern void (__stdcall *MQDoc_GetGlobalInverseMatrix)(MQDocument doc, MQObject obj, float *matrix);
#endif
#if MQPLUGIN_VERSION >= 0x0241
extern int  (__stdcall *MQDoc_InsertObject)(MQDocument doc, MQObject obj, MQObject before);
#endif
#if MQPLUGIN_VERSION >= 0x0310
extern int  (__stdcall *MQDoc_CreateUserData)(MQDocument doc, MQUserDataInfo *info);
extern void (__stdcall *MQDoc_DeleteUserData)(MQDocument doc, int userdata_type, int userdata_id);
#endif

//
// class MQScene
//
#if MQPLUGIN_VERSION >= 0x0210
extern void (__stdcall *MQScene_InitSize)(MQScene scene, int width, int height);
extern void (__stdcall *MQScene_GetProjMatrix)(MQScene scene, float *matrix);
extern void (__stdcall *MQScene_GetViewMatrix)(MQScene scene, float *matrix);
#endif
#if MQPLUGIN_VERSION >= 0x0240
extern void (__stdcall *MQScene_FloatValue)(MQScene scene, int type_id, float *values);
#endif
#if MQPLUGIN_VERSION >= 0x0241
extern BOOL (__stdcall *MQScene_GetVisibleFace)(MQScene scene, MQObject obj, BOOL *visible);
#endif
#if MQPLUGIN_VERSION >= 0x0311
extern void (__stdcall *MQScene_IntValue)(MQScene scene, int type_id, int *values);
#endif

//
// class MQObject
//
extern void (__stdcall *MQObj_Delete)(MQObject obj);
extern MQObject (__stdcall *MQObj_Clone)(MQObject obj);
extern void (__stdcall *MQObj_Merge)(MQObject dest, MQObject source);
extern void (__stdcall *MQObj_Freeze)(MQObject obj, DWORD flag);
extern void (__stdcall *MQObj_GetName)(MQObject obj, char *buffer, int size);
extern int  (__stdcall *MQObj_GetVertexCount)(MQObject obj);
extern void (__stdcall *MQObj_GetVertex)(MQObject obj, int index, MQPoint *pts);
extern void (__stdcall *MQObj_SetVertex)(MQObject obj, int index, MQPoint *pts);
extern void (__stdcall *MQObj_GetVertexArray)(MQObject obj, MQPoint *ptsarray);
extern int  (__stdcall *MQObj_GetFaceCount)(MQObject obj);
extern int  (__stdcall *MQObj_GetFacePointCount)(MQObject obj, int face);
extern void (__stdcall *MQObj_GetFacePointArray)(MQObject obj, int face, int *vertex);
extern void (__stdcall *MQObj_GetFaceCoordinateArray)(MQObject obj, int face, MQCoordinate *uvarray);
extern int  (__stdcall *MQObj_GetFaceMaterial)(MQObject obj, int face);
#if MQPLUGIN_VERSION >= 0x0240
extern UINT (__stdcall *MQObj_GetFaceUniqueID)(MQObject obj, int face);
extern int (__stdcall *MQObj_GetFaceIndexFromUniqueID)(MQObject obj, UINT unique_id);
#endif
extern void (__stdcall *MQObj_SetName)(MQObject obj, const char *buffer);
extern int  (__stdcall *MQObj_AddVertex)(MQObject obj, MQPoint *p);
extern BOOL (__stdcall *MQObj_DeleteVertex)(MQObject obj, int index, BOOL del_face);
extern int  (__stdcall *MQObj_GetVertexRefCount)(MQObject obj, int index);
#if MQPLUGIN_VERSION >= 0x0240
extern UINT (__stdcall *MQObj_GetVertexUniqueID)(MQObject obj, int index);
extern int (__stdcall *MQObj_GetVertexIndexFromUniqueID)(MQObject obj, UINT unique_id);
#endif
#if MQPLUGIN_VERSION >= 0x0300
extern int  (__stdcall *MQObj_GetVertexRelatedFaces)(MQObject obj, int vertex, int *faces);
#endif
//extern DWORD (__stdcall *MQObj_GetVertexColor)(MQObject obj, int index); // OBSOLETE
//extern void (__stdcall *MQObj_SetVertexColor)(MQObject obj, int index, DWORD color); // OBSOLETE
extern float (__stdcall *MQObj_GetVertexWeight)(MQObject obj, int index);
extern void (__stdcall *MQObj_SetVertexWeight)(MQObject obj, int index, float value);
extern void (__stdcall *MQObj_CopyVertexAttribute)(MQObject obj, int vert1, MQObject obj2, int vert2);
extern int  (__stdcall *MQObj_AddFace)(MQObject obj, int count, int *index);
extern BOOL (__stdcall *MQObj_DeleteFace)(MQObject obj, int index, BOOL del_vert);
extern BOOL (__stdcall *MQObj_InvertFace)(MQObject obj, int index);
extern void (__stdcall *MQObj_SetFaceMaterial)(MQObject obj, int face, int material);
extern void (__stdcall *MQObj_SetFaceCoordinateArray)(MQObject obj, int face, MQCoordinate *uvarray);
#if MQPLUGIN_VERSION >= 0x0230
extern DWORD (__stdcall *MQObj_GetFaceVertexColor)(MQObject obj, int face, int vertex);
extern void (__stdcall *MQObj_SetFaceVertexColor)(MQObject obj, int face, int vertex, DWORD color);
#endif
#if MQPLUGIN_VERSION >= 0x0310
extern float (__stdcall *MQObj_GetFaceEdgeCrease)(MQObject obj, int face, int line);
extern void (__stdcall *MQObj_SetFaceEdgeCrease)(MQObject obj, int face, int line, float crease);
#endif
#if MQPLUGIN_VERSION >= 0x0300
extern BOOL (__stdcall *MQObj_GetFaceVisible)(MQObject obj, int face);
extern void (__stdcall *MQObj_SetFaceVisible)(MQObject obj, int face, BOOL flag);
#endif
extern void (__stdcall *MQObj_OptimizeVertex)(MQObject obj, float distance, MQBool *apply);
extern void (__stdcall *MQObj_Compact)(MQObject obj);
extern DWORD (__stdcall *MQObj_GetVisible)(MQObject obj);
extern void (__stdcall *MQObj_SetVisible)(MQObject obj, DWORD visible);
extern DWORD (__stdcall *MQObj_GetPatchType)(MQObject obj);
extern void (__stdcall *MQObj_SetPatchType)(MQObject obj, DWORD type);
extern int  (__stdcall *MQObj_GetPatchSegment)(MQObject obj);
extern void (__stdcall *MQObj_SetPatchSegment)(MQObject obj, int segment);
#if MQPLUGIN_VERSION >= 0x0210
extern int  (__stdcall *MQObj_GetShading)(MQObject obj);
extern void (__stdcall *MQObj_SetShading)(MQObject obj, int type);
extern float (__stdcall *MQObj_GetSmoothAngle)(MQObject obj);
extern void (__stdcall *MQObj_SetSmoothAngle)(MQObject obj, float degree);
extern int  (__stdcall *MQObj_GetMirrorType)(MQObject obj);
extern void (__stdcall *MQObj_SetMirrorType)(MQObject obj, int type);
extern DWORD (__stdcall *MQObj_GetMirrorAxis)(MQObject obj);
extern void (__stdcall *MQObj_SetMirrorAxis)(MQObject obj, DWORD axis);
extern float (__stdcall *MQObj_GetMirrorDistance)(MQObject obj);
extern void (__stdcall *MQObj_SetMirrorDistance)(MQObject obj, float dis);
extern int  (__stdcall *MQObj_GetLatheType)(MQObject obj);
extern void (__stdcall *MQObj_SetLatheType)(MQObject obj, int type);
extern DWORD (__stdcall *MQObj_GetLatheAxis)(MQObject obj);
extern void (__stdcall *MQObj_SetLatheAxis)(MQObject obj, DWORD axis);
extern int  (__stdcall *MQObj_GetLatheSegment)(MQObject obj);
extern void (__stdcall *MQObj_SetLatheSegment)(MQObject obj, int segment);
#endif
#if MQPLUGIN_VERSION >= 0x0240
extern int (__stdcall *MQObj_GetIntValue)(MQObject obj, int type_id);
extern void (__stdcall *MQObj_GetFloatArray)(MQObject obj, int type_id, float *array);
extern void (__stdcall *MQObj_SetIntValue)(MQObject obj, int type_id, int value);
extern void (__stdcall *MQObj_SetFloatArray)(MQObject obj, int type_id, const float *array);
#endif
#if MQPLUGIN_VERSION >= 0x0310
extern BOOL (__stdcall *MQObj_AllocUserData)(MQObject obj, int userdata_id);
extern void (__stdcall *MQObj_FreeUserData)(MQObject obj, int userdata_id);
extern BOOL (__stdcall *MQObj_GetUserData)(MQObject obj, int userdata_id, int offset, int copy_bytes, void *buffer);
extern BOOL (__stdcall *MQObj_SetUserData)(MQObject obj, int userdata_id, int offset, int copy_bytes, const void *buffer);
extern BOOL (__stdcall *MQObj_AllocVertexUserData)(MQObject obj, int userdata_id);
extern void (__stdcall *MQObj_FreeVertexUserData)(MQObject obj, int userdata_id);
extern BOOL (__stdcall *MQObj_GetVertexUserData)(MQObject obj, int userdata_id, int vertex_start_index, int copy_vertex_num, int offset, int copy_bytes, void *buffer);
extern BOOL (__stdcall *MQObj_SetVertexUserData)(MQObject obj, int userdata_id, int vertex_start_index, int copy_vertex_num, int offset, int copy_bytes, const void *buffer);
extern BOOL (__stdcall *MQObj_AllocFaceUserData)(MQObject obj, int userdata_id);
extern void (__stdcall *MQObj_FreeFaceUserData)(MQObject obj, int userdata_id);
extern BOOL (__stdcall *MQObj_GetFaceUserData)(MQObject obj, int userdata_id, int face_start_index, int copy_face_num, int offset, int copy_bytes, void *buffer);
extern BOOL (__stdcall *MQObj_SetFaceUserData)(MQObject obj, int userdata_id, int face_start_index, int copy_face_num, int offset, int copy_bytes, const void *buffer);
#endif

//
// class MQMaterial
//
extern void (__stdcall *MQMat_Delete)(MQMaterial mat);
#if MQPLUGIN_VERSION >= 0x0230
extern int (__stdcall *MQMat_GetIntValue)(MQMaterial mat, int type_id);
extern void (__stdcall *MQMat_GetFloatArray)(MQMaterial mat, int type_id, float *array);
#endif
extern void (__stdcall *MQMat_GetName)(MQMaterial mat, char *buffer, int size);
extern void (__stdcall *MQMat_GetColor)(MQMaterial mat, MQColor *color);
extern float (__stdcall *MQMat_GetAlpha)(MQMaterial mat);
extern float (__stdcall *MQMat_GetDiffuse)(MQMaterial mat);
extern float (__stdcall *MQMat_GetAmbient)(MQMaterial mat);
extern float (__stdcall *MQMat_GetEmission)(MQMaterial mat);
extern float (__stdcall *MQMat_GetSpecular)(MQMaterial mat);
extern float (__stdcall *MQMat_GetPower)(MQMaterial mat);
extern void (__stdcall *MQMat_GetTextureName)(MQMaterial mat, char *buffer, int size);
extern void (__stdcall *MQMat_GetAlphaName)(MQMaterial mat, char *buffer, int size);
extern void (__stdcall *MQMat_GetBumpName)(MQMaterial mat, char *buffer, int size);
#if MQPLUGIN_VERSION >= 0x0230
extern void (__stdcall *MQMat_SetIntValue)(MQMaterial mat, int type_id, int value);
extern void (__stdcall *MQMat_SetFloatArray)(MQMaterial mat, int type_id, const float *array);
#endif
extern void (__stdcall *MQMat_SetName)(MQMaterial mat, const char *name);
extern void (__stdcall *MQMat_SetColor)(MQMaterial mat, MQColor *color);
extern void (__stdcall *MQMat_SetAlpha)(MQMaterial mat, float value);
extern void (__stdcall *MQMat_SetDiffuse)(MQMaterial mat, float value);
extern void (__stdcall *MQMat_SetAmbient)(MQMaterial mat, float value);
extern void (__stdcall *MQMat_SetEmission)(MQMaterial mat, float value);
extern void (__stdcall *MQMat_SetSpecular)(MQMaterial mat, float value);
extern void (__stdcall *MQMat_SetPower)(MQMaterial mat, float value);
extern void (__stdcall *MQMat_SetTextureName)(MQMaterial mat, const char *name);
extern void (__stdcall *MQMat_SetAlphaName)(MQMaterial mat, const char *name);
extern void (__stdcall *MQMat_SetBumpName)(MQMaterial mat, const char *name);
#if MQPLUGIN_VERSION >= 0x0310
extern BOOL (__stdcall *MQMat_AllocUserData)(MQMaterial mat, int userdata_id);
extern void (__stdcall *MQMat_FreeUserData)(MQMaterial mat, int userdata_id);
extern BOOL (__stdcall *MQMat_GetUserData)(MQMaterial mat, int userdata_id, int offset, int copy_bytes, void *buffer);
extern BOOL (__stdcall *MQMat_SetUserData)(MQMaterial mat, int userdata_id, int offset, int copy_bytes, const void *buffer);
#endif

//
// class MQMatrix
//
#if MQPLUGIN_VERSION >= 0x0240
extern void (__stdcall *MQMatrix_FloatValue)(float *mtx, int type_id, float *values);
#endif

//
// class MQXmlElement
//
#if MQPLUGIN_VERSION >= 0x0240
extern void (__stdcall *MQXmlElem_Value)(MQXmlElement elem, int type_id, void *values);
#endif



//
// class MQCDocument
//
class MQCDocument
{
public:
	int 		GetObjectCount(void);
	MQObject 	GetObject(int index);
#if MQPLUGIN_VERSION >= 0x0310
	MQObject 	GetObjectFromUniqueID(int id);
#endif
	int 		GetCurrentObjectIndex(void);
	void 		SetCurrentObjectIndex(int index);
	int 		AddObject(MQObject obj);
	void 		DeleteObject(int index);
	int 		GetObjectIndex(MQObject obj);
#if MQPLUGIN_VERSION >= 0x0310
	void		GetUnusedObjectName(char *buffer, int buffer_size);
	void		GetUnusedObjectName(char *buffer, int buffer_size, const char *base_name);
#endif
	int 		GetMaterialCount(void);
	MQMaterial 	GetMaterial(int index);
#if MQPLUGIN_VERSION >= 0x0310
	MQMaterial 	GetMaterialFromUniqueID(int id);
#endif
	int 		GetCurrentMaterialIndex(void);
	void 		SetCurrentMaterialIndex(int index);
	int 		AddMaterial(MQMaterial mat);
	void 		DeleteMaterial(int index);
#if MQPLUGIN_VERSION >= 0x0310
	void		GetUnusedMaterialName(char *buffer, int buffer_size);
	void		GetUnusedMaterialName(char *buffer, int buffer_size, const char *base_name);
#endif
	void 		Compact(void);
	void 		ClearSelect(DWORD flag);
	BOOL 		AddSelectVertex(int objindex, int vertindex);
	BOOL 		DeleteSelectVertex(int objindex, int vertindex);
	BOOL 		IsSelectVertex(int objindex, int vertindex);
	BOOL 		AddSelectVertex(MQSelectVertex sel);
	BOOL 		DeleteSelectVertex(MQSelectVertex sel);
	BOOL 		IsSelectVertex(MQSelectVertex sel);
	BOOL 		AddSelectLine(int objindex, int faceindex, int lineindex);
	BOOL 		DeleteSelectLine(int objindex, int faceindex, int lineindex);
	BOOL 		IsSelectLine(int objindex, int faceindex, int lineindex);
	BOOL 		AddSelectLine(MQSelectLine sel);
	BOOL 		DeleteSelectLine(MQSelectLine sel);
	BOOL 		IsSelectLine(MQSelectLine sel);
	BOOL 		AddSelectFace(int objindex, int faceindex);
	BOOL 		DeleteSelectFace(int objindex, int faceindex);
	BOOL 		IsSelectFace(int objindex, int faceindex);
	BOOL 		AddSelectFace(MQSelectFace sel);
	BOOL 		DeleteSelectFace(MQSelectFace sel);
	BOOL 		IsSelectFace(MQSelectFace sel);
#if MQPLUGIN_VERSION >= 0x0230
	BOOL 		AddSelectUVVertex(int objindex, int faceindex, int vertindex);
	BOOL 		DeleteSelectUVVertex(int objindex, int faceindex, int vertindex);
	BOOL 		IsSelectUVVertex(int objindex, int faceindex, int vertindex);
#endif
#if MQPLUGIN_VERSION >= 0x0210
	BOOL 		FindMappingFile(char *out_path, const char *filename, DWORD map_type);
	MQScene 	GetScene(int index);
#endif
#if MQPLUGIN_VERSION >= 0x0310
	BOOL		GetMappingImageSize(const char *filename, DWORD map_type, int& width, int& height);
#endif
#if MQPLUGIN_VERSION >= 0x0240
	MQObject	GetParentObject(MQObject obj);
	int			GetChildObjectCount(MQObject obj);
	MQObject	GetChildObject(MQObject obj, int index);
	void		GetGlobalMatrix(MQObject obj, MQMatrix& matrix);
	void		GetGlobalInverseMatrix(MQObject obj, MQMatrix& matrix);
#endif
#if MQPLUGIN_VERSION >= 0x0241
	int			InsertObject(MQObject obj, MQObject before);
#endif
#if MQPLUGIN_VERSION >= 0x0310
private:
	int  		CreateUserData(DWORD productID, DWORD pluginID, const char *identifier, int userdata_type, int bytes_per_object);
	int  		FindUserData(DWORD productID, DWORD pluginID, const char *identifier, int userdata_type);
public:
	int  		CreateObjectUserData(DWORD productID, DWORD pluginID, const char *identifier, int bytes_per_object);
	void		DeleteObjectUserData(int userdata_id);
	int  		FindObjectUserData(DWORD productID, DWORD pluginID, const char *identifier);
	int  		CreateVertexUserData(DWORD productID, DWORD pluginID, const char *identifier, int bytes_per_vertex);
	void		DeleteVertexUserData(int userdata_id);
	int  		FindVertexUserData(DWORD productID, DWORD pluginID, const char *identifier);
	int  		CreateFaceUserData(DWORD productID, DWORD pluginID, const char *identifier, int bytes_per_face);
	void		DeleteFaceUserData(int userdata_id);
	int  		FindFaceUserData(DWORD productID, DWORD pluginID, const char *identifier);
	int  		CreateMaterialUserData(DWORD productID, DWORD pluginID, const char *identifier, int bytes_per_material);
	void		DeleteMaterialUserData(int userdata_id);
	int  		FindMaterialUserData(DWORD productID, DWORD pluginID, const char *identifier);
#endif
};



#if MQPLUGIN_VERSION >= 0x0210
//
// class MQCScene
//
class MQCScene
{
public:
	void InitSize(int width, int height);
	void GetProjMatrix(float *matrix);
	void GetViewMatrix(float *matrix);
#if MQPLUGIN_VERSION >= 0x0240
	MQPoint GetCameraPosition();
	MQAngle GetCameraAngle();
	MQPoint GetLookAtPosition();
	MQPoint GetRotationCenter();
	float GetFOV();
	//MQPoint GetGlobalDirectionalLight(); // OBSOLETE in Rev3.11: Replaced with GetGlobalDirectionalLightDirection()
	MQColor GetGlobalAmbientColor();
	void SetCameraPosition(const MQPoint& p);
	void SetCameraAngle(const MQAngle& angle);
	void SetLookAtPosition(const MQPoint& p);
	void SetRotationCenter(const MQPoint& p);
	void SetFOV(float fov);
	//void SetGlobalDirectionalLight(const MQPoint& dir); // OBSOLETE in Rev3.11: Replaced with SetGlobalDirectionalLightDirection()
	void SetGlobalAmbientColor(const MQColor& amb);

	MQPoint Convert3DToScreen(const MQPoint& p, float *out_w = NULL);
	MQPoint ConvertScreenTo3D(const MQPoint& p);
#endif
#if MQPLUGIN_VERSION >= 0x0241
	BOOL GetVisibleFace(MQObject obj, BOOL *visible);
#endif
#if MQPLUGIN_VERSION >= 0x0311
	int AddGlobalDirectionalLight();
	BOOL DeleteGlobalDirectionalLight(int index);
	int GetGlobalDirectionalLightNum();
	MQPoint GetGlobalDirectionalLightDirection(int index);
	MQColor GetGlobalDirectionalLightColor(int index);
	void SetGlobalDirectionalLightDirection(int index, const MQPoint& dir);
	void SetGlobalDirectionalLightColor(int index, const MQColor& col);
#endif
};
#endif


//
// class MQCObject
//
class MQCObject
{
public:
	void 	DeleteThis(void);
	MQObject Clone(void);
	void 	Merge(MQObject source);
	void 	Freeze(DWORD flag);
	void 	GetName(char *buffer, int size);
	int  	GetVertexCount(void);
	MQPoint GetVertex(int index);
	void 	SetVertex(int index, MQPoint pts);
	void 	GetVertexArray(MQPoint *ptsarray);
	int  	AddVertex(MQPoint p);
	BOOL 	DeleteVertex(int index);
	int  	GetVertexRefCount(int index);
#if MQPLUGIN_VERSION >= 0x0240
	UINT  	GetVertexUniqueID(int index);
	int  	GetVertexIndexFromUniqueID(UINT unique_id);
#endif
#if MQPLUGIN_VERSION >= 0x0300
	int		GetVertexRelatedFaces(int vertex, int *faces);
#endif
	//DWORD 	GetVertexColor(int index); // OBSOLUTE
	//void 	SetVertexColor(int index, DWORD color); // OBSOLUTE
	float 	GetVertexWeight(int index);
	void 	SetVertexWeight(int index, float value);
	void 	CopyVertexAttribute(int vert1, MQObject obj2, int vert2);
	int  	GetFaceCount(void);
	int  	GetFacePointCount(int face);
	void 	GetFacePointArray(int face, int *vertex);
	void 	GetFaceCoordinateArray(int face, MQCoordinate *uvarray);
	int  	GetFaceMaterial(int face);
#if MQPLUGIN_VERSION >= 0x0240
	UINT  	GetFaceUniqueID(int face);
	int  	GetFaceIndexFromUniqueID(UINT unique_id);
#endif
	void 	SetName(const char *buffer);
	int  	AddFace(int count, int *index);
	BOOL 	DeleteFace(int index, bool delete_vertex=true);
	BOOL 	InvertFace(int index);
	void 	SetFaceMaterial(int face, int material);
	void 	SetFaceCoordinateArray(int face, MQCoordinate *uvarray);
#if MQPLUGIN_VERSION >= 0x0230
	DWORD  	GetFaceVertexColor(int face, int vertex);
	void  	SetFaceVertexColor(int face, int vertex, DWORD color);
#endif
#if MQPLUGIN_VERSION >= 0x0310
	float	GetFaceEdgeCrease(int face, int line);
	void	SetFaceEdgeCrease(int face, int line, float crease);
#endif
#if MQPLUGIN_VERSION >= 0x0300
	int		GetFaceVisible(int face);
	void	SetFaceVisible(int face, BOOL visible);
#endif
	void 	OptimizeVertex(float distance, MQBool *apply);
	void 	Compact(void);
	DWORD 	GetVisible(void);
	void 	SetVisible(DWORD visible);
	DWORD 	GetPatchType(void);
	void 	SetPatchType(DWORD type);
	int  	GetPatchSegment(void);
	void 	SetPatchSegment(int segment);
#if MQPLUGIN_VERSION >= 0x0310
	BOOL	GetPatchTriangle(void);
	void	SetPatchTriangle(BOOL flag);
#endif
#if MQPLUGIN_VERSION >= 0x0210
	int  	GetShading(void);
	void 	SetShading(int type);
	float 	GetSmoothAngle(void);
	void 	SetSmoothAngle(float degree);
	int  	GetMirrorType(void);
	void 	SetMirrorType(int type);
	DWORD 	GetMirrorAxis(void);
	void 	SetMirrorAxis(DWORD axis);
	float 	GetMirrorDistance(void);
	void 	SetMirrorDistance(float dis);
	int  	GetLatheType(void);
	void 	SetLatheType(int type);
	DWORD 	GetLatheAxis(void);
	void 	SetLatheAxis(DWORD axis);
	int  	GetLatheSegment(void);
	void 	SetLatheSegment(int segment);
#endif
#if MQPLUGIN_VERSION >= 0x0240
	UINT	GetUniqueID(void);
	int		GetDepth(void);
	void	SetDepth(int depth);
	BOOL	GetFolding(void);
	void	SetFolding(BOOL flag);
	BOOL	GetLocking(void);
	void	SetLocking(BOOL flag);
	MQColor	GetColor(void);
	void	SetColor(MQColor color);
	BOOL	GetColorValid(void);
	void	SetColorValid(BOOL flag);
	MQPoint	GetScaling(void);
	void	SetScaling(MQPoint scale);
	MQAngle	GetRotation(void);
	void	SetRotation(MQAngle angle);
	MQPoint	GetTranslation(void);
	void	SetTranslation(MQPoint trans);
	MQMatrix	GetLocalMatrix(void);
	void		SetLocalMatrix(const MQMatrix& mtx);
	MQMatrix	GetLocalInverseMatrix(void);
#endif
#if MQPLUGIN_VERSION >= 0x0300
	int		GetType(void);
	void	SetType(int type);
	float	GetLightValue(void);
	void	SetLightValue(float value);
	int		GetLightAttenuation(void);
	void	SetLightAttenuation(int value);
	float	GetLightFallOffEnd(void);
	void	SetLightFallOffEnd(float distance);
	float	GetLightFallOffHalf(void);
	void	SetLightFallOffHalf(float distance);
#endif
#if MQPLUGIN_VERSION >= 0x0310
	BOOL	GetSelected();
	void	SetSelected(BOOL flag);
	BOOL	AllocUserData(int userdata_id);
	void 	FreeUserData(int userdata_id);
	BOOL 	GetUserData(int userdata_id, void *buffer);
	BOOL 	GetUserDataPart(int userdata_id, int offset, int copy_bytes, void *buffer);
	BOOL 	SetUserData(int userdata_id, const void *buffer);
	BOOL 	SetUserDataPart(int userdata_id, int offset, int copy_bytes, const void *buffer);
	BOOL	AllocVertexUserData(int userdata_id);
	void 	FreeVertexUserData(int userdata_id);
	BOOL 	GetVertexUserData(int userdata_id, int vertex_index, void *buffer);
	BOOL 	GetVertexUserDataPart(int userdata_id, int vertex_start_index, int copy_vertex_num, int offset, int copy_bytes, void *buffer);
	BOOL 	SetVertexUserData(int userdata_id, int vertex_index, const void *buffer);
	BOOL 	SetVertexUserDataPart(int userdata_id, int vertex_start_index, int copy_vertex_num, int offset, int copy_bytes, const void *buffer);
	BOOL	AllocFaceUserData(int userdata_id);
	void 	FreeFaceUserData(int userdata_id);
	BOOL 	GetFaceUserData(int userdata_id, int face_index, void *buffer);
	BOOL 	GetFaceUserDataPart(int userdata_id, int face_start_index, int copy_face_num, int offset, int copy_bytes, void *buffer);
	BOOL 	SetFaceUserData(int userdata_id, int face_index, const void *buffer);
	BOOL 	SetFaceUserDataPart(int userdata_id, int face_start_index, int copy_face_num, int offset, int copy_bytes, const void *buffer);
#endif
};


//
// class MQCMaterial
//
class MQCMaterial
{
public:
	void 	DeleteThis(void);
	void 	GetName(char *buffer, int size);
#if MQPLUGIN_VERSION >= 0x0240
	UINT 	GetUniqueID(void);
#endif
	MQColor GetColor(void);
	float 	GetAlpha(void);
	float 	GetDiffuse(void);
	float 	GetAmbient(void);
	float 	GetEmission(void);
	float 	GetSpecular(void);
	float 	GetPower(void);
	void 	GetTextureName(char *buffer, int size);
	void 	GetAlphaName(char *buffer, int size);
	void 	GetBumpName(char *buffer, int size);
	void 	SetName(const char *name);
	void 	SetColor(MQColor color);
	void 	SetAlpha(float value);
	void 	SetDiffuse(float value);
	void 	SetAmbient(float value);
	void 	SetEmission(float value);
	void 	SetSpecular(float value);
	void 	SetPower(float value);
	void 	SetTextureName(const char *name);
	void 	SetAlphaName(const char *name);
	void 	SetBumpName(const char *name);
#if MQPLUGIN_VERSION >= 0x0230
	int 	GetShader(void);
	int 	GetVertexColor(void);
	int 	GetMappingType(void);
	MQPoint GetMappingPosition(void);
	MQPoint GetMappingScaling(void);
	MQAngle GetMappingAngle(void);
	void 	SetShader(int shader);
	void 	SetVertexColor(int value);
	void 	SetMappingType(int type);
	void 	SetMappingPosition(MQPoint pos);
	void 	SetMappingScaling(MQPoint scale);
	void 	SetMappingAngle(MQAngle angle);
#endif
#if MQPLUGIN_VERSION >= 0x0310
	BOOL	GetSelected(void);
	void	SetSelected(BOOL flag);
	BOOL	GetDoubleSided(void);
	void	SetDoubleSided(BOOL value);
	BOOL	AllocUserData(int userdata_id);
	void 	FreeUserData(int userdata_id);
	BOOL 	GetUserData(int userdata_id, void *buffer);
	BOOL 	GetUserDataPart(int userdata_id, int offset, int copy_bytes, void *buffer);
	BOOL 	SetUserData(int userdata_id, const void *buffer);
	BOOL 	SetUserDataPart(int userdata_id, int offset, int copy_bytes, const void *buffer);
#endif
};


//
// class MQCXmlElement
//
#if MQPLUGIN_VERSION >= 0x0240
class MQCXmlElement
{
public:
	MQXmlElement AddChildElement(const char *name);
	MQXmlElement AddChildElement(const wchar_t *name);
	BOOL RemoveChildElement(MQXmlElement child);

	MQXmlElement FirstChildElement(void);
	MQXmlElement FirstChildElement(const char *name);
	MQXmlElement FirstChildElement(const wchar_t *name);
	MQXmlElement NextChildElement(MQXmlElement child);
	MQXmlElement NextChildElement(const char *name, MQXmlElement child);
	MQXmlElement NextChildElement(const wchar_t *name, MQXmlElement child);
	MQXmlElement GetParentElement();

	std::string GetName(void);
	std::wstring GetNameW(void);
	std::string GetText(void);
	std::wstring GetTextW(void);
	BOOL GetText(std::string& result_value);
	BOOL GetText(std::wstring& result_value);
	std::string GetAttribute(const char *name);
	std::wstring GetAttribute(const wchar_t *name);
	BOOL GetAttribute(const char *name, std::string& result_value);
	BOOL GetAttribute(const wchar_t *name, std::wstring& result_value);

	void SetText(const char *text);
	void SetText(const wchar_t *text);
	void SetAttribute(const char *name, const char *value);
	void SetAttribute(const wchar_t *name, const wchar_t *value);

protected:
	std::string Utf8ToAnsi(const char *ptr);
	std::wstring Utf8ToWide(const char *ptr);
	std::string AnsiToUtf8(const char *ptr);
	std::string WideToUtf8(const wchar_t *ptr);
};
#endif



// class MQCDocument
inline int 		MQCDocument::GetObjectCount(void) 			{ return MQDoc_GetObjectCount(this); }
inline MQObject MQCDocument::GetObject(int index) 			{ return MQDoc_GetObject(this, index); }
#if MQPLUGIN_VERSION >= 0x0310
inline MQObject MQCDocument::GetObjectFromUniqueID(int id) 	{ return MQDoc_GetObjectFromUniqueID(this, id); }
#endif
inline int 		MQCDocument::GetCurrentObjectIndex(void) 	{ return MQDoc_GetCurrentObjectIndex(this); }
inline void 	MQCDocument::SetCurrentObjectIndex(int index) 	{ MQDoc_SetCurrentObjectIndex(this, index); }
inline int 		MQCDocument::AddObject(MQObject obj) 		{ return MQDoc_AddObject(this, obj); }
inline void 	MQCDocument::DeleteObject(int index) 		{ MQDoc_DeleteObject(this, index); }
inline int 		MQCDocument::GetObjectIndex(MQObject obj) 	{ return MQDoc_GetObjectIndex(this, obj); }
#if MQPLUGIN_VERSION >= 0x0310
inline void		MQCDocument::GetUnusedObjectName(char *buffer, int buffer_size) { return MQDoc_GetUnusedObjectName(this, buffer, buffer_size, NULL); }
inline void		MQCDocument::GetUnusedObjectName(char *buffer, int buffer_size, const char *base_name) { return MQDoc_GetUnusedObjectName(this, buffer, buffer_size, base_name); }
#endif
inline int 		MQCDocument::GetMaterialCount(void) 		{ return MQDoc_GetMaterialCount(this); }
inline MQMaterial MQCDocument::GetMaterial(int material) 	{ return MQDoc_GetMaterial(this, material); }
#if MQPLUGIN_VERSION >= 0x0310
inline MQMaterial MQCDocument::GetMaterialFromUniqueID(int id) 	{ return MQDoc_GetMaterialFromUniqueID(this, id); }
#endif
inline int 		MQCDocument::GetCurrentMaterialIndex(void) 		{ return MQDoc_GetCurrentMaterialIndex(this); }
inline void 	MQCDocument::SetCurrentMaterialIndex(int index) { MQDoc_SetCurrentMaterialIndex(this, index); }
inline int 		MQCDocument::AddMaterial(MQMaterial mat) 	{ return MQDoc_AddMaterial(this, mat); }
inline void 	MQCDocument::DeleteMaterial(int index) 		{ MQDoc_DeleteMaterial(this, index); }
#if MQPLUGIN_VERSION >= 0x0310
inline void		MQCDocument::GetUnusedMaterialName(char *buffer, int buffer_size) { return MQDoc_GetUnusedMaterialName(this, buffer, buffer_size, NULL); }
inline void		MQCDocument::GetUnusedMaterialName(char *buffer, int buffer_size, const char *base_name) { return MQDoc_GetUnusedMaterialName(this, buffer, buffer_size, base_name); }
#endif
inline void 	MQCDocument::Compact(void) 					{ MQDoc_Compact(this); }
inline void 	MQCDocument::ClearSelect(DWORD flag) 		{ MQDoc_ClearSelect(this, flag); }
inline BOOL 	MQCDocument::AddSelectVertex(int objindex, int vertindex) 		{ return MQDoc_AddSelectVertex(this, objindex, vertindex); }
inline BOOL 	MQCDocument::DeleteSelectVertex(int objindex, int vertindex) 	{ return MQDoc_DeleteSelectVertex(this, objindex, vertindex); }
inline BOOL 	MQCDocument::IsSelectVertex(int objindex, int vertindex) 		{ return MQDoc_IsSelectVertex(this, objindex, vertindex); }
inline BOOL 	MQCDocument::AddSelectVertex(MQSelectVertex sel) 				{ return MQDoc_AddSelectVertex(this, sel.object, sel.vertex); }
inline BOOL 	MQCDocument::DeleteSelectVertex(MQSelectVertex sel) 			{ return MQDoc_DeleteSelectVertex(this, sel.object, sel.vertex); }
inline BOOL 	MQCDocument::IsSelectVertex(MQSelectVertex sel) 				{ return MQDoc_IsSelectVertex(this, sel.object, sel.vertex); }
inline BOOL 	MQCDocument::AddSelectLine(int objindex, int faceindex, int lineindex) 		{ return MQDoc_AddSelectLine(this, objindex, faceindex, lineindex); }
inline BOOL 	MQCDocument::DeleteSelectLine(int objindex, int faceindex, int lineindex) 	{ return MQDoc_DeleteSelectLine(this, objindex, faceindex, lineindex); }
inline BOOL 	MQCDocument::IsSelectLine(int objindex, int faceindex, int lineindex) 		{ return MQDoc_IsSelectLine(this, objindex, faceindex, lineindex); }
inline BOOL 	MQCDocument::AddSelectLine(MQSelectLine sel) 								{ return MQDoc_AddSelectLine(this, sel.object, sel.face, sel.line); }
inline BOOL 	MQCDocument::DeleteSelectLine(MQSelectLine sel) 							{ return MQDoc_DeleteSelectLine(this, sel.object, sel.face, sel.line); }
inline BOOL 	MQCDocument::IsSelectLine(MQSelectLine sel) 								{ return MQDoc_IsSelectLine(this, sel.object, sel.face, sel.line); }
inline BOOL 	MQCDocument::AddSelectFace(int objindex, int faceindex) 					{ return MQDoc_AddSelectFace(this, objindex, faceindex); }
inline BOOL 	MQCDocument::DeleteSelectFace(int objindex, int faceindex) 					{ return MQDoc_DeleteSelectFace(this, objindex, faceindex); }
inline BOOL 	MQCDocument::IsSelectFace(int objindex, int faceindex) 						{ return MQDoc_IsSelectFace(this, objindex, faceindex); }
inline BOOL 	MQCDocument::AddSelectFace(MQSelectFace sel) 								{ return MQDoc_AddSelectFace(this, sel.object, sel.face); }
inline BOOL 	MQCDocument::DeleteSelectFace(MQSelectFace sel) 							{ return MQDoc_DeleteSelectFace(this, sel.object, sel.face); }
inline BOOL 	MQCDocument::IsSelectFace(MQSelectFace sel) 								{ return MQDoc_IsSelectFace(this, sel.object, sel.face); }
#if MQPLUGIN_VERSION >= 0x0230
inline BOOL 	MQCDocument::AddSelectUVVertex(int objindex, int faceindex, int vertindex)		{ return MQDoc_AddSelectUVVertex(this, objindex, faceindex, vertindex); }
inline BOOL 	MQCDocument::DeleteSelectUVVertex(int objindex, int faceindex, int vertindex)	{ return MQDoc_DeleteSelectUVVertex(this, objindex, faceindex, vertindex); }
inline BOOL 	MQCDocument::IsSelectUVVertex(int objindex, int faceindex, int vertindex)		{ return MQDoc_IsSelectUVVertex(this, objindex, faceindex, vertindex); }
#endif
#if MQPLUGIN_VERSION >= 0x0210
inline BOOL 	MQCDocument::FindMappingFile(char *out_path, const char *filename, DWORD map_type) { return MQDoc_FindMappingFile(this, out_path, filename, map_type); }
inline MQScene 	MQCDocument::GetScene(int index) 	{ return MQDoc_GetScene(this, index); }
#endif
#if MQPLUGIN_VERSION >= 0x0310
inline BOOL		MQCDocument::GetMappingImageSize(const char *filename, DWORD map_type, int& width, int& height)
{
	void *array[5];
	int bpp;
	void *buffer;
	array[0] = &width;
	array[1] = &height;
	array[2] = &bpp;
	array[3] = NULL;
	array[4] = &buffer;

	if(!MQDoc_GetMappingImage(this, filename, map_type, array)){
		width = height = 0;
		return FALSE;
	}
	return TRUE;
}
#endif
#if MQPLUGIN_VERSION >= 0x0240
inline MQObject	MQCDocument::GetParentObject(MQObject obj) 					{ return MQDoc_GetParentObject(this, obj); }
inline int		MQCDocument::GetChildObjectCount(MQObject obj) 				{ return MQDoc_GetChildObjectCount(this, obj); }
inline MQObject	MQCDocument::GetChildObject(MQObject obj, int index) 		{ return MQDoc_GetChildObject(this, obj, index); }
inline void		MQCDocument::GetGlobalMatrix(MQObject obj, MQMatrix& mtx)	{ MQDoc_GetGlobalMatrix(this, obj, mtx.t); }
inline void		MQCDocument::GetGlobalInverseMatrix(MQObject obj, MQMatrix& mtx){ MQDoc_GetGlobalInverseMatrix(this, obj, mtx.t); }
#endif
#if MQPLUGIN_VERSION >= 0x0241
inline int		MQCDocument::InsertObject(MQObject obj, MQObject before)	{ return MQDoc_InsertObject(this, obj, before); }
#endif
#if MQPLUGIN_VERSION >= 0x0310
inline int MQCDocument::CreateUserData(DWORD productID, DWORD pluginID, const char *identifier, int userdata_type, int bytes_per_object)
{
	MQUserDataInfo info;
	info.dwSize = sizeof(info);
	info.productID = productID;
	info.pluginID = pluginID;
#if _MSC_VER >=1400
	strncpy_s(info.identifier, _countof(info.identifier), identifier, _countof(info.identifier)-1);
#else
	strncpy(info.identifier, identifier, sizeof(info.identifier)-1);
#endif
	info.userdata_type = userdata_type;
	info.bytes_per_element = bytes_per_object;
	info.create = true;
	return MQDoc_CreateUserData(this, &info);
}

inline int MQCDocument::FindUserData(DWORD productID, DWORD pluginID, const char *identifier, int userdata_type)
{
	MQUserDataInfo info;
	info.dwSize = sizeof(info);
	info.productID = productID;
	info.pluginID = pluginID;
#if _MSC_VER >=1400 
	strncpy_s(info.identifier, _countof(info.identifier), identifier, _countof(info.identifier)-1);
#else
	strncpy(info.identifier, identifier, sizeof(info.identifier)-1);
#endif
	info.userdata_type = userdata_type;
	info.bytes_per_element = 0;
	return MQDoc_CreateUserData(this, &info);
}

inline int  	MQCDocument::CreateObjectUserData(DWORD productID, DWORD pluginID, const char *identifier, int bytes_per_object) { return CreateUserData(productID, pluginID, identifier, MQUSERDATA_OBJECT, bytes_per_object); }
inline void		MQCDocument::DeleteObjectUserData(int userdata_id) { MQDoc_DeleteUserData(this, MQUSERDATA_OBJECT, userdata_id); }
inline int  	MQCDocument::FindObjectUserData(DWORD productID, DWORD pluginID, const char *identifier) { return FindUserData(productID, pluginID, identifier, MQUSERDATA_OBJECT); }
inline int  	MQCDocument::CreateVertexUserData(DWORD productID, DWORD pluginID, const char *identifier, int bytes_per_vertex) { return CreateUserData(productID, pluginID, identifier, MQUSERDATA_VERTEX, bytes_per_vertex); }
inline void		MQCDocument::DeleteVertexUserData(int userdata_id) { MQDoc_DeleteUserData(this, MQUSERDATA_VERTEX, userdata_id); }
inline int  	MQCDocument::FindVertexUserData(DWORD productID, DWORD pluginID, const char *identifier) { return FindUserData(productID, pluginID, identifier, MQUSERDATA_VERTEX); }
inline int  	MQCDocument::CreateFaceUserData(DWORD productID, DWORD pluginID, const char *identifier, int bytes_per_face) { return CreateUserData(productID, pluginID, identifier, MQUSERDATA_FACE, bytes_per_face); }
inline void		MQCDocument::DeleteFaceUserData(int userdata_id) { MQDoc_DeleteUserData(this, MQUSERDATA_FACE, userdata_id); }
inline int  	MQCDocument::FindFaceUserData(DWORD productID, DWORD pluginID, const char *identifier) { return FindUserData(productID, pluginID, identifier, MQUSERDATA_FACE); }
inline int  	MQCDocument::CreateMaterialUserData(DWORD productID, DWORD pluginID, const char *identifier, int bytes_per_material) { return CreateUserData(productID, pluginID, identifier, MQUSERDATA_MATERIAL, bytes_per_material); }
inline void		MQCDocument::DeleteMaterialUserData(int userdata_id) { MQDoc_DeleteUserData(this, MQUSERDATA_MATERIAL, userdata_id); }
inline int  	MQCDocument::FindMaterialUserData(DWORD productID, DWORD pluginID, const char *identifier) { return FindUserData(productID, pluginID, identifier, MQUSERDATA_MATERIAL); }
#endif


// class MQCScene
#if MQPLUGIN_VERSION >= 0x0210
inline void 	MQCScene::InitSize(int width, int height) 		{ MQScene_InitSize(this, width, height); }
inline void 	MQCScene::GetProjMatrix(float *matrix) 			{ MQScene_GetProjMatrix(this, matrix); }
inline void 	MQCScene::GetViewMatrix(float *matrix) 			{ MQScene_GetViewMatrix(this, matrix); }
#endif
#if MQPLUGIN_VERSION >= 0x0240
inline MQPoint 	MQCScene::GetCameraPosition()					{ float val[3]; MQScene_FloatValue(this,MQSCENE_GET_CAMERA_POS,val); return MQPoint(val[0],val[1],val[2]); }
inline MQAngle 	MQCScene::GetCameraAngle()						{ float val[3]; MQScene_FloatValue(this,MQSCENE_GET_CAMERA_ANGLE,val); return MQAngle(val[0],val[1],val[2]); }
inline MQPoint 	MQCScene::GetLookAtPosition()					{ float val[3]; MQScene_FloatValue(this,MQSCENE_GET_LOOK_AT_POS,val); return MQPoint(val[0],val[1],val[2]); }
inline MQPoint 	MQCScene::GetRotationCenter()					{ float val[3]; MQScene_FloatValue(this,MQSCENE_GET_ROTATION_CENTER,val); return MQPoint(val[0],val[1],val[2]); }
inline float 	MQCScene::GetFOV()								{ float val; MQScene_FloatValue(this,MQSCENE_GET_FOV,&val); return val; }
// OBSOLETE in Rev3.11: Replaced with GetGlobalDirectionalLightDirection()
//inline MQPoint 	MQCScene::GetGlobalDirectionalLight()			{ float val[3]; MQScene_FloatValue(this,MQSCENE_GET_DIRECTIONAL_LIGHT,val); return MQPoint(val[0],val[1],val[2]); }
inline MQColor 	MQCScene::GetGlobalAmbientColor()				{ float val[3]; MQScene_FloatValue(this,MQSCENE_GET_AMBIENT_COLOR,val); return MQColor(val[0],val[1],val[2]); }
inline void 	MQCScene::SetCameraPosition(const MQPoint& p)	{ float val[3]; val[0]=p.x; val[1]=p.y; val[2]=p.z; MQScene_FloatValue(this,MQSCENE_SET_CAMERA_POS,val); }
inline void 	MQCScene::SetCameraAngle(const MQAngle& angle)	{ float val[3]; val[0]=angle.head; val[1]=angle.pich; val[2]=angle.bank; MQScene_FloatValue(this,MQSCENE_SET_CAMERA_ANGLE,val); }
inline void 	MQCScene::SetLookAtPosition(const MQPoint& p)	{ float val[6]; val[0]=p.x; val[1]=p.y; val[2]=p.z; val[3]=0; val[4]=1; val[5]=0; MQScene_FloatValue(this,MQSCENE_SET_LOOK_AT_POS,val); }
inline void 	MQCScene::SetRotationCenter(const MQPoint& p)	{ float val[3]; val[0]=p.x; val[1]=p.y; val[2]=p.z; MQScene_FloatValue(this,MQSCENE_SET_ROTATION_CENTER,val); }
inline void 	MQCScene::SetFOV(float fov)						{ MQScene_FloatValue(this,MQSCENE_SET_FOV,&fov); }
// OBSOLETE in Rev3.11: Replaced with SetGlobalDirectionalLightDirection()
//inline void 	MQCScene::SetGlobalDirectionalLight(const MQPoint& vec)	{ float val[3]; val[0]=vec.x; val[1]=vec.y; val[2]=vec.z; MQScene_FloatValue(this,MQSCENE_SET_DIRECTIONAL_LIGHT,val); }
inline void 	MQCScene::SetGlobalAmbientColor(const MQColor& amb){ float val[3]; val[0]=amb.r; val[1]=amb.g; val[2]=amb.b; MQScene_FloatValue(this,MQSCENE_SET_AMBIENT_COLOR,val); }
inline MQPoint	MQCScene::Convert3DToScreen(const MQPoint& p, float *out_w){
	float val[7];
	val[0]=p.x; val[1]=p.y; val[2]=p.z;
	MQScene_FloatValue(this,MQSCENE_CONVERT_3D_TO_SCREEN,val);
	if (out_w != NULL) *out_w = val[6];
	return MQPoint(val[3],val[4],val[5]);
}
inline MQPoint	MQCScene::ConvertScreenTo3D(const MQPoint& p){
	float val[6];
	val[0]=p.x; val[1]=p.y; val[2]=p.z;
	MQScene_FloatValue(this,MQSCENE_CONVERT_SCREEN_TO_3D,val);
	return MQPoint(val[3],val[4],val[5]);
}
#endif
#if MQPLUGIN_VERSION >= 0x0241
inline BOOL 	MQCScene::GetVisibleFace(MQObject obj, BOOL *visible)	{ return MQScene_GetVisibleFace(this,obj,visible); }
#endif
#if MQPLUGIN_VERSION >= 0x0311
inline int		MQCScene::AddGlobalDirectionalLight()					{ int val[1]; MQScene_IntValue(this,MQSCENE_ADD_MULTILIGHT,val); return val[0]; }
inline BOOL		MQCScene::DeleteGlobalDirectionalLight(int index)		{ int val[2]; val[0]=index; MQScene_IntValue(this,MQSCENE_DELETE_MULTILIGHT,val); return val[1] ? TRUE : FALSE; }
inline int	 	MQCScene::GetGlobalDirectionalLightNum()				{ int val[1]; MQScene_IntValue(this,MQSCENE_GET_MULTILIGHT_NUMBER,val); return val[0]; }
inline MQPoint 	MQCScene::GetGlobalDirectionalLightDirection(int index)	{ float val[3]; MQScene_IntValue(this,MQSCENE_SET_MULTILIGHT_INDEX,&index); MQScene_FloatValue(this,MQSCENE_GET_MULTILIGHT_DIR,val); return MQPoint(val[0],val[1],val[2]); }
inline MQColor	MQCScene::GetGlobalDirectionalLightColor(int index)		{ float val[3]; MQScene_IntValue(this,MQSCENE_SET_MULTILIGHT_INDEX,&index); MQScene_FloatValue(this,MQSCENE_GET_MULTILIGHT_COLOR,val); return MQColor(val[0],val[1],val[2]); }
inline void		MQCScene::SetGlobalDirectionalLightDirection(int index, const MQPoint& dir)			{ float val[3]; MQScene_IntValue(this,MQSCENE_SET_MULTILIGHT_INDEX,&index); val[0]=dir.x; val[1]=dir.y; val[2]=dir.z; MQScene_FloatValue(this,MQSCENE_SET_MULTILIGHT_DIR,val); }
inline void 	MQCScene::SetGlobalDirectionalLightColor(int index, const MQColor& col)	{ float val[3]; MQScene_IntValue(this,MQSCENE_SET_MULTILIGHT_INDEX,&index); val[0]=col.r; val[1]=col.g; val[2]=col.b; MQScene_FloatValue(this,MQSCENE_SET_MULTILIGHT_COLOR,val); }
#endif

// class MQCObject
inline void 	MQCObject::DeleteThis(void) 					{ MQObj_Delete(this); }
inline MQObject MQCObject::Clone(void) 							{ return MQObj_Clone(this); }
inline void 	MQCObject::Merge(MQObject source) 				{ MQObj_Merge(this, source); }
inline void 	MQCObject::Freeze(DWORD flag) 					{ MQObj_Freeze(this, flag); }
inline void 	MQCObject::GetName(char *buffer, int size) 		{ MQObj_GetName(this, buffer, size); }
inline int  	MQCObject::GetVertexCount(void) 				{ return MQObj_GetVertexCount(this); }
inline MQPoint 	MQCObject::GetVertex(int index) 				{ MQPoint pts; MQObj_GetVertex(this, index, &pts); return pts; }
inline void 	MQCObject::SetVertex(int index, MQPoint pts) 	{ MQObj_SetVertex(this, index, &pts); }
inline void 	MQCObject::GetVertexArray(MQPoint *ptsarray) 	{ MQObj_GetVertexArray(this, ptsarray); }
inline int  	MQCObject::AddVertex(MQPoint p) 					{ return MQObj_AddVertex(this, &p); }
inline BOOL 	MQCObject::DeleteVertex(int index) 					{ return MQObj_DeleteVertex(this, index, TRUE); }
inline int  	MQCObject::GetVertexRefCount(int index) 			{ return MQObj_GetVertexRefCount(this, index); }
#if MQPLUGIN_VERSION >= 0x0240
inline UINT  	MQCObject::GetVertexUniqueID(int index) 			{ return MQObj_GetVertexUniqueID(this, index); }
inline int  	MQCObject::GetVertexIndexFromUniqueID(UINT unique_id){ return MQObj_GetVertexIndexFromUniqueID(this, unique_id); }
#endif
#if MQPLUGIN_VERSION >= 0x0300
inline int		MQCObject::GetVertexRelatedFaces(int vertex, int *faces){ return MQObj_GetVertexRelatedFaces(this, vertex, faces); }
#endif
//inline DWORD 	MQCObject::GetVertexColor(int index) 				{ return MQObj_GetVertexColor(this, index); } // OBSOLUTE
//inline void 	MQCObject::SetVertexColor(int index, DWORD color) 	{ MQObj_SetVertexColor(this, index, color); } // OBSOLUTE
inline float 	MQCObject::GetVertexWeight(int index) 				{ return MQObj_GetVertexWeight(this, index); }
inline void 	MQCObject::SetVertexWeight(int index, float value) 	{ MQObj_SetVertexWeight(this, index, value); }
inline void 	MQCObject::CopyVertexAttribute(int vert1, MQObject obj2, int vert2) { MQObj_CopyVertexAttribute(this, vert1, obj2, vert2); }
inline int  	MQCObject::GetFaceCount(void) 					{ return MQObj_GetFaceCount(this); }
inline int  	MQCObject::GetFacePointCount(int face) 			{ return MQObj_GetFacePointCount(this, face); }
inline void 	MQCObject::GetFacePointArray(int face, int *vertex) { MQObj_GetFacePointArray(this, face, vertex); }
inline void 	MQCObject::GetFaceCoordinateArray(int face, MQCoordinate *uvarray) { MQObj_GetFaceCoordinateArray(this, face, uvarray); }
inline int  	MQCObject::GetFaceMaterial(int face) 				{ return MQObj_GetFaceMaterial(this, face); }
#if MQPLUGIN_VERSION >= 0x0240
inline UINT  	MQCObject::GetFaceUniqueID(int face) 				{ return MQObj_GetFaceUniqueID(this, face); }
inline int  	MQCObject::GetFaceIndexFromUniqueID(UINT unique_id) { return MQObj_GetFaceIndexFromUniqueID(this, unique_id); }
#endif
inline void 	MQCObject::SetName(const char *buffer)		 		{ MQObj_SetName(this, buffer); }
inline int  	MQCObject::AddFace(int count, int *index) 			{ return MQObj_AddFace(this, count, index); }
inline BOOL 	MQCObject::DeleteFace(int index, bool delete_vertex){ return MQObj_DeleteFace(this, index, delete_vertex); }
inline BOOL 	MQCObject::InvertFace(int index) 					{ return MQObj_InvertFace(this, index); }
inline void 	MQCObject::SetFaceMaterial(int face, int material) 	{ MQObj_SetFaceMaterial(this, face, material); }
inline void 	MQCObject::SetFaceCoordinateArray(int face, MQCoordinate *uvarray) { MQObj_SetFaceCoordinateArray(this, face, uvarray); }
#if MQPLUGIN_VERSION >= 0x0230
inline DWORD  	MQCObject::GetFaceVertexColor(int face, int vertex) 				{ return MQObj_GetFaceVertexColor(this, face, vertex); }
inline void  	MQCObject::SetFaceVertexColor(int face, int vertex, DWORD color) 	{ MQObj_SetFaceVertexColor(this, face, vertex, color); }
#endif
#if MQPLUGIN_VERSION >= 0x0310
inline float 	MQCObject::GetFaceEdgeCrease(int face, int line)               { return MQObj_GetFaceEdgeCrease(this, face, line ); }
inline void		MQCObject::SetFaceEdgeCrease(int face, int line, float crease) { MQObj_SetFaceEdgeCrease(this, face, line, crease); }
#endif
#if MQPLUGIN_VERSION >= 0x0300
inline BOOL  	MQCObject::GetFaceVisible(int face) 				{ return MQObj_GetFaceVisible(this, face); }
inline void  	MQCObject::SetFaceVisible(int face, BOOL flag) 		{ MQObj_SetFaceVisible(this, face, flag); }
#endif
inline void 	MQCObject::OptimizeVertex(float distance, MQBool *apply) { MQObj_OptimizeVertex(this, distance, apply); }
inline void 	MQCObject::Compact(void) 					{ MQObj_Compact(this); }
inline DWORD 	MQCObject::GetVisible(void) 				{ return MQObj_GetVisible(this); }
inline void 	MQCObject::SetVisible(DWORD visible)	 	{ MQObj_SetVisible(this, visible); }
inline DWORD 	MQCObject::GetPatchType(void) 				{ return MQObj_GetPatchType(this); }
inline void 	MQCObject::SetPatchType(DWORD type) 		{ MQObj_SetPatchType(this, type); }
inline int  	MQCObject::GetPatchSegment(void) 			{ return MQObj_GetPatchSegment(this); }
inline void 	MQCObject::SetPatchSegment(int segment) 	{ MQObj_SetPatchSegment(this, segment); }
#if MQPLUGIN_VERSION >= 0x0310
inline BOOL		MQCObject::GetPatchTriangle(void)			{ return MQObj_GetIntValue(this, MQOBJ_ID_PATCH_TRIANGLE) != 0 ? TRUE : FALSE; }
inline void		MQCObject::SetPatchTriangle(BOOL flag)      { MQObj_SetIntValue(this, MQOBJ_ID_PATCH_TRIANGLE, flag ? 1 : 0); }
#endif
#if MQPLUGIN_VERSION >= 0x0210
inline int  	MQCObject::GetShading(void) 			{ return MQObj_GetShading(this); }
inline void 	MQCObject::SetShading(int type) 		{ MQObj_SetShading(this, type); }
inline float 	MQCObject::GetSmoothAngle(void) 		{ return MQObj_GetSmoothAngle(this); }
inline void 	MQCObject::SetSmoothAngle(float degree) { MQObj_SetSmoothAngle(this, degree); }
inline int  	MQCObject::GetMirrorType(void) 			{ return MQObj_GetMirrorType(this); }
inline void 	MQCObject::SetMirrorType(int type) 		{ MQObj_SetMirrorType(this, type); }
inline DWORD 	MQCObject::GetMirrorAxis(void) 			{ return MQObj_GetMirrorAxis(this); }
inline void 	MQCObject::SetMirrorAxis(DWORD axis) 	{ MQObj_SetMirrorAxis(this, axis); }
inline float 	MQCObject::GetMirrorDistance(void) 		{ return MQObj_GetMirrorDistance(this); }
inline void 	MQCObject::SetMirrorDistance(float dis) { MQObj_SetMirrorDistance(this, dis); }
inline int  	MQCObject::GetLatheType(void) 			{ return MQObj_GetLatheType(this); }
inline void 	MQCObject::SetLatheType(int type) 		{ MQObj_SetLatheType(this, type); }
inline DWORD 	MQCObject::GetLatheAxis(void) 			{ return MQObj_GetLatheAxis(this); }
inline void 	MQCObject::SetLatheAxis(DWORD axis) 	{ MQObj_SetLatheAxis(this, axis); }
inline int  	MQCObject::GetLatheSegment(void) 		{ return MQObj_GetLatheSegment(this); }
inline void 	MQCObject::SetLatheSegment(int segment) { MQObj_SetLatheSegment(this, segment); }
#endif
#if MQPLUGIN_VERSION >= 0x0240
inline UINT		MQCObject::GetUniqueID(void) 			{ return (UINT)MQObj_GetIntValue(this, MQOBJ_ID_UNIQUE_ID); }
inline int		MQCObject::GetDepth(void) 				{ return MQObj_GetIntValue(this, MQOBJ_ID_DEPTH); }
inline void		MQCObject::SetDepth(int depth) 			{ MQObj_SetIntValue(this, MQOBJ_ID_DEPTH, depth); }
inline BOOL		MQCObject::GetFolding(void) 			{ return MQObj_GetIntValue(this, MQOBJ_ID_FOLDING) ? TRUE : FALSE; }
inline void		MQCObject::SetFolding(BOOL flag) 		{ MQObj_SetIntValue(this, MQOBJ_ID_FOLDING, flag ? 1 : 0); }
inline BOOL		MQCObject::GetLocking(void) 			{ return MQObj_GetIntValue(this, MQOBJ_ID_LOCKING) ? TRUE : FALSE; }
inline void		MQCObject::SetLocking(BOOL flag) 		{ MQObj_SetIntValue(this, MQOBJ_ID_LOCKING, flag ? 1 : 0); }
inline MQColor	MQCObject::GetColor(void) 				{ float val[3]; MQObj_GetFloatArray(this, MQOBJ_ID_COLOR, val); return MQColor(val[0],val[1],val[2]); }
inline void		MQCObject::SetColor(MQColor color) 		{ float val[3]; val[0]=color.r; val[1]=color.g; val[2]=color.b; MQObj_SetFloatArray(this, MQOBJ_ID_COLOR, val); }
inline BOOL		MQCObject::GetColorValid(void) 			{ return MQObj_GetIntValue(this, MQOBJ_ID_COLOR_VALID) ? TRUE : FALSE; }
inline void		MQCObject::SetColorValid(BOOL flag) 	{ MQObj_SetIntValue(this, MQOBJ_ID_COLOR_VALID, flag); }
inline MQPoint	MQCObject::GetScaling(void) 			{ float val[3]; MQObj_GetFloatArray(this, MQOBJ_ID_SCALING, val); return MQPoint(val[0],val[1],val[2]); }
inline void		MQCObject::SetScaling(MQPoint scale) 	{ float val[3]; val[0]=scale.x; val[1]=scale.y; val[2]=scale.z; MQObj_SetFloatArray(this, MQOBJ_ID_SCALING, val); }
inline MQAngle	MQCObject::GetRotation(void) 			{ float val[3]; MQObj_GetFloatArray(this, MQOBJ_ID_ROTATION, val); return MQAngle(val[0],val[1],val[2]); }
inline void		MQCObject::SetRotation(MQAngle angle) 	{ float val[3]; val[0]=angle.head; val[1]=angle.pich; val[2]=angle.bank; MQObj_SetFloatArray(this, MQOBJ_ID_ROTATION, val); }
inline MQPoint	MQCObject::GetTranslation(void) 		{ float val[3]; MQObj_GetFloatArray(this, MQOBJ_ID_TRANSLATION, val); return MQPoint(val[0],val[1],val[2]); }
inline void		MQCObject::SetTranslation(MQPoint trans){ float val[3]; val[0]=trans.x; val[1]=trans.y; val[2]=trans.z; MQObj_SetFloatArray(this, MQOBJ_ID_TRANSLATION, val); }
inline MQMatrix	MQCObject::GetLocalMatrix(void) 		{ MQMatrix mtx; MQObj_GetFloatArray(this, MQOBJ_ID_LOCAL_MATRIX, mtx.t); return mtx; }
inline void		MQCObject::SetLocalMatrix(const MQMatrix& mtx)	{ MQObj_SetFloatArray(this, MQOBJ_ID_LOCAL_MATRIX, mtx.t); }
inline MQMatrix	MQCObject::GetLocalInverseMatrix(void)	{ MQMatrix mtx; MQObj_GetFloatArray(this, MQOBJ_ID_LOCAL_INVERSE_MATRIX, mtx.t); return mtx; }
#endif
#if MQPLUGIN_VERSION >= 0x0300
inline int		MQCObject::GetType(void)				{ return MQObj_GetIntValue(this, MQOBJ_ID_TYPE); }
inline void		MQCObject::SetType(int type)            { MQObj_SetIntValue(this, MQOBJ_ID_TYPE, type); }
inline float	MQCObject::GetLightValue(void)          { float val[1]; MQObj_GetFloatArray(this, MQOBJ_ID_LIGHT_VALUE, val); return val[0]; }
inline void		MQCObject::SetLightValue(float value)   { float val[1]; val[0]=value; MQObj_SetFloatArray(this, MQOBJ_ID_LIGHT_VALUE, val); }
inline int		MQCObject::GetLightAttenuation(void) 	{ return MQObj_GetIntValue(this, MQOBJ_ID_LIGHT_ATTENUATION); }
inline void		MQCObject::SetLightAttenuation(int value)		{ MQObj_SetIntValue(this, MQOBJ_ID_LIGHT_ATTENUATION, value); }
inline float	MQCObject::GetLightFallOffEnd(void)		{ float val[1]; MQObj_GetFloatArray(this, MQOBJ_ID_LIGHT_FALLOFF_END, val); return val[0]; }
inline void		MQCObject::SetLightFallOffEnd(float distance)	{ float val[1]; val[0]=distance; MQObj_SetFloatArray(this, MQOBJ_ID_LIGHT_FALLOFF_END, val); }
inline float	MQCObject::GetLightFallOffHalf(void)	{ float val[1]; MQObj_GetFloatArray(this, MQOBJ_ID_LIGHT_FALLOFF_HALF, val); return val[0]; }
inline void		MQCObject::SetLightFallOffHalf(float distance)	{ float val[1]; val[0]=distance; MQObj_SetFloatArray(this, MQOBJ_ID_LIGHT_FALLOFF_HALF, val); }
#endif
#if MQPLUGIN_VERSION >= 0x0310
inline BOOL		MQCObject::GetSelected()					{ return MQObj_GetIntValue(this, MQOBJ_ID_SELECTED); }
inline void		MQCObject::SetSelected(BOOL flag)			{ MQObj_SetIntValue(this, MQOBJ_ID_SELECTED, flag); }
inline BOOL		MQCObject::AllocUserData(int userdata_id) { return MQObj_AllocUserData(this, userdata_id); }
inline void 	MQCObject::FreeUserData(int userdata_id)	{ MQObj_FreeUserData(this, userdata_id); }
inline BOOL 	MQCObject::GetUserData(int userdata_id, void *buffer)       { return MQObj_GetUserData(this, userdata_id, 0, 0, buffer); }
inline BOOL 	MQCObject::GetUserDataPart(int userdata_id, int offset, int copy_bytes, void *buffer)       { return MQObj_GetUserData(this, userdata_id, offset, copy_bytes, buffer); }
inline BOOL 	MQCObject::SetUserData(int userdata_id, const void *buffer) { return MQObj_SetUserData(this, userdata_id, 0, 0, buffer); }
inline BOOL 	MQCObject::SetUserDataPart(int userdata_id, int offset, int copy_bytes, const void *buffer) { return MQObj_SetUserData(this, userdata_id, offset, copy_bytes, buffer); }
inline BOOL		MQCObject::AllocVertexUserData(int userdata_id) { return MQObj_AllocVertexUserData(this, userdata_id); }
inline void 	MQCObject::FreeVertexUserData(int userdata_id)	{ MQObj_FreeVertexUserData(this, userdata_id); }
inline BOOL 	MQCObject::GetVertexUserData(int userdata_id, int vertex_index, void *buffer)       { return MQObj_GetVertexUserData(this, userdata_id, vertex_index, 1, 0, 0, buffer); }
inline BOOL 	MQCObject::GetVertexUserDataPart(int userdata_id, int vertex_start_index, int copy_vertex_num, int offset, int copy_bytes, void *buffer)       { return MQObj_GetVertexUserData(this, userdata_id, vertex_start_index, copy_vertex_num, offset, copy_bytes, buffer); }
inline BOOL 	MQCObject::SetVertexUserData(int userdata_id, int vertex_index, const void *buffer) { return MQObj_SetVertexUserData(this, userdata_id, vertex_index, 1, 0, 0, buffer); }
inline BOOL 	MQCObject::SetVertexUserDataPart(int userdata_id, int vertex_start_index, int copy_vertex_num, int offset, int copy_bytes, const void *buffer) { return MQObj_SetVertexUserData(this, userdata_id, vertex_start_index, copy_vertex_num, offset, copy_bytes, buffer); }
inline BOOL		MQCObject::AllocFaceUserData(int userdata_id) { return MQObj_AllocFaceUserData(this, userdata_id); }
inline void 	MQCObject::FreeFaceUserData(int userdata_id)  { MQObj_FreeFaceUserData(this, userdata_id); }
inline BOOL 	MQCObject::GetFaceUserData(int userdata_id, int face_index, void *buffer)       { return MQObj_GetFaceUserData(this, userdata_id, face_index, 1, 0, 0, buffer); }
inline BOOL 	MQCObject::GetFaceUserDataPart(int userdata_id, int face_start_index, int copy_face_num, int offset, int copy_bytes, void *buffer) { return MQObj_GetFaceUserData(this, userdata_id, face_start_index, copy_face_num, offset, copy_bytes, buffer); }
inline BOOL 	MQCObject::SetFaceUserData(int userdata_id, int face_index, const void *buffer) { return MQObj_SetFaceUserData(this, userdata_id, face_index, 1, 0, 0, buffer); }
inline BOOL 	MQCObject::SetFaceUserDataPart(int userdata_id, int face_start_index, int copy_face_num, int offset, int copy_bytes, const void *buffer) { return MQObj_SetFaceUserData(this, userdata_id, face_start_index, copy_face_num, offset, copy_bytes, buffer); }
#endif


// class MQCMaterial
inline void 	MQCMaterial::DeleteThis(void) 					{ MQMat_Delete(this); }
inline void 	MQCMaterial::GetName(char *buffer, int size) 	{ MQMat_GetName(this, buffer, size); }
#if MQPLUGIN_VERSION >= 0x0240
inline UINT 	MQCMaterial::GetUniqueID(void) 					{ return (UINT)MQMat_GetIntValue(this, MQMAT_ID_UNIQUE_ID); }
#endif
#if MQPLUGIN_VERSION >= 0x0230
inline int 		MQCMaterial::GetShader(void) 					{ return MQMat_GetIntValue(this, MQMAT_ID_SHADER); }
inline int 		MQCMaterial::GetVertexColor(void) 				{ return MQMat_GetIntValue(this, MQMAT_ID_VERTEXCOLOR); }
#endif
#if MQPLUGIN_VERSION >= 0x0310
inline BOOL		MQCMaterial::GetSelected()						{ return MQMat_GetIntValue(this, MQMAT_ID_SELECTED); }
inline BOOL		MQCMaterial::GetDoubleSided(void) 				{ return MQMat_GetIntValue(this, MQMAT_ID_DOUBLESIDED) != 0 ? TRUE : FALSE; }
#endif
inline MQColor 	MQCMaterial::GetColor(void) 			{ MQColor color; MQMat_GetColor(this, &color); return color; }
inline float 	MQCMaterial::GetAlpha(void) 			{ return MQMat_GetAlpha(this); }
inline float 	MQCMaterial::GetDiffuse(void) 			{ return MQMat_GetDiffuse(this); }
inline float 	MQCMaterial::GetAmbient(void) 			{ return MQMat_GetAmbient(this); }
inline float 	MQCMaterial::GetEmission(void) 			{ return MQMat_GetEmission(this); }
inline float 	MQCMaterial::GetSpecular(void) 			{ return MQMat_GetSpecular(this); }
inline float 	MQCMaterial::GetPower(void) 			{ return MQMat_GetPower(this); }
#if MQPLUGIN_VERSION >= 0x0230
inline int 		MQCMaterial::GetMappingType(void) 		{ return MQMat_GetIntValue(this, MQMAT_ID_MAPPROJ); }
inline MQPoint 	MQCMaterial::GetMappingPosition(void) 	{ float val[3]; MQMat_GetFloatArray(this, MQMAT_ID_MAPPROJ_POSITION, val); return MQPoint(val[0], val[1], val[2]); }
inline MQPoint 	MQCMaterial::GetMappingScaling(void) 	{ float val[3]; MQMat_GetFloatArray(this, MQMAT_ID_MAPPROJ_SCALING,  val); return MQPoint(val[0], val[1], val[2]); }
inline MQAngle 	MQCMaterial::GetMappingAngle(void) 		{ float val[3]; MQMat_GetFloatArray(this, MQMAT_ID_MAPPROJ_ANGLE,    val); return MQAngle(val[0], val[1], val[2]); }
#endif
inline void 	MQCMaterial::GetTextureName(char *buffer, int size) { MQMat_GetTextureName(this, buffer, size); }
inline void 	MQCMaterial::GetAlphaName(char *buffer, int size) 	{ MQMat_GetAlphaName(this, buffer, size); }
inline void 	MQCMaterial::GetBumpName(char *buffer, int size) 	{ MQMat_GetBumpName(this, buffer, size); }
inline void 	MQCMaterial::SetName(const char *name) 				{ MQMat_SetName(this, name); }
#if MQPLUGIN_VERSION >= 0x0230
inline void 	MQCMaterial::SetShader(int shader) 		{ MQMat_SetIntValue(this, MQMAT_ID_SHADER, shader); }
inline void 	MQCMaterial::SetVertexColor(int value) 	{ MQMat_SetIntValue(this, MQMAT_ID_VERTEXCOLOR, value); }
#endif
#if MQPLUGIN_VERSION >= 0x0310
inline void		MQCMaterial::SetSelected(BOOL flag)		{ MQMat_SetIntValue(this, MQMAT_ID_SELECTED, flag); }
inline void 	MQCMaterial::SetDoubleSided(BOOL value) { MQMat_SetIntValue(this, MQMAT_ID_DOUBLESIDED, value ? 1: 0); }
#endif
inline void 	MQCMaterial::SetColor(MQColor color) 	{ MQMat_SetColor(this, &color); }
inline void 	MQCMaterial::SetAlpha(float value) 		{ MQMat_SetAlpha(this, value); }
inline void 	MQCMaterial::SetDiffuse(float value) 	{ MQMat_SetDiffuse(this, value); }
inline void 	MQCMaterial::SetAmbient(float value) 	{ MQMat_SetAmbient(this, value); }
inline void 	MQCMaterial::SetEmission(float value) 	{ MQMat_SetEmission(this, value); }
inline void 	MQCMaterial::SetSpecular(float value) 	{ MQMat_SetSpecular(this, value); }
inline void 	MQCMaterial::SetPower(float value) 		{ MQMat_SetPower(this, value); }
#if MQPLUGIN_VERSION >= 0x0230
inline void 	MQCMaterial::SetMappingType(int type) 	{ MQMat_SetIntValue(this, MQMAT_ID_MAPPROJ, type); }
inline void 	MQCMaterial::SetMappingPosition(MQPoint pos) 	{ float val[3]; val[0]=pos.x; val[1]=pos.y; val[2]=pos.z; MQMat_SetFloatArray(this, MQMAT_ID_MAPPROJ_POSITION, val); }
inline void 	MQCMaterial::SetMappingScaling(MQPoint scale) 	{ float val[3]; val[0]=scale.x; val[1]=scale.y; val[2]=scale.z; MQMat_SetFloatArray(this, MQMAT_ID_MAPPROJ_SCALING, val); }
inline void 	MQCMaterial::SetMappingAngle(MQAngle angle) 	{ float val[3]; val[0]=angle.head; val[1]=angle.pich; val[2]=angle.bank; MQMat_SetFloatArray(this, MQMAT_ID_MAPPROJ_ANGLE, val); }
#endif
inline void 	MQCMaterial::SetTextureName(const char *name) 	{ MQMat_SetTextureName(this, name); }
inline void 	MQCMaterial::SetAlphaName(const char *name) 	{ MQMat_SetAlphaName(this, name); }
inline void 	MQCMaterial::SetBumpName(const char *name) 		{ MQMat_SetBumpName(this, name); }
#if MQPLUGIN_VERSION >= 0x0310
inline BOOL		MQCMaterial::AllocUserData(int userdata_id) { return MQMat_AllocUserData(this, userdata_id); }
inline void 	MQCMaterial::FreeUserData(int userdata_id)	{ MQMat_FreeUserData(this, userdata_id); }
inline BOOL 	MQCMaterial::GetUserData(int userdata_id, void *buffer)       { return MQMat_GetUserData(this, userdata_id, 0, 0, buffer); }
inline BOOL 	MQCMaterial::GetUserDataPart(int userdata_id, int offset, int copy_bytes, void *buffer)       { return MQMat_GetUserData(this, userdata_id, offset, copy_bytes, buffer); }
inline BOOL 	MQCMaterial::SetUserData(int userdata_id, const void *buffer) { return MQMat_SetUserData(this, userdata_id, 0, 0, buffer); }
inline BOOL 	MQCMaterial::SetUserDataPart(int userdata_id, int offset, int copy_bytes, const void *buffer) { return MQMat_SetUserData(this, userdata_id, offset, copy_bytes, buffer); }
#endif

#if MQPLUGIN_VERSION >= 0x0240
// class MQMatrix
inline MQPoint	MQMatrix::GetScaling() const			{ float val[3]; MQMatrix_FloatValue((float*)this->t, MQMATRIX_GET_SCALING, val); return MQPoint(val[0],val[1],val[2]); }
inline MQAngle	MQMatrix::GetRotation() const			{ float val[3]; MQMatrix_FloatValue((float*)this->t, MQMATRIX_GET_ROTATION, val); return MQAngle(val[0],val[1],val[2]); }
inline MQPoint	MQMatrix::GetTranslation() const		{ float val[3]; MQMatrix_FloatValue((float*)this->t, MQMATRIX_GET_TRANSLATION, val); return MQPoint(val[0],val[1],val[2]); }
inline void		MQMatrix::SetTransform(const MQPoint *scaling, const MQAngle *rotation, const MQPoint *trans){
	 float val[9];
	 val[0] = scaling->x; val[1] = scaling->y; val[2] = scaling->z;
	 val[3] = rotation->head; val[4] = rotation->pich; val[5] = rotation->bank;
	 val[6] = trans->x; val[7] = trans->y; val[8] = trans->z;
	 MQMatrix_FloatValue(this->t, MQMATRIX_SET_TRANSFORM, val);
}
inline void		MQMatrix::SetInverseTransform(const MQPoint *scaling, const MQAngle *rotation, const MQPoint *trans){
	 float val[9];
	 val[0] = scaling->x; val[1] = scaling->y; val[2] = scaling->z;
	 val[3] = rotation->head; val[4] = rotation->pich; val[5] = rotation->bank;
	 val[6] = trans->x; val[7] = trans->y; val[8] = trans->z;
	 MQMatrix_FloatValue(this->t, MQMATRIX_SET_INVERSE_TRANSFORM, val);
}
#endif


#endif //MQPLUGIN_EXPORTS

#endif //MQPluginH


