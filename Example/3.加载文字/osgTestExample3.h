#pragma once
#include <osg/Geode>
#include <osg/Group>
#include <osg/Geometry>
#include <osg/MatrixTransform>
#include <osg/StateSet>
#include <osg/StateAttribute>
#include <osg/ShadeModel>
#include <osg/CullFace>
#include <osg/PolygonMode>
#include <osg/LineWidth>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osgText/Text>
#include <osgText/Font>
#include <osgViewer/Viewer>


osg::ref_ptr<osg::Node> createScenceGraph();
osg::ref_ptr<osg::Geometry> createDrawable();
osg::ref_ptr<osg::Geometry> createDrawable1();
int osgTestExample3();