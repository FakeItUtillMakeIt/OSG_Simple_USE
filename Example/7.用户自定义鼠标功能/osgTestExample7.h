#pragma once
//�ṩ�¼���
#include <osgGA/Event>
//�ṩ������
#include <osgUtil/IntersectionVisitor>
//�ӿھ������
#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgGA/EventHandler>
#include <osgGA/GUIEventHandler>
#include <osgGA/Device>
#include <osg/MatrixTransform>
#include <osgGA/GUIActionAdapter>

#include "osgTestExample5.h"

//������� 3D ������Ҫĳ����ʽ���û�ѡ���ܣ��ն��û������Դ�����
//����ѡ��ǰ����ʾ�Ļ����ĳ��һ���֡��û�ѡ������򵥵���ʽΪ���û���
//����ƶ����������ض���λ�ã��������ꡣ�����ڲ����������㣬�Ա㽫 2D
//����� XY ����λ��ӳ�䵽��ȷ�� 3D ����ͼ�νڵ��ϣ�������ڵ��ַ�Ա㽫
//��ʹ�á�

//�ӱ�����˵��OSG ����ͨ������������ʵ���û�ѡ��
//z
//��������¼���osgGA ���ṩ����������������¼����¼��࣬����
//��ƽ̨�޹ص����ԡ�
//z
//�жϳ���ͼ�ε��ĸ����ֱ�����긲�ǡ�osgUtil ���ṩ��һ���ཻ��
//��intersection���࣬��������� XY �������Χ������Χ�У����жϰ�
//Χ���볡��ͼ�ε��ཻ�����osgUtil ��������ǰ�����˳�򷵻����Χ
//���ཻ�Ľڵ��б�
//���ڽ��������ʵ������������Ĳ�����

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
			// �������ڰ��°���ʱû���ƶ�����ôִ���û�ѡ��Ĵ���
			// ������Ĭ�ϵ�������������д���
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
		if (!viewer->getSceneData()) // û�п���ѡ��ġ�
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
				// ���ҽ����ڵ�·���е����һ�� MatrixTransform��
				// �����ǽ�Ҫ��ص��������ѡ������
				osg::MatrixTransform* mt =
					dynamic_cast<osg::MatrixTransform*>(
						nodePath[idx]);
				if (mt == NULL)
					continue;

				// �������
				// ˵�����ڽڵ�·�����ҵ�������� MatrixTransform��
				if (_selectedNode.valid())
					// ���ԭ����ѡ��ڵ�ص����Ա�֤��ֹͣ���С�
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
