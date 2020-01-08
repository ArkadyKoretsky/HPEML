#pragma once
#ifndef System_namespace
#define System_namespace

#include <iostream>
#include <fstream> 
#include <string>
#include "t_timer.h"
#include "HPEML.h"

namespace System
{

	size_t static VECSIZE = 8;
	size_t static I_BLOCKSIZE = 32;
	size_t static J_BLOCKSIZE = 32;
	size_t static K_BLOCKSIZE = 32;
	size_t static UNROLL_1 = 4; // UNROLL_1 * VECSIZE <= min{I_BLOCKSIZE, J_BLOCKSIZE, K_BLOCKSIZE}
	size_t static UNROLL_2 = 2; //UNROLL_2 * VECSIZE <= min{I_BLOCKSIZE, J_BLOCKSIZE, K_BLOCKSIZE}
	size_t static count_it = 10;

	//public:

	size_t getVecsize() { return VECSIZE; }
	size_t getI_BLOCKSIZE() { return I_BLOCKSIZE; }
	size_t getJ_BLOCKSIZE() { return J_BLOCKSIZE; }
	size_t getK_BLOCKSIZE() { return K_BLOCKSIZE; }
	size_t getUNROLL_1() { return UNROLL_1; }
	size_t getUNROLL_2() { return UNROLL_2; }

	void setVecsize(size_t vecSize) { VECSIZE = vecSize; }
	void static setJ_BLOCKSIZE(size_t blockSize) { J_BLOCKSIZE = blockSize; }
	void static setK_BLOCKSIZE(size_t blockSize) { K_BLOCKSIZE = blockSize; }
	void static setI_BLOCKSIZE(size_t blockSize) { I_BLOCKSIZE = blockSize; }
	void static setUnroll_1(size_t unroll) { UNROLL_1 = unroll; }
	void static setUNROLL_2(size_t unroll) { UNROLL_2 = unroll; }

	void static setValues()
	{
		VECSIZE = 8;
		I_BLOCKSIZE = 32;
		J_BLOCKSIZE = 32;
		K_BLOCKSIZE = 32;
		UNROLL_1 = 4;
		UNROLL_2 = 2;
		count_it = 10;
	}

	void Init()
	{
		//setValues();
		double t = 0;
		t_timer tt;
		for (int i = 16; i <= 256; i *= 2)
		{
			setJ_BLOCKSIZE(i);
			setK_BLOCKSIZE(i);
			setI_BLOCKSIZE(i);
			std::ofstream o("size" + std::to_string(i) + ".csv");
			for (int j = i; j <= 4096 * 4096; j *= 2)
			{
				Matrix<Float> A(j, j, "rand");
				//, B(j, j, "rand")
				for (size_t k = 0; k < count_it; k++)
				{
					tt.start();		//start timer
					//A *= B;
					cout << "1" << endl;
					tt.stop();	//stop timer
					t += tt.get_time();
				}
				double time = t / count_it;
				o << i << ";" << j * j << ";" << time << endl;
				t = 0;
			}
			o.close();
		}
	}

};

#endif //!end namespace
