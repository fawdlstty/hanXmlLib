////////////////////////////////////////////////////////////////////////////////
//
//  File Name:    hXmlObject.cpp
//  Class Name:   hXmlObject
//  Description:  ��������һ���ڵ����
//  Author:       Fawdlstty
//  Author URI:   https://www.fawdlstty.com
//  License:      MIT
//  Last Update:  Aug 14, 2017
//
////////////////////////////////////////////////////////////////////////////////



#include "stdafx.h"
#include "hXmlObject.h"
#include "hXmlDoc.h"



hXmlObject::hXmlObject (hXmlDoc *pDoc) {
}

hXmlObject::hXmlObject (hXmlDoc *pDoc, CXmlNodePtr pNode) : m_pDoc (pDoc), m_pNode (pNode) {
}

hXmlObject::~hXmlObject () {
}

hXmlObject &hXmlObject::operator= (hXmlObject &o) {
	m_pDoc = o.m_pDoc;
	m_pNode = o.m_pNode;
	return *this;
}

// ��鵱ǰ�ڵ��Ƿ���Ч
bool hXmlObject::is_valid () {
	return !!m_pNode.get ();
}

// ��ȡ��ǰ�ڵ������ռ�����
CString hXmlObject::get_uri () {
	if (!is_valid ())
		return _T ("");
	CString str = m_pNode->GetName ();
	int p = str.Find (_T (':'));
	if (p >= 0)
		return str.Left (p);
	return _T ("");
}

// ��ȡ��ǰ�ڵ�����
CString hXmlObject::get_name () {
	if (!is_valid ())
		return _T ("");
	CString str = m_pNode->GetName ();
	int p = str.Find (_T (':'));
	if (p >= 0)
		return str.Right (str.GetLength () - p - 1);
	return str;
}

// �Ƴ���ǰ�ڵ�
void hXmlObject::remove () {
	if (!is_valid ())
		return;
	m_pNode->Detach ();
}

// ��ȡ�ӽڵ�����
int hXmlObject::get_child_count () {
	if (!is_valid ())
		return 0;
	return m_pNode->GetChildren ()->GetCount ();
}

// ��ȡ�ӽڵ�
hXmlObject hXmlObject::operator[] (CString strName) {
	if (!is_valid ())
		return hXmlObject (m_pDoc);
	return hXmlObject (m_pDoc, m_pNode->GetChild (strName, FALSE));
}

// ��ȡ�ӽڵ�
hXmlObject hXmlObject::operator[] (int iIndex) {
	if (!is_valid ())
		return hXmlObject (m_pDoc);
	if (iIndex < 0 || iIndex >= get_child_count ())
		return hXmlObject (m_pDoc);
	return hXmlObject (m_pDoc, m_pNode->GetChildren ()->GetItem (iIndex));
}

// �����ӽڵ�
hXmlObject hXmlObject::create_child (CString strName, CString strPrefix /*= _T ("")*/) {
	if (!is_valid ())
		return hXmlObject (m_pDoc);
	hXmlObject obj = m_pDoc->create_node (strName, strPrefix);
	m_pNode->AttachChild (obj.m_pNode);
	return obj;
}

// �Ƴ������ӽڵ�
bool hXmlObject::remove_all_children () {
	if (!is_valid ())
		return false;
	return !!m_pNode->RemoveChildren ();
}

// ��������
bool hXmlObject::set_attr (CString strName, CString strValue, CString strPrefix /*= _T ("")*/) {
	if (!is_valid ())
		return false;
	return !!m_pNode->SetAttribute (strName, strValue, strPrefix, m_pDoc->m_map [strPrefix != _T ("") ? strPrefix : _T (".")]);
}

// ��������
bool hXmlObject::set_attr (CString strName, int iValue, CString strPrefix /*= _T ("")*/) {
	if (!is_valid ())
		return false;
	CString strValue;
	strValue.Format (_T ("%d"), iValue);
	return set_attr (strName, strValue, strPrefix);
}

// ��ȡ����
CString hXmlObject::get_attr (CString strName, CString strPrefix /*= _T ("")*/) {
	if (!is_valid ())
		return _T ("");
	CString strTmpName;
	if (strPrefix != _T ("") && m_pDoc->m_map.size () != 0)
		strTmpName.Format (_T ("%s:%s"), strPrefix, strName);
	else
		strTmpName = strName;
	return m_pNode->GetAttribute (strTmpName);
}

// �Ƴ�����
bool hXmlObject::remove_attr (CString strName, CString strPrefix /*= _T ("")*/) {
	if (!is_valid ())
		return false;
	CString strTmpName;
	if (strPrefix != _T ("") && m_pDoc->m_map.size () != 0)
		strTmpName.Format (_T ("%s:%s"), strPrefix, strName);
	else
		strTmpName = strName;
	return !!m_pNode->RemoveAttribute (strTmpName);
}

// ��ȡֵ
CString hXmlObject::get_value () {
	if (!is_valid ())
		return _T ("");
	return m_pNode->GetValue ();
}

// ����ֵ
bool hXmlObject::set_value (CString strValue) {
	if (!is_valid ())
		return false;
	return !!m_pNode->SetValue (strValue);
}

// ��ȡ inner xml
CString hXmlObject::get_inner_xml () {
	if (!is_valid ())
		return _T ("");
	return m_pNode->GetInnerXml ();
}

// ��ȡ outer xml
CString hXmlObject::get_outer_xml () {
	if (!is_valid ())
		return _T ("");
	return m_pNode->GetOuterXml ();
}
