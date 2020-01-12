#pragma once
#ifndef Initialization_Class
#define Initialization_Class
#include "t_timer.h"
#include "System.h"
#include "Matrix.h"
#include "Float.h"
#include <iostream>
#include <fstream> 
#include <string>

class Initialization
{
public:
	void static Init()
	{
		//setValues();
		double t = 0;
		t_timer tt;
		for (int i = 16; i <= 256; i *= 2)
		{
			System::setJ_BLOCKSIZE(i);
			System::setK_BLOCKSIZE(i);
			System::setI_BLOCKSIZE(i);
			std::ofstream o("size" + std::to_string(i) + ".csv");
			for (int j = i; j <= 4096 * 4096; j *= 2)
			{
				Matrix<Float> A(j, j, "rand"), B(j, j, "rand");
				for (size_t k = 0; k < 10; k++)
				{
					tt.start();		//start timer
					A *= B;
					tt.stop();	//stop timer
					t += tt.get_time();
				}
				double time = t / 10;
				o << i << ";" << j * j << ";" << time << endl;
				t = 0;
			}
			o.close();
		}
	}

};



#endif