#include "FileManager.h"
#include "../Furniture/Furniture.h"
#include "../Trees/Trees.h"
#include "../Enemy/Turrets/Turrets.h"
#include "../EntityManager.h"

#include <fstream>
#include <iostream>

FileManager::FileManager()
	: m_iColumn(1)
{
}

FileManager::~FileManager()
{
}

// This function is for the reading of Data from file
void FileManager::ReadFile(const string m_sFilename)
{
	ifstream myFile;
	string info = ""; //data in file
	string tempinfo = ""; //temp to store info from file
	bool skipFirstLine = false;
	FileManager::objectData storeObj;

	myFile.open(m_sFilename);

	//check for error
	if (myFile.fail() /*function to check if file exist / corrupted */)
	{
		std::cout << "Error Opening File!" << std::endl;
	}

	//read info
	if (myFile.is_open())
	{
		while (getline(myFile, info)) //read by line
		{
			//if its first line, skip
			if (!skipFirstLine)
			{
				skipFirstLine = true;
				continue;
			}

			//check for individual values
			for (int i = 0; i < info.length(); ++i)
			{
				switch (m_iColumn)
				{
					case 1: //type
					{
						//take in individual chars
						for (int chara = i; chara < info.length(); ++chara)
						{
							//before comma
							if (info[chara] != ',')
							{
								tempinfo += info[chara];
							}
							else
							{
								//when comma, set i to read the next string
								i = chara;
								break;
							}
						}
						storeObj.Type = (tempinfo);
						break;
					}
					case 2: //name
					{
						//take in individual chars
						for (int chara = i; chara < info.length(); ++chara)
						{
							//before comma
							if (info[chara] != ',')
							{
								tempinfo += info[chara];
							}
							else
							{
								//when comma, set i to read the next string
								i = chara;
								break;
							}
						}
						storeObj.Name = tempinfo;
						break;
					}
					case 3: //position.x
					{
						//take in individual chars
						for (int chara = i; chara < info.length(); ++chara)
						{
							//before comma
							if (info[chara] != ',')
							{
								tempinfo += info[chara];
							}
							else
							{
								//when comma, set i to read the next string
								i = chara;
								break;
							}
						}
						storeObj.positionX = tempinfo;
						break;
					}
					case 4: //position.y
					{
						//take in individual chars
						for (int chara = i; chara < info.length(); ++chara)
						{
							//before comma
							if (info[chara] != ',')
							{
								tempinfo += info[chara];
							}
							else
							{
								//when comma, set i to read the next string
								i = chara;
								break;
							}
						}
						storeObj.positionY = tempinfo;
						break;
					}
					case 5: //position.z
					{
						//take in individual chars
						for (int chara = i; chara < info.length(); ++chara)
						{
							//before comma
							if (info[chara] != ',')
							{
								tempinfo += info[chara];
							}
							else
							{
								//when comma, set i to read the next string
								i = chara;
								break;
							}
						}
						storeObj.positionZ = tempinfo;
						break;
					}
					case 6: //scale.x
					{
						//take in individual chars
						for (int chara = i; chara < info.length(); ++chara)
						{
							//before comma
							if (info[chara] != ',')
							{
								tempinfo += info[chara];
							}
							else
							{
								//when comma, set i to read the next string
								i = chara;
								break;
							}
						}
						storeObj.scaleX = tempinfo;
						break;
					}
					case 7: //scale.y
					{
						//take in individual chars
						for (int chara = i; chara < info.length(); ++chara)
						{
							//before comma
							if (info[chara] != ',')
							{
								tempinfo += info[chara];
							}
							else
							{
								//when comma, set i to read the next string
								i = chara;
								break;
							}
						}
						storeObj.scaleY = tempinfo;
						break;
					}
					case 8: //scale.z
					{
						//take in individual chars
						for (int chara = i; chara < info.length(); ++chara)
						{
							//before comma
							if (info[chara] != ',')
							{
								tempinfo += info[chara];
							}
							else
							{
								//when comma, set i to read the next string
								i = chara;
								break;
							}
						}
						storeObj.scaleZ = tempinfo;
						break;
					}
					case 9: //if have, obj type
					{
						//take in individual chars
						for (int chara = i; chara < info.length(); ++chara)
						{
							//before comma
							if (info[chara] != ',')
							{
								tempinfo += info[chara];
							}
							else
							{
								//when comma, set i to read the next string
								i = chara;
								break;
							}
						}
						storeObj.objType = tempinfo;
						break;
					}

				} //end switch

				m_iColumn++;
				tempinfo = "";
			}

			objVec.push_back(storeObj);
			info = "";
			m_iColumn = 1;
		} 

	}

	myFile.close();
}

//This function is to create and render objects
void FileManager::CreateObjects()
{
	for (vector<FileManager::objectData>::iterator it = objVec.begin(); it != objVec.end(); ++it)
	{
		FileManager::objectData store = (FileManager::objectData)(*it);

		// Furniture
		if (stoi(store.Type) == 1)
		{
			Create::Furniture3D(store.Name,
				Vector3(stof(store.positionX), stof(store.positionY), stof(store.positionZ)),
				Vector3(stof(store.scaleX), stof(store.scaleY), stof(store.scaleZ)));
		}

		// Enemy ninja troops
		/*else if (stoi(store.Type) == 2)
		{
			CEnemy3D* enemy = new CEnemy3D();
			enemy = Create::Enemy3D(store.Name,
				Vector3(stof(store.positionX), stof(store.positionY), stof(store.positionZ)),
				Vector3(stof(store.scaleX), stof(store.scaleY), stof(store.scaleZ)), stoi(store.objType));
			enemy->Init();
			enemy->SetType(1);
		}*/

		// Trees (Random Spawn)
		else if (stoi(store.Type) == 3)
		{
			srand(time(NULL));
			Create::Trees3D(store.Name,
				Vector3(Math::RandFloatMinMax(-stof(store.positionX), stof(store.positionX))
					, stof(store.positionY),
					Math::RandFloatMinMax(-stof(store.positionZ), stof(store.positionZ))),
				Vector3(stof(store.scaleX), stof(store.scaleY), stof(store.scaleZ)));
		}

		// Turrets
		else if (stoi(store.Type) == 4)
		{
			Create::Turret3D(store.Name,
				Vector3(stof(store.positionX), stof(store.positionY), stof(store.positionZ)),
				Vector3(stof(store.scaleX), stof(store.scaleY), stof(store.scaleZ)), stoi(store.objType));
		}
	}
	objVec.clear();
}

void FileManager::PrintData()
{
	for (vector<FileManager::objectData>::iterator it = objVec.begin(); it != objVec.end(); ++it)
	{
		FileManager::objectData store = (FileManager::objectData)(*it);
		cout << stoi(store.Type) << ", ";
		cout << store.Name << ", ";
		cout << stof(store.positionX) << ", ";
		cout << stof(store.positionY) << ", ";
		cout << stof(store.positionZ) << ", ";
		cout << stof(store.scaleX) << ", ";
		cout << stof(store.scaleX) << ", ";
		cout << stof(store.scaleZ) << endl;
	}
}

vector<FileManager::objectData> FileManager::returnVec()
{
	return objVec;
}