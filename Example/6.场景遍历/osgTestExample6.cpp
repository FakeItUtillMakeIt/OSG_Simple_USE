#include "osgTestExample6.h"

void osgTestExample6() {
	//�ӳ�����Ѱ�Ҷ�Ӧ�ڵ�

	osg::ref_ptr<osg::Node> geode = osgDB::readNodeFile("2.osg");
	FindNamedNode findNNode("1");
	geode->accept(findNNode);

}