# hanXmlLib

一个简单的XML访问库

访问库基于CXml实现。

使用MIT协议进行开源

使用方法类似如下实现：

	// 打开文档
	hXmlDoc doc = hXmlDoc::create_from_file (_T ("D:/a.xml"));
	// 根据字符串创建文档
	hXmlDoc doc2 = hXmlDoc::create_from_string (_T ("<Root><a /></Root>"));
	// 创建新文档
	hXmlDoc doc3 = hXmlDoc::create_new (_T ("RootNode"));

	// 创建节点
	hXmlObject obj = doc.create_child (_T ("ChildNode"));
	// 设置属性
	obj.set_attr (_T ("name"), _T ("aaa"));
	// 获取属性
	CString attr = obj.get_attr (_T ("name"));
	// 移除属性
	obj.remove_attr ();
	// 移除当前节点
	obj.remove ();

	// 保存当前文档
	doc.save (_T ("D:/a.xml"));

CXml是一个挺优秀的库。但这个库相对于带命名空间xml操作来说还是有些不易上手。这个库主要提供带命名空间的库的操作。使用方式是，所有的创建节点、设置参数的位置只需要传一个Prefix就行了，不用传命名空间地址。通过创建XML对象时设置命名空间列表即可实现。