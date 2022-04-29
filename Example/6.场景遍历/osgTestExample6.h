#pragma once
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/NodeVisitor>


// 这个类从 NodeVisitor 派生，用于查找指定名称的节点。
class FindNamedNode : public osg::NodeVisitor
{
public:
	FindNamedNode(const std::string& name)
		: osg::NodeVisitor( // 遍历所有子节点。
			//使能执行遍历
			osg::NodeVisitor::TRAVERSE_ALL_CHILDREN),
		_name(name) {}

	// 这个方法将调用场景功能图形中的每个节点，
	// 检查其名称是否符合输入的要求。
	// 如果符合的话，将保存节点的地址。
	virtual void apply(osg::Node& node)
	{
		if (node.getName() == _name)
			_node = &node;

		// 继续遍历场景图形剩余的部分。
		traverse(node);
	}

	virtual void apply(osg::Transform& node)
	{
		if (node.getName() == _name)
			_node = &node;

		// 继续遍历场景图形剩余的部分。
		traverse(node);
	}

	osg::Node* getNode() { return _node.get(); }

protected:
	std::string _name;
	osg::ref_ptr<osg::Node> _node;
};

void osgTestExample6();