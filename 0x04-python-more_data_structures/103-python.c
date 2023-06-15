#include <Python.h>
#include <stdio.h>

void print_python_list(PyObject *p) {
    if (!PyList_Check(p)) {
        fprintf(stderr, "[ERROR] Invalid List Object\n");
        return;
    }

    Py_ssize_t size = PyList_Size(p);
    Py_ssize_t allocated = ((PyListObject *)p)->allocated;
    Py_ssize_t i;

    printf("[*] Python list info\n");
    printf("[*] Size of the Python List = %ld\n", size);
    printf("[*] Allocated = %ld\n", allocated);

    for (i = 0; i < size; i++) {
        PyObject *item = PyList_GET_ITEM(p, i);
        const char *type = item->ob_type->tp_name;

        printf("Element %ld: %s\n", i, type);
    }
}

void print_python_bytes(PyObject *p) {
    if (!PyBytes_Check(p)) {
        fprintf(stderr, "[ERROR] Invalid Bytes Object\n");
        return;
    }

    PyBytesObject *bytes_obj = (PyBytesObject *)p;
    Py_ssize_t size = PyBytes_Size(p);
    Py_ssize_t i;
    Py_ssize_t max_print = size > 10 ? 10 : size;

    printf("[.] bytes object info\n");
    printf("  size: %ld\n", size);
    printf("  trying string: %s\n", PyBytes_AS_STRING(p));
    printf("  first %ld bytes: ", max_print);

    for (i = 0; i < max_print; i++) {
        printf("%02x", (unsigned char)bytes_obj->ob_sval[i]);
        if (i < max_print - 1)
            printf(" ");
    }

    printf("\n");
}
