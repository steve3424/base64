#include <stdio.h>

// Ignores print statements in code being tested
#define SUPPRESS_PRINTF

#ifdef SUPPRESS_PRINTF
#define printf(...) 
#define TEST_PRINT(...) fprintf(stdout, __VA_ARGS__)
#else
#define TEST_PRINT(...) printf(__VA_ARGS__)
#endif

#include "..\\src\\base64.c"

// Run test, fill out this struct, and return
typedef struct {
	int passed;
	char error_str[128];	
} UnitTestResult;

// Create an array of these and fill out with test functions
typedef struct {
	char* test_name;
	UnitTestResult (*test_func)();
} UnitTest;

uint8_t* CreateRandomBytes(int num_bytes) {
	uint8_t* data = malloc(num_bytes); 
	for(int i = 0; i < num_bytes; ++i) {
		uint8_t num = rand() % 255;
		data[i] = num;
	}
	return data;
}

int CompareBytes(uint8_t* bytes_1, uint8_t* bytes_2, uint64_t size) {
	for(uint64_t i = 0; i < size; ++i) {
		if(bytes_1[i] != bytes_2[i]) {
			return 0;
		}
	}

	return 1;
}

UnitTestResult TEST_1024_bytes() {
	uint64_t num_bytes = 1024;
	uint8_t* data          = CreateRandomBytes(num_bytes);
	char*    base64_string = Base64Encode(data, num_bytes);
	uint64_t data_size     = 0;
	uint8_t* data_decoded  = Base64Decode(base64_string, &data_size);

	UnitTestResult test_result;
	if(!CompareBytes(data, data_decoded, num_bytes)) {
		test_result.passed = 0;
		snprintf(test_result.error_str, sizeof(test_result.error_str), "Mismatch on decode...\n");
	}
	else {
		test_result.passed = 1;
	}

	free(data);
	free(base64_string);
	free(data_decoded);

	return test_result;
}

UnitTestResult TEST_2048_bytes() {
	uint64_t num_bytes = 2048;
	uint8_t* data          = CreateRandomBytes(num_bytes);
	char*    base64_string = Base64Encode(data, num_bytes);
	uint64_t data_size     = 0;
	uint8_t* data_decoded  = Base64Decode(base64_string, &data_size);

	UnitTestResult test_result;
	if(!CompareBytes(data, data_decoded, num_bytes)) {
		test_result.passed = 0;
		snprintf(test_result.error_str, sizeof(test_result.error_str), "Mismatch on decode...\n");
	}
	else {
		test_result.passed = 1;
	}

	free(data);
	free(base64_string);
	free(data_decoded);

	return test_result;
}

UnitTestResult TEST_4096_bytes() {
	uint64_t num_bytes = 4096;
	uint8_t* data          = CreateRandomBytes(num_bytes);
	char*    base64_string = Base64Encode(data, num_bytes);
	uint64_t data_size     = 0;
	uint8_t* data_decoded  = Base64Decode(base64_string, &data_size);

	UnitTestResult test_result;
	if(!CompareBytes(data, data_decoded, num_bytes)) {
		test_result.passed = 0;
		snprintf(test_result.error_str, sizeof(test_result.error_str), "Mismatch on decode...\n");
	}
	else {
		test_result.passed = 1;
	}

	free(data);
	free(base64_string);
	free(data_decoded);

	return test_result;
}

UnitTestResult TEST_8192_bytes() {
	uint64_t num_bytes = 8192;
	uint8_t* data          = CreateRandomBytes(num_bytes);
	char*    base64_string = Base64Encode(data, num_bytes);
	uint64_t data_size     = 0;
	uint8_t* data_decoded  = Base64Decode(base64_string, &data_size);

	UnitTestResult test_result;
	if(!CompareBytes(data, data_decoded, num_bytes)) {
		test_result.passed = 0;
		snprintf(test_result.error_str, sizeof(test_result.error_str), "Mismatch on decode...\n");
	}
	else {
		test_result.passed = 1;
	}

	free(data);
	free(base64_string);
	free(data_decoded);

	return test_result;
}

