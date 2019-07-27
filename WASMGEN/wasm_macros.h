//
//  wasm_macros.h
//  WASMGEN
//
//  Created by Mashpoe on 7/25/19.
//

#ifndef wasm_macros_h
#define wasm_macros_h

#define $magic		0x00, 0x61, 0x73, 0x6D // spells out "\0asm"
#define $version	0x01, 0x00, 0x00, 0x00 // wasm version 1


#define $i32		0x7F
#define $i64		0x7E
#define $f32		0x7D
#define $f64		0x7C

#define $func		0x60

#define $sec_type	0x01
#define $sec_func	0x03
#define $sec_mem	0x05
#define $sec_export	0x07
#define $sec_code	0x0A

#endif /* wasm_macros_h */
