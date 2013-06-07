//---------------------------------------------------------------------------
//
//   MQBasePlugin
//
//          Copyright(C) 1999-2012, tetraface Inc.
//
//     This is a wrapper for using C++ classes without taking care of 
//    Metasequoia plug-in interface API.
//     The API functions for each type of a plug-in are defined as the 
//    pure virtual functions, and it is necessary to implement them 
//    in an inherited class.
//
//    　Metasequoia用プラグインインターフェースをAPIレベルから隠蔽して
//    C++のクラスとして扱うためのラッパーです。
//      各プラグインの種類ごとに必須のAPIは純粋仮想関数として定義され
//    ているため、これらの関数は継承クラス側で実装を行う必要があります。
//
//---------------------------------------------------------------------------

#ifndef _MQBASEPLUGIN_H_
#define _MQBASEPLUGIN_H_

#include "MQPlugin.h"
#include <string>

class MQSetting;


// Base class for all plug-ins
// すべてのプラグインの基底クラス
class MQBasePlugin
{
public:
	// Constructor
	// コンストラクタ
	MQBasePlugin();

	// Destructor
	// デストラクタ
	virtual ~MQBasePlugin();

	// Get a plug-in ID
	// プラグインIDを返す。
	virtual void GetPlugInID(DWORD *Product, DWORD *ID) = 0;

	// Get a plug-in name
	// プラグイン名を返す。
	virtual const char *GetPlugInName(void) = 0;

	// Get a type of the plug-in
	// プラグインのタイプを返す。
	virtual int GetPlugInType(void) = 0;

	// Open a setting file
	// 設定ファイルを開く
	MQSetting *OpenSetting(void);

	// Close a setting file
	// 設定ファイルを閉じる
	void CloseSetting(MQSetting *setting);

	// Send a plug-in own mesage to other plug-ins
	// 他のプラグインにプラグイン独自のメッセージを送る
	int SendUserMessage(MQDocument doc, DWORD target_product, DWORD target_id, const char *description, void *param);
};


// Import plug-in class
// インポートプラグインクラス
class MQImportPlugin : public MQBasePlugin
{
public:
	// Get a type of the plug-in
	// プラグインのタイプを返す。
	virtual int GetPlugInType(void) { return MQPLUGIN_TYPE_IMPORT; }

	// Get a file type for importing
	// 入力出力可能なファイルタイプを返す。
	virtual const char *EnumFileType(int index) = 0;

	// Get a file extension for importing
	// 入力可能な拡張子を返す。
	virtual const char *EnumFileExt(int index) = 0;

	// Import a file
	// ファイルの読み込み
	virtual BOOL ImportFile(int index, const char *filename, MQDocument doc) = 0;

};

// Export plug-in class
// エクスポートプラグインクラス
class MQExportPlugin : public MQBasePlugin
{
public:
	// Get a type of the plug-in
	// プラグインのタイプを返す。
	virtual int GetPlugInType(void) { return MQPLUGIN_TYPE_EXPORT; }

	// Get a file type for exporting
	// 出力可能なファイルタイプを返す。
	virtual const char *EnumFileType(int index) = 0;

	// Get a file extension for exporting
	// 出力可能な拡張子を返す。
	virtual const char *EnumFileExt(int index) = 0;

	// Export a file
	// ファイルの出力
	virtual BOOL ExportFile(int index, const char *filename, MQDocument doc) = 0;

};

// Plug-in class using a menu 
// メニュー型プラグインの基底クラス
class MQMenuBasePlugin : public MQBasePlugin
{
public:
	// Get a string displayed in a menu
	// ポップアップメニューに表示される文字列を返す。
	virtual const char *EnumString(int index) = 0;

	virtual BOOL Execute(int index, MQDocument doc) = 0;
};

// Create plug-in class
// 作成プラグインクラス
class MQCreatePlugin : public MQMenuBasePlugin
{
public:
	// Get a type of the plug-in
	// プラグインのタイプを返す。
	virtual int GetPlugInType(void) { return MQPLUGIN_TYPE_CREATE; }
};

