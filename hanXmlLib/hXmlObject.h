////////////////////////////////////////////////////////////////////////////////
//
//  File Name:    hXmlObject.h
//  Class Name:   hXmlObject
//  Description:  ��������һ���ڵ����
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

	// ��鵱ǰ�ڵ��Ƿ���Ч
	bool is_valid ();

	// ��ȡ��ǰ�ڵ������ռ�����
	CString get_uri ();

	// ��ȡ��ǰ�ڵ�����
	CString get_name ();

	// �Ƴ���ǰ�ڵ�
	void remove ();

	// ��ȡ�ӽڵ�����
	int get_child_count ();

	// ��ȡ�ӽڵ�
	hXmlObject operator[] (CString strName);

	// ��ȡ�ӽڵ�
	hXmlObject operator[] (int iIndex);

	// �����ӽڵ�
	hXmlObject create_child (CString strName, CString strPrefix = _T (""));

	// �Ƴ������ӽڵ�
	bool remove_all_children ();

	// ��������
	bool set_attr (CString strName, CString strValue, CString strPrefix = _T (""));

	// ��������
	bool set_attr (CString strName, int iValue, CString strPrefix = _T (""));

	// ��ȡ����
	CString get_attr (CString strName, CString strPrefix = _T (""));

	// �Ƴ�����
	bool remove_attr (CString strName, CString strPrefix = _T (""));

	// ��ȡ��������
	std::vector<std::pair<CString, CString>> get_all_attr ();

	// ��ȡֵ
	CString get_value ();

	// ����ֵ
	bool set_value (CString strValue);

	// ��ȡ inner xml
	CString get_inner_xml ();

	// ��ȡ outer xml
	CString get_outer_xml ();

protected:
	hXmlDoc *m_pDoc = nullptr;
	CXmlNodePtr m_pNode;
};

#endif //__H_XML_OBJECT_H__
