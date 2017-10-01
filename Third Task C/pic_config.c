#include "pic_config.h"

bit_test_int(int value, int pos) {
	return (value >> pos) & 1;
}