
#include "crc.hpp"
#include <iostream>

void xorAux(int* src1, int* src2, int* dst, int len){
	for (int i = 1; i < len; i++) {
		if (src1[i] == src2[i]) {
			dst[i - 1] = 0;
		}
		else {
			dst[i - 1] = 1;
		}
	}
}
/*
 * param msg - message to encode
 * param p - polynom for the CRC
 * param g - degree of the polynom
 * */
void encode(int* msg, int len, int* p, int g, int* e_msg){
	if (!msg | !p | !e_msg) {
		return;	//input error
	}
	int* tx = new int[len + g]();
	for (int i = 0; i < len; i++) {  //create t(x) polynom 
		tx[i] = msg[i];
	}
	for (int i = len; i < len+g; i++) {  //multiply by x^g (addion 0 at the end)
		tx[i] = 0;
	}


	int* theRemaining = new int[g + 1]();
	int* zeroCase = new int[g + 1]();
	int* oneCase = new int[g + 1]();
	for (int i = 0, j = g; i < g + 1; i++, j--){
		zeroCase[i] = 0;
		oneCase[i] = p[j];
	}
	for (int j = 0; j < g + 1; j++){
		theRemaining[j] = tx[j];
	}
	for (int i = 0; i < len; i++){
		if (theRemaining[0] == 1){
			xorAux(oneCase, theRemaining, theRemaining, g + 1);
		}
		else{
			xorAux(zeroCase, theRemaining, theRemaining, g + 1);
		}
		int border = i + g + 1;
		if (border >= len+g){
			border = i + g;
		}
		theRemaining[g] = tx[border];
	}
	for (int i = 0; i < g; i++){		//add the reamaining to the end of t(x)
		tx[len + i] = theRemaining[i];
	}
	for (int i = 0; i < len + g; i++){
		e_msg[i] = tx[i];
	}
	delete[] tx;
	delete[] oneCase;
	delete[] zeroCase;
	delete[] theRemaining;
	return;

}

bool validate(int* msg, int len, int* p, int g){
	if (!msg | !p) {
		return false;	//input error
	}
	int* theRemaining = new int[g + 1]();
	int* zeroCase = new int[g + 1]();
	int* oneCase = new int[g + 1]();
	for (int i = 0, j = g; i < g + 1; i++, j--){
		zeroCase[i] = 0;
		oneCase[i] = p[j];
	}
	for (int j = 0; j < g + 1; j++){
		theRemaining[j] = msg[j];
	}
	for (int i = 0; i < len-g; i++){
		if (theRemaining[0] == 1){
			xorAux(oneCase, theRemaining, theRemaining, g + 1);
		}
		else{
			xorAux(zeroCase, theRemaining, theRemaining, g + 1);
		}
		int border = i + g + 1;
		if (border >= len){
			border = i + g;
		}
		theRemaining[g] = msg[border];
	}
	for (int i = 0; i < g ; i++){
		if (theRemaining[i] != 0){
			delete[] oneCase;
			delete[] zeroCase;
			delete[] theRemaining;
			return true;
		}
	}
	delete[] oneCase;
	delete[] zeroCase;
	delete[] theRemaining;
	return false;
}






