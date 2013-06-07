//---------------------------------------------------------------------------
//
//   MQ3DLib.cpp      Copyright(C) 1999-2012, tetraface Inc.
//
//		A collection of convenient functions.
//
//    　ちょっと便利な関数集。
//
//---------------------------------------------------------------------------

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "MQPlugin.h"
#include "MQ3DLib.h"


// For C++Builder5
// float型浮動小数点演算関数に対応していないC++Builder5用対策
#ifdef __BORLANDC__
#define  acosf  acos
#define  cosf   cos
#endif


//---------------------------------------------------------------------------
//  GetNormal()
//     Get a normal vector for a face constituted by three points.
//     3点からなる面の法線を得る
//---------------------------------------------------------------------------
MQPoint GetNormal(const MQPoint& p0, const MQPoint& p1, const MQPoint& p2)
{
	MQPoint ep = GetCrossProduct(p1-p2, p0-p1);

	if(ep == MQPoint(0,0,0))
		return MQPoint(0,0,0);

	return ep / GetSize(ep);
}

//---------------------------------------------------------------------------
//  GetQuadNormal()
//     Get a normal vector for a face constituted by four points.
//     4点からなる面の法線を得る
//---------------------------------------------------------------------------
MQPoint GetQuadNormal(const MQPoint& p0, const MQPoint& p1, const MQPoint& p2, const MQPoint& p3)
{
	MQPoint n,n1a,n1b,n2a,n2b;

	n1a = GetNormal(p0, p1, p2);
	n1b = GetNormal(p0, p2, p3);
	n2a = GetNormal(p1, p2, p3);
	n2b = GetNormal(p1, p3, p0);

	// 凹型や歪んだ四角形の場合は片方の内積が小さくなるので、
	// ２法線の内積の値を比較して、大きい方を選ぶ
	if(GetInnerProduct(n1a,n1b) > GetInnerProduct(n2a,n2b)) {
		n = Normalize(n1a + n1b);
	} else {
		n = Normalize(n2a + n2b);
	}

	return n;
}

//---------------------------------------------------------------------------
//  GetTriangleArea()
//     Get an area of a triangle constituted by three points
//     3点からなる三角形の面積を得る
//---------------------------------------------------------------------------
float GetTriangleArea(const MQPoint& p1, const MQPoint& p2, const MQPoint& p3)
{
	MQPoint v1,v2;
	float d1,d2,t,u;

	v1=p2-p1; d1=v1.abs();
	v2=p3-p1; d2=v2.abs();
	t = d1*d2;
	if(t == 0) return 0;
	u = (GetInnerProduct(v1,v2) / t);
	return t * (1 - u*u);
}

float GetTriangleArea(const MQCoordinate& p1, const MQCoordinate& p2, const MQCoordinate& p3)
{
	MQCoordinate v1,v2;
	float d1,d2,t,u;

	v1=p2-p1; d1=GetSize(v1);
	v2=p3-p1; d2=GetSize(v2);
	t = d1*d2;
	if(t == 0) return 0;
	u = (GetInnerProduct(v1,v2) / t);
	return t * (1 - u*u);
}

//---------------------------------------------------------------------------
//  GetCrossingAngle()
//     Get an angle which the two vectors intersect in radian (from 0 and PI).
//     2ベクトルの交差する角度をラジアン単位の0からπまでの値で得る
//---------------------------------------------------------------------------
float GetCrossingAngle(const MQPoint& v1, const MQPoint& v2)
{
	float d,c;

	d = GetSize(v1) * GetSize(v2);
	if(d == 0.0f)
		return 0.0f;

	c = GetInnerProduct(v1, v2) / d;
	if(c >= 1.0f) return 0.0f;
	if(c <=-1.0f) return PI;

	return acosf(c);
}

float GetCrossingAngle(const MQCoordinate& v1, const MQCoordinate& v2)
{
	float d,c;

	d = GetSize(v1) * GetSize(v2);
	if(d == 0.0f)
		return 0.0f;

	c = GetInnerProduct(v1, v2) / d;
	if(c >= 1.0f) return 0.0f;
	if(c <=-1.0f) return PI;

	return acosf(c);
}

