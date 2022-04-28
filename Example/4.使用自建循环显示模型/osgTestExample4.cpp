#include "osgTestExample4.h"

void osgTestExample4() {
	osgViewer::Viewer viewer;
	osg::Node* node = osgDB::readNodeFile("2.osg");
	osg::Object::DataVariance* a = new osg::Object::DataVariance(osg::Object::DYNAMIC);
	node->setDataVariance(*a);
	viewer.setSceneData(node);
	viewer.getCamera()->setProjectionMatrixAsPerspective(100, 1, 1, 50);

	//创建矩阵，指定到视点的距离
	osg::Matrix trans;
	trans.makeTranslate(0, 0, -12);
	//旋转角度
	double angle(0);
	bool flag = true;
	while (!viewer.done())
	{
		//创建旋转矩阵
		osg::Matrix rot;
		rot.makeRotate(angle, osg::Vec3(1, 0, 0));
		angle += 0.1;
		//设置视口矩阵
		viewer.getCamera()->setViewMatrix(rot * trans);
		//viewer.getCamera()->setViewMatrixAsLookAt(osg::Vec3d(0, 0, 0), osg::Vec3d(10, 0, 0), osg::Vec3d(0, 10, 1));
		//绘制下一帧
		system("pause");
		viewer.frame();
		node->asGroup()->getChild(0)->setNodeMask(flag);
	
		
		flag = !flag;
	}
}