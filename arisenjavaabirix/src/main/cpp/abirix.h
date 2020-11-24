// copyright defined in ABIRSN/LICENSE.txt

#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ABIRSN_context_s ABIRSN_context;
typedef int ABIRSN_bool;

// Create a context. The context holds all memory allocated by functions in this header. Returns null on failure.
ABIRSN_context* ABIRSN_create();

// Destroy a context.
void ABIRSN_destroy(ABIRSN_context* context);

// Get last error. Never returns null. The context owns the returned string.
const char* ABIRSN_get_error(ABIRSN_context* context);

// Get generated binary. The context owns the returned memory. Functions return null on error; use ABIRSN_get_error to
// retrieve error.
int ABIRSN_get_bin_size(ABIRSN_context* context);
const char* ABIRSN_get_bin_data(ABIRSN_context* context);

// Convert generated binary to hex. The context owns the returned string. Returns null on error; use ABIRSN_get_error to
// retrieve error.
const char* ABIRSN_get_bin_hex(ABIRSN_context* context);

// Name conversion. The context owns the returned memory. Functions return null on error; use ABIRSN_get_error to
// retrieve error.
uint64_t ABIRSN_string_to_name(ABIRSN_context* context, const char* str);
const char* ABIRSN_name_to_string(ABIRSN_context* context, uint64_t name);

// Set abi (JSON format). Returns false on error.
ABIRSN_bool ABIRSN_set_abi(ABIRSN_context* context, uint64_t contract, const char* abi);

// Set abi (binary format). Returns false on error.
ABIRSN_bool ABIRSN_set_abi_bin(ABIRSN_context* context, uint64_t contract, const char* data, size_t size);

// Set abi (hex format). Returns false on error.
ABIRSN_bool ABIRSN_set_abi_hex(ABIRSN_context* context, uint64_t contract, const char* hex);

// Get the type name for an action. The contract owns the returned memory. Returns null on error; use ABIRSN_get_error
// to retrieve error.
const char* ABIRSN_get_type_for_action(ABIRSN_context* context, uint64_t contract, uint64_t action);

// Convert json to binary. Use ABIRSN_get_bin_* to retrieve result. Returns false on error.
ABIRSN_bool ABIRSN_json_to_bin(ABIRSN_context* context, uint64_t contract, const char* type, const char* json);

// Convert json to binary. Allow json field reordering. Use ABIRSN_get_bin_* to retrieve result. Returns false on error.
ABIRSN_bool ABIRSN_json_to_bin_reorderable(ABIRSN_context* context, uint64_t contract, const char* type,
                                           const char* json);

// Convert binary to json. The context owns the returned string. Returns null on error; use ABIRSN_get_error to retrieve
// error.
const char* ABIRSN_bin_to_json(ABIRSN_context* context, uint64_t contract, const char* type, const char* data,
                               size_t size);

// Convert hex to json. The context owns the returned memory. Returns null on error; use ABIRSN_get_error to retrieve
// error.
const char* ABIRSN_hex_to_json(ABIRSN_context* context, uint64_t contract, const char* type, const char* hex);

#ifdef __cplusplus
}
#endif