// Select plug-in class
// 選択プラグインクラス
class MQSelectPlugin : public MQMenuBasePlugin
{
public:
	// Get a type of the plug-in
	// プラグインのタイプを返す。
	virtual int GetPlugInType(void) { return MQPLUGIN_TYPE_SELECT; }
};

// Object plug-in class
// オブジェクトプラグインクラス
class MQObjectPlugin : public MQMenuBasePlugin
{
public:
	// Get a type of the plug-in
	// プラグインのタイプを返す。
	virtual int GetPlugInType(void) { return MQPLUGIN_TYPE_OBJECT; }
};

// Station plug-in class
// 常駐型プラグインクラス
/*
	常駐型プラグインのベースとなるクラスです。
	常駐型プラグインはメニュー[パネル]に項目を追加し、内部状態の変化を
	メッセージとして受け取り、プラグイン独自の処理を行います。
*/
class MQStationPlugin : public MQBasePlugin
{
public:
	// Parameters for OnNewDocument()
	// OnNewDocument()のパラメータ
	struct NEW_DOCUMENT_PARAM {
		MQXmlElement elem;	// プラグインによって保存されたXML要素
	};

	// Parameters for OnSaveDocument()
	// OnSaveDocument()のパラメータ
	struct SAVE_DOCUMENT_PARAM {
		MQXmlElement elem;	// プラグインに割り当てられた保存用XML要素
		BOOL bSaveUniqueID;	// ユニークIDを保存するかどうか
	};

	// Parameters for GetSceneOption()
	// GetSceneOption()のパラメータ
	struct SCENE_OPTION {
		BOOL ShowVertex;	// 頂点を表示
		BOOL ShowLine;		// 辺を表示
		BOOL ShowFace;		// 面を表示
		BOOL FrontOnly;		// 前面のみ表示
		BOOL ShowBkimg;		// 下絵を表示
	};

	// Coordinate type
	// 座標タイプ
	enum COORDINATE_TYPE {
		COORDINATE_SCREEN	= 0,	// スクリーン座標
		COORDINATE_WORLD	= 1,	// ワールド座標
		COORDINATE_LOCAL	= 2,	// ローカル座標
	};

public:
	// Constructor
	// コンストラクタ
	MQStationPlugin();

	// Get a type of the plug-in
	// プラグインのタイプを返す。
	virtual int GetPlugInType(void) { return MQPLUGIN_TYPE_STATION; }

	// Get a string displayed in a menu or on a button
	// ポップアップメニューまたはボタンに表示される文字列を返す。
	virtual const char *EnumString(void) = 0;

	// Initialize an application
	// アプリケーションの初期化
	virtual BOOL Initialize() = 0;
	// Exit an application
	// アプリケーションの終了
	virtual void Exit() = 0;

	// A message for activating or deactivation a window
	// 表示・非表示切り替え要求
	virtual BOOL Activate(MQDocument doc, BOOL flag) = 0;
	// A message for checking an activated state of a plug-in
	// 表示・非表示状態の返答
	virtual BOOL IsActivated(MQDocument doc) = 0;
	// A message for minimizing a window
	// ウインドウの最小化への返答
	virtual void OnMinimize(MQDocument doc, BOOL flag);
	// A message for receiving a plug-in own message
	// プラグイン独自のメッセージの受け取り
	virtual int OnReceiveUserMessage(MQDocument doc, DWORD src_product, DWORD src_id, const char *description, void *message);
	// A message for drawing
	// 描画時の処理
	virtual void OnDraw(MQDocument doc, MQScene scene, int width, int height);