//---------------------------------------------------------------------------
//  SearchInvertedFace()
//     Check whether a face exists in the opposite direction of the specified one.
//     It returns an index of the face if it exists, or returns -1 if not exist.
//     反対向きの面が存在するかどうかを調べる
//     存在していればその面のインデックスを、なければ-1を返す
//---------------------------------------------------------------------------
int SearchInvertedFace(MQObject obj, int faceindex, int start, int end)
{
	int i,j,k;
	int cvidx[4], dvidx[4];

	int face_count = obj->GetFaceCount();
	if(faceindex >= face_count)
		return -1;

	int pt_count = obj->GetFacePointCount(faceindex);
	if(pt_count == 0)
		return -1;

	obj->GetFacePointArray(faceindex, dvidx);

	if(start < 0) start = 0;
	if(end   < 0) end   = face_count-1;

	for(i=start; i<=end; i++)
	{
		if(pt_count != obj->GetFacePointCount(i))
			continue;
		
		obj->GetFacePointArray(i, cvidx);

		for(j=0; j<pt_count; j++) {
			if(cvidx[j] != dvidx[0]) continue;
			for(k=1; k<pt_count; k++) {
				if(cvidx[(j+k)%pt_count] != dvidx[pt_count-k])
					break;
			}
			if(k == pt_count)
				return i;
		}
	}

	return -1;
}


//---------------------------------------------------------------------------
//  IsFrontFace()
//     Check whether a direction of the face is front side in the scene.
//     面の向きが表かどうか調べる
//---------------------------------------------------------------------------
bool IsFrontFace(MQScene scene, MQObject obj, int face_index)
{
	int num = obj->GetFacePointCount(face_index);
	int vert_index[4];
	obj->GetFacePointArray(face_index, vert_index);

	MQPoint sp[4];
	for (int i=0; i<num; i++){
		sp[i] = scene->Convert3DToScreen(obj->GetVertex(vert_index[i]));

		// 視野より手前にあれば表とみなさない
		if (sp[i].z <= 0) return false;
	}

	// 法線の向きで調べる
	if(num >= 3){
		if((sp[1].x-sp[0].x) * (sp[2].y-sp[1].y) - (sp[1].y-sp[0].y) * (sp[2].x-sp[1].x) < 0) {
			return true;
		}else if(num >= 4){
			if((sp[2].x-sp[0].x) * (sp[3].y-sp[2].y) - (sp[2].y-sp[0].y) * (sp[3].x-sp[2].x) < 0) {
				return true;
			}
		}
	}
	else if (num > 0){
		return true;
	}

	return false;
}



//---------------------------------------------------------------------------
//  CalculateTangent()
//     Calculate a tangent vector from positions, normals and coordinates.
//     位置・法線・UV座標から接線ベクトルを計算する
//---------------------------------------------------------------------------
void CalculateTangent(const MQPoint& v0, const MQPoint& v1, const MQPoint& v2,
		const MQPoint& n0, const MQPoint& n1, const MQPoint& n2,
		const MQCoordinate& t0, const MQCoordinate& t1, const MQCoordinate& t2,
		MQPoint& tan0, MQPoint& tan1, MQPoint& tan2)
{
	MQPoint edge1, edge2, crossP;

	edge1.x = v1.x - v0.x;
	edge1.y = t1.u - t0.u; // s-vector - don't need to compute this multiple times
	edge1.z = t1.v - t0.v; // t-vector
	edge2.x = v2.x - v0.x;
	edge2.y = t2.u - t0.u; // another s-vector
	edge2.z = t2.v - t0.v; // another t-vector
	crossP = Normalize(GetCrossProduct(edge1, edge2));
	if(fabs(crossP.x) < 1e-4f){
		crossP.x = 1.0f;
	}
	float tanX = -crossP.y / crossP.x;
	tan0.x = tanX;
	tan1.x = tanX;
	tan2.x = tanX;

	// y, s, t
	edge1.x = v1.y - v0.y;
	edge2.x = v2.y - v0.y;
	crossP = Normalize(GetCrossProduct(edge1, edge2));
	if(fabs(crossP.x) < 1e-4f){
		crossP.x = 1.0f;
	}
	float tanY = -crossP.y / crossP.x;
	tan0.y = tanY;
	tan1.y = tanY;
	tan2.y = tanY;

	// z, s, t
	edge1.x = v1.z - v0.z;
	edge2.x = v2.z - v0.z;
	crossP = Normalize(GetCrossProduct(edge1, edge2));
	if(fabs(crossP.x) < 1e-4f){
		crossP.x = 1.0f;
	}
	float tanZ = -crossP.y / crossP.x;
	tan0.z = tanZ;
	tan1.z = tanZ;
	tan2.z = tanZ;

	// Orthonormalize to normal
	tan0 -= n0 * GetInnerProduct(tan0, n0);
	tan1 -= n1 * GetInnerProduct(tan1, n1);
	tan2 -= n2 * GetInnerProduct(tan2, n2);

	// Normalize tangents
	tan0 = Normalize(tan0);
	tan1 = Normalize(tan1);
	tan2 = Normalize(tan2);
}

