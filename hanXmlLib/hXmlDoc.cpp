////////////////////////////////////////////////////////////////////////////////
//
//  File Name:    hXmlDoc.cpp
//  Class Name:   hXmlDoc
//  Description:  用于描述一个文档对象
//  Author:       Fawdlstty
//  Author URI:   https://www.fawdlstty.com
//  License:      MIT
//  Last Update:  Aug 14, 2017
//
////////////////////////////////////////////////////////////////////////////////



#include "stdafx.h"
#include "hXmlDoc.h"



hXmlDoc::hXmlDoc () : hXmlObject (this) {
}

hXmlDoc::~hXmlDoc () {
}

hXmlDoc &hXmlDoc::operator= (hXmlDoc &o) {
	hXmlObject::operator= (o);
	m_xml = o.m_xml;
	return *this;
}

// 检查当前节点是否有效
bool hXmlDoc::is_valid () {
	if (!m_bState)
		return false;
	return hXmlObject::is_valid ();
}

// 保存文件
bool hXmlDoc::save (CString strFile) {
	return !!m_xml.SaveWithFormatted (strFile);
}

// 设置SchemaLocation
void hXmlDoc::set_schema_location (std::initializer_list<std::pair<CString, CString>> list) {
	// 生成Prefix
	CString strPrefix = _T ("");
	for (std::pair<CString, CString> namesp : m_map) {
		if (namesp.second == _T ("http://www.w3.org/2001/XMLSchema-instance"))
			strPrefix = namesp.first;
	}
	if (strPrefix == _T ("")) {
		m_map [_T ("xsi")] = _T ("http://www.w3.org/2001/XMLSchema-instance");
		set_attr (_T ("xmlns:xsi"), m_map [_T ("xsi")]);
		strPrefix = _T ("xsi");
	}

	// 生成Uri
	CString strUri = _T (""), strTmp;
	for (std::pair<CString, CString> uri : list) {
		strTmp.Format (_T (" %s %s"), uri.first, uri.second);
		strUri += strTmp;
	}
	if (strUri.GetLength () > 0)
		strUri = strUri.Right (strUri.GetLength () - 1);
	set_attr (_T ("schemaLocation"), strUri, strPrefix);
}

// 根据文件创建对象
hXmlDoc hXmlDoc::create_from_file (CString strFile) {
	hXmlDoc doc;
	doc.m_bState = !!doc.m_xml.Open (strFile);
	doc.parse_prefix ();
	return doc;
}

// 根据XML字符串创建对象
hXmlDoc hXmlDoc::create_from_string (CString strXml) {
	hXmlDoc doc;
	doc.m_bState = !!doc.m_xml.LoadXml (strXml);
	doc.parse_prefix ();
	return doc;
}

// 创建新对象
hXmlDoc hXmlDoc::create_new (CString strRootName, std::initializer_list<std::pair<CString, CString>> list) {
	hXmlDoc doc;
	doc.m_bState = !!doc.m_xml.Create (strRootName);
	for (std::pair<CString, CString> item : list) {
		CString strPrefix = (item.first != _T ("") ? item.first : _T ("."));
		doc.m_map [strPrefix] = item.second;
		doc.set_attr (_T ("xmlns"), item.second, item.first);
	}
	return doc;
}

// 用于通过字符串创建XML或者打开XML文档时，根据Prefix设置命名空间
void hXmlDoc::parse_prefix () {
	std::vector<std::pair<CString, CString>> v_attr = get_all_attr ();
	for (std::pair<CString, CString> attr : v_attr) {
		CString strPrefix = attr.first, strUri = attr.second;
		if (strPrefix.GetLength () >= 5 && strPrefix.Left (5) == _T ("xmlns")) {
			if (strPrefix.GetLength () == 5)
				strPrefix = _T (".");
			else
				strPrefix = strPrefix.Right (strPrefix.GetLength () - 6);
			m_map [strPrefix] = strUri;
		}
	}
}

// 创建节点
hXmlObject hXmlDoc::create_node (CString strName, CString strPrefix /*= _T ("")*/) {
	if (!is_valid ())
		return hXmlObject (this);
	strPrefix = (strPrefix != _T ("") ? strPrefix : _T ("."));
	return hXmlObject (this, m_xml.CreateNode (strName, strPrefix, m_map [strPrefix]));
}
