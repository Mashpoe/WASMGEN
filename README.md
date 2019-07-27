# WASMGEN
A tool for creating WebAssembly JIT compilers in C.

With the advent of WebAssembly, languages other than JavaScript can finally run on the Web, but most of them are compiled languages like C, C++, and Rust. Some interpreters have been made, but in order to make a truly fast and lightweight interpreter, you need to include a JIT compiler that produces WebAssembly.

Assemblers are not ideal for JIT compilers, especially when they're running on the web because they have overhead and make your interpreter much larger. This simple tool was made for C programs to quickly produce binary-formatted WebAssembly, rather than producing WebAssembly in text form or LLVM IR code that will be run through an assembler.

This tool doesn't let you use WebAssembly in text form, but it does make the binary format much more readable and easier to edit.

Here is some sample code:

```c
wasm_code* code = wasm_code_create();

$wasm(code,
	  $magic, $version,			    // meta info; magic number & wasm version

	  $sec_type, 0x07,			    // type section, size of 0
	  0x01,						          // num types

	  $func, 0x02, $i32, $i32,	// function with two (0x02) parameters, i32 and i32
	  0x01, $i32,				        // function has one (0x01) i32 result

	  $sec_func, 0x02,			    // function section, size of 0x02
	  0x01, 0x00,				        // one (0x01) function, function 0 signature index

	  $sec_export, 0x07,		    // export section, guess size of 0x07
	  0x01, 0x03,				        // number of exports (0x01), string size of 3 (0x03) chars
		'a','d','d',			        // export name string (add)
	  0x00, 0x00,				        // export kind, export func

	  $sec_code, 0x09, 0x01,	  // function section, size of 0x09, one (0x01) function

	  // function body
	  0x07, 0x00,				        // size of 0x07, local decl count of 0
	  $local_get, 0x00,			    // local.get, local index 0
	  $local_get, 0x01,			    // local.get, local index 1
	  $i32_add,					        // i32.add
	  $end,						          // end

);

```

As you can probably tell, a lot of this is done with the C preprocessor. When compiling, the code above roughly translates to this:

```c

wasm_code* code = wasm_code_create();

wasm_code_add(code, ((char[]){
	0x00, 0x61, 0x73, 0x6D, 0x01, 0x00, 0x00, 0x00, 0x01, 0x07, 0x01, 0x60, 0x02, 0x7F, 0x7F, 0x01,
	0x7F, 0x03, 0x02, 0x01, 0x00, 0x07, 0x07, 0x01, 0x03, 0x61, 0x64, 0x64, 0x00, 0x00, 0x0A, 0x09,
	0x01, 0x07, 0x00, 0x20, 0x00, 0x20, 0x01, 0x6A, 0x0B
}), 41);

```

This results in a very fast JIT compiler that can take code and quickly fill a buffer with executable, binary-formatted WebAssembly.

Of course, you can split up your program into multiple `$wasm` statements, which can be useful for offloading certain code generation to other functions. You can also group things inside the body of a `$wasm` statement using `$(` and `)` parentheses. Parentheses have no effect on the preprocessor output, but they can help for organization.

```c

wasm_code* code = wasm_code_create();

$wasm(code,
	  $magic, $version,
	  $sec_type, 0x07,
	  0x01,
);

// seperate $wasm statements writing to the same buffer
$wasm(code,
	// separate sections with parentheses
	$(
		$func, 0x02, $i32, $i32,
		0x01, $i32,
		$sec_func, 0x02,
		0x01, 0x00
	),

	$(
		$sec_export, 0x07,
		0x01, 0x03,
		'a','d','d',
		0x00, 0x00
	),
);

$wasm(code,
	$sec_code, 0x09, 0x01,

	// function body
	$(
		0x07, 0x00,
		$local_get, 0x00,
		$local_get, 0x01,
		$i32_add,
		$end
	)

);

```

The code above will produce the exact same WebAssembly, but it's broken up into sections to make it more readable.

You can print the entire WebAssembly buffer via `wasm_code_print(code);` and you can write the buffer to a file via `wasm_code_output(code, "output.wasm");`.
