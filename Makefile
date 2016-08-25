#  WARNING: As of Fall 2010, this makefile doesn't work...
#  Makefile for fltk applications
#
# set LOCAL to the path to fltk
LOCAL = /usr
INCLUDE = -I$(LOCAL)/include -I/usr/X11R6/include -I./glew/include -I./
LIBDIR = -L$(LOCAL)/lib -L/usr/X11R6/lib

LIBS = -lfltk -lfltk_gl -lXext -lX11 -lm -lGL -lGLU -lfltk_images -lpthread -lpng -ljpeg -lGLEW

CFLAGS = -g -FLTK1 -fpermissive

CC = g++

.SUFFIXES: .o .cpp .cxx

.cpp.o: 
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $*.o $<

.cxx.o: 
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $*.o $<

ALL.O = graphwidget.o model.o curveevaluator.o particleSystem.o vault.o trackball.o shaders.o rijndael.o rect.o properties.o linearcurveevaluator.o indicatorwindow.o curve.o imageio.o camera.o modelerdraw.o modelerui.o modelerview.o sample.o point.o vect.o cameras.o r2d2.o beziercurveevaluator.o  bsplinecurveevaluator.o  CRcurveevaluator.o

modeler: $(ALL.O)
	$(CC) $(CFLAGS) -o $@ $(ALL.O) $(INCLUDE) $(LIBDIR) $(LIBS)

clean:
	rm -f $(ALL.O) modeler
