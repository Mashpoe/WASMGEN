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
		  $magic, $version,			// meta info; magic number & wasm version
		  
		  $sec_type, 0x07,			// type section, size of 0
		  0x01,						// num types
		  
		  $func, 0x02, $i32, $i32,	// function with two (0x02) parameters, i32 and i32
		  0x01, $i32,				// function has one (0x01) i32 result
		  
		  $sec_func, 0x02,			// function section, size of 0x02
		  0x01, 0x00,				// one (0x01) function, function 0 signature index
		  
		  $sec_export, 0x07,		// export section, guess size of 0x07
		  0x01, 0x03,				// number of exports (0x01), string size of 3 (0x03) chars
		  	'a','d','d',			// export name string (add)
		  0x00, 0x00,				// export kind, export func
		  
		  $sec_code, 0x09, 0x01,	// function section, size of 0x09, one (0x01) function
		  
		  // function body
		  0x07, 0x00,				// size of 0x07, local decl count of 0
		  $local_get, 0x00,			// local.get, local index 0
		  $local_get, 0x01,			// local.get, local index 1
		  $i32_add,					// i32.add
		  $end,						// end
		  
	);
	
	wasm_code_print(code);
	
	wasm_code_output(code, "output.wasm");
	
	return 0;
}