UnitTestResult TEST_1025_bytes() {
	uint64_t num_bytes = 1025;
	uint8_t* data          = CreateRandomBytes(num_bytes);
	char*    base64_string = Base64Encode(data, num_bytes);
	uint64_t data_size     = 0;
	uint8_t* data_decoded  = Base64Decode(base64_string, &data_size);

	UnitTestResult test_result;
	if(!CompareBytes(data, data_decoded, num_bytes)) {
		test_result.passed = 0;
		snprintf(test_result.error_str, sizeof(test_result.error_str), "Mismatch on decode...\n");
	}
	else {
		test_result.passed = 1;
	}

	free(data);
	free(base64_string);
	free(data_decoded);

	return test_result;
}

UnitTestResult TEST_2049_bytes() {
	uint64_t num_bytes = 2049;
	uint8_t* data          = CreateRandomBytes(num_bytes);
	char*    base64_string = Base64Encode(data, num_bytes);
	uint64_t data_size     = 0;
	uint8_t* data_decoded  = Base64Decode(base64_string, &data_size);

	UnitTestResult test_result;
	if(!CompareBytes(data, data_decoded, num_bytes)) {
		test_result.passed = 0;
		snprintf(test_result.error_str, sizeof(test_result.error_str), "Mismatch on decode...\n");
	}
	else {
		test_result.passed = 1;
	}

	free(data);
	free(base64_string);
	free(data_decoded);

	return test_result;
}

UnitTestResult TEST_4097_bytes() {
	uint64_t num_bytes = 4097;
	uint8_t* data          = CreateRandomBytes(num_bytes);
	char*    base64_string = Base64Encode(data, num_bytes);
	uint64_t data_size     = 0;
	uint8_t* data_decoded  = Base64Decode(base64_string, &data_size);

	UnitTestResult test_result;
	if(!CompareBytes(data, data_decoded, num_bytes)) {
		test_result.passed = 0;
		snprintf(test_result.error_str, sizeof(test_result.error_str), "Mismatch on decode...\n");
	}
	else {
		test_result.passed = 1;
	}

	free(data);
	free(base64_string);
	free(data_decoded);

	return test_result;
}

UnitTestResult TEST_8193_bytes() {
	uint64_t num_bytes = 8193;
	uint8_t* data          = CreateRandomBytes(num_bytes);
	char*    base64_string = Base64Encode(data, num_bytes);
	uint64_t data_size     = 0;
	uint8_t* data_decoded  = Base64Decode(base64_string, &data_size);

	UnitTestResult test_result;
	if(!CompareBytes(data, data_decoded, num_bytes)) {
		test_result.passed = 0;
		snprintf(test_result.error_str, sizeof(test_result.error_str), "Mismatch on decode...\n");
	}
	else {
		test_result.passed = 1;
	}

	free(data);
	free(base64_string);
	free(data_decoded);

	return test_result;
}

int main() {
	#define NUM_TESTS 8
	UnitTest all_tests[NUM_TESTS];

	UnitTest test_0;
	test_0.test_name = "TEST_1024_bytes()";
	test_0.test_func =  TEST_1024_bytes;
	all_tests[0] = test_0;

	UnitTest test_1;
	test_1.test_name = "TEST_2048_bytes()";
	test_1.test_func =  TEST_2048_bytes;
	all_tests[1] = test_1;

	UnitTest test_2;
	test_2.test_name = "TEST_4096_bytes()";
	test_2.test_func =  TEST_4096_bytes;
	all_tests[2] = test_2;

	UnitTest test_3;
	test_3.test_name = "TEST_8192_bytes()";
	test_3.test_func =  TEST_8192_bytes;
	all_tests[3] = test_3;

	UnitTest test_4;
	test_4.test_name = "TEST_1025_bytes()";
	test_4.test_func =  TEST_1025_bytes;
	all_tests[4] = test_4;

	UnitTest test_5;
	test_5.test_name = "TEST_2049_bytes()";
	test_5.test_func =  TEST_2049_bytes;
	all_tests[5] = test_5;

	UnitTest test_6;
	test_6.test_name = "TEST_4097_bytes()";
	test_6.test_func =  TEST_4097_bytes;
	all_tests[6] = test_6;

	UnitTest test_7;
	test_7.test_name = "TEST_8193_bytes()";
	test_7.test_func =  TEST_8193_bytes;
	all_tests[7] = test_7;

	for(int i = 0; i < NUM_TESTS; ++i) {
		TEST_PRINT("Running test %s...", all_tests[i].test_name);
		UnitTestResult test_result = all_tests[i].test_func();
		if(test_result.passed) {
			TEST_PRINT("PASSED\n");
		}
		else {
			TEST_PRINT("FAILED\n");
			TEST_PRINT(test_result.error_str);
		}
	}
}