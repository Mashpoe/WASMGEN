//
//  wasm_code.h
//  WASMGEN
//
//  Created by Mashpoe on 7/26/19.
//

#ifndef wasm_code_h
#define wasm_code_h

#include "wasm_macros.h"
#include <stddef.h>
#include <stdbool.h>

// evaluates args for nested expressions
#define $eval_args(...)	__VA_ARGS__

// for nested expressions
#define $(...)	$eval_args(__VA_ARGS__)

// concatenates wasm bytes into a char array
#define $cat_arr(...)	((char[]){__VA_ARGS__})

// adds bytes to a wasm_code* object
#define $wasm(code, ...)	(wasm_code_add(code, $cat_arr(__VA_ARGS__), sizeof($cat_arr(__VA_ARGS__))))

typedef struct wasm_code wasm_code;

wasm_code* wasm_code_create(void);

void wasm_code_add(wasm_code* code, char* bytes, size_t count);

void wasm_code_print(wasm_code* code);

bool wasm_code_output(wasm_code* code, const char* filename);

#endif /* wasm_code_h */