void CalculateTangent(const MQPoint& v0, const MQPoint& v1, const MQPoint& v2,
		const MQPoint& normal,
		const MQCoordinate& t0, const MQCoordinate& t1, const MQCoordinate& t2,
		MQPoint& tangent)
{
	MQPoint edge1, edge2, crossP;

	edge1.x = v1.x - v0.x;
	edge1.y = t1.u - t0.u; // s-vector - don't need to compute this multiple times
	edge1.z = t1.v - t0.v; // t-vector
	edge2.x = v2.x - v0.x;
	edge2.y = t2.u - t0.u; // another s-vector
	edge2.z = t2.v - t0.v; // another t-vector
	crossP = Normalize(GetCrossProduct(edge1, edge2));
	if(fabs(crossP.x) < 1e-4f){
		crossP.x = 1.0f;
	}
	float tanX = -crossP.y / crossP.x;
	tangent.x = tanX;

	// y, s, t
	edge1.x = v1.y - v0.y;
	edge2.x = v2.y - v0.y;
	crossP = Normalize(GetCrossProduct(edge1, edge2));
	if(fabs(crossP.x) < 1e-4f){
		crossP.x = 1.0f;
	}
	float tanY = -crossP.y / crossP.x;
	tangent.y = tanY;

	// z, s, t
	edge1.x = v1.z - v0.z;
	edge2.x = v2.z - v0.z;
	crossP = Normalize(GetCrossProduct(edge1, edge2));
	if(fabs(crossP.x) < 1e-4f){
		crossP.x = 1.0f;
	}
	float tanZ = -crossP.y / crossP.x;
	tangent.z = tanZ;

	// Orthonormalize to normal
	tangent -= normal * GetInnerProduct(tangent, normal);

	// Normalize tangents
	tangent = Normalize(tangent);
}


void CalculateTangentAndBinormal(const MQPoint& v0, const MQPoint& v1, const MQPoint& v2,
		const MQPoint& n0, const MQPoint& n1, const MQPoint& n2,
		const MQCoordinate& t0, const MQCoordinate& t1, const MQCoordinate& t2,
		MQPoint& tan0, MQPoint& tan1, MQPoint& tan2, 
		MQPoint& bin0, MQPoint& bin1, MQPoint& bin2)
{
	MQPoint edge1, edge2, crossP;

	edge1.x = v1.x - v0.x;
	edge1.y = t1.u - t0.u; // s-vector - don't need to compute this multiple times
	edge1.z = t1.v - t0.v; // t-vector
	edge2.x = v2.x - v0.x;
	edge2.y = t2.u - t0.u; // another s-vector
	edge2.z = t2.v - t0.v; // another t-vector
	crossP = Normalize(GetCrossProduct(edge1, edge2));
	if(fabs(crossP.x) < 1e-4f){
		crossP.x = 1.0f;
	}
	tan0.x = tan1.x = tan2.x = -crossP.y / crossP.x;
	bin0.x = bin1.x = bin2.x = -crossP.z / crossP.x;

	// y, s, t
	edge1.x = v1.y - v0.y;
	edge2.x = v2.y - v0.y;
	crossP = Normalize(GetCrossProduct(edge1, edge2));
	if(fabs(crossP.x) < 1e-4f){
		crossP.x = 1.0f;
	}
	tan0.y = tan1.y = tan2.y = -crossP.y / crossP.x;
	bin0.y = bin1.y = bin2.y = -crossP.z / crossP.x;

	// z, s, t
	edge1.x = v1.z - v0.z;
	edge2.x = v2.z - v0.z;
	crossP = Normalize(GetCrossProduct(edge1, edge2));
	if(fabs(crossP.x) < 1e-4f){
		crossP.x = 1.0f;
	}
	tan0.z = tan1.z = tan2.z = -crossP.y / crossP.x;
	bin0.z = bin1.z = bin2.z = -crossP.z / crossP.x;

	// Orthonormalize to normal
	tan0 -= n0 * GetInnerProduct(tan0, n0);
	tan1 -= n1 * GetInnerProduct(tan1, n1);
	tan2 -= n2 * GetInnerProduct(tan2, n2);
	bin0 -= n0 * GetInnerProduct(bin0, n0);
	bin1 -= n1 * GetInnerProduct(bin1, n1);
	bin2 -= n2 * GetInnerProduct(bin2, n2);

	// Normalize tangents and binormals
	tan0 = Normalize(tan0);
	tan1 = Normalize(tan1);
	tan2 = Normalize(tan2);
	bin0 = Normalize(bin0);
	bin1 = Normalize(bin1);
	bin2 = Normalize(bin2);
}


