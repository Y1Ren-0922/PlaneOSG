// PlaneOSG.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <json.h>
#include <iostream>
#include <fstream>
#include "PlaceClass.h"

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osg/Node>
#include <osgViewer/ViewerEventHandlers>
#include <osg/MatrixTransform>
#include <osgGA/GUIEventHandler>
#include <osgGA/TrackballManipulator>
#include <osgManipulator/TrackballDragger>
#include <osgManipulator/TranslateAxisDragger>
#include <osgManipulator/ScaleAxisDragger>
#include <osg/PositionAttitudeTransform>
#include <osg/Geode>

using namespace std;

//创建地板
osg::ref_ptr<osg::Geode> createFloor()
{
	osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;
	// 地板格子长、宽、行、列
	float dx = 1.0f;
	float dy = 1.0f;
	int rows = 20;
	int cols = 20;
	osg::Vec3 vec3center(0.0f - dx * rows / 2 - dx / 2,
		0.0f - dx * cols / 2 - dx / 2,
		0.0f);
	// 顶点
	osg::Vec3Array *pVec3Array = new osg::Vec3Array;
	for (int index = 0; index <= rows; index++)
	{
		for (int index2 = 0; index2 <= cols; index2++)
		{
			pVec3Array->push_back(osg::Vec3(index2 * dx, index * dy, 0) + vec3center);
		}
	}
	// 颜色
	osg::Vec4Array *pVec4ColorArray = new osg::Vec4Array;
	pVec4ColorArray->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	pVec4ColorArray->push_back(osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f));
	// 索引（使用索引，之前的demo没有使用过，此源码第一次使用）之处
	osg::UIntArray * pCoordIndices = new osg::UIntArray;
	osg::UIntArray * pColorIndices = new osg::UIntArray;
	for (int index = 0; index < rows; index++)
	{
		for (int index2 = 0; index2 < cols; index2++)
		{
			// 顶点索引
			pCoordIndices->push_back((index2)+(index) * (cols + 1));
			pCoordIndices->push_back((index2 + 1) + (index) * (cols + 1));
			pCoordIndices->push_back((index2 + 1) + (index + 1) * (cols + 1));
			pCoordIndices->push_back((index2)+(index + 1) * (cols + 1));
			pColorIndices->push_back(((index2)+(index + 1) * (cols + 1))
				% pVec4ColorArray->size());
		}
	}
	// 法线
	osg::Vec3Array * pNormal = new osg::Vec3Array;
	pNormal->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
	// 图形（支持索引的需要使用deprecated_osg: :Geometry)
	deprecated_osg::Geometry * pGeometry = new deprecated_osg::Geometry;

	pGeometry->setVertexArray(pVec3Array);
	pGeometry->setVertexIndices(pCoordIndices);

	pGeometry->setColorArray(pVec4ColorArray);
	pGeometry->setColorIndices(pColorIndices);
	pGeometry->setColorBinding(deprecated_osg::Geometry::BIND_PER_PRIMITIVE);

	pGeometry->setSecondaryColorArray(pVec4ColorArray);
	pGeometry->setSecondaryColorIndices(pColorIndices);
	pGeometry->setSecondaryColorBinding(deprecated_osg::Geometry::BIND_PER_PRIMITIVE);

	pGeometry->setNormalArray(pNormal);
	pGeometry->setNormalBinding(deprecated_osg::Geometry::BIND_OVERALL);

	pGeometry->addPrimitiveSet(
		new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, pCoordIndices->size()));
	osg::StateSet *pStateSet = pGeometry->getOrCreateStateSet();
	pStateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	pStateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
	pGeode->addDrawable(pGeometry);
	return pGeode;
}


