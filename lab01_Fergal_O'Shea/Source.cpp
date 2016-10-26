#include <stdio.h> 
#include <string.h> 
#include <cmath>
#include <iostream>

#define NUM_TEST_KEYS 8
#define MAX_KEY_LENGTH 16
#define HASH_TABLE_SIZE_M 17

using namespace std;

char hash_table[HASH_TABLE_SIZE_M][MAX_KEY_LENGTH];


int hash_function(const char *key, int table_size) {
	int index = 0;
	
	for (int i = 0; i < strlen(key); i++) {
		if (i / 2 == 0) {
			index = index + pow(key[i], 2);
		}
		else {
			index = index + pow(key[i], 3);
		}
	}
	return abs(index%HASH_TABLE_SIZE_M);
}

int re_hash_function(const char *key, int table_size) {
	int index = 0;

	for (int i = strlen(key) - 1; i >= 0; i--) {
		index = index + strlen(key)*pow(key[i], i);
	}
	return abs(index%HASH_TABLE_SIZE_M)+1;
}

int main() {

	char test_strings[NUM_TEST_KEYS][MAX_KEY_LENGTH] = {
		"prince adam", "orko", "cringer", "teela", "aleet", "princess adora", "orko", "jimmy"
	};

	printf(
		"             key      table index\n-----------------------------------\n");

	for (int i = 0; i < NUM_TEST_KEYS; i++) {
		int index = hash_function(test_strings[i], HASH_TABLE_SIZE_M);

		if (hash_table[index][0] == 0) {
			strcpy_s(hash_table[index], test_strings[i]);
		}

		else {

			int increment= re_hash_function(test_strings[i], HASH_TABLE_SIZE_M) % HASH_TABLE_SIZE_M;
			index = (index + i*increment) % (HASH_TABLE_SIZE_M);

			while (hash_table[index][0] != 0) {
				index = (index + i*increment) % (HASH_TABLE_SIZE_M);
			}
			strcpy_s(hash_table[index],test_strings[i]);
		}
		
		printf("%16s %6i\n", test_strings[i], index);
	}

	for (int i = 0; i < HASH_TABLE_SIZE_M; i++) {
		printf("%i\t%s\n",i, hash_table[i]);
	}

	//
	// calculate table load here
	//
	int stop;
	cin >> stop;
	return 0;
}