//---------------------------------------------------------------------------
//  class MQGouraudHash
//     MQObjNormalクラスで内部的に使われるハッシュ
//---------------------------------------------------------------------------
class MQGouraudHash
{
public:
	MQPoint nv;
	int count;
	MQGouraudHash *next;

	inline MQGouraudHash() { nv.zero(); count=0; next=NULL; }
};

typedef MQGouraudHash *MQGouraudHashTable[4];

//---------------------------------------------------------------------------
//  class MQObjNormal
//     オブジェクト中の法線を計算するクラス。
//     スムージング角度に対する処理も行われる。
//     使用例は以下のような感じ。
//
//       MQObjNormal *normal = new MQObjNormal(obj);
//       int face_count = obj->GetFaceCount();
//       for(int face=0; face<face_count; face++) {
//           int count = obj->GetFacePointCount(face);
//           for(int vert=0; vert<count; vert++) {
//				MQPoint nv = normal->Get(face, vert);
//              // ここに法線に対する処理を入れる
//           }
//       }
//       delete normal;
//---------------------------------------------------------------------------
MQObjNormal::~MQObjNormal()
{
	delete[] normal;
}

MQObjNormal::MQObjNormal(MQObject obj)
{
	int i,j;
	int face_count, vert_count;
	int vi[4];

	face_count = obj->GetFaceCount();
	vert_count = obj->GetVertexCount();

	MQPoint *face_n = new MQPoint[face_count];
	normal = new MQPoint[face_count * 4];

	// 面ごとに法線を計算
	for(i=0; i<face_count; i++)
	{
		int count = obj->GetFacePointCount(i);

		// 三角形と四角形では面に対する法線の計算法は異なる
		switch(count) {
		case 3:
			obj->GetFacePointArray(i, vi);
			face_n[i] = GetNormal(
				obj->GetVertex(vi[0]), obj->GetVertex(vi[1]), obj->GetVertex(vi[2]));
			break;
		case 4:
			obj->GetFacePointArray(i, vi);
			face_n[i] = GetQuadNormal(
				obj->GetVertex(vi[0]), obj->GetVertex(vi[1]), 
				obj->GetVertex(vi[2]), obj->GetVertex(vi[3]));
			break;
		default:
			face_n[i].zero();
			break;
		}
	}

	switch(obj->GetShading()) {
	case MQOBJECT_SHADE_FLAT:
		for(i=0; i<face_count; i++)
		{
			int count = obj->GetFacePointCount(i);
			for(j=0; j<count; j++)
				normal[i*4+j] = face_n[i];
			for(; j<4; j++)
				normal[i*4+j].zero();
		}
		break;

	case MQOBJECT_SHADE_GOURAUD:
		{
			MQGouraudHashTable *vtbl, *cvt;
			MQGouraudHash *hash, *chs;

			// スムージング角度の取得
			float facet = cosf( RAD(obj->GetSmoothAngle()) );

			// ハッシュの初期化
			vtbl = new MQGouraudHashTable[face_count];
			hash = new MQGouraudHash[vert_count + face_count*4];
			int hash_count = vert_count;

			// 面ごとにハッシュに法線ベクトルをセット
			for(i=0,cvt=vtbl; i<face_count; i++,cvt++)
			{
				int count = obj->GetFacePointCount(i);
				if(count < 3) continue;

				obj->GetFacePointArray(i, vi);

				// 面中の各頂点ごとに法線ベクトルをハッシュへ格納してやる
				for(j=0; j<count; j++)
				{
					// 注目する頂点に対してのハッシュを得る
					chs = &hash[vi[j]];

					// ハッシュがまだ空ならそこに情報を格納
					if(chs->count == 0) {
						chs->nv = face_n[i];
						chs->count++;
						(*cvt)[j] = chs;
						continue;
					}

					// ハッシュが空でないなら、既に格納されている法線とのスムージング
					// 角度をチェックする必要がある。
					// アルゴリズムとしては不完全かもしれないが、とりあえず実用程度に
					// はなると思う。

					const MQPoint& pa = face_n[i];
					float da = pa.norm();
					for(; ; chs=chs->next)
					{
						// ２面の角度をチェック
						float c = 0.0f;
						if(da > 0.0f) {
							MQPoint& pb = chs->nv;
							float db = pb.norm();
							if(db > 0.0f)
								c = GetInnerProduct(pa, pb) / sqrtf(da*db);
						}
							
						// スムージング角度以内か？
						if(c >= facet)
						{
							// 注目する頂点に対して面の法線ベクトルをそのまま加算する。
							// 本来なら、注目する頂点に属する面内の２辺の角度によって
							// ベクトルの加算量を変えるべきだが、とりあえずパス。
							chs->nv += pa;
							chs->count++;
							(*cvt)[j] = chs;
							break;
						}

						// スムージングは行われないので、次のハッシュをチェック。
						// 次のハッシュデータがない場合は新規作成。
						if(chs->next == NULL) {
							(*cvt)[j] = chs->next = &hash[hash_count++];
							chs = chs->next;
							chs->nv = pa;
							chs->count = 1;
							chs->next = NULL;
							break;
						}
					}
				}
			}

			// ハッシュ中の法線ベクトルの正規化
			for(i=0,chs=hash; i<hash_count; i++,chs++) {
				if(chs->count > 1)
					chs->nv.normalize();
			}

			// 法線をバッファにセット
			for(i=0,cvt=vtbl; i<face_count; i++,cvt++)
			{
				int count = obj->GetFacePointCount(i);
				if(count < 3) continue;
				for(j=0; j<count; j++)
					normal[i*4+j] = (*cvt)[j]->nv;
				for(; j<4; j++)
					normal[i*4+j].zero();
			}

			// ハッシュを解放
			delete[] vtbl;
			delete[] hash;
		}
		break;
	}

	delete[] face_n;
}