/*
osg::ref_ptr<osg::PositionAttitudeTransform> getPAT(osg::Node* pNode, string filename)
{
	//创建createAnimationPath类对象
	createAnimationPath *animaPath = new createAnimationPath(filename);
	//获取路径
	osg::AnimationPath *pAnimationPath = animaPath->getPath();
	//获取飞机初始状态
	osg::MatrixTransform *pMatTrans = animaPath->getInitState();
	pMatTrans->addChild(pNode);

	osg::ref_ptr<osg::PositionAttitudeTransform> pPositionAttitudeTransform = new osg::PositionAttitudeTransform;
	//使用更新回调来控制飞机飞行
	pPositionAttitudeTransform->setUpdateCallback(new osg::AnimationPathCallback(pAnimationPath, 0.0, 1.0));
	pPositionAttitudeTransform->addChild(pMatTrans);

	return pPositionAttitudeTransform;
}
*/

//键盘事件处理类
class keyEventHandler :public osgGA::GUIEventHandler
{
public:
	keyEventHandler(osgViewer::Viewer *viewerParam) { viewer1 = viewerParam;  }
	osg::ref_ptr<osg::Node> pNode = osgDB::readNodeFile("cessna.osg");
	//事件处理函数
	//ea用来识别各种事件类型，aa可以得到viewer
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
	{
		if (!viewer1) { return false; }

		switch (ea.getEventType())
		{
			//若为键盘按下
		case osgGA::GUIEventAdapter::KEYDOWN:
		{
			//若为Space
			if (ea.getKey() == 0x20)
			{
				
				//创建createAnimationPath类对象
				createAnimationPath *animaPath = new createAnimationPath("Looping.json");
				//获取路径
				osg::AnimationPath *pAnimationPath = animaPath->getPath();
				//获取飞机初始状态
				osg::MatrixTransform *pMatTrans = animaPath->getInitState();
				pMatTrans->addChild(pNode);

				osg::ref_ptr<osg::PositionAttitudeTransform> pPositionAttitudeTransform = new osg::PositionAttitudeTransform;
				//使用更新回调来控制飞机飞行
				pPositionAttitudeTransform->setUpdateCallback(new osg::AnimationPathCallback(pAnimationPath, 0.0, 1.0));
				pPositionAttitudeTransform->addChild(pMatTrans);
				viewer1->getSceneData()->asGroup()->addChild(pPositionAttitudeTransform);
		
			}
			//若为backSpace
			if (ea.getKey() == 0xFF08)
			{
				
				//创建createAnimationPath类对象
				createAnimationPath *animaPath = new createAnimationPath("Roll.json");
				//获取路径
				osg::AnimationPath *pAnimationPath = animaPath->getPath();
				//获取飞机初始状态
				osg::MatrixTransform *pMatTrans = animaPath->getInitState();
				pMatTrans->addChild(pNode);

				osg::ref_ptr<osg::PositionAttitudeTransform> pPositionAttitudeTransform = new osg::PositionAttitudeTransform;
				//使用更新回调来控制飞机飞行
				pPositionAttitudeTransform->setUpdateCallback(new osg::AnimationPathCallback(pAnimationPath, 0.0, 1.0));
				pPositionAttitudeTransform->addChild(pMatTrans);
				viewer1->getSceneData()->asGroup()->addChild(pPositionAttitudeTransform);
				
				/*
				osg::ref_ptr<osg::PositionAttitudeTransform> pPositionAttitudeTransform = getPAT(pNode, "Roll.json");
				viewer1->getSceneData()->asGroup()->addChild(pPositionAttitudeTransform);
				*/
			}
			//若为Tab
			if (ea.getKey() == 0xFF09)
			{
				//创建createAnimationPath类对象
				createAnimationPath *animaPath = new createAnimationPath("Turn.json");
				//获取路径
				osg::AnimationPath *pAnimationPath = animaPath->getPath();
				//获取飞机初始状态
				osg::MatrixTransform *pMatTrans = animaPath->getInitState();
				pMatTrans->addChild(pNode);

				osg::ref_ptr<osg::PositionAttitudeTransform> pPositionAttitudeTransform = new osg::PositionAttitudeTransform;
				//使用更新回调来控制飞机飞行
				pPositionAttitudeTransform->setUpdateCallback(new osg::AnimationPathCallback(pAnimationPath, 0.0, 1.0));
				pPositionAttitudeTransform->addChild(pMatTrans);
				viewer1->getSceneData()->asGroup()->addChild(pPositionAttitudeTransform);

			}
			//若为pause
			if (ea.getKey() == 0xFF13)
			{
				//创建createAnimationPath类对象
				createAnimationPath *animaPath = new createAnimationPath("InverLooping.json");
				//获取路径
				osg::AnimationPath *pAnimationPath = animaPath->getPath();
				//获取飞机初始状态
				osg::MatrixTransform *pMatTrans = animaPath->getInitState();
				pMatTrans->addChild(pNode);

				osg::ref_ptr<osg::PositionAttitudeTransform> pPositionAttitudeTransform = new osg::PositionAttitudeTransform;
				//使用更新回调来控制飞机飞行
				pPositionAttitudeTransform->setUpdateCallback(new osg::AnimationPathCallback(pAnimationPath, 0.0, 1.0));
				pPositionAttitudeTransform->addChild(pMatTrans);
				viewer1->getSceneData()->asGroup()->addChild(pPositionAttitudeTransform);
			}
			//若为delete
			if (ea.getKey() == 0xFFFF)
			{
				//创建createAnimationPath类对象
				createAnimationPath *animaPath = new createAnimationPath("Immelmann_Turn.json");
				//获取路径
				osg::AnimationPath *pAnimationPath = animaPath->getPath();
				//获取飞机初始状态
				osg::MatrixTransform *pMatTrans = animaPath->getInitState();
				pMatTrans->addChild(pNode);

				osg::ref_ptr<osg::PositionAttitudeTransform> pPositionAttitudeTransform = new osg::PositionAttitudeTransform;
				//使用更新回调来控制飞机飞行
				pPositionAttitudeTransform->setUpdateCallback(new osg::AnimationPathCallback(pAnimationPath, 0.0, 1.0));
				pPositionAttitudeTransform->addChild(pMatTrans);
				viewer1->getSceneData()->asGroup()->addChild(pPositionAttitudeTransform);

			}
			//若为home
			if (ea.getKey() == 0xFF50)
			{
				//创建createAnimationPath类对象
				createAnimationPath *animaPath = new createAnimationPath("Trudeln.json");
				//获取路径
				osg::AnimationPath *pAnimationPath = animaPath->getPath();
				//获取飞机初始状态
				osg::MatrixTransform *pMatTrans = animaPath->getInitState();
				pMatTrans->addChild(pNode);

				osg::ref_ptr<osg::PositionAttitudeTransform> pPositionAttitudeTransform = new osg::PositionAttitudeTransform;
				//使用更新回调来控制飞机飞行
				pPositionAttitudeTransform->setUpdateCallback(new osg::AnimationPathCallback(pAnimationPath, 0.0, 1.0));
				pPositionAttitudeTransform->addChild(pMatTrans);
				viewer1->getSceneData()->asGroup()->addChild(pPositionAttitudeTransform);

			}
			//若为page up
			if (ea.getKey() == 0xFF55)
			{
				//创建createAnimationPath类对象
				createAnimationPath *animaPath = new createAnimationPath("Split-S.json");
				//获取路径
				osg::AnimationPath *pAnimationPath = animaPath->getPath();
				//获取飞机初始状态
				osg::MatrixTransform *pMatTrans = animaPath->getInitState();
				pMatTrans->addChild(pNode);

				osg::ref_ptr<osg::PositionAttitudeTransform> pPositionAttitudeTransform = new osg::PositionAttitudeTransform;
				//使用更新回调来控制飞机飞行
				pPositionAttitudeTransform->setUpdateCallback(new osg::AnimationPathCallback(pAnimationPath, 0.0, 1.0));
				pPositionAttitudeTransform->addChild(pMatTrans);
				viewer1->getSceneData()->asGroup()->addChild(pPositionAttitudeTransform);

			}
			//若为page down
			if (ea.getKey() == 0xFF56)
			{
				//创建createAnimationPath类对象
				createAnimationPath *animaPath = new createAnimationPath("Rollenkehre.json");
				//获取路径
				osg::AnimationPath *pAnimationPath = animaPath->getPath();
				//获取飞机初始状态
				osg::MatrixTransform *pMatTrans = animaPath->getInitState();
				pMatTrans->addChild(pNode);

				osg::ref_ptr<osg::PositionAttitudeTransform> pPositionAttitudeTransform = new osg::PositionAttitudeTransform;
				//使用更新回调来控制飞机飞行
				pPositionAttitudeTransform->setUpdateCallback(new osg::AnimationPathCallback(pAnimationPath, 0.0, 1.0));
				pPositionAttitudeTransform->addChild(pMatTrans);
				viewer1->getSceneData()->asGroup()->addChild(pPositionAttitudeTransform);
			}
			break;
		}
		default:
			break;
		}
		return false;
	}
private:
	osgViewer::Viewer *viewer1;
};

