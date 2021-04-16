#include "PlaceClass.h"

#include <json.h>

//�ָ��ַ���
vector<string> createAnimationPath::split(const string &str, const string &pattern)
{
	//��ŷָ��Ľ��
	vector<string> result;
	//���ַ���ĩβ����ָ����������ȡ���һ��
	string strs = str + pattern;
	string::size_type pos;
	int size = strs.size();

	for (int i = 0; i < size; i++)
	{
		//find����pattern��һ�γ��ֵ�λ��
		pos = strs.find(pattern, i);
		if (pos < size)
		{
			//substr��ȡi��pos-i���ַ���
			string s = str.substr(i, pos - i);
			result.push_back(s);
			//���³�ʼ����λ��
			i = pos + pattern.size();
		}
	}
	return result;
}

//�õ��ɻ��ĳ�ʼ״̬
osg::MatrixTransform* createAnimationPath::getInitState()
{
	std::ifstream ifs(fileName);

	Json::Value root;
	Json::Reader reader;

	if (reader.parse(ifs, root))
	{
		//��ȡ������ʼ״̬
		Json::Value initialState = root["initialState"];
		osg::Matrix matrix = initState->getMatrix();

		//��ʼλ��ת��
		if (initialState.isMember("translate"))
		{
			string initialTranslate = initialState["translate"].asString();
			vector<string> Vtranslate = split(initialTranslate, ",");
			float translateX = atof(Vtranslate[0].c_str());
			float translateY = atof(Vtranslate[1].c_str());
			float translateZ = atof(Vtranslate[2].c_str());
			matrix = osg::Matrix::translate(translateX, translateY, translateZ) * matrix;
		}

		//��ʼ��ת�Ƕ�
		string initialIndegree = initialState["rotate"]["indegree"].asString();
		float initIndegree = atof(initialIndegree.c_str());

		//��ʼ��ת����
		string initialOrientation = initialState["rotate"]["orientation"].asString();
		vector<string> Vorientation = split(initialOrientation, ",");
		float rotateX = atof(Vorientation[0].c_str());
		float rotateY = atof(Vorientation[1].c_str());
		float rotateZ = atof(Vorientation[2].c_str());

		//��ʼ����״̬
		string initialScale = initialState["scale"].asString();
		vector<string> Vscale = split(initialScale, ",");
		float scaleX = atof(Vscale[0].c_str());
		float scaleY = atof(Vscale[1].c_str());
		float scaleZ = atof(Vscale[2].c_str());

		if (initialState.isMember("rotate1"))
		{
			//��ʼ��ת�Ƕ�
			string initialIndegree1 = initialState["rotate1"]["indegree"].asString();
			float initIndegree1 = atof(initialIndegree1.c_str());

			string initialOrientation1 = initialState["rotate1"]["orientation"].asString();
			vector<string> Vorientation1 = split(initialOrientation1, ",");
			float rotateX1 = atof(Vorientation1[0].c_str());
			float rotateY1 = atof(Vorientation1[1].c_str());
			float rotateZ1 = atof(Vorientation1[2].c_str());



			matrix = osg::Matrix::rotate(osg::inDegrees(initIndegree), osg::Vec3f(rotateX, rotateY, rotateZ)) *
				osg::Matrix::rotate(osg::inDegrees(initIndegree1), osg::Vec3f(rotateX1, rotateY1, rotateZ1)) * matrix;
		}
		else
		{
			matrix = osg::Matrix::rotate(osg::inDegrees(initIndegree), osg::Vec3f(rotateX, rotateY, rotateZ)) * matrix;
		}

		matrix = osg::Matrix::scale(scaleX, scaleY, scaleZ) * matrix;
		initState->setMatrix(matrix);

	}
	return initState;
}

