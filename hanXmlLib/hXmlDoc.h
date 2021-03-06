////////////////////////////////////////////////////////////////////////////////
//
//  File Name:    hXmlDoc.h
//  Class Name:   hXmlDoc
//  Description:  用于描述一个文档对象
//  Author:       Fawdlstty
//  Author URI:   https://www.fawdlstty.com
//  License:      MIT
//  Last Update:  Aug 14, 2017
//
////////////////////////////////////////////////////////////////////////////////



#ifndef __H_XML_DOC_H__
#define __H_XML_DOC_H__

#include <vector>
#include <map>
#include <initializer_list>

#include "CXml/Xml.h"
using namespace JWXml;
#include "hXmlObject.h"

class hXmlDoc : public hXmlObject {
	friend class hXmlObject;

	// 创建对象需要使用静态函数进行创建
	hXmlDoc ();
public:
	virtual ~hXmlDoc ();
	hXmlDoc &operator= (hXmlDoc &o);

	// 检查当前节点是否有效
	bool is_valid ();

	// 保存文件
	bool save (CString strFile);

	// 设置SchemaLocation
	void set_schema_location (std::initializer_list<std::pair<CString, CString>> list);

public:
	// 根据文件创建对象
	static hXmlDoc create_from_file (CString strFile);

	// 根据XML字符串创建对象
	static hXmlDoc create_from_string (CString strXml);

	// 创建新对象
	static hXmlDoc create_new (CString strRootName, std::initializer_list<std::pair<CString, CString>> list);

private:
	// 创建节点
	hXmlObject create_node (CString strName, CString strPrefix = _T (""));

	// 用于通过字符串创建XML或者打开XML文档时，根据Prefix设置命名空间
	void parse_prefix ();

	CXml						m_xml;
	bool						m_bState = false;
	std::map<CString, CString>	m_map;
};

#endif //__H_XML_DOC_H__
