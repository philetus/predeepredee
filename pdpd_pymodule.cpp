/*  gooey_pymodule.cpp
 *
 *  python interface for pdpd.gooey module
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */

using namespace std;
using namespace pdpd;
using namespace gooey;

#include <Python.h> // python api

#include "TheGooeyDemon.h"
#include "Window_pytype.h"

// python interpreter wants plain c? :P
#ifdef __cplusplus
extern "C" {
#endif 
 
// pointer to hold demon once started
static TheGooeyDemon* demon;

// error to be raised if something goes wrong
static PyObject *GooeyError;

// *** start gooey demon
static PyObject*
start_gooey_demon(PyObject*, PyObject*) // ignore self and args
{
    if (!start_gooey_thread(demon))
        return NULL; // if starting gooey demon fails, return null pointer
    
    // return None on success
    Py_INCREF(Py_None);
    return Py_None;
}

// *** stop gooey demon
static PyObject*
stop_gooey_demon(PyObject*, PyObject*) // ignore self and args
{
    if (!stop_gooey_thread(demon))
        return NULL; // if starting gooey demon fails, return null pointer
    
    // return None on success
    Py_INCREF(Py_None);
    return Py_None;
}

// *** create pdpd window
static PyObject *
create_window(PyObject*, PyObject*) // ignore self and args
{
    // TODO create window object and return it
    return Py_BuildValue("i", sts);
}

// *** module initialization function
PyMODINIT_FUNC
PyInit_gooey(void)
{
    PyObject *m;

    m = PyModule_Create(&gooey_module);
    if (m == NULL)
        return NULL;

    GooeyError = PyErr_NewException("gooey.error", NULL, NULL);
    Py_INCREF(GooeyError);
    PyModule_AddObject(m, "error", GooeyError);
    return m;
}

// *** list of methods to be exposed in python
static PyMethodDef gooey_methods[] = {
    {"start_gooey_demon",  start_gooey_demon, METH_VARARGS,
     "Start GUI manager demon in separate thread."},
    {"stop_gooey_demon",  start_gooey_demon, METH_VARARGS,
     "Stop GUI manager demon."},
    {"create_window",  create_window, METH_VARARGS,
     "Create a new window."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef gooey_module = {
   PyModuleDef_HEAD_INIT,
   "gooey",   /* name of module */
   NULL, /* module documentation, may be NULL */
   -1,       /* size of per-interpreter state of the module,
                or -1 if the module keeps state in global variables. */
   gooey_methods
};

#ifdef __cplusplus
}
#endif 
