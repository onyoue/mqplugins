//---------------------------------------------------------------------------
//
//   MQSetting
//
//          Copyright(C) 1999-2012, tetraface Inc.
//
//	   A class for accessing .ini files used to save settings. By using 
//    this class, it is easy to keep a compatibility for the future 
//    version.
//
//    　Metasequoiaが設定を保存するためのiniファイルにアクセスする
//    クラスです。
//      将来、設定ファイルがXMLファイルなどに変更されても、このクラスを
//    介してアクセスすればコードレベルでの互換性は保ちやすくなります。
//
//---------------------------------------------------------------------------

#ifndef _MQSETTING_H_
#define _MQSETTING_H_

#include <string>

// Class for accessing a setting file
// 設定ファイルへのアクセス関数
class MQSetting
{
public:
	// Constructor
	// コンストラクタ
	MQSetting(const char *filename, const char *section_name);

	// Destructor
	// デストラクタ
	virtual ~MQSetting();

	// Load the specified item with a name
	// 名前指定された項目の読み込み
	void Load(const char *name, bool& value, bool default_value=false);
	void Load(const char *name, int& value, int default_value=0);
	void Load(const char *name, unsigned int& value, unsigned int default_value=0);
	void Load(const char *name, float& value, float default_value=0.0f);
	void Load(const char *name, std::string& value, const std::string& default_value="");

	// Save the specified item with a name
	// 名前指定された項目の出力
	void Save(const char *name, const bool& value);
	void Save(const char *name, const int& value);
	void Save(const char *name, const unsigned int& value);
	void Save(const char *name, const float& value);
	void Save(const char *name, const std::string& value);

private:
	std::string m_Filename;
	std::string m_Section;
};


#endif _MQSETTING_H_
