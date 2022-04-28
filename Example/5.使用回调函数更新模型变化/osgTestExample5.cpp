#include "osgTestExample5.h"

void osgTestExample5() {
	// 加载牛的模型。
	osg::Node* cow = osgDB::readNodeFile("2.osg");
	osg::Node* cow1 = osgDB::readNodeFile("1.osg");
	// 设置数据变量为 STATIC，因为程序中不会修改它。
	cow->setDataVariance(osg::Object::STATIC);
	cow1->setDataVariance(osg::Object::STATIC);

	// 创建 MatrixTransform 来显示左边的牛。
	osg::ref_ptr<osg::MatrixTransform> mtLeft =
		new osg::MatrixTransform;
	mtLeft->setName("Left Cow\nDYNAMIC");
	// 设置数据变量为 DYNAMIC，
	// 告诉 OSG 这个节点将在更新遍历中被修改。
	mtLeft->setDataVariance(osg::Object::DYNAMIC);
	// 设置更新回调。
	mtLeft->setUpdateCallback(new RotateCB);
	osg::Matrix m;
	m.makeTranslate(-6.f, 0.f, 0.f);
	mtLeft->setMatrix(m);
	mtLeft->addChild(cow);

	// 创建 MatrixTransform 来显示右边的牛。
	osg::ref_ptr<osg::MatrixTransform> mtRight =
		new osg::MatrixTransform;
	mtRight->setName("Right Cow\nSTATIC");

	// 设置数据变量为 STATIC，因为程序中不会修改它。
	mtRight->setDataVariance(osg::Object::DYNAMIC);
	mtRight->setUpdateCallback(new RotateRB);
	osg::Matrix m1;
	
	m1.makeTranslate(6.f, 0.f, 0.f);
	mtRight->setMatrix(m1);
	mtRight->addChild(cow1);

	// 创建 Group 根节点。
	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->setName("Root Node");

	// 设置数据变量为 STATIC，因为程序中不会修改它。
	root->setDataVariance(osg::Object::STATIC);
	root->addChild(mtLeft.get());
	root->addChild(mtRight.get());
	
	osgViewer::Viewer viewer;
	viewer.setSceneData(root.get());
	viewer.getCamera()->setClearColor(osg::Vec4(1,1,1,1));
	viewer.run();
}
