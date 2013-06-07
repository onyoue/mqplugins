#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "MQSetting.h"


// Constructor
// コンストラクタ
MQSetting::MQSetting(const char *filename, const char *section_name)
{
	m_Filename = filename;
	m_Section = section_name;
}

// Destructor
// デストラクタ
MQSetting::~MQSetting()
{
}

void MQSetting::Load(const char *name, bool& value, bool default_value)
{
	UINT ret = GetPrivateProfileInt(m_Section.c_str(), name, default_value ? 1 : 0, m_Filename.c_str());
	value = ret ? true : false;
}

void MQSetting::Load(const char *name, int& value, int default_value)
{
	UINT ret = GetPrivateProfileInt(m_Section.c_str(), name, default_value, m_Filename.c_str());
	value = (int)ret;
}

void MQSetting::Load(const char *name, unsigned int& value, unsigned int default_value)
{
	UINT ret = GetPrivateProfileInt(m_Section.c_str(), name, default_value, m_Filename.c_str());
	value = (unsigned int)ret;
}

void MQSetting::Load(const char *name, float& value, float default_value)
{
	char defstr[64], ret[2048];
	sprintf_s(defstr, sizeof(defstr), "%e", default_value);
	DWORD len = GetPrivateProfileString(m_Section.c_str(), name, defstr, ret, sizeof(ret), m_Filename.c_str());
	sscanf_s(ret, "%e", &value);
}

void MQSetting::Load(const char *name, std::string& value, const std::string& default_value)
{
	char ret[2048];
	DWORD len = GetPrivateProfileString(m_Section.c_str(), name, default_value.c_str(), ret, sizeof(ret), m_Filename.c_str());
	value = ret;
}

void MQSetting::Save(const char *name, const bool& value)
{
	char buf[64];
	sprintf_s(buf, sizeof(buf), "%d", value ? true : false);
	WritePrivateProfileString(m_Section.c_str(), name, buf, m_Filename.c_str());
}

void MQSetting::Save(const char *name, const int& value)
{
	char buf[64];
	sprintf_s(buf, sizeof(buf), "%d", value);
	WritePrivateProfileString(m_Section.c_str(), name, buf, m_Filename.c_str());
}

void MQSetting::Save(const char *name, const unsigned int& value)
{
	char buf[64];
	sprintf_s(buf, sizeof(buf), "%u", value);
	WritePrivateProfileString(m_Section.c_str(), name, buf, m_Filename.c_str());
}

void MQSetting::Save(const char *name, const float& value)
{
	char buf[64];
	sprintf_s(buf, sizeof(buf), "%e", value);
	WritePrivateProfileString(m_Section.c_str(), name, buf, m_Filename.c_str());
}

void MQSetting::Save(const char *name, const std::string& value)
{
	WritePrivateProfileString(m_Section.c_str(), name, value.c_str(), m_Filename.c_str());
}

