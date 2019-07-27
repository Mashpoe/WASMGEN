//
//  main.c
//  WASMGEN
//
//  Created by Mashpoe on 7/25/19.
//

#include <stdio.h>
#include "wasm_code.h"

int main(int argc, const char * argv[]) {
	// insert code here...
	
	wasm_code* code = wasm_code_create();
	
	$wasm(code,
		  $magic, $version
	);
	
	wasm_code_print(code);
	
	return 0;
}
