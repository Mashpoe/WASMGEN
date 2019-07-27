//
//  wasm_code.c
//  WASMGEN
//
//  Created by Mashpoe on 7/26/19.
//

#include "wasm_code.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

#define CODE_MIN_BYTES 1024
#define REALLOC_FACTOR 1.5

struct wasm_code {
	char* bytes;
	size_t alloc;
	size_t pos;
};

wasm_code* wasm_code_create(void) {
	wasm_code* code = malloc(sizeof(wasm_code));
	code->bytes = malloc(CODE_MIN_BYTES);
	code->alloc = CODE_MIN_BYTES;
	code->pos = 0;
	
	return code;
}

void wasm_code_add(wasm_code* code, char* bytes, size_t count) {
	size_t new_pos = code->pos + count;
	
	if (new_pos >= code->alloc)
		code->bytes = realloc(code->bytes, new_pos * REALLOC_FACTOR); // guaranteed to fit new bytes
	
	memcpy(&code->bytes[code->pos], bytes, count);
	
	code->pos = new_pos;
}

void wasm_code_print(wasm_code* code) {
	
	printf("offset: 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
	printf("------:------------------------------------------------");
	
	for (size_t i = 0; i < code->pos; i++) {
		if (i % 0x10 == 0)
			printf("\n%06zX: ", i - i % 0x10);
		printf("%02X ", code->bytes[i]);
	}
	
	printf("\n");
}

bool wasm_code_output(wasm_code* code, const char* output) {
	
	FILE* f = fopen(output, "wb");
	
	if (!f)
		return false;
	
	fwrite(code->bytes, code->pos, 1, f);
	
	return true;
	
}
