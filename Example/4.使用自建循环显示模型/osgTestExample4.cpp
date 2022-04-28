#include "osgTestExample4.h"

void osgTestExample4() {
	osgViewer::Viewer viewer;
	osg::Node* node = osgDB::readNodeFile("2.osg");
	osg::Object::DataVariance* a = new osg::Object::DataVariance(osg::Object::DYNAMIC);
	node->setDataVariance(*a);
	viewer.setSceneData(node);
	viewer.getCamera()->setProjectionMatrixAsPerspective(100, 1, 1, 50);

	//��������ָ�����ӵ�ľ���
	osg::Matrix trans;
	trans.makeTranslate(0, 0, -12);
	//��ת�Ƕ�
	double angle(0);
	bool flag = true;
	while (!viewer.done())
	{
		//������ת����
		osg::Matrix rot;
		rot.makeRotate(angle, osg::Vec3(1, 0, 0));
		angle += 0.1;
		//�����ӿھ���
		viewer.getCamera()->setViewMatrix(rot * trans);
		//viewer.getCamera()->setViewMatrixAsLookAt(osg::Vec3d(0, 0, 0), osg::Vec3d(10, 0, 0), osg::Vec3d(0, 10, 1));
		//������һ֡
		system("pause");
		viewer.frame();
		node->asGroup()->getChild(0)->setNodeMask(flag);
	
		
		flag = !flag;
	}
}