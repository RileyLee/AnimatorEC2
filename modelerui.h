// generated by Fast Light User Interface Designer (fluid) version 1.0107

#ifndef MODELERUI_H
#define MODELERUI_H

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <map>
#include <string>

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/fl_message.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Progress.H>
#include <FL/Fl_Roller.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Tile.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Tabs.H>
#include "FL/Fl_Tree.H" // The FLTK Tree comes from FLTK 1.1.3

#include "modelerview.h"
#include "dialog.h"
#include "imageio.h"
#include "camera.h"
#include "modelerdraw.h"
#include "model.h"
#include "vault.h"

#include "graphwidget.h"
#include "particleSystem.h"
#include "indicatorwindow.h"
#include "cameras.h"

// TODO: refactor out this forward declaration
class ModelerView;
class SimpleCameraModel;

class ModelerUserInterface {
public:
	enum ImageFileTypes	{ PNG, JPEG	};
	ModelerUserInterface();
	Fl_Double_Window *m_controlsWindow;
private:
	void cb_m_controlsWindow_i(Fl_Double_Window*, void*);
	static void cb_m_controlsWindow(Fl_Double_Window*, void*);
public:
	Fl_Menu_Bar *m_controlsMenuBar;
	static Fl_Menu_Item menu_m_controlsMenuBar[];
private:
	void cb_loadcurve_i(Fl_Menu_*, void*);
	static void cb_loadcurve(Fl_Menu_*, void*);
	void cb_Save_i(Fl_Menu_*, void*);
	static void cb_Save(Fl_Menu_*, void*);
	void cb_Save1_i(Fl_Menu_*, void*);
	static void cb_Save1(Fl_Menu_*, void*);
	void cb_Open_i(Fl_Menu_*, void*);
	static void cb_Open(Fl_Menu_*, void*);
	void cb_Save2_i(Fl_Menu_*, void*);
	static void cb_Save2(Fl_Menu_*, void*);
	void cb_Exit_i(Fl_Menu_*, void*);
	static void cb_Exit(Fl_Menu_*, void*);
	void cb_Normal_i(Fl_Menu_*, void*);
	static void cb_Normal(Fl_Menu_*, void*);
	void cb_Flat_i(Fl_Menu_*, void*);
	static void cb_Flat(Fl_Menu_*, void*);
	void cb_Wireframe_i(Fl_Menu_*, void*);
	static void cb_Wireframe(Fl_Menu_*, void*);
	void cb_High_i(Fl_Menu_*, void*);
	static void cb_High(Fl_Menu_*, void*);
	void cb_Medium_i(Fl_Menu_*, void*);
	static void cb_Medium(Fl_Menu_*, void*);
	void cb_Low_i(Fl_Menu_*, void*);
	static void cb_Low(Fl_Menu_*, void*);
	void cb_Poor_i(Fl_Menu_*, void*);
	static void cb_Poor(Fl_Menu_*, void*);
	void cb_Reload_i();
	static void cb_Reload(Fl_Menu*, void*);
	void cb_GenShaders_i();
	static void cb_GenShaders(Fl_Menu*, void*);
public:
  static Fl_Menu_Item *m_controlsAnimOnMenu;
private:
  void cb_m_controlsAnimOnMenu_i(Fl_Menu_*, void*);
  static void cb_m_controlsAnimOnMenu(Fl_Menu_*, void*);
  void cb_m_controlsBrowser_i(Fl_Browser*, void*);
  static void cb_m_controlsBrowser(Fl_Browser*, void*);
public:
/////////////////////// WINDOW PANES ///////////////////////////

	/** Divides the view vertically. */
	Fl_Tile* m_splitPane;

		/** Left UI pane */
		Fl_Group* leftPane;

			/** Splits the control pane from the tree view */
			Fl_Tile* m_controlSplitPane;

				/** Tree of Modeler controls. */
				Fl_Tree *m_controlsTree;

				/** Pane containing controls for each control group. */
				Fl_Group* m_controlPane;

				/** Scrolling area that contains a model's controls. */
				Fl_Scroll *m_controlsScroll;

					/** Packs controls inside m_controlsScroll */
					Fl_Pack *m_controlsPack;

		/** The right half of the screen, containing the 3D view. */
		Fl_Group* m_viewPane;
	
			/** The 3D view */
			ModelerView *m_modelerView;

			/** Curve UI pane */
			Fl_Group* curvePane;

				/** Camera controls */
				Fl_Group* cameraPane;

