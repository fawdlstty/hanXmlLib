////////////////////////////////////////////////////////////////////////////////
//
//  File Name:    hXmlObject.h
//  Class Name:   hXmlObject
//  Description:  用于描述一个节点对象
//  Author:       Fawdlstty
//  Author URI:   https://www.fawdlstty.com
//  License:      MIT
//  Last Update:  Aug 14, 2017
//
////////////////////////////////////////////////////////////////////////////////



#ifndef __H_XML_OBJECT_H__
#define __H_XML_OBJECT_H__

#include <vector>

#include "CXml/Xml.h"
using namespace JWXml;

class hXmlDoc;

class hXmlObject {
public:
	hXmlObject (hXmlDoc *pDoc);
	hXmlObject (hXmlDoc *pDoc, CXmlNodePtr pNode);
	virtual ~hXmlObject ();
	hXmlObject (hXmlObject &o);
	hXmlObject &operator= (hXmlObject &o);

	// 检查当前节点是否有效
	bool is_valid ();

	// 获取当前节点命名空间名称
	CString get_uri ();

	// 获取当前节点名称
	CString get_name ();

	// 移除当前节点
	void remove ();

	// 获取子节点数量
	int get_child_count ();

	// 获取子节点
	hXmlObject operator[] (CString strName);

	// 获取子节点
	hXmlObject operator[] (int iIndex);

	// 创建子节点
	hXmlObject create_child (CString strName, CString strPrefix = _T (""));

	// 移除所有子节点
	bool remove_all_children ();

	// 设置属性
	bool set_attr (CString strName, CString strValue, CString strPrefix = _T (""));

	// 设置属性
	bool set_attr (CString strName, int iValue, CString strPrefix = _T (""));

	// 获取属性
	CString get_attr (CString strName, CString strPrefix = _T (""));

	// 移除属性
	bool remove_attr (CString strName, CString strPrefix = _T (""));

	// 获取所有属性
	std::vector<std::pair<CString, CString>> get_all_attr ();

	// 获取值
	CString get_value ();

	// 设置值
	bool set_value (CString strValue);

	// 获取 inner xml
	CString get_inner_xml ();

	// 获取 outer xml
	CString get_outer_xml ();

protected:
	hXmlDoc *m_pDoc = nullptr;
	CXmlNodePtr m_pNode;
};

#endif //__H_XML_OBJECT_H__
