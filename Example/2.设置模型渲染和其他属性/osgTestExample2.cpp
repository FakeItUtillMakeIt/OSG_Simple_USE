#include "osgTestExample2.h"
#include <osgViewer/Viewer>
#include <osg/Texture2D>
#include <iostream>

osg::ref_ptr<osg::Geometry> createDrawable() {
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	
	osg::ref_ptr<osg::Vec3Array> vertex = new osg::Vec3Array;
	vertex->push_back(osg::Vec3(-1.f, 0, -1.f));
	vertex->push_back(osg::Vec3(1.f, 0, -1.f));
	vertex->push_back(osg::Vec3(1.f, 0, 1.f));
	vertex->push_back(osg::Vec3(-1.f, 0, 1.f));


	geom->setVertexArray(vertex.get());

	osg::ref_ptr<osg::Vec4Array> colorv = new osg::Vec4Array;
	colorv->push_back(osg::Vec4(1.f,0.f,0.f,1.f));
	colorv->push_back(osg::Vec4(0.f, 1.f, 0.f, 1.f));
	colorv->push_back(osg::Vec4(0.f, 0.f, 1.f, 1.f));
	colorv->push_back(osg::Vec4(1.f, 1.f, 1.f, 1.f));

	geom->setColorArray(colorv.get());
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	osg::ref_ptr<osg::Vec3Array> fax = new osg::Vec3Array;
	fax->push_back(osg::Vec3(0, -1, 0));
	geom->setNormalArray(fax.get());
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

	
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
	
	return geom.get();

}


osg::ref_ptr<osg::Geometry> createDrawable1() {
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	osg::ref_ptr<osg::Vec3Array> vertex = new osg::Vec3Array;
	vertex->push_back(osg::Vec3(-1.f, 1, -1.f));
	vertex->push_back(osg::Vec3(1.f, 1, -1.f));
	vertex->push_back(osg::Vec3(1.f, 1, 1.f));
	vertex->push_back(osg::Vec3(-1.f, 1, 1.f));


	geom->setVertexArray(vertex.get());


	osg::ref_ptr<osg::Vec4Array> colorv = new osg::Vec4Array;
	colorv->push_back(osg::Vec4(1.f, 0.f, 0.f, 1.f));
	colorv->push_back(osg::Vec4(1.f, 1.f, 0.f, 1.f));
	colorv->push_back(osg::Vec4(0.f, 0.f, 1.f, 1.f));
	colorv->push_back(osg::Vec4(1.f, 1.f, 1.f, 1.f));

	geom->setColorArray(colorv.get());
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	osg::ref_ptr<osg::Vec3Array> fax = new osg::Vec3Array;
	fax->push_back(osg::Vec3(0, -1, 0));
	geom->setNormalArray(fax.get());
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

	//osg::ref_ptr<osg::Vec2Array> textureArray = new osg::Vec2Array;
	//textureArray->push_back(osg::Vec2(-1,  1));
	//textureArray->push_back(osg::Vec2(0, 1));
	//textureArray->push_back(osg::Vec2(1, 0));
	//textureArray->push_back(osg::Vec2(-1, -1));

	//geom->setTexCoordArray(0, textureArray.get());
	//


	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	return geom.get();

}

osg::ref_ptr<osg::Node> createScenceGraph() {
	osg::ref_ptr<osg::Group> root = new osg::Group;
	{
		//root节点StateSet中禁止光照
		//使用PROTECTED保证修改不会被osgViewer覆盖
		osg::StateSet* state = new osg::StateSet;
		state->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
		state->setMode(GL_LIGHT0, osg::StateAttribute::ON | osg::StateAttribute::PROTECTED);
		state->setMode(GL_LIGHT1, osg::StateAttribute::ON | osg::StateAttribute::PROTECTED);
		root->setStateSet(state);
	}
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;

	geode->addDrawable(createDrawable().get());
	geode->addDrawable(createDrawable1().get());


	osg::Matrix m;
	{
		//左上角使用缺省属性渲染几何体
		osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
		m.makeTranslate(-2.f, 0.f, 2.f);
		mt->setMatrix(m);
		root->addChild(mt.get());
		mt->addChild(geode.get());

	}

	{
		//右上角设置着色为FLAT
		osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
		m.makeTranslate(2.f, 0.f, 2.f);
		mt->setMatrix(m);
		root->addChild(mt.get());
		mt->addChild(geode.get());
		osg::StateSet* state = mt->getOrCreateStateSet();
		osg::ShadeModel* sm = new osg::ShadeModel();
		sm->setMode(osg::ShadeModel::FLAT);
		state->setAttribute(sm);
	}

	{
		//左下角,背面剔除
		osg::ref_ptr<osg::MatrixTransform> mt =new osg::MatrixTransform;
		m.makeTranslate(-2.f, 0.f, -2.f);
		mt->setMatrix(m);
		root->addChild(mt.get());
		mt->addChild(geode.get());

		osg::StateSet* state = mt->getOrCreateStateSet();
		osg::CullFace* cf = new osg::CullFace();
		state->setAttributeAndModes(cf);
	}

	{
		//右下角,设置多边形填充模式为LINE
		osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
		m.makeTranslate(2.f, 0.f, -2.f);
		mt->setMatrix(m);
		root->addChild(mt.get());
		mt->addChild(geode.get());

		osg::StateSet* state = mt->getOrCreateStateSet();
		osg::PolygonMode* pm = new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK,osg::PolygonMode::LINE);
		state->setAttributeAndModes(pm);

		osg::LineWidth* lw = new osg::LineWidth(3.f);
		state->setAttribute(lw);
	}

	osg::StateSet* state = geode->getOrCreateStateSet();
	//读取纹理图像
	osg::ref_ptr<osg::Image> image = new osg::Image;
	image->setFileName("1.png");
	//将图像关联到Texture2D对象
	osg::ref_ptr<osg::Texture2D> t2d = new osg::Texture2D;
	t2d->setImage(image.get());
	state->setTextureAttributeAndModes(0,t2d.get());
	
	//t2d->setUnRefImageDataAfterApply(true);
	auto ret = osgDB::writeNodeFile(*root.get(), "2.osg");
	if (!ret)
	{
		osg::notify(osg::FATAL) << std::endl;
	}
	return root.get();


}
int osgTestExample2() {
	osgViewer::Viewer viewer;
	
	
	viewer.setSceneData(createScenceGraph().get());
	viewer.run();
	return 0;
}