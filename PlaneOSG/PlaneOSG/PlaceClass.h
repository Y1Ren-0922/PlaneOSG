#pragma once
#ifndef Plane_H_
#define Place_H_

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osg/Node>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>

using namespace std;

class createAnimationPath {
public:
	//构造函数 
	createAnimationPath() = default;
	createAnimationPath(const string &s) : fileName(s) { }

	void createPath();
	osg::AnimationPath *getPath();
	osg::MatrixTransform *getInitState();
	
	//工具函数 分割字符串
	vector<string> split(const string &str, const string &pattern);

private:
	//形成的路径
	osg::AnimationPath *pAnimationPath = new osg::AnimationPath();
	//飞机初始状态
	osg::MatrixTransform *initState = new osg::MatrixTransform();
	//json文件名字 即要执行的动作
	string fileName;
};


#endif // !Plane_H_