//����json�ļ�����·��
void createAnimationPath::createPath()
{
	std::ifstream ifs(fileName);

	Json::Value root;
	Json::Reader reader;

	if (reader.parse(ifs, root))
	{
		//���õĹؼ�������
		int num = root["keyPoint"].size();

		for (int i = 0; i < num; ++i)
		{
			Json::Value keyPoint = root["keyPoint"][i];

			//��ȡjson�ļ��е�ʱ����Ϣ
			string Stime = keyPoint["time"].asString();
			//c_str��Stimeת��Ϊc���͵��ַ���
			float time = atof(Stime.c_str());

			//��ȡjson�ļ��зɻ���λ����Ϣ
			string position = keyPoint["position"].asString();
			vector<string> Vposition = split(position, ",");
			double positionX = atof(Vposition[0].c_str());
			double positionY = atof(Vposition[1].c_str());
			double positionZ = atof(Vposition[2].c_str());

			//��ȡ�Ƕ���Ϣ
			string Sindegree1 = keyPoint["orientations_1"]["indegree"].asString();
			float indegree1 = atof(Sindegree1.c_str());

			//��ȡ������Ϣ
			string orientation_1 = keyPoint["orientations_1"]["orientation"].asString();
			vector<string> Vorientation1 = split(orientation_1, ",");
			float orientation1X = atof(Vorientation1[0].c_str());
			float orientation1Y = atof(Vorientation1[1].c_str());
			float orientation1Z = atof(Vorientation1[2].c_str());


			if (keyPoint.isMember("orientations_2"))
			{
				//��ȡ�Ƕ���Ϣ
				string Sindegree2 = keyPoint["orientations_2"]["indegree"].asString();
				float indegree2 = atof(Sindegree2.c_str());
				//��ȡ������Ϣ
				string orientation_2 = keyPoint["orientations_2"]["orientation"].asString();
				vector<string> Vorientation2 = split(orientation_2, ",");
				float orientation2X = atof(Vorientation2[0].c_str());
				float orientation2Y = atof(Vorientation2[1].c_str());
				float orientation2Z = atof(Vorientation2[2].c_str());

				if (keyPoint.isMember("orientations_3"))
				{
					//��ȡ�Ƕ���Ϣ
					string Sindegree3 = keyPoint["orientations_3"]["indegree"].asString();
					float indegree3 = atof(Sindegree3.c_str());
					//��ȡ������Ϣ
					string orientation_3 = keyPoint["orientations_3"]["orientation"].asString();
					vector<string> Vorientation3 = split(orientation_3, ",");
					float orientation3X = atof(Vorientation3[0].c_str());
					float orientation3Y = atof(Vorientation3[1].c_str());
					float orientation3Z = atof(Vorientation3[2].c_str());

					if (keyPoint.isMember("orientations_4"))
					{
						//��ȡ�Ƕ���Ϣ
						string Sindegree4 = keyPoint["orientations_4"]["indegree"].asString();
						float indegree4 = atof(Sindegree4.c_str());
						//��ȡ������Ϣ
						string orientation_4 = keyPoint["orientations_4"]["orientation"].asString();
						vector<string> Vorientation4 = split(orientation_4, ",");
						float orientation4X = atof(Vorientation4[0].c_str());
						float orientation4Y = atof(Vorientation4[1].c_str());
						float orientation4Z = atof(Vorientation4[2].c_str());

						osg::Quat rotation(osg::Quat(osg::inDegrees(indegree1), osg::Vec3f(orientation1X, orientation1Y, orientation1Z))*
							osg::Quat(osg::inDegrees(indegree2), osg::Vec3f(orientation2X, orientation2Y, orientation2Z)) *
							osg::Quat(osg::inDegrees(indegree3), osg::Vec3f(orientation3X, orientation3Y, orientation3Z))*
							osg::Quat(osg::inDegrees(indegree4), osg::Vec3f(orientation4X, orientation4Y, orientation4Z)));
						pAnimationPath->insert(time, osg::AnimationPath::ControlPoint(osg::Vec3f(positionX, positionY, positionZ), rotation));
					}
					else
					{
						osg::Quat rotation(osg::Quat(osg::inDegrees(indegree1), osg::Vec3f(orientation1X, orientation1Y, orientation1Z))*
							osg::Quat(osg::inDegrees(indegree2), osg::Vec3f(orientation2X, orientation2Y, orientation2Z)) *
							osg::Quat(osg::inDegrees(indegree3), osg::Vec3f(orientation3X, orientation3Y, orientation3Z)));
						pAnimationPath->insert(time, osg::AnimationPath::ControlPoint(osg::Vec3f(positionX, positionY, positionZ), rotation));
					}

				}
				else
				{
					osg::Quat rotation(osg::Quat(osg::inDegrees(indegree1), osg::Vec3f(orientation1X, orientation1Y, orientation1Z))*
						osg::Quat(osg::inDegrees(indegree2), osg::Vec3f(orientation2X, orientation2Y, orientation2Z)));
					pAnimationPath->insert(time, osg::AnimationPath::ControlPoint(osg::Vec3f(positionX, positionY, positionZ), rotation));
				}
			}
			else
			{
				pAnimationPath->insert(time, osg::AnimationPath::ControlPoint(osg::Vec3f(positionX, positionY, positionZ),
					osg::Quat(osg::inDegrees(indegree1), osg::Vec3f(orientation1X, orientation1Y, orientation1Z))));
			}

		}
	}
}

//��ȡ·��
osg::AnimationPath* createAnimationPath::getPath()
{
	createPath();
	return pAnimationPath;
}