	// A message for initializing a document
	// ドキュメント初期化時
	virtual void OnNewDocument(MQDocument doc, const char *filename, NEW_DOCUMENT_PARAM& param);
	// A message for exiting a document
	// ドキュメント終了時
	virtual void OnEndDocument(MQDocument doc);
	// A message for saving a document
	// ドキュメント保存時
	virtual void OnSaveDocument(MQDocument doc, const char *filename, SAVE_DOCUMENT_PARAM& param);
	// A message for an undo
	// アンドゥ実行時
	virtual BOOL OnUndo(MQDocument doc, int undo_state);
	// A message for an redo
	// リドゥ実行時
	virtual BOOL OnRedo(MQDocument doc, int redo_state);
	// A message for updating an undo state
	// アンドゥ状態更新時
	virtual void OnUpdateUndo(MQDocument doc, int undo_state, int undo_size);
	// A message for editing objects
	// オブジェクトの編集時
	virtual void OnObjectModified(MQDocument doc);
	// A message for selecting objects
	// オブジェクトの選択状態の変更時
	virtual void OnObjectSelected(MQDocument doc);
	// A message for changing a current object
	// カレントオブジェクトの変更時
	virtual void OnUpdateObjectList(MQDocument doc);
	// A message for modifying parameters of materials
	// マテリアルのパラメータ変更時
	virtual void OnMaterialModified(MQDocument doc);
	// A message for changing a current material
	// カレントマテリアルの変更時
	virtual void OnUpdateMaterialList(MQDocument doc);
	// A message for updating a scene
	// シーン情報の変更時
	virtual void OnUpdateScene(MQDocument doc, MQScene scene);


	// Begin the callback procedure
	// コールバック処理の開始
	void BeginCallback(void *option);

	// Close a window
	// ウインドウを閉じる
	void WindowClose();


private:
	struct StationCallbackInnerOption {
		MQStationPlugin *this_ptr;
		void *option;
	};

	// Callback for a procedure by the plug-in
	// プラグイン内からの処理に対するコールバック
	static BOOL __stdcall StationCallback(MQDocument doc, void *option);

protected:
	// Implementation for the callback
	// コールバックに対する実装部
	virtual bool ExecuteCallback(MQDocument doc, void *option) = 0;

	// Options for visibility in CreateDrawObject() (Multiple values are enabled.)
	// CreateDrawObject()のvisibilityに渡す引数（複数指定可）
	enum DRAW_OBJECT_VIISIBILITY {
		DRAW_OBJECT_POINT = 1,		// Show vertices | 頂点を表示
		DRAW_OBJECT_LINE = 2,		// Show lines    | ラインを表示
		DRAW_OBJECT_FACE = 4,		// Show faces    | 面を表示
		DRAW_FORCE_DWORD = 0xFFFFFFFF,
	};

	// Add a drawing object in OnDraw()
	// OnDraw()時に描画オブジェクトを追加
	MQObject CreateDrawingObject(MQDocument doc, DRAW_OBJECT_VIISIBILITY visibility, BOOL instant=TRUE);

	// Add a material for a drawing object in OnDraw()
	// OnDraw()時に描画オブジェクト用マテリアルを追加
	MQMaterial CreateDrawingMaterial(MQDocument doc, int& index, BOOL instant=TRUE);

	// Delete a drawing object
	// 描画オブジェクトを削除する
	void DeleteDrawingObject(MQDocument doc, MQObject obj);

	// Delete a material for drawing objects
	// 描画オブジェクト用マテリアルを削除する
	void DeleteDrawingMaterial(MQDocument doc, MQMaterial mat);

	// Get a current undo state
	// 現在のアンドゥの状態カウンタを取得
	int GetCurrentUndoState(MQDocument doc);

	// Get display options of the scene
	// シーンの表示オプションを取得
	void GetSceneOption(MQScene scene, SCENE_OPTION& option);
};


// Command plug-in class
// コマンド型プラグインクラス
/*
	コマンドプラグインのベースとなるクラスです。
	コマンドプラグインはコマンドパネル上にボタンを追加し、マウスなどの
	操作に応じた独自の処理を行うことができます。
*/
class MQCommandPlugin : public MQStationPlugin
{
public:
	// Parameters for mouse events
	// マウスイベント時のパラメータ
	struct MOUSE_BUTTON_STATE {
		POINT MousePos;	// マウスカーソルの位置
		int Wheel;		// マウスホイールの回転量（WHEEL_DELTAの倍数または約数）
		BOOL LButton;	// 左ボタンが押されているか
		BOOL MButton;	// 中ボタンが押されているか
		BOOL RButton;	// 右ボタンが押されているか
		BOOL Shift;		// Shiftキーが押されているか
		BOOL Ctrl;		// Ctrlキーが押されているか
		BOOL Alt;		// Altキーが押されているか
	};