				/** Particle system controls */
				Fl_Group* particlePane;
	void show();
public:
  ~ModelerUserInterface();

///////////////////// TAKING SCREENSHOTS ////////////////////////////
public:
	void saveFrame(const char* filename, int fileType = 0,
									 int quality = 95);

///////////////////// LOADING AND SAVING SCRIPTS /////////////////////
public:
	static void cb_LoadScript(Fl_Menu_* o, void* v);
	static void cb_SaveScript(Fl_Menu_* o, void* v);
	static void cb_SaveMovie(Fl_Menu_* o, void* v);
	void loadScript();
	void saveScript();
	void saveMovie();
	void finishSavingMovie();
	static void cancelRender(Fl_Button* button, ModelerUserInterface* ui);
///////////////////// SETTING MOVIE OPTIONS /////////////////////////
  void setMovieLength();
  void setMovieLength(float len);
  static void cb_setMovieLength(Fl_Menu_* o, void* v);

  void setResolution();
  static void cb_setResolution(Fl_Menu_* o, void* v);

  static void cb_setFPS(Fl_Menu*, void*);
  void setFPS();
  void setFPS(int fps);

///////////////////////// FILE DIALOGS ////////////////////////////
private:
  const char* fileDialog(Fl_Native_File_Chooser::Type dialogType,
	  const char* filter, const char* title=NULL);
  Fl_Native_File_Chooser* m_nativeChooser;

public: // TODO: make private?
  int loadFile(std::string& buffer,
			   const bool save = false,
			   const char* title = "Open File",
			   const char* filter = "All Files\t*.*",
			   const char* extensions = "");

///////////////////// PARTICLE SYSTEM ////////////////////////
private:
	/** Particle system */
	ParticleSystem* ps;

	/** Shows the range of the animation that has been baked. */
	IndicatorWindow* particleBakeIndicator;

	/** True if we're simulating the particle system. */
	bool simulating;
public:
	/** Mark a range in the particle system indicator. */
    void indicatorRangeMarkerRange(float fMin, float fMax);

	/** Returns the particle system for the current model. */
	ParticleSystem* getParticleSystem();

///////////////////////// SINGLETON INFO //////////////////////////
private:
	/** The single instance of this class. */
	static ModelerUserInterface* instance;
public:
	/** Returns the current instance of ModelerUserInterface. */
	static ModelerUserInterface* getInstance();

/////////////////////////// MODEL DATA //////////////////////////////
private:
	Model* model;

public:
	/** Set the model (and show controls for it) */
	void setModel(Model* model);

/////////////////////////// ANIMATION //////////////////////////
private:
	/** True if we're animating. */
	bool animating;

	/** Number of frames of animation shown in each second. */
	int framesPerSecond;

	/** True while the current frame is drawing. */
	bool drawing;

public:
	/** Gets called every few moments, and handles animation. */
	static void handleTimeout(void* ui);

	/** Gets called every few moments, and handles animation. */
	void handleTimeoutInner();

//////////////////////// MODELER CONTROLS ////////////////////////////
private:
	/** Current group being shown in the Modeler view. */
	GroupProperty* currentGroup;

	/** List of groups that can be displayed. */
	std::vector<GroupProperty*> groups;

public:
	/** Called when the Show Light/Camera Markers menu item is clicked. */
	static void showMarkersCallback(Fl_Menu_* m, void* p);


	/** Adds the entries from the given group property. */
	void populateList(GroupProperty* group, Fl_Tree_Item* parent = NULL);

	/**
	 * Shows controls for the given group property.
	 * TODO: show multiple control groups!
	 */
	void pickGroupProperty(GroupProperty* group);

	/** Called when you change a slider. */
	static void SliderCallback(Fl_Slider*, void*);

	/** Called when you change a checkbox. */
	static void ButtonCallback(Fl_Button*, void*);

	/** Called when a color picker is clicked. */
	static void ColorPickerCallback(Fl_Color_Chooser*, void*);

	/** Called when you change a choice. */
	static void ChoiceCallback(Fl_Button* button, void* p);

	/** Called when a slider should be updated. */
	static void updateRangeSlider(RangeProperty* prop, Fl_Slider* slider, void* v);

	/** Called when a checkbox should be updated. */
	static void updateCheckbox(BooleanProperty* prop, Fl_Button* checkbox, void* v);

	/** Called when a color picker should be updated. */
	static void updateColorChooser(RGBProperty* prop, Fl_Color_Chooser* chooser, void* v);

