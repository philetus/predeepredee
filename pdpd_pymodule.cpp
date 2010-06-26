/*  pdpd_gooey_pymodule.cpp
 *
 *  example illustrating defining a new python type
 *  
 *  from http://docs.python.org/py3k/extending/newtypes.html
 *  
 */
 
#include <Python.h>
#include "structmember.h"

#include "Gooey.h"
#include "WorldWindow.h"
#include "renderer/TargetCamera.h"
#include "renderer/ThingDrawer.h"

// python interpreter wants plain c? :P
#ifdef __cplusplus
extern "C" {
#endif 

/*
 *
 *  *** pdpd wrapper types to be exposed
 *
 */
typedef struct {
    PyObject_HEAD
    pdpd::Gooey* _gooey;
} Gooey;

typedef struct {
    PyObject_HEAD
    pdpd::WorldWindow* _window;
} Window;


/*
 *
 *  *** gooey wrapper  
 *
 */
static void
Gooey_dealloc(Gooey* self)
{
    // free c++ gooey object memory
    delete self->_gooey;
    
    // free python object memory
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject*
Gooey_new(PyTypeObject *type, PyObject*, PyObject*)
{
    Gooey* self;

    self = (Gooey*)type->tp_alloc(type, 0);
    if (self != NULL) 
    {
        self->_gooey = new pdpd::Gooey;
        if (self->_gooey == NULL)
          {
            Py_DECREF(self);
            return NULL;
          }
    }

    return (PyObject*)self;
}

static int
Gooey_init(Gooey* self, PyObject*, PyObject*) // no args, no keywords
{
    return 0;
}

// starts event loop
static PyObject*
Gooey_loop(Gooey* self)
{
    self->_gooey->loop(); // hangs until event loop is stopped

    Py_INCREF(Py_None);
    return Py_None;
}

// stops event loop
static PyObject*
Gooey_kill(Gooey* self)
{
    self->_gooey->handle_quit(); // stops event loop, physics and sdl lib

    Py_INCREF(Py_None);
    return Py_None;
}

// show window on screen
static PyObject*
Gooey_show(Gooey* self, PyObject* wndw)
{
    Window* window = reinterpret_cast<Window*>(wndw);
    if(window == NULL)
    {
        return NULL;
    }
    self->_gooey->show(window->_window);

    Py_INCREF(Py_None);
    return Py_None;
}

// remove window from screen
static PyObject*
Gooey_unshow(Gooey* self, PyObject* wndw)
{
    Window* window = reinterpret_cast<Window*>(wndw);
    if(window == NULL)
    {
        return NULL;
    }
    self->_gooey->unshow(window->_window);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef Gooey_methods[] = {
/*
    {"welcome", (PyCFunction)Gooey_welcome, METH_O,
     "welcome a new thing to world"
    },
    {"dismiss", (PyCFunction)Gooey_dismiss, METH_O,
     "dismiss a thing from world"
    },
*/
    {"show", (PyCFunction)Gooey_show, METH_O,
     "show a window on screen"
    },
    {"unshow", (PyCFunction)Gooey_unshow, METH_O,
     "remove window from screen"
    },
    {"loop", (PyCFunction)Gooey_loop, METH_NOARGS,
     "start event loop"
    },
    {"kill", (PyCFunction)Gooey_kill, METH_NOARGS,
     "stop event loop"
    },
    {NULL}  /* Sentinel */
};

static PyTypeObject GooeyType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pdpd.Gooey",              /* tp_name */
    sizeof(Gooey),             /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)Gooey_dealloc, /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT |
        Py_TPFLAGS_BASETYPE,   /* tp_flags */
    "Gooey object type",       /* tp_doc */
    0,		                   /* tp_traverse */
    0,		                   /* tp_clear */
    0,		                   /* tp_richcompare */
    0,		                   /* tp_weaklistoffset */
    0,		                   /* tp_iter */
    0,		                   /* tp_iternext */
    Gooey_methods,             /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)Gooey_init,      /* tp_init */
    0,                         /* tp_alloc */
    Gooey_new,                 /* tp_new */
};

/*
 *
 *  *** window wrapper  
 *
 */
static void
Window_dealloc(Window* self)
{
    // free c++ gooey object memory
    delete self->_window;
    
    // free python object memory
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject*
Window_new(PyTypeObject *type, PyObject*, PyObject*)
{
    Window* self;

    self = (Window*)type->tp_alloc(type, 0);
    if (self != NULL) 
    {
        pdpd::renderer::TargetCamera* camera = 
            new pdpd::renderer::TargetCamera();
        pdpd::renderer::ThingDrawer* drawer = 
            new pdpd::renderer::ThingDrawer();
        self->_window = new pdpd::WorldWindow(camera, drawer);
        if (self->_window == NULL)
          {
            Py_DECREF(self);
            return NULL;
          }
    }

    return (PyObject*)self;
}

static int
Window_init(Window* self, PyObject*, PyObject*)
{
    return 0;
}


static PyTypeObject WindowType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "pdpd.Window",              /* tp_name */
    sizeof(Window),             /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)Window_dealloc, /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT |
        Py_TPFLAGS_BASETYPE,   /* tp_flags */
    "Window object type",       /* tp_doc */
    0,		                   /* tp_traverse */
    0,		                   /* tp_clear */
    0,		                   /* tp_richcompare */
    0,		                   /* tp_weaklistoffset */
    0,		                   /* tp_iter */
    0,		                   /* tp_iternext */
    0,                         /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)Window_init,      /* tp_init */
    0,                         /* tp_alloc */
    Window_new,                 /* tp_new */
};

/*
 *
 *  *** module setup
 *
 */
static PyModuleDef pdpd_module = {
    PyModuleDef_HEAD_INIT,
    "pdpd",
    "predee predee physics simulation library.",
    -1,
    NULL, NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC
PyInit_pdpd(void) 
{
    PyObject* module;

    if (PyType_Ready(&GooeyType) < 0)
        return NULL;

    if (PyType_Ready(&WindowType) < 0)
        return NULL;

    module = PyModule_Create(&pdpd_module);
    if (module == NULL)
        return NULL;

    Py_INCREF(&GooeyType);
    PyModule_AddObject(module, "Gooey", (PyObject*)&GooeyType);

    Py_INCREF(&WindowType);
    PyModule_AddObject(module, "Window", (PyObject*)&WindowType);
    
    return module;
}


#ifdef __cplusplus
}
#endif 
