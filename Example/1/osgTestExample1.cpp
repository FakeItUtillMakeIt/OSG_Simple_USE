#include "osgTestExample1.h"

//创建一个视图
osg::ref_ptr<osg::Group> createScenceGraph() {
	osg::ref_ptr<osg::Geometry> geom1 = new osg::Geometry;

	// 创建四个顶点的数组

	osg::ref_ptr<osg::Vec3Array> v1 = new osg::Vec3Array;
	geom1->setVertexArray(v1.get());
	v1->push_back(osg::Vec3(1.f, 0.f, -1.f));
	v1->push_back(osg::Vec3(1.f, 0.f, -1.f));
	v1->push_back(osg::Vec3(1.f, 0.f, 1.f));
	v1->push_back(osg::Vec3(-2.f, 0.f, 1.f));

	// 创建四种颜色的数组

	osg::ref_ptr<osg::Vec4Array> c1 = new osg::Vec4Array;

	geom1->setColorArray(c1.get());
	geom1->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	c1->push_back(osg::Vec4(1.f, 0.f, 0.f, 1.f));
	c1->push_back(osg::Vec4(0.f, 1.f, 0.f, 1.f));
	c1->push_back(osg::Vec4(0.f, 0.f, 1.f, 1.f));
	c1->push_back(osg::Vec4(1.f, 1.f, 1.f, 1.f));

	// 为唯一的法线创建一个数组

	osg::ref_ptr<osg::Vec3Array> n1 = new osg::Vec3Array;

	//设置法线数据绑定方式

	geom1->setNormalArray(n1.get());


	geom1->setNormalBinding(osg::Geometry::BIND_OVERALL);

	n1->push_back(osg::Vec3(0.f, 1.f, 0.f));

	// 由保存的数据绘制四个顶点的多边形

	geom1->addPrimitiveSet(
		new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	//root节点
	osg::ref_ptr<osg::Group> group = new osg::Group;
	// 向 Geode 类添加几何体（Drawable）并返回 Geode 


	osg::ref_ptr<osg::Geode> geode1 = new osg::Geode;
	geode1->addDrawable(geom1.get());

	osg::ref_ptr<osg::LOD> lod = new osg::LOD;
	lod->addChild(geom1, 0, 1000);
	lod->setCenterMode(osg::LOD::USER_DEFINED_CENTER);
	lod->setCenter(osg::Vec3(0, 0, 0));

	group->addChild(lod.get());

	return group.get();
}

osg::ref_ptr<osg::Group> createScenceGraph1() {
	// 创建一个用于保存几何信息的对象
	
	osg::ref_ptr<osg::Geometry> geom1 = new osg::Geometry;

	// 创建四个顶点的数组

	osg::ref_ptr<osg::Vec3Array> v1 = new osg::Vec3Array;
	geom1->setVertexArray(v1.get());
	v1->push_back(osg::Vec3(0.f, 0.f, -1.f));
	v1->push_back(osg::Vec3(0.f, 1.f, 0.f));
	v1->push_back(osg::Vec3(0.f, 0.f, 1.f));
	v1->push_back(osg::Vec3(-1.f, 0.f, 1.f));

	// 创建四种颜色的数组
	
	osg::ref_ptr<osg::Vec4Array> c1 = new osg::Vec4Array;
	
	geom1->setColorArray(c1.get());
	geom1->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	c1->push_back(osg::Vec4(1.f, 0.f, 0.f, 1.f));
	c1->push_back(osg::Vec4(0.f, 1.f, 0.f, 1.f));
	c1->push_back(osg::Vec4(0.f, 0.f, 1.f, 1.f));
	c1->push_back(osg::Vec4(1.f, 1.f, 1.f, 1.f));

	// 为唯一的法线创建一个数组

	osg::ref_ptr<osg::Vec3Array> n1 = new osg::Vec3Array;

	//设置法线数据绑定方式

	geom1->setNormalArray(n1.get());

	
	geom1->setNormalBinding(osg::Geometry::BIND_OVERALL);
	
	n1->push_back(osg::Vec3(0.f, 1.f, 0.f));

	// 由保存的数据绘制四个顶点的多边形
	
	geom1->addPrimitiveSet(
		new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP, 0, 4));

	//root节点
	osg::ref_ptr<osg::Group> group = new osg::Group;
	// 向 Geode 类添加几何体（Drawable）并返回 Geode 
	
	
	osg::ref_ptr<osg::Geode> geode1 = new osg::Geode;
	geode1->addDrawable(geom1.get());

	osg::ref_ptr<osg::LOD> lod = new osg::LOD;
	lod->addChild(geom1, 0, 1000);
	lod->setCenterMode(osg::LOD::USER_DEFINED_CENTER);
	lod->setCenter(osg::Vec3(0, 0, 0));

	group->addChild(lod.get());

	return group.get();
}

int osgTestExample1()
{

	/*osg::ref_ptr<osg::Node> root = createScenceGraph();
	if (!root.valid())
	{
		osg::notify(osg::FATAL) << "Failed in createScenceGraph" << endl;
	}

    bool result = osgDB::writeNodeFile(*(root.get()), "1.osg");
    if (!result)
    {
        osg::notify(osg::FATAL) << "Failed in osgDB::writeNode" << endl;
    }*/

	osg::ref_ptr<osg::Switch> switch1 = new osg::Switch;
	switch1->addChild(createScenceGraph().get(),true);
	switch1->addChild(createScenceGraph1().get(),true);

	
    osgViewer::Viewer viewer;
	//auto a = osgDB::readNodeFile("1.osg");
    //viewer.setSceneData(a->asGroup());
	viewer.setSceneData(switch1.get());
	
	viewer.setName("hello osg");
	viewer.run();


    return 0;
}

int osgTestExample1_1() {
	osg::ref_ptr<osg::Geometry> geod = new osg::Geometry;
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	v->push_back(osg::Vec3(25, 25, 25));
	v->push_back(osg::Vec3(0, 0, 0));
	v->push_back(osg::Vec3(0, 0, 25));
	geod->setVertexArray(v.get());
	geod->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP, 0, 3));

	osgViewer::Viewer viewer;
	//auto a = osgDB::readNodeFile("1.osg");
	//viewer.setSceneData(a->asGroup());
	//viewer.setSceneData(switch1.get());
	viewer.setSceneData(geod.get());
	viewer.setName("hello osg");
	viewer.run();

	return 0;
}