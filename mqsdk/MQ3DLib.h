//---------------------------------------------------------------------------
//
//   MQ3DLib.h      Copyright(C) 1999-2012, tetraface Inc.
//
//		A collection of convenient functions.
//
//    　ちょっと便利な関数集。
//
//---------------------------------------------------------------------------

#ifndef MQ3DLIB_H
#define MQ3DLIB_H

#include <math.h>

// For C++Builder5
// float型浮動小数点演算関数に対応していないC++Builder5用対策
#ifdef __BORLANDC__
#define sqrtf sqrt
#endif


// Ratio of the circumference of a circle to its diameter
// 円周率π
#ifndef PI
	#define PI 3.1415926536f
#endif

// Convert degree (from 0 to 360) to radian (from 0 and 2*PI)
// 弧度(0から360)からラジアン(0から2π)へ変換
#ifndef RAD
	#define RAD(_x) ((_x)/180.0f*PI)
#endif

// Convert radian (from 0 and 2*pi) to degree (from 0 to 360)
// ラジアン(0から2π)から弧度(0から360)へ変換
#ifndef DEG
	#define DEG(_x) ((_x)/PI*180.0f)
#endif

// The square of the magnitude of a vector 
// ベクトルのサイズの２乗
inline float GetNorm(const MQPoint& p)
{
	return p.x*p.x + p.y*p.y + p.z*p.z;
}

inline float GetNorm(const MQCoordinate& p)
{
	return p.u*p.u + p.v*p.v;
}

// The magnitude of a vector 
// ベクトルのサイズ
inline float GetSize(const MQPoint& p)
{
	return sqrtf(p.x*p.x + p.y*p.y + p.z*p.z);
}

inline float GetSize(const MQCoordinate& p)
{
	return sqrtf(p.u*p.u + p.v*p.v);
}

// Normalize a vector
// ベクトルの正規化
inline MQPoint Normalize(const MQPoint& p) 
{
	float s = GetSize(p);
	if(s == 0.0f)
		return MQPoint(0,0,0);
	return p / s;
}

// Get an inner product
// 内積の値を得る
inline float GetInnerProduct(const MQPoint& pa, const MQPoint& pb)
{
	return pa.x * pb.x + pa.y * pb.y + pa.z * pb.z; 
}

inline float GetInnerProduct(const MQCoordinate& pa, const MQCoordinate& pb)
{
	return pa.u * pb.u + pa.v * pb.v;
}

// Get a cross product
// 外積ベクトルを得る
inline MQPoint GetCrossProduct(const MQPoint& v1, const MQPoint& v2)
{
	return MQPoint(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}

inline MQPoint GetExteriorProduct(const MQPoint& v1, const MQPoint& v2)
{
	return GetCrossProduct(v1, v2); 
}

// Get a normal vector for a face constituted by three points
// 3点からなる面の法線を得る
MQPoint GetNormal(const MQPoint& p0, const MQPoint& p1, const MQPoint& p2);

// Get a normal vector for a face constituted by four points
// 4点からなる面の法線を得る
MQPoint GetQuadNormal(const MQPoint& p0, const MQPoint& p1, const MQPoint& p2, const MQPoint& p3);

// Get an area of a triangle constituted by three points
// 3点からなる三角形の面積を得る
float GetTriangleArea(const MQPoint& p1, const MQPoint& p2, const MQPoint& p3);
float GetTriangleArea(const MQCoordinate& p1, const MQCoordinate& p2, const MQCoordinate& p3);

// Get an angle which the two vectors intersect in radian (from 0 and PI)
// 2ベクトルの交差する角度をラジアン単位の0からπまでの値で得る
float GetCrossingAngle(const MQPoint& v1, const MQPoint& v2);
float GetCrossingAngle(const MQCoordinate& v1, const MQCoordinate& v2);

// Check whether a face exists in the opposite direction of the specified one.
// It returns an index of the face if it exists, or returns -1 if not exist.
// 反対向きの面が存在するかどうかを調べる
// 存在していればその面のインデックスを、なければ-1を返す
int SearchInvertedFace(MQObject obj, int faceindex, int start=-1, int end=-1);

// Check whether a direction of the face is front side in the scene
// 面の向きが表かどうか調べる
bool IsFrontFace(MQScene scene, MQObject obj, int face_index);

// Calculate a tangent vector from positions, normals and coordinates
// 位置・法線・UV座標から接線ベクトルを計算する
void CalculateTangent(const MQPoint& v0, const MQPoint& v1, const MQPoint& v2,
		const MQPoint& n0, const MQPoint& n1, const MQPoint& n2,
		const MQCoordinate& t0, const MQCoordinate& t1, const MQCoordinate& t2,
		MQPoint& tan0, MQPoint& tan1, MQPoint& tan2);

void CalculateTangent(const MQPoint& v0, const MQPoint& v1, const MQPoint& v2,
		const MQPoint& normal, 
		const MQCoordinate& t0, const MQCoordinate& t1, const MQCoordinate& t2,
		MQPoint& tangent);

// Calculate a tangent vector and a binormal vector from positions, normals and coordinates
// 位置・法線・UV座標から接線ベクトル・従法線ベクトルを計算する
void CalculateTangentAndBinormal(const MQPoint& v0, const MQPoint& v1, const MQPoint& v2,
		const MQPoint& n0, const MQPoint& n1, const MQPoint& n2,
		const MQCoordinate& t0, const MQCoordinate& t1, const MQCoordinate& t2,
		MQPoint& tan0, MQPoint& tan1, MQPoint& tan2, 
		MQPoint& bin0, MQPoint& bin1, MQPoint& bin2);


// Class for calculating normal vectors in an object
// オブジェクト中の法線を計算するクラス
class MQObjNormal
{
protected:
	MQPoint *normal;
public:
	MQObjNormal(MQObject obj);
	virtual ~MQObjNormal();

	inline MQPoint& Get(int face_index, int pt_index) {
		return normal[face_index*4 + pt_index];
	}
};


// A pair of an edge using in the MQObjEdge class
// MQObjEdgeクラス内で使用されるエッジ対情報
class MQObjEdgePair
{
public:
	int face;
	int line;

	inline MQObjEdgePair() { face = line = -1; }
	inline MQObjEdgePair(int f, int l) { face = f; line = l; }
	inline MQObjEdgePair& operator = (const MQObjEdgePair& r)
		{ face=r.face; line=r.line; return *this; }
};

typedef MQObjEdgePair MQObjEdgePairFace[4];


// Class for managing pairs of edges
// オブジェクトのエッジ対管理クラス
class MQObjEdge
{
protected:
	int m_face;
	MQObject m_obj;
	MQObjEdgePairFace *m_pair;
public:
	MQObjEdge(MQObject obj);
	virtual ~MQObjEdge();

	bool getPair(int face_index, int line_index, int& pair_face, int& pair_line);
};


#endif //MQ3DLIB_H
