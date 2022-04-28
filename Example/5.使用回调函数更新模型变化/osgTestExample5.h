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
		// 通常应该确认一下更新访问器（update visitor）是否存在，
 // 不过这个例子中没有必要这样做。
		
		osg::MatrixTransform* mtLeft =dynamic_cast<osg::MatrixTransform*>(node);
		osg::Matrix mR, mT;
		mT.makeTranslate(-6., 0., 0.);
		mR.makeRotate(_angle, osg::Vec3(0., 0., 1.));
		mtLeft->setMatrix(mR * mT);

		// 下一次回调时角度就会增大。
		_angle += 0.01;
		// 指定继续传递参数，
 // 这样 OSG 可以接着执行其它带有回调的节点。
		//RotateCB::operator()中包含了对 traverse()的调用。这是一个 osg::NodeVisitor
	/*	类的方法。如果场景图形中有不止一个更新回调的话，这个方法将允许 OSG 访
			问其它的节点并执行其回调。*/
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
		// 通常应该确认一下更新访问器（update visitor）是否存在，
 // 不过这个例子中没有必要这样做。

		osg::MatrixTransform* mtLeft = dynamic_cast<osg::MatrixTransform*>(node);
		osg::Matrix mR, mT;
		mT.makeTranslate(6., 0., 0.);
		mR.makeRotate(_angle, osg::Vec3(0., 0., 1.));
		mtLeft->setMatrix(mR * mT);

		// 下一次回调时角度就会增大。
		_angle += 0.05;
		// 指定继续传递参数，
 // 这样 OSG 可以接着执行其它带有回调的节点。
		traverse(node, nv);
	}

protected:
	double _angle;

};



void osgTestExample5();


