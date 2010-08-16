from distutils.core import setup, Extension

pdpd_module = Extension(
    'pdpd',
    include_dirs = [
        '/usr/include',
        '/usr/local/include/SDL', 
        '/usr/local/include/bullet', 
        '/usr/include/cairo', '/usr/include/pixman-1', 
        '/usr/include/freetype2', '/usr/include/libpng12',
        ],
    libraries = [
        'SDL', 'pthread',  # for sdl
        'cairo', # for cairo
        'BulletDynamics', 'BulletCollision', # for bullet
        'LinearMath', 'BulletSoftBody',      # for bullet too
        'GLU' # for opengl util lib
        ],
    library_dirs = ['/usr/lib', '/usr/local/lib'],
    sources = [
        'pdpd_pymodule.cpp',
        'Gooey.cpp',
        'World.cpp',
        'WorldWindow.cpp',
        'renderer/TargetCamera.cpp',
        'renderer/ThingDrawer.cpp',
        'renderer/WorldRenderer.cpp',
        'things/Box.cpp',
        'things/Thing.cpp',
        'geometry3/Facet.cpp',
        'geometry3/Vector3.cpp'
        ])

setup (name = 'pdpd_package',
       version = '0.1',
       description = 'predee predee physics simulation library',
       ext_modules = [pdpd_module])
