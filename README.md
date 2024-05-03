### JUST A LITTLE WARNING :)
Due to the lates Qt updates my shaders dont work as good as they should, but dont worry, i will fix it as soon as i can :)

# 3DViewer
## Information
In this project a program to visualise the 3D wireframe models in C++ was implemented. 

Implementation includes:
- The program was developed in C++ language of C++17 standard;
- The program is built with Makefile which contains standard set of targets for GNU-programs: all, install, uninstall, clean, dvi, dist, tests;
- The program can visualise only one model on the screen at a time;
- The program provides the ability to:
    - Load a wireframe model from an obj file (vertices and surfaces list support only);
    - Translate the model by a given distance in relation to the X, Y, Z axes;
    - Rotate the model by a given angle in relation to its X, Y, Z axes;
    - Scale the model by a given value;
    - Customize the type of projection (parallel and central);
    - Set up the type (solid, dashed), color and thickness of the edges, display method (none, circle, square), color and size of the vertices;
    - Choose the background color;
    - Settings are saved between program restarts.
- GUI implementation, based on Qt library;
- The program was implemented using the MVC pattern, and also;
- The program allows saving the captured (rendered) images as bmp and jpeg files;
- The program provide an ability of recording small screencasts - the current custom affine transformation of the loaded object into gif-animation (640x480, 10fps, 5s) by a special button.

## Makefile targets
 - **all**: runs targets install,  tests and gcov_report;
 - **install**: builds the project as an App-bundle;
 - **uninstall**: deletes installed application;
 - **clean**: deletes all files used during running targets tests, dvi, dist, gcov_report;
 - **dvi**: creates documentation files with provided "doxyfile", opens html-page with project documentation (doxygen is required);
 - **dist**: creates tar-archive with ready to use app inside;