//---------------------------------------------------------------------------
//  class MQObjEdge
//     オブジェクト中のエッジ対を管理する
//     以下のようにしてface_indexで示される面中のline_indexの辺を共有して
//     いる面のインデックスがpfに、辺のインデックスがplに得られる。
//     使用例は以下。
//
//       int pf,pl;
//       MQObjEdge *edge = new MQObjEdge(obj);
//       edge->getPair(face_index, line_index, pf, pl);
//       delete edge;
//
//---------------------------------------------------------------------------
MQObjEdge::MQObjEdge(MQObject obj)
{
	int vert_count = obj->GetVertexCount();
	int face_count = obj->GetFaceCount();

	m_obj = obj;
	m_face = face_count;
	m_pair = new MQObjEdgePairFace[face_count];

class MRelTree
{
public:
	MQObjEdgePair pair;
	int next;

	inline MRelTree() { next = -1; }
	inline MRelTree& operator = (const MRelTree& r)
		{pair=r.pair; next=r.next; return *this;}
};

	MRelTree *tree = new MRelTree[vert_count + face_count*4];

	int regvc = vert_count;
	for(int cf=0; cf<face_count; cf++)
	{
		int cvi[4];
		int cfc = obj->GetFacePointCount(cf);

		if(cfc < 3)
			continue;

		obj->GetFacePointArray(cf, cvi);

		cfc--; // decrement to be faster
		for(int j=0; j<=cfc; j++)
		{
			// check tree
			int v1 = cvi[j];
			int v2 = cvi[j<cfc? j+1 : 0];
			for(MRelTree drel=tree[v2]; drel.pair.face>=0; drel=tree[drel.next])
			{
				int dvi[4];
				int df = drel.pair.face;
				int dfc = obj->GetFacePointCount(df);
				obj->GetFacePointArray(df, dvi);
				if(m_pair[df][drel.pair.line].face < 0)
				{
					if(/*v2 == dvi[drel.pair.line]
					&&*/ v1 == dvi[drel.pair.line<dfc-1 ? drel.pair.line+1 : 0])
					{
						// set relation
						m_pair[df][drel.pair.line] = MQObjEdgePair(cf,j);
						m_pair[cf][j] = drel.pair;
						goto CR_REG_END;
					}
				}
				if(drel.next < 0) break;
			}
			// not find in tree, so regist vertex1
			MRelTree *ctr;
			for(ctr=&tree[v1]; ctr->pair.face>=0; ctr=&tree[ctr->next]){
				if(ctr->next < 0){
					ctr->next = regvc;
					ctr = &tree[regvc++];
					break;
				}
			}
			ctr->pair = MQObjEdgePair(cf,j);
CR_REG_END:;
		}
	}

	delete[] tree;
}

MQObjEdge::~MQObjEdge()
{
	delete[] m_pair;
}

bool MQObjEdge::getPair(int face_index, int line_index, int& pair_face, int& pair_line)
{
	if(face_index >= m_face)
		return false;

	if(m_pair[face_index][line_index].face < 0)
		return false;

	pair_face = m_pair[face_index][line_index].face;
	pair_line = m_pair[face_index][line_index].line;

	return true;
}


