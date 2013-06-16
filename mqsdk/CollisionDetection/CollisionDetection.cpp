//---------------------------------------------------------------------------
//
//   Separate
//
//          Copyright(C) 1999-2012, tetraface Inc.
//
//     Sample of Select plug-in for making selected faces scattering.
//     Created DLL must be installed in "Plugins\Select" directory.
//
//    　選択した面をバラバラにする選択プラグインのサンプル。
//    　作成したDLLは"Plugins\Select"フォルダに入れる必要がある。
//
//
//---------------------------------------------------------------------------

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "MQPlugin.h"
#include <vector>
#include "AABBTree.h"

HINSTANCE hInstance;

BOOL CollisionDetect(MQDocument doc);


//---------------------------------------------------------------------------
//  DllMain
//---------------------------------------------------------------------------
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	//ダイアログボックスの表示に必要なので、インスタンスを保存しておく
	hInstance = (HINSTANCE)hModule;

	//プラグインとしては特に必要な処理はないので、何もせずにTRUEを返す
    return TRUE;
}

//---------------------------------------------------------------------------
//  MQGetPlugInID
//    プラグインIDを返す。
//    この関数は起動時に呼び出される。
//---------------------------------------------------------------------------
MQPLUGIN_EXPORT void MQGetPlugInID(DWORD *Product, DWORD *ID)
{
	// プロダクト名(制作者名)とIDを、全部で64bitの値として返す
	// 値は他と重複しないようなランダムなもので良い
	*Product = 0x19761D20;
	*ID      = 0x19760174;
}

//---------------------------------------------------------------------------
//  MQGetPlugInName
//    プラグイン名を返す。
//    この関数は[プラグインについて]表示時に呼び出される。
//---------------------------------------------------------------------------
MQPLUGIN_EXPORT const char *MQGetPlugInName(void)
{
	// プラグイン名
	return "Collision Detection";
}

//---------------------------------------------------------------------------
//  MQGetPlugInType
//    プラグインのタイプを返す。
//    この関数は起動時に呼び出される。
//---------------------------------------------------------------------------
MQPLUGIN_EXPORT int MQGetPlugInType(void)
{
	// 選択部変形用プラグインである
	return MQPLUGIN_TYPE_SELECT;
}

//---------------------------------------------------------------------------
//  MQEnumString
//    ポップアップメニューに表示される文字列を返す。
//    この関数は起動時に呼び出される。
//---------------------------------------------------------------------------
MQPLUGIN_EXPORT const char *MQEnumString(int index)
{
	switch(index){
	case 0: return "Collision Detection";
	}
	return NULL;
}

//---------------------------------------------------------------------------
//  MQModifySelect
//    メニューから選択されたときに呼び出される。
//---------------------------------------------------------------------------
MQPLUGIN_EXPORT BOOL MQModifySelect(int index, MQDocument doc)
{
	switch(index){
	case 0: return CollisionDetect(doc);
	}
	return FALSE;
}

struct {
	int segment;
} lathe;

void createVertexArray( MQObject obj, std::vector< glm::vec3 >& vertices )
{
	int face_count = obj->GetFaceCount();
	int vert_count = obj->GetVertexCount();

	int vert_index[3];

	for(int i=0; i<face_count; i++)
	{
		int count = obj->GetFacePointCount(i);
		if(count != 3)
			continue;
		
		// 独立した頂点を追加
		obj->GetFacePointArray(i, vert_index);
		for (int vert=0; vert<count; ++vert)
		{
			auto v = obj->GetVertex(vert_index[vert]);
			vertices.push_back(glm::vec3(v.x, v.y, v.z));
		}
	}
}

BOOL CollisionDetect(MQDocument doc)
{
	//int vert, vert_index[4], new_vert[4];
	//MQCoordinate uv[4];
	//MQSelectFace sel;
	BOOL result = FALSE;

	std::vector<MQObject> selectedObjs;
	int obj_count = doc->GetObjectCount();
	for (int i=0; i<obj_count; ++i)
	{
		MQObject obj = doc->GetObject(i);
		if(obj == NULL)
			continue;
		selectedObjs.push_back(obj);
	}

	if (selectedObjs.size() != 2) {
		::MessageBox(NULL, "select two objects", NULL, MB_OK);
		return FALSE;
	}
	MQObject obj1 = selectedObjs[0];
	MQObject obj2 = selectedObjs[1];

	std::vector< glm::vec3 > vertices1;
	std::vector< glm::vec3 > vertices2;

	createVertexArray(obj1, vertices1);
	createVertexArray(obj2, vertices2);

	auto aabbTree1 = std::unique_ptr<AABBNode>(CreateAABBTree(vertices1));
	auto aabbTree2 = std::unique_ptr<AABBNode>(CreateAABBTree(vertices2));

	std::vector< std::pair<AABBNode*, AABBNode*> > results;
	CollisionDetection(aabbTree1.get(), aabbTree2.get(), results);

	doc->ClearSelect(MQDOC_CLEARSELECT_FACE);
	for (int i=0; i < results.size(); ++i)
	{
		auto collisionItem  = results[i];
		//doc->AddSelectFace(obj1->GetUniqueID(), collisionItem.first->id);
		//doc->AddSelectFace(obj2->GetUniqueID(), collisionItem.second->id);
		doc->AddSelectFace(0, collisionItem.first->id);
		doc->AddSelectFace(1, collisionItem.second->id);
	}
	
	return result;
}

