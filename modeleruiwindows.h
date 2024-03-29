// generated by Fast Light User Interface Designer (fluid) version 1.00

#ifndef modeleruiwindows_h
#define modeleruiwindows_h
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Pack.H>
#include "FL/Fl_Box.h"
#include "FL/Fl_Value_Slider.h"
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include "rulerwindow.h"
#include "graphwidget.h"
#include <FL/Fl_Choice.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Value_Slider.H>
#include "indicatorwindow.h"
#include <FL/Fl_Slider.H>
#include <FL/Fl_Output.H>
#include "modelerview.h"

class ModelerUIWindows {
public:
  ModelerUIWindows();
  Fl_Window *m_pwndMainWnd;
  Fl_Menu_Bar *m_pmbMenuBar;
  static Fl_Menu_Item menu_m_pmbMenuBar[];
  static Fl_Menu_Item *m_pmiOpenAniScript;
  static Fl_Menu_Item *m_pmiSaveAniScript;
  static Fl_Menu_Item *m_pmiSaveBitmapFile;
  static Fl_Menu_Item *m_pmiSaveMovie;
  static Fl_Menu_Item *m_pmiExit;
  static Fl_Menu_Item *m_pmiNormal;
  static Fl_Menu_Item *m_pmiFlatShaded;
  static Fl_Menu_Item *m_pmiWireFrame;
  static Fl_Menu_Item *m_pmiHightQuality;
  static Fl_Menu_Item *m_pmiMediumQuality;
  static Fl_Menu_Item *m_pmiLowQuality;
  static Fl_Menu_Item *m_pmiPoorQuality;
  static Fl_Menu_Item *m_pmiSetAniLen;
  Fl_Browser *m_pbrsBrowser;
  Fl_Tabs *m_ptabTab;
  Fl_Scroll *m_pscrlScroll;
  Fl_Pack *m_ppckPack;
  Fl_Group *m_pgrpCurveGroup;
  RulerWindow *m_pwndHRuler;
  RulerWindow *m_pwndVRuler;
  GraphWidget *m_pwndGraphWidget;
  Fl_Choice *m_pchoCurveType;
  static Fl_Menu_Item menu_m_pchoCurveType[];
  Fl_Light_Button *m_pbtWrap;
  Fl_Light_Button* m_pbtAdaptive;
  Fl_Button *m_pbtZoomAll;
  Fl_Button *m_pbtStepBack;
  Fl_Button *m_pbtPlay;
  Fl_Button *m_pbtStepForw;
  Fl_Light_Button *m_pbtLoop;
  Fl_Light_Button *m_pbtSimulate;
  Fl_Value_Slider *m_psldrFPS;
  IndicatorWindow *m_pwndIndicatorWnd;
  Fl_Slider *m_psldrTimeSlider;
  Fl_Slider *m_psldrPlayStart;
  Fl_Slider *m_psldrPlayEnd;
  Fl_Value_Slider* m_pbtflatness;
  Fl_Value_Slider* m_pbttension;
  Fl_Output *m_poutTime;
  Fl_Output *m_poutPlayStart;
  Fl_Output *m_poutPlayEnd;
  Fl_Button *m_pbtClearSim;
  Fl_Button *m_pbtSetCamKeyFrame;
  Fl_Button *m_pbtRemoveCamKeyFrame;
  Fl_Button *m_pbtRemoveAllCamKeyFrames;
  Fl_Window *m_pwndModelerWnd;
  ModelerView *m_pwndModelerView;
};
#endif
