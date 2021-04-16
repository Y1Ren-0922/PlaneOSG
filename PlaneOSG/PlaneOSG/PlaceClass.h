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
	//���캯�� 
	createAnimationPath() = default;
	createAnimationPath(const string &s) : fileName(s) { }

	void createPath();
	osg::AnimationPath *getPath();
	osg::MatrixTransform *getInitState();
	
	//���ߺ��� �ָ��ַ���
	vector<string> split(const string &str, const string &pattern);

private:
	//�γɵ�·��
	osg::AnimationPath *pAnimationPath = new osg::AnimationPath();
	//�ɻ���ʼ״̬
	osg::MatrixTransform *initState = new osg::MatrixTransform();
	//json�ļ����� ��Ҫִ�еĶ���
	string fileName;
};


#endif // !Plane_H_
