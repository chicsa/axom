// pyUserLibrarymodule.hpp
// This is generated code, do not edit
// blah blah
// yada yada
//

/*
 * This is generated code.
 * Any edits must be made between the splicer.begin and splicer.end blocks.
 * All other edits will be lost.
 * Once a block is edited remove the 'UNMODIFIED' on the splicer.begin
 * comment to allow the block to be preserved when it is regenerated.
 */

#ifndef HDR_BASISMODULE
#define HDR_BASISMODULE
#include <Python.h>
#if PY_MAJOR_VERSION >= 3
#define IS_PY3K
#endif
// splicer begin include
// splicer end include
namespace example {
namespace nested {
extern PyTypeObject PP_ExClass1_Type;
extern PyTypeObject PP_ExClass2_Type;
// splicer begin C_declaration
// splicer end C_declaration
// splicer begin class.ExClass1.C_declaration
// splicer end class.ExClass1.C_declaration

typedef struct {
PyObject_HEAD
// splicer begin class.ExClass1.C_object
// splicer end class.ExClass1.C_object
} PP_ExClass1;
// splicer begin class.ExClass2.C_declaration
// splicer end class.ExClass2.C_declaration

typedef struct {
PyObject_HEAD
// splicer begin class.ExClass2.C_object
// splicer end class.ExClass2.C_object
} PP_ExClass2;

extern PyObject *PP_error_obj;

#ifdef __cplusplus
extern "C" {
#endif
#ifdef IS_PY3K
#define MOD_INITBASIS PyInit_userlibrary
#else
#define MOD_INITBASIS inituserlibrary
#endif
PyMODINIT_FUNC MOD_INITBASIS(void);
#endif
#ifdef __cplusplus
}
#endif

}  // namespace example
}  // namespace nested