	/** Called when a choice should be updated. */
	static void updateChoice(ChoiceProperty* prop, Fl_Group* parent, void* v);

	/** Refreshes the view */
	static void cb_Refresh(Fl_Widget*, void*);

	/** Called when the user clicks an item in the Modeler tree */
	static void TreeCallback(Fl_Tree* tree, void* p);

///////////////////////// ANIMATOR CURVES ////////////////////////////
private:
	/** List of curve properties */
	PropertyList curveProps;

public:
	/** Tree that displays the animation curves. */
	Fl_Tree* curvesTree;


/////////////////////// SAVING MOVIE FRAMES ////////////////////////////
private:
	/** JPEG render quality */
	int renderJPEGQuality;

	/**
	 * Type of images to be saved when the movie is rendered.
	 * 0 = PNG, 1 = JPEG
	 */
	int renderFileType;
	std::string renderFileName, renderFileExt;

	/** True if a movie is being rendered. */
	bool rendering;

	/** Rendering UI stuff */
	Fl_Group* renderGroup;
	Fl_Progress* renderProgress;
	int renderFrame;
	int oldWidth, oldHeight;

public:
	/* Movie rendering dimensions */
	int movieWidth, movieHeight;


//////////////////////// ANIMATOR CAMERA ////////////////////////
private:
	// Default camera to use if none is present in the model.
	SimpleCameraModel* defaultCam;
	
public:
	/** Turns control over to FLTK */
	int run();

public:
	/** The graph widget */
	GraphWidget* graph;

	/** Curve type chooser */
	Fl_Choice* chooserCurveType;

	/** Wrapping checkbox */
	Fl_Check_Button* checkboxWrap;

	/** Time slider */
	Fl_Value_Slider* sliderTime;

	/** Checkbox for looking through the camera. */
	Fl_Check_Button* checkboxUseCamera;

	/** Choose a curve by number */
	void pickCurve(int curve, bool selected = true);

	/** Play the animation. */
	void play();

	/** Pause the animation. */
	void stop();

	/** Play if we're paused, or pause if we're playing */
	void playOrStop();

	/** Rewind to the start. */
	void rewind();

	/** Fast-forward to the end. */
	void fastForward();

	/** Set the current time being shown. */
	void setTime(float t);

	/** Get the current time. */
	float getTime();

	/** Snap the model to the curves' values. */
	void snapModel();

	/** Zoom the graph out as far as possible. */
	void zoomAll();

	/** Checkbox for simulating particles. */
	Fl_Check_Button* checkboxSimulate;

	/** Button for clearing baked particles. */
	Fl_Button* buttonClearParticles;

	/** Button for zooming out as far as possible. */
	Fl_Button* buttonZoomAll;

	/** Returns the number of frames per second. */
	int getFPS();

/************************* CALLBACKS **************************/

	static void CurveTreeCallback(Fl_Tree* tree, void* p);

	static void TabsCallback(Fl_Tabs* tab, void* p);

	static void chooserCurveTypeCallback(Fl_Choice* chooser, void* p);

	static void checkboxWrapCallback(Fl_Check_Button* button, void* p);

	static void buttonPlayCallback(Fl_Button* button, void* p);

	static void buttonRewindCallback(Fl_Button* button, void* p);

	static void buttonFastForwardCallback(Fl_Button* button, void* p);

	static void graphCallback(GraphWidget* graph, void* p);

	static void sliderTimeCallback(Fl_Value_Slider* slider, void* p);

	static void buttonZoomAllCallback(Fl_Button* button, void* p);

	static void checkboxSimulateCallback(Fl_Check_Button* button, void* p);

	void setSimulate(bool sim);

	void cb_clearSim(Fl_Button* o, void* v);

	void clearSim();

	static void checkboxUseCameraCallback(Fl_Check_Button* checkbox, void* p);

	static void buttonPlotCameraCallback(Fl_Button* button, void* p);

	static void buttonClearCameraCallback(Fl_Button* button, void* p);

	void useCamera(bool use);

	void plotCamera();

	void clearCamera();

	void syncSimulate();

	static void buttonClearParticlesCallback(Fl_Button* button, void* p);

	void clearParticles();

private:
	// The play button.
	Fl_Button* buttonPlay;

	void populateCurveList(Property* prop, Fl_Tree_Item* parent = NULL);

	// Curve types
	static Fl_Menu_Item curveTypeMenu[];
};

#endif // MODELERUI_H
