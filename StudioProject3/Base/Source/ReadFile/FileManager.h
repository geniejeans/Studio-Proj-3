#pragma once
#include <string>
#include <vector>
#include <sstream>

#include "Vector3.h"

using std::string;
using std::vector;

class FileManager
{
	int m_iColumn; //each column in csv file

	static FileManager* Instance; //private static pointer

public:
	FileManager();
	~FileManager();
	
	struct objectData
	{
		string Type;
		string Name;
		string positionX;
		string positionY;
		string positionZ;
		string scaleX;
		string scaleY;
		string scaleZ;
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

	//get static pointer
	static FileManager* GetInstance()
	{
		if (!Instance) //no instance is found
			Instance = new FileManager(); //create new instance

		return Instance;
	}
};
