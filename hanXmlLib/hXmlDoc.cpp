////////////////////////////////////////////////////////////////////////////////
//
//  File Name:    hXmlDoc.cpp
//  Class Name:   hXmlDoc
//  Description:  ��������һ���ĵ�����
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

// ��鵱ǰ�ڵ��Ƿ���Ч
bool hXmlDoc::is_valid () {
	if (!m_bState)
		return false;
	return hXmlObject::is_valid ();
}

// �����ļ�
bool hXmlDoc::save (CString strFile) {
	return !!m_xml.SaveWithFormatted (strFile);
}

// ����SchemaLocation
void hXmlDoc::set_schema_location (std::initializer_list<std::pair<CString, CString>> list) {
	// ����Prefix
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

	// ����Uri
	CString strUri = _T (""), strTmp;
	for (std::pair<CString, CString> uri : list) {
		strTmp.Format (_T (" %s %s"), uri.first, uri.second);
		strUri += strTmp;
	}
	if (strUri.GetLength () > 0)
		strUri = strUri.Right (strUri.GetLength () - 1);
	set_attr (_T ("schemaLocation"), strUri, strPrefix);
}

// �����ļ���������
hXmlDoc hXmlDoc::create_from_file (CString strFile) {
	hXmlDoc doc;
	doc.m_bState = !!doc.m_xml.Open (strFile);
	doc.parse_prefix ();
	return doc;
}

// ����XML�ַ�����������
hXmlDoc hXmlDoc::create_from_string (CString strXml) {
	hXmlDoc doc;
	doc.m_bState = !!doc.m_xml.LoadXml (strXml);
	doc.parse_prefix ();
	return doc;
}

// �����¶���
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

// ����ͨ���ַ�������XML���ߴ�XML�ĵ�ʱ������Prefix���������ռ�
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

// �����ڵ�
hXmlObject hXmlDoc::create_node (CString strName, CString strPrefix /*= _T ("")*/) {
	if (!is_valid ())
		return hXmlObject (this);
	strPrefix = (strPrefix != _T ("") ? strPrefix : _T ("."));
	return hXmlObject (this, m_xml.CreateNode (strName, strPrefix, m_map [strPrefix]));
}