int main(int argc, char **argv)
{
	
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	
	//创建组节点
	osg::ref_ptr<osg::Group> gp = new osg::Group;
	//创建地板
	osg::ref_ptr<osg::Geode> pGeode = createFloor();
	gp->addChild(pGeode.get());

	string choose;
	cout << "Json file list:          keyBoard list:" << endl;
	cout << " 1、Looping.json           1、Looping: Space" << endl;
	cout << " 2、Turn.json              2、Turn: Tab" << endl;
	cout << " 3、Roll.json              3、Roll: backSpace" << endl;
	cout << " 4、InverLooping.json      4、InverLooping: pause" << endl;
	cout << " 5、Immelmann_Turn.json    5、Immelmann_Turn: delete" << endl;
	cout << " 6、Split-S.json           6、Split-S: page up" << endl;
	cout << " 7、Trudeln.json           7、Trudeln: home" << endl;
	cout << " 8、Rollenkehre.json       8、Rollenkehre: page down" << endl;

	cout << "Please choose json or keyBoard：";
	cin >> choose;

	//若使用json文件控制
	if (choose == "json")
	{
		
		//存放文件名
		string filename;
		//从命令行获取轨迹文件名
		cout << "Please input json file name: ";
		cin >> filename;

		//加载飞机模型
		osg::ref_ptr<osg::Node> pNode = osgDB::readNodeFile("cessna.osg");
		
		//创建createAnimationPath类对象
		createAnimationPath *animaPath = new createAnimationPath(filename);
		//获取路径
		osg::AnimationPath *pAnimationPath = animaPath->getPath();
		//获取飞机初始状态
		osg::MatrixTransform *pMatTrans = animaPath->getInitState();
		pMatTrans->addChild(pNode);

		osg::ref_ptr<osg::PositionAttitudeTransform> pPositionAttitudeTransform = new osg::PositionAttitudeTransform;
		//使用更新回调来控制飞机飞行
		pPositionAttitudeTransform->setUpdateCallback(new osg::AnimationPathCallback(pAnimationPath, 0.0, 1.0));
		pPositionAttitudeTransform->addChild(pMatTrans);

		gp->addChild(pPositionAttitudeTransform);
		
	
	}
	
	//若使用键盘按键控制
	else if (choose == "keyBoard")
	{
		viewer->addEventHandler(new keyEventHandler(viewer));
	}
	else
	{
		cout << "input error!" << endl;
		return 0;
	}
	
	viewer->setSceneData(gp.get());
	
	viewer->realize();

	//设置显示窗口的大小
	osgViewer::GraphicsWindow *pWnd = dynamic_cast<osgViewer::GraphicsWindow*>(viewer->getCamera()->getGraphicsContext());
	if (pWnd) {
		pWnd->setWindowRectangle(400, 400, 1400, 1000);

		pWnd->setWindowDecoration(true);
	}

	viewer->run();


	return 0;
	
}

