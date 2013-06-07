//---------------------------------------------------------------------------
//
//   ImportDXF
//
//          Copyright(C) 1999-2012, tetraface Inc.
//
//      Sample of Import plug-in for importing a DXF (AutoCAD) file.
//      Created DLL must be installed in "Plugins\Import" directory.
//      This is just a sample. Metasequoia already contains the embedded 
//     DXF importer in the main body. There is no means to use this plug-in.
//
//    　DXF(AutoCAD)形式を入力するインポートプラグインのサンプル。
//    　作成したDLLは"Plugins\Import"フォルダに入れる必要がある。
//    　DXF形式自体がＣＡＤ向けの機能しか提供していないのと、加えて仕様の詳細
//    を知らないため、このサンプルではあまり多くの情報を入力していない。
//    なお、これは単なるサンプルであって、Metasequoiaの内部にはDXFインポート
//    機能が組み込まれているので、このプロジェクトで作成したプラグインを使う
//    意味はない。
//
//
//---------------------------------------------------------------------------

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "MQPlugin.h"
#include <fstream>

BOOL LoadSTL(const char *filename, MQDocument doc);


//---------------------------------------------------------------------------
//  DllMain
//---------------------------------------------------------------------------
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
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
	*ID      = 0x19760173;
}

//---------------------------------------------------------------------------
//  MQGetPlugInName
//    プラグイン名を返す。
//    この関数は[プラグインについて]表示時に呼び出される。
//---------------------------------------------------------------------------
MQPLUGIN_EXPORT const char *MQGetPlugInName(void)
{
	// プラグイン名
	return "STL bin Importer";
}

//---------------------------------------------------------------------------
//  MQGetPlugInType
//    プラグインのタイプを返す。
//    この関数は起動時に呼び出される。
//---------------------------------------------------------------------------
MQPLUGIN_EXPORT int MQGetPlugInType(void)
{
	// 入力用プラグインである
	return MQPLUGIN_TYPE_IMPORT;
}

//---------------------------------------------------------------------------
//  MQEnumFileType
//    入力または出力可能なファイルタイプを返す。
//    ファイルタイプは別名保存時のダイアログに表示される。
//    この関数は起動時に呼び出される。
//---------------------------------------------------------------------------
MQPLUGIN_EXPORT const char *MQEnumFileType(int index)
{
	switch(index){
	case 0: return "STL binary (*.stl)";
	}
	return NULL;
}

//---------------------------------------------------------------------------
//  MQEnumFileExt
//    入力または出力可能な拡張子を返す。
//    この関数は起動時に呼び出される。
//---------------------------------------------------------------------------
MQPLUGIN_EXPORT const char *MQEnumFileExt(int index)
{
	switch(index){
	case 0: return "stl";
	}
	return NULL;
}

//---------------------------------------------------------------------------
//  MQImportFile
//    [読み込み]やドラッグ＆ドロップで読み込むときに呼び出される。
//---------------------------------------------------------------------------
MQPLUGIN_EXPORT BOOL MQImportFile(int index, const char *filename, MQDocument doc)
{
	switch(index){
	case 0: return LoadSTL(filename, doc);
	}
	return FALSE;
}


// DXF形式を入力
BOOL LoadSTL(const char *filename, MQDocument doc)
{
	int index[3];
	MQPoint p;

    std::ifstream ifs(filename, std::ios::in | std::ios::binary);
    if (ifs.fail()) {
		return FALSE;
    }

	// オブジェクトの作成
	MQObject obj = MQ_CreateObject();
	//MQObj_SetName(obj, ""); //このサンプルでは名前は付けないのでコメントアウト

	char header[80];
    ifs.read(header, sizeof(header));
    int triangleCount = 0;
    ifs.read((char*)&triangleCount, sizeof(int));

    float tmpNormal[3];
    MQPoint tmpVertices[3];

    for (int i = 0; i < triangleCount; i++) 
	{
	    ifs.read((char*)tmpNormal, sizeof(float) * 3);
	    ifs.read((char*)tmpVertices, sizeof(float) * 9);
	    
	    char dummy[2];
	    ifs.read(dummy, 2);

		index[0] = obj->AddVertex(tmpVertices[0]);
		index[1] = obj->AddVertex(tmpVertices[2]);
		index[2] = obj->AddVertex(tmpVertices[1]);

		obj->AddFace(3, index);
    }

	// もし面がまったく登録されていないならFALSEを返す
	if(obj->GetFaceCount() == 0)
	{
		obj->DeleteThis();
		return FALSE;
	}

	// 各ポリゴンはバラバラであるため、同じ位置(実際には小数点誤差を考慮して
	// 0.0001以下の距離)にあるすべて頂点を結合する
	obj->OptimizeVertex(0.0001f, NULL);

	// オブジェクトをドキュメントへ登録
	doc->AddObject(obj);

	return TRUE;
}

