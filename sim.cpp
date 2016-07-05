
#include "crc.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <ctime>
#define NUM_SIMULATIONS 2000

double checkOneError(int* msg, int len, int* g_poly, int len_g);
double checkTwoErrors(int* msg, int len, int* g_poly, int len_g);


//just a random message, you can choose one of your one...
int msg[256] = {1,1,1,1,0,1,1,0,0,1,0,0,1,1,1,1,1,0,0,1,0,0,0,1,1,0,1,
		0,1,1,1,1,0,0,0,1,0,0,1,0,0,1,0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,
		0,1,1,0,1,1,1,1,1,0,1,1,1,0,1,0,0,1,0,0,1,0,1,1,1,0,1,1,0,1,
		1,0,0,0,1,1,0,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1,0,
		1,1,1,0,1,0,1,0,0,1,1,1,1,0,1,1,1,1,0,1,1,0,0,1,1,0,1,0,0,0,
		1,1,0,1,0,0,1,1,0,1,0,0,1,0,0,0,0,1,1,0,1,1,1,1,1,1,0,1,1,1,
		1,1,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,1,0,1,1,0,1,1,0,1,1,
		1,0,1,1,1,1,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,1,1,
		1,0,0,1,1,0,0,1,1,0,1,0,0,0,0,0,1,1,1};

//int msg1[5] = { 1, 0, 0, 1, 1 };
//int pp[3] = { 0, 1, 1 }; //x+x^2

int p1[2] = {1,1};	//1+x
int p2[65] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,1};	// x^64
int p3[16] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 };	//1+x^14+x^15

int main(){
	double* results = new double[6]();
	for (int i = 0; i < 6; i++){
		results[i] = 0;
	}
	for (int i = 0; i < NUM_SIMULATIONS; i++){
		results[0] += checkOneError(msg, 256, p1, 1);
		results[2] += checkOneError(msg, 256, p2, 64);
		results[4] += checkOneError(msg, 256, p3, 15);
		results[1] += checkTwoErrors(msg, 256, p1, 1);
		results[3] += checkTwoErrors(msg, 256, p2, 64);
		results[5] += checkTwoErrors(msg, 256, p3, 15);
	}
	for (int i = 0; i < 6; i++){
		std::cout << results[i] / NUM_SIMULATIONS << std::endl;
	}
	int tmp;
	std::cin >> tmp;
	return 0;
}

double checkOneError(int* msg, int len, int* g_poly, int len_g){
	int randNum = rand() % (len + len_g);
	int* res = new int[len + len_g]();
	encode(msg, len, g_poly, len_g, res);
	res[randNum] = (res[randNum] + 1) % 2;

	bool flag = validate(res, (len + len_g), g_poly, len_g);
	if (flag){
		delete[] res;
		return (double)1;
	}
	delete[] res;
	return (double)0;
}

double checkTwoErrors(int* msg, int len, int* g_poly, int len_g){
	
	int randNum = rand() % (len + len_g);
	int randNum2 = rand() % (len + len_g);
	int i = 0;
	while (randNum == randNum2 && i < len + len_g){
		randNum2 = rand() % (len + len_g);
		i++;
	}
	int* res = new int[len + len_g]();
	encode(msg, len, g_poly, len_g, res);
	res[randNum] = (res[randNum] + 1) % 2;
	res[randNum2] = (res[randNum2] + 1) % 2;
	bool flag = validate(res, (len + len_g), g_poly, len_g);
	if (flag){
		delete[] res;
		return (double)1;
	}
	delete[] res;
	return (double)0;
}
