#pragma once
#ifndef Initialization_Class
#define Initialization_Class
#include "t_timer.h"
#include "System.h"
#include "Matrix.h"
#include <iostream>
#include <fstream> 
#include <string>
#include <regex>
#include <array>
#include <cmath>
#include "Float.h"

// windows\linux libraries
#ifdef _WIN32
//#include <windows.h> // the visual compiler doing problems with this library
#else
#include <unistd.h> // linux library
#endif


#define CTIMES 10
#define MinBlockSize 16
#define MaxBlockSize 256
#define MinMatrixSize 16
#define MaxMatrixSize 4096

class Initialization
{
public:
	static std::pair<int, double>  times[5];
	void static Init()
	{
		double t = 0;
		t_timer tt;
		for (int i = MinBlockSize; i <= MaxBlockSize; i *= 2)
		{
			System::setJ_BLOCKSIZE(i);
			System::setK_BLOCKSIZE(i);
			System::setI_BLOCKSIZE(i);
			std::ofstream o("size" + std::to_string(i) + ".csv");
			cout << "size" + std::to_string(i) + ".csv is open" << endl;
			for (int j = MinMatrixSize; j <= MaxMatrixSize; j *= 2)
			{
				Matrix<Float> A(j, j, "rand"), B(j, j, "rand");
				for (size_t k = 0; k < CTIMES; k++)
				{
					tt.start();		//start timer
					A *= B;
					tt.stop();	//stop timer
					t += tt.get_time();
				}
				double time = t / CTIMES;
				o << i << ";" << j << "*" << j << ";" << time << std::endl;
				std::cout << i << ";" << j << "*" << j << ";" << time << std::endl;
				t = 0;
			}
			o.close();
			cout << "file closed" << endl;
		}
	}

	vector<std::string> static splitLine(string line)
	{
		std::string s{ line };
		std::regex regex{ R"([;]+)" };
		std::sregex_token_iterator it{ s.begin(), s.end(), regex, -1 };
		std::vector<std::string> words{ it, {} };
		return words;
	}

	void static readData()
	{
		int counter = 0;
		double time = 0;
		string line;
		for (int i = MinBlockSize; i <= MaxBlockSize; i *= 2)
		{
			std::fstream o("size" + std::to_string(i) + ".csv", ios::in);
			int  size = 0;
			for (int j = MinMatrixSize; j <= MaxMatrixSize; j *= 2)
			{
				std::getline(o, line);
				vector<std::string> split = splitLine(line);
				time += std::stod(split[2]);
				size++;
			}
			times[counter].first = i;
			times[counter].second = (time / size);
			cout << "avg time : " << time / size << endl;;
			time = 0;
			size = 0;
			counter++;
		}
		double min = times[0].second, index = times[0].first;
		for (int i = 0; i < 5; i++)
		{
			if (min > times[i].second)
			{
				min = times[i].second;
				index = times[i].first;
			}
		}
		System::setJ_BLOCKSIZE(index);
		System::setK_BLOCKSIZE(index);
		System::setI_BLOCKSIZE(index);
		cout << index << endl;
	}

	void static readCache()
	{
#ifdef _WIN32
		cout << "Sorry! This functionality is not suported on Windows." << endl;
#else
		cout << "L1 Instructions Cache Size = " << sysconf(_SC_LEVEL1_ICACHE_SIZE) / pow(2, 10) << " KB" << endl;
		cout << "L1 Data Cache Size = " << sysconf(_SC_LEVEL1_DCACHE_SIZE) / pow(2, 10) << " KB" << endl;
		cout << "L2 Cache Size = " << sysconf(_SC_LEVEL2_CACHE_SIZE) / pow(2, 10) << " KB" << endl;
		cout << "L3 Cache Size = " << sysconf(_SC_LEVEL3_CACHE_SIZE) / pow(2, 10) << " KB" << endl;
#endif
	}

	void static getOS()
	{
#ifdef _WIN32
		cout << "Windows" << endl;
#else
		cout << "Linux" << endl;
#endif
	}
};

#endif