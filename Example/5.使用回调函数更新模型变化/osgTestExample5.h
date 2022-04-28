#pragma once
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osg/Matrix>
#include <osg/Matrixd>
#include <osg/MatrixTransform>
#include <osg/Matrixf>

class RotateCB:public osg::NodeCallback
{
public:
	

	RotateCB() :_angle(0.) {

	}
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv) {
		// ͨ��Ӧ��ȷ��һ�¸��·�������update visitor���Ƿ���ڣ�
 // �������������û�б�Ҫ��������
		
		osg::MatrixTransform* mtLeft =dynamic_cast<osg::MatrixTransform*>(node);
		osg::Matrix mR, mT;
		mT.makeTranslate(-6., 0., 0.);
		mR.makeRotate(_angle, osg::Vec3(0., 0., 1.));
		mtLeft->setMatrix(mR * mT);

		// ��һ�λص�ʱ�ǶȾͻ�����
		_angle += 0.01;
		// ָ���������ݲ�����
 // ���� OSG ���Խ���ִ���������лص��Ľڵ㡣
		//RotateCB::operator()�а����˶� traverse()�ĵ��á�����һ�� osg::NodeVisitor
	/*	��ķ������������ͼ�����в�ֹһ�����»ص��Ļ���������������� OSG ��
			�������Ľڵ㲢ִ����ص���*/
		traverse(node, nv);
	}

protected:
	double _angle;

};

class RotateRB :public osg::NodeCallback
{
public:


	RotateRB() :_angle(0.) {

	}
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv) {
		// ͨ��Ӧ��ȷ��һ�¸��·�������update visitor���Ƿ���ڣ�
 // �������������û�б�Ҫ��������

		osg::MatrixTransform* mtLeft = dynamic_cast<osg::MatrixTransform*>(node);
		osg::Matrix mR, mT;
		mT.makeTranslate(6., 0., 0.);
		mR.makeRotate(_angle, osg::Vec3(0., 0., 1.));
		mtLeft->setMatrix(mR * mT);

		// ��һ�λص�ʱ�ǶȾͻ�����
		_angle += 0.05;
		// ָ���������ݲ�����
 // ���� OSG ���Խ���ִ���������лص��Ľڵ㡣
		traverse(node, nv);
	}

protected:
	double _angle;

};



void osgTestExample5();


