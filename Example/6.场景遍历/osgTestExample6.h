#pragma once
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/NodeVisitor>


// ������ NodeVisitor ���������ڲ���ָ�����ƵĽڵ㡣
class FindNamedNode : public osg::NodeVisitor
{
public:
	FindNamedNode(const std::string& name)
		: osg::NodeVisitor( // ���������ӽڵ㡣
			//ʹ��ִ�б���
			osg::NodeVisitor::TRAVERSE_ALL_CHILDREN),
		_name(name) {}

	// ������������ó�������ͼ���е�ÿ���ڵ㣬
	// ����������Ƿ���������Ҫ��
	// ������ϵĻ���������ڵ�ĵ�ַ��
	virtual void apply(osg::Node& node)
	{
		if (node.getName() == _name)
			_node = &node;

		// ������������ͼ��ʣ��Ĳ��֡�
		traverse(node);
	}

	virtual void apply(osg::Transform& node)
	{
		if (node.getName() == _name)
			_node = &node;

		// ������������ͼ��ʣ��Ĳ��֡�
		traverse(node);
	}

	osg::Node* getNode() { return _node.get(); }

protected:
	std::string _name;
	osg::ref_ptr<osg::Node> _node;
};

void osgTestExample6();