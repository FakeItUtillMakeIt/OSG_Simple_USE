#include "osgTestExample7.h"

void osgTestExample7() {
	osgViewer::Viewer viewer;
	osg::ref_ptr<osg::Node> g = osgDB::readNodeFile("2.osg");
	viewer.setSceneData(g.get());
	viewer.addEventHandler(new PickHandler);
	viewer.run();
}