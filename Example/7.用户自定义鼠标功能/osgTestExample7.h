#pragma once
//提供事件类
#include <osgGA/Event>
//提供工具类
#include <osgUtil/IntersectionVisitor>
//视口矩阵控制
#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgGA/EventHandler>
#include <osgGA/GUIEventHandler>
#include <osgGA/Device>
#include <osg/MatrixTransform>
#include <osgGA/GUIActionAdapter>

#include "osgTestExample5.h"

//大多数的 3D 程序都需要某种形式的用户选择功能，终端用户可以以此来交
//互地选择当前被显示的画面的某个一部分。用户选择中最简单的形式为，用户将
//鼠标移动到场景中特定的位置，并点击鼠标。程序内部将进行运算，以便将 2D
//的鼠标 XY 坐标位置映射到正确的 3D 场景图形节点上，并保存节点地址以便将
//来使用。

//从本质上说，OSG 程序通过两个步骤来实现用户选择。
//z
//接收鼠标事件。osgGA 库提供了允许程序接收鼠标事件的事件类，它具
//备平台无关的特性。
//z
//判断场景图形的哪个部分被鼠标光标覆盖。osgUtil 库提供了一种相交集
//（intersection）类，可以在鼠标 XY 坐标的周围创建包围盒，并判断包
//围盒与场景图形的相交情况。osgUtil 将按照由前至后的顺序返回与包围
//盒相交的节点列表。
//本节将讨论如何实现这两个步骤的操作。

class PickHandler:public osgGA::GUIEventHandler
{
public:
	PickHandler() :_mX(0), _mY(0) {

	}
	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) {
		osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
		if (!viewer)
		{
			return false;
		}
		switch (ea.getEventType())
		{
		case osgGA::GUIEventAdapter::PUSH:
		{
  			_mX = ea.getX();
			_mY = ea.getY();
			
			return true;
		}
		//case osgGA::GUIEventAdapter::MOVE:
	
		case osgGA::GUIEventAdapter::DOUBLECLICK:
		{
			// 如果鼠标在按下按键时没有移动，那么执行用户选择的处理，
			// 否则将由默认的鼠标控制器类进行处理
			if (_mX==ea.getX() && _mY==ea.getY())
			{
				auto a = ea.getXnormalized();
				auto b = ea.getYnormalized();
				if (pick(a,b,viewer))
				{
					return true;
				}
				return false;
			}
			
		}

		default:
			break;
		}
	}
	~PickHandler() {

	}

protected:
	float _mX, _mY;
	osg::ref_ptr<osg::MatrixTransform>  _selectedNode;
	

	bool pick(const double x, const double y, osgViewer::Viewer* viewer)
	{
		if (!viewer->getSceneData()) // 没有可以选择的。
			return false;

		double w(0.05), h(0.05);
		osgUtil::PolytopeIntersector* picker =
			new osgUtil::PolytopeIntersector(
				osgUtil::Intersector::PROJECTION, x - w, y - h, x + w, y + h);
		osgUtil::IntersectionVisitor iv(picker);
		viewer->getCamera()->accept(iv);
		if (picker->containsIntersections())
		{
			osg::NodePath nodePath =
				picker->getFirstIntersection().nodePath;
			unsigned int idx = nodePath.size();
			while (idx--)
			{
				// 查找交集节点路径中的最后一个 MatrixTransform；
				// 它就是将要与回调相关联的选择结果。
				osg::MatrixTransform* mt =
					dynamic_cast<osg::MatrixTransform*>(
						nodePath[idx]);
				if (mt == NULL)
					continue;

				// 到了这里，
				// 说明已在节点路径中找到了所需的 MatrixTransform。
				if (_selectedNode.valid())
					// 清除原来的选择节点回调，以保证它停止运行。
					_selectedNode->setUpdateCallback(NULL);
				_selectedNode = mt;
				_selectedNode->addChild(viewer->asNode());
				_selectedNode->setUpdateCallback(new RotateCB);
				
				break;
			}
			if (!_selectedNode.valid())
				osg::notify() << "Pick failed." << std::endl;
		}
		else if (_selectedNode.valid())
		{
			_selectedNode->setUpdateCallback(NULL);
			_selectedNode = NULL;
		}
		return _selectedNode.valid();
	
	}

};



void osgTestExample7();
