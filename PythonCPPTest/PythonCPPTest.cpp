#include <Python.h>
#include <iostream>
#include <vector>
#include <locale>
#include <codecvt>

// Helper function to convert char* to wchar_t*
std::wstring charToWChar(const char* str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(str);
}

// C++ function that will be exposed to Python
static PyObject* cpp_hello_function(PyObject* self, PyObject* args) {
    const char* name;

    // Parse the Python arguments (expects a single string)
    if (!PyArg_ParseTuple(args, "s", &name)) {
        return NULL;
    }

    // Print a C++ style greeting
    printf("Hello from C++ function! Name: %s\n", name);

    // Return a Python None object
    Py_RETURN_NONE;
}

// Define methods to be exposed to Python
static PyMethodDef EmbMethods[] = {
    // {"Python function name", Function reference, Arguments type, Docstring}
    {"cpp_hello", cpp_hello_function, METH_VARARGS, "Say hello from C++."},
    {NULL, NULL, 0, NULL}  // Sentinel
};

// Define a module that holds the methods
static struct PyModuleDef EmbModule = {
    PyModuleDef_HEAD_INIT,
    "embmodule",    // Module name
    NULL,           // Module documentation
    -1,             // Size of per-interpreter state (-1 if state is global)
    EmbMethods      // Method definitions
};

// Function to initialize the module
PyMODINIT_FUNC PyInit_embmodule(void) {
    return PyModule_Create(&EmbModule);
}

int main(int argc, char* argv[]) {
    // Initialize Python interpreter
    Py_Initialize();

    // Convert char* argv to wchar_t*
    std::vector<wchar_t*> wargv(argc);
    std::vector<std::wstring> wargvStorage(argc);
    for (int i = 0; i < argc; ++i) {
        wargvStorage[i] = charToWChar(argv[i]);  // Convert to wstring
        wargv[i] = const_cast<wchar_t*>(wargvStorage[i].c_str());  // Store wchar_t*
    }

    // Add the C++ defined module to Python
    PyImport_AppendInittab("embmodule", PyInit_embmodule);

    // Set Python's sys.argv using wide character version of the arguments
    PySys_SetArgvEx(argc, wargv.data(), 0);

    // Start an interactive Python console
    PyRun_SimpleString(
        "import embmodule\n"       // Import the custom module
        "print('Welcome to the embedded Python interpreter!')\n"
        "while True:\n"
        "    try:\n"
        "        user_input = input('>>> ')\n"  // Input prompt
        "        exec(user_input)\n"
        "    except Exception as e:\n"
        "        print(f'Error: {e}')\n"
    );

    // Finalize the Python interpreter
    Py_Finalize();
    return 0;
}
