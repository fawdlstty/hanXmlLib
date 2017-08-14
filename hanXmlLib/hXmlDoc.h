////////////////////////////////////////////////////////////////////////////////
//
//  File Name:    hXmlDoc.h
//  Class Name:   hXmlDoc
//  Description:  ��������һ���ĵ�����
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

	// ����������Ҫʹ�þ�̬�������д���
	hXmlDoc ();
public:
	virtual ~hXmlDoc ();
	hXmlDoc &operator= (hXmlDoc &o);

	// ��鵱ǰ�ڵ��Ƿ���Ч
	bool is_valid ();

public:
	// �����ļ���������
	static hXmlDoc create_from_file (CString strFile);

	// ����XML�ַ�����������
	static hXmlDoc create_from_string (CString strXml);

	// �����¶���
	static hXmlDoc create_new (CString strRootName, std::initializer_list<std::pair<CString, CString>> list);

private:
	// �����ڵ�
	hXmlObject create_node (CString strName, CString strPrefix = _T (""));

	CXml						m_xml;
	bool						m_bState = false;
	std::map<CString, CString>	m_map;
};

#endif //__H_XML_DOC_H__