	// EDIT_OPTION::SnapGrid, GetSnappedPos()への指定（複数可）
	enum SNAP_GRID_TYPE {
		SNAP_GRID_X = 1,	// X軸に吸着
		SNAP_GRID_Y = 2,	// Y軸に吸着
		SNAP_GRID_Z = 4,	// Z軸に吸着
	};

	// Parameters for GetEditOption()
	// GetEditOption()のパラメータ
	struct EDIT_OPTION {
		BOOL EditVertex;	// 頂点を編集可
		BOOL EditLine;		// ラインを編集可
		BOOL EditFace;		// 面を編集可
		BOOL SelectRect;	// 矩形選択
		BOOL SelectRope;	// 投げ縄選択
		BOOL SnapX;			// X軸に沿った編集
		BOOL SnapY;			// Y軸に沿った編集
		BOOL SnapZ;			// Z軸に沿った編集
		COORDINATE_TYPE CoordinateType;	// 座標軸の種類
		SNAP_GRID_TYPE SnapGrid;		// グリッドへの吸着
		BOOL Symmetry;		// 対象編集
		float SymmetryDistance;	// 対象とみなす距離
		BOOL CurrentObjectOnly;	// カレントオブジェクトのみを編集
	};

	// Options for GetResourceCursor()
	// GetResourceCursor()の引数
	enum MQCURSOR_TYPE {
		MQCURSOR_SIZEALL	= -22,		// ４方向矢印
		MQCURSOR_HANDPOINT	= -21,		// 指先
		MQCURSOR_HELP		= -20,		// 疑問符付き
		MQCURSOR_NO			= -18,		// 禁止
		MQCURSOR_WAIT		= -11,		// 砂時計
		MQCURSOR_UPARROW	= -10,		// 上向き矢印
		MQCURSOR_SIZEWE		= -9,		// 左右を指す両方向矢印
		MQCURSOR_SIZENWSE	= -8,		// 左上と右下を指す両方向矢印
		MQCURSOR_SIZENS		= -7,		// 上下を指す両方向矢印
		MQCURSOR_SIZENESW	= -6,		// 右上と左下を指す両方向矢印
		MQCURSOR_CROSS		= -3,		// 十字
		MQCURSOR_NONE		= -1,		// 非表示
		MQCURSOR_DEFAULT	= 0,		// 標準
		MQCURSOR_RECT		= 1,		// 範囲
		MQCURSOR_ROPE		= 2,		// 投げ縄
		MQCURSOR_MOVE		= 3,		// 移動
		MQCURSOR_SCALE		= 4, 		// 拡大
		MQCURSOR_ROTATE		= 5,		// 回転
	};

	// A type using for HitTest()
	// HitTest()で使用される型
	enum HIT_TYPE {
		HIT_TYPE_NONE	= 0,//なし
		HIT_TYPE_VERTEX	= 1,//頂点
		HIT_TYPE_LINE	= 2,//ライン
		HIT_TYPE_FACE	= 4,//面
	};

	// Parameters for HitTest()
	// HitTest()のパラメータ
	struct HIT_TEST_PARAM {
		// input
		BOOL TestVertex;	// 頂点の検知を行う
		BOOL TestLine;		// ラインを検知
		BOOL TestFace;		// 面を検知

		// output
		HIT_TYPE HitType;	// 検知されたタイプ
		MQPoint HitPos;		// 検知された位置
		int ObjectIndex;	// 検知されたオブジェクト
		int VertexIndex;	// 頂点のインデックス（頂点が検知されたときのみ）
		int LineIndex;		// ラインのインデックス（ラインが検知されたときのみ）
		int FaceIndex;		// 面のインデックス（ラインまたは面が検知されたときのみ）

		HIT_TEST_PARAM(){
			TestVertex = TestLine = TestFace = true;
		}
	};

public:
	// Constructor
	// コンストラクタ
	MQCommandPlugin();

	// Get a type of the plug-in
	// プラグインのタイプを返す。
	virtual int GetPlugInType(void) { return MQPLUGIN_TYPE_COMMAND; }
	// 表示・非表示状態の返答
	virtual BOOL IsActivated(MQDocument doc);
	// コールバックに対する実装部
	virtual bool ExecuteCallback(MQDocument doc, void *option);

