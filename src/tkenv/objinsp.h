//==========================================================================
//  OBJINSP.H - part of
//
//                     OMNeT++/OMNEST
//            Discrete System Simulation in C++
//
//==========================================================================

/*--------------------------------------------------------------*
  Copyright (C) 1992-2008 Andras Varga
  Copyright (C) 2006-2008 OpenSim Ltd.

  This file is distributed WITHOUT ANY WARRANTY. See the file
  `license' for details on this and other legal matters.
*--------------------------------------------------------------*/

#ifndef __OBJINSP_H
#define __OBJINSP_H

#include <tk.h>
#include "inspector.h"
#include "envirbase.h"

NAMESPACE_BEGIN

class TGenericObjectInspector : public TInspector
{
   protected:
      bool hascontentspage;
      bool focuscontentspage;
   public:
      TGenericObjectInspector();
      ~TGenericObjectInspector();
      virtual void setObject(cObject *obj);
      void setContentsPage(bool show, bool focus) {hascontentspage = show; focuscontentspage = focus;}
      virtual void createWindow(const char *window, const char *geometry);
      virtual void update();
      virtual void writeBack();
      virtual int inspectorCommand(Tcl_Interp *interp, int argc, const char **argv);
};


class TWatchInspector: public TInspector
{
   public:
      TWatchInspector();
      virtual void createWindow(const char *window, const char *geometry);
      virtual void update();
      virtual void writeBack();
};

NAMESPACE_END

#endif



