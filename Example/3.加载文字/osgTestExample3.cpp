#include "osgTestExample3.h"

int osgTestExample3() {

	//osg::ref_ptr<osgText::Font> font = osgText::readFontFile("fonts/cour.ttf");
	osg::ref_ptr<osgText::Text> text = new osgText::Text;
	//text->setFont(font.get());
	text->setText("hello osgText");
	text->setColor(osg::Vec4(0, 0, 1.f, 1.f));
	text->setPosition(osg::Vec3(10, 20, 10));
	text->setAxisAlignment(osgText::Text::SCREEN);
	text->setFontResolution(128, 128);

	osgViewer::Viewer viewer;
	viewer.setSceneData(text.get());
	return viewer.run();
	
}