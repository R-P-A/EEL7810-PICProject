#include "config.h"

bit_test_int(int value, unsigned int pos) {
	return (value >> pos) & 1;
}


bit_test_uint(unsigned int value, unsigned int pos){
	return (value >> pos) & 1;
}