	// When a left button is pressed
	// 左ボタンが押されたとき
	virtual BOOL OnLeftButtonDown(MQDocument doc, MQScene scene, MOUSE_BUTTON_STATE& state);
	// When a mouse is moved with pressing a left button
	// 左ボタンが押されながらマウスが移動したとき
	virtual BOOL OnLeftButtonMove(MQDocument doc, MQScene scene, MOUSE_BUTTON_STATE& state);
	// When a left button is released
	// 左ボタンが離されたとき
	virtual BOOL OnLeftButtonUp(MQDocument doc, MQScene scene, MOUSE_BUTTON_STATE& state);
	// When a middle button is pressed
	// 中ボタンが押されたとき
	virtual BOOL OnMiddleButtonDown(MQDocument doc, MQScene scene, MOUSE_BUTTON_STATE& state);
	// When a mouse is moved with pressing a middle button
	// 中ボタンが押されながらマウスが移動したとき
	virtual BOOL OnMiddleButtonMove(MQDocument doc, MQScene scene, MOUSE_BUTTON_STATE& state);
	// When a middle button is released
	// 中ボタンが離されたとき
	virtual BOOL OnMiddleButtonUp(MQDocument doc, MQScene scene, MOUSE_BUTTON_STATE& state);
	// When a right button is pressed
	// 右ボタンが押されたとき
	virtual BOOL OnRightButtonDown(MQDocument doc, MQScene scene, MOUSE_BUTTON_STATE& state);
	// When a mouse is moved with pressing a right button
	// 右ボタンが押されながらマウスが移動したとき
	virtual BOOL OnRightButtonMove(MQDocument doc, MQScene scene, MOUSE_BUTTON_STATE& state);
	// When a right button is released
	// 右ボタンが離されたとき
	virtual BOOL OnRightButtonUp(MQDocument doc, MQScene scene, MOUSE_BUTTON_STATE& state);
	// When a mouse is moved
	// マウスが移動したとき
	virtual BOOL OnMouseMove(MQDocument doc, MQScene scene, MOUSE_BUTTON_STATE& state);
	// When a mouse wheel is rotated
	// マウスのホイールが回転したとき
	virtual BOOL OnMouseWheel(MQDocument doc, MQScene scene, MOUSE_BUTTON_STATE& state);
	// When a key is pressed
	// キーが押されたとき
	virtual BOOL OnKeyDown(MQDocument doc, MQScene scene, int key, MOUSE_BUTTON_STATE& state);
	// When a key is released
	// キーが離されたとき
	virtual BOOL OnKeyUp(MQDocument doc, MQScene scene, int key, MOUSE_BUTTON_STATE& state);

protected:
	// Update an undo buffer
	// アンドゥバッファを更新する
	void UpdateUndo();
	// Reserve updating a scene
	// シーンの再描画を予約する
	void RedrawScene(MQScene scene);
	// Reserve updating all scenes
	// すべてのシーンの再描画を予約する
	void RedrawAllScene();
	// Get edit options
	// 編集オプションを取得
	void GetEditOption(EDIT_OPTION& option);
	// Get a snapped position
	// スナップ位置を取得
	MQPoint GetSnappedPos(MQScene scene, const MQPoint& p, SNAP_GRID_TYPE type);
	// Detect a target at the specified position at the scene
	// シーン内の指定された位置にあるものを検知
	bool HitTest(MQScene scene, POINT p, HIT_TEST_PARAM& param);
	// Get a default mouse cursor
	// 標準マウスカーソルを取得
	HCURSOR GetResourceCursor(MQCURSOR_TYPE cursor_type);
	// Get a mouse cursor
	// マウスカーソルを設定
	void SetMouseCursor(HCURSOR cursor);
	// Set a string displayed on a status bar
	// ステータスバーの文字列を設定
	void SetStatusString(const char *str);
};


// Get a plug-in class
// プラグインのベースクラスを返す
extern MQBasePlugin *GetPluginClass();


#endif _MQBASEPLUGIN_H_
