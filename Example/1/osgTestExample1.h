#pragma once

#include <iostream>
#include <osg/ref_ptr>
#include <osgDB/Registry>
#include <osgDB/WriteFile>
#include <osg/Notify>
#include <osg/Geode>
#include <osg/Geometry>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>

using namespace std;

osg::ref_ptr<osg::Group> createScenceGraph();
osg::ref_ptr<osg::Group> createScenceGraph1();
int osgTestExample1();
int osgTestExample1_1();