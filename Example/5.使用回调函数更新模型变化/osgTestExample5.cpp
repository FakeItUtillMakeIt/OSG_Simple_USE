#include "osgTestExample5.h"

void osgTestExample5() {
	// ����ţ��ģ�͡�
	osg::Node* cow = osgDB::readNodeFile("2.osg");
	osg::Node* cow1 = osgDB::readNodeFile("1.osg");
	// �������ݱ���Ϊ STATIC����Ϊ�����в����޸�����
	cow->setDataVariance(osg::Object::STATIC);
	cow1->setDataVariance(osg::Object::STATIC);

	// ���� MatrixTransform ����ʾ��ߵ�ţ��
	osg::ref_ptr<osg::MatrixTransform> mtLeft =
		new osg::MatrixTransform;
	mtLeft->setName("Left Cow\nDYNAMIC");
	// �������ݱ���Ϊ DYNAMIC��
	// ���� OSG ����ڵ㽫�ڸ��±����б��޸ġ�
	mtLeft->setDataVariance(osg::Object::DYNAMIC);
	// ���ø��»ص���
	mtLeft->setUpdateCallback(new RotateCB);
	osg::Matrix m;
	m.makeTranslate(-6.f, 0.f, 0.f);
	mtLeft->setMatrix(m);
	mtLeft->addChild(cow);

	// ���� MatrixTransform ����ʾ�ұߵ�ţ��
	osg::ref_ptr<osg::MatrixTransform> mtRight =
		new osg::MatrixTransform;
	mtRight->setName("Right Cow\nSTATIC");

	// �������ݱ���Ϊ STATIC����Ϊ�����в����޸�����
	mtRight->setDataVariance(osg::Object::DYNAMIC);
	mtRight->setUpdateCallback(new RotateRB);
	osg::Matrix m1;
	
	m1.makeTranslate(6.f, 0.f, 0.f);
	mtRight->setMatrix(m1);
	mtRight->addChild(cow1);

	// ���� Group ���ڵ㡣
	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->setName("Root Node");

	// �������ݱ���Ϊ STATIC����Ϊ�����в����޸�����
	root->setDataVariance(osg::Object::STATIC);
	root->addChild(mtLeft.get());
	root->addChild(mtRight.get());
	
	osgViewer::Viewer viewer;
	viewer.setSceneData(root.get());
	viewer.getCamera()->setClearColor(osg::Vec4(1,1,1,1));
	viewer.run();
}
