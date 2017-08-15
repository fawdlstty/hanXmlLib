////////////////////////////////////////////////////////////////////////////////
//
//  File Name:    hXmlObject.cpp
//  Class Name:   hXmlObject
//  Description:  用于描述一个节点对象
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

hXmlObject::hXmlObject (hXmlObject &o) {
	m_pDoc = o.m_pDoc;
	m_pNode = o.m_pNode;
}

hXmlObject &hXmlObject::operator= (hXmlObject &o) {
	m_pDoc = o.m_pDoc;
	m_pNode = o.m_pNode;
	return *this;
}

// 检查当前节点是否有效
bool hXmlObject::is_valid () {
	return !!m_pNode.get ();
}

// 获取当前节点命名空间名称
CString hXmlObject::get_uri () {
	if (!is_valid ())
		return _T ("");
	CString str = m_pNode->GetName ();
	int p = str.Find (_T (':'));
	if (p >= 0)
		return str.Left (p);
	return _T ("");
}

// 获取当前节点名称
CString hXmlObject::get_name () {
	if (!is_valid ())
		return _T ("");
	CString str = m_pNode->GetName ();
	int p = str.Find (_T (':'));
	if (p >= 0)
		return str.Right (str.GetLength () - p - 1);
	return str;
}

// 移除当前节点
void hXmlObject::remove () {
	if (!is_valid ())
		return;
	m_pNode->Detach ();
}

// 获取子节点数量
int hXmlObject::get_child_count () {
	if (!is_valid ())
		return 0;
	return m_pNode->GetChildren ()->GetCount ();
}

// 获取子节点
hXmlObject hXmlObject::operator[] (CString strName) {
	if (!is_valid ())
		return hXmlObject (m_pDoc);
	return hXmlObject (m_pDoc, m_pNode->GetChild (strName, FALSE));
}

// 获取子节点
hXmlObject hXmlObject::operator[] (int iIndex) {
	if (!is_valid ())
		return hXmlObject (m_pDoc);
	if (iIndex < 0 || iIndex >= get_child_count ())
		return hXmlObject (m_pDoc);
	return hXmlObject (m_pDoc, m_pNode->GetChildren ()->GetItem (iIndex));
}

// 创建子节点
hXmlObject hXmlObject::create_child (CString strName, CString strPrefix /*= _T ("")*/) {
	if (!is_valid ())
		return hXmlObject (m_pDoc);
	hXmlObject obj = m_pDoc->create_node (strName, strPrefix);
	m_pNode->AttachChild (obj.m_pNode);
	return obj;
}

// 移除所有子节点
bool hXmlObject::remove_all_children () {
	if (!is_valid ())
		return false;
	return !!m_pNode->RemoveChildren ();
}

// 设置属性
bool hXmlObject::set_attr (CString strName, CString strValue, CString strPrefix /*= _T ("")*/) {
	if (!is_valid ())
		return false;
	return !!m_pNode->SetAttribute (strName, strValue, strPrefix, m_pDoc->m_map [strPrefix != _T ("") ? strPrefix : _T (".")]);
}

// 设置属性
bool hXmlObject::set_attr (CString strName, int iValue, CString strPrefix /*= _T ("")*/) {
	if (!is_valid ())
		return false;
	CString strValue;
	strValue.Format (_T ("%d"), iValue);
	return set_attr (strName, strValue, strPrefix);
}

// 获取属性
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

// 移除属性
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

// 获取所有属性
std::vector<std::pair<CString, CString>> hXmlObject::get_all_attr () {
	std::vector<std::pair<CString, CString>> v_attr;
	CString strXml = this->get_outer_xml ();
	strXml = strXml.Left (strXml.Find (_T (">")) + 1);

	int state = 0;
	CString strPrefix = _T (""), strUri = _T ("");
	for (int i = 0, state = 0; i < strXml.GetLength (); ++i) {
		TCHAR tch = strXml [i];
		if (state == 0) { // 还未进入节点标签
			if ((tch >= _T ('A') && tch <= _T ('Z')) || (tch >= _T ('a') && tch <= _T ('z')))
				++state;
		} else if (state == 1) { // 在节点标签中
			if (tch == _T (' ') || tch == _T ('\t'))
				++state;
		} else if (state == 2) { // 待进入属性Prefix
			if ((tch >= _T ('A') && tch <= _T ('Z')) || (tch >= _T ('a') && tch <= _T ('z'))) {
				++state;
				strPrefix += tch;
			}
		} else if (state == 3) { // 在属性的Prefix中
			if (tch == _T (' ') || tch == _T ('\t') || tch == _T ('='))
				++state;
			else
				strPrefix += tch;
		} else if (state == 4) { // 待进入属性Uri
			if ((tch >= _T ('A') && tch <= _T ('Z')) || (tch >= _T ('a') && tch <= _T ('z'))) {
				++state;
				strUri += tch;
			}
		} else if (state == 5) { // 在属性的Uri中
			if (tch == _T (' ') || tch == _T ('\t') || tch == _T ('>')) {
				state = 2;
				v_attr.push_back (std::make_pair (strPrefix, strUri));
				strPrefix = strUri = _T ("");
			}
			else
				strUri += tch;
		}
	}
	return v_attr;
}

// 获取值
CString hXmlObject::get_value () {
	if (!is_valid ())
		return _T ("");
	return m_pNode->GetValue ();
}

// 设置值
bool hXmlObject::set_value (CString strValue) {
	if (!is_valid ())
		return false;
	return !!m_pNode->SetValue (strValue);
}

// 获取 inner xml
CString hXmlObject::get_inner_xml () {
	if (!is_valid ())
		return _T ("");
	return m_pNode->GetInnerXml ();
}

// 获取 outer xml
CString hXmlObject::get_outer_xml () {
	if (!is_valid ())
		return _T ("");
	return m_pNode->GetOuterXml ();
}
