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

// �����ļ���������
hXmlDoc hXmlDoc::create_from_file (CString strFile) {
	hXmlDoc doc;
	doc.m_bState = !!doc.m_xml.Open (strFile);
	return doc;
}

// ����XML�ַ�����������
hXmlDoc hXmlDoc::create_from_string (CString strXml) {
	hXmlDoc doc;
	doc.m_bState = !!doc.m_xml.LoadXml (strXml);
	return doc;
}

// �����¶���
hXmlDoc hXmlDoc::create_new (CString strRootName, std::initializer_list<std::pair<CString, CString>> list) {
	hXmlDoc doc;
	doc.m_bState = !!doc.m_xml.Create (strRootName);
	for (std::pair<CString, CString> item : list) {
		CString strPrefix = (item.first != _T ("") ? item.first : _T ("."));
		doc.m_map [strPrefix] = item.second;
	}
	return doc;
}

// �����ڵ�
hXmlObject hXmlDoc::create_node (CString strName, CString strPrefix /*= _T ("")*/) {
	if (!is_valid ())
		return hXmlObject (this);
	strPrefix = (strPrefix != _T ("") ? strPrefix : _T ("."));
	return hXmlObject (this, m_xml.CreateNode (strName, strPrefix, m_map [strPrefix]));
}
