#pragma once
#include <string>
#include <vector>
#include <sstream>

#include "Vector3.h"
#include "SingletonTemplate.h"

using std::string;
using std::vector;

class FileManager : public Singleton<FileManager>
{
	int m_iColumn; //each column in csv file

public:
	FileManager();
	~FileManager();
	
	struct objectData
	{
		string Type,
				Name,
				positionX,
				positionY,
				positionZ,
				scaleX,
				scaleY,
				scaleZ,
				objType;
		 
	}object;

	//vector storing all the objects
	vector<objectData> objVec;
	//Get vector
	vector<objectData> returnVec();

	//Read File
	void ReadFile(const string m_sFilename);
	//Creation of objects
	void CreateObjects();

	//Debug Purpose
	void PrintData();
};
