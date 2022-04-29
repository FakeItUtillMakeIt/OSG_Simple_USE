#include "osgTestExample6.h"

void osgTestExample6() {
	//从场景中寻找对应节点

	osg::ref_ptr<osg::Node> geode = osgDB::readNodeFile("2.osg");
	FindNamedNode findNNode("1");
	geode->accept(findNNode);

}