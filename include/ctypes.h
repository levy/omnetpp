//==========================================================================
//   CTYPES.H  - header for
//                             OMNeT++
//            Discrete System Simulation in C++
//
//  Declaration of the following functions:
//    createOne( char *classname )
//
//  Declaration of the following classes:
//    cModuleInterface: defines a module interface (gates+parameters)
//    cModuleType     : module class + interface pairs
//    cLinkType       : channel type (propagation delay, error rate, data rate)
//    cNetworkType    : network
//    cClassRegister  : creates an object of a specific type
//    cInspectorFactory : inspector creation
//
//==========================================================================

/*--------------------------------------------------------------*
  Copyright (C) 1992-2001 Andras Varga
  Technical University of Budapest, Dept. of Telecommunications,
  Stoczek u.2, H-1111 Budapest, Hungary.

  This file is distributed WITHOUT ANY WARRANTY. See the file
  `license' for details on this and other legal matters.
*--------------------------------------------------------------*/

#ifndef __CTYPES_H
#define __CTYPES_H

#include "defs.h"

#include <stdarg.h>
#include "chead.h"
#include "cobject.h"

//=========================================================================
//=== classes declared here
class  cModuleInterface;
class  cModuleType;
class  cLinkType;
class  cNetworkType;
class  cFunctionType;
class  cInspectorFactory;

//=== class mentioned
class  cModule;
class  cPar;

//=== function types used by cModuleType & cLinkType

/**
 * Prototype for functions that are called by cModuleType objects
 * to create modules of a specific type.
 * @ingroup EnumsTypes
 */
typedef cModule *(*ModuleCreateFunc)(const char *, cModule *);

/**
 * Prototype for functions that are called by cLinkType objects
 * to create parameter objects for a link of a specific type.
 * @ingroup EnumsTypes
 */
typedef cPar *(*ParCreateFunc)();

//==========================================================================

//
// Used internally by cModuleInterface
//
// FIXME: why not inner class?
struct sDescrItem {
    char what;
    char *name;
    char *types;
    char type;
};

/**
 * Represents a module interface: gates and parameter names.
 *
 * cModuleInterfaces are the compiled form of NED declarations of simple
 * modules. They are created in the following way:
 *
 *  1) starting point is the NED declarations of simple modules, e.g:
 *     <PRE><TT>
 *        simple Generator
 *          parameters: ia_rate;
 *          gates: out: out;
 *        endsimple
 *     </PRE></TT>
 *
 *  2) the nedc compiler translates the NED declaration into a
 *     ModuleInterface...End macro and places it into the _n.cc file.
 *     <PRE><TT>
 *        ModuleInterface( Generator )
 *          Parameter ( "ia_rate", AnyType )
 *          Gate      ( "out",     Output  )
 *        End
 *     </PRE></TT>
 *
 *     The macro translates into a static cModuleInterface object declaration
 *     (#define for macros in macros.h)
 *
 *  3) When the program starts up, cModuleInterface constructor runs and
 *     places the object on the modinterfaces list.
 *
 *  4) When a module is created, the appropriate cModuleInterface object
 *     is looked up from the list, and the module's gates and parameters
 *     are created according to the description in the cModuleInterface
 *     object.
 *
 * @ingroup Internals
 */
class SIM_API cModuleInterface : public cObject
{
    // structures used in a cModuleInterface
    struct sGateInfo {
       char *name;
       char type;
       bool vect;
    };

    struct sParamInfo {
       char *name;
       char *types;
    };

    struct sMachineInfo {
       char *name;
    };

  protected:
    int ngate;
    sGateInfo *gatev;
    int nparam;
    sParamInfo *paramv;
    int nmachine;            // NET
    sMachineInfo *machinev;  // NET

  private:
    // internal
    void allocate(int ngte, int npram, int nmach);

    // internal
    void check_consistency();

    // internal
    void setup(sDescrItem *descr_table);

  public:
    /** @name Constructors, destructor, assignment */
    //@{

    /**
     * Constructor.
     */
    cModuleInterface(const char *name, sDescrItem *descr_table);

    /**
     * Copy constructor.
     */
    cModuleInterface(const cModuleInterface& mi);

    /**
     * Destructor.
     */
    virtual ~cModuleInterface();

    /**
     * Assignment operator. The name member doesn't get copied; see cObject's operator=() for more details.
     */
    cModuleInterface& operator=(const cModuleInterface& mi);
    //@}

    /** @name Redefined cObject member functions. */
    //@{

    /**
     * Returns pointer to a string containing the class name, "cModuleInterface".
     */
    virtual const char *className() const {return "cModuleInterface";}

    /**
     * Creates and returns an exact copy of this object.
     * See cObject for more details.
     */
    virtual cObject *dup() const  {return new cModuleInterface(*this);}
    //@}

    /** @name Applying the interface to modules. */
    //@{

    /**
     * Adds parameters and gates specified by the interface to the given module.
     */
    void addParametersGatesTo(cModule *module);

    /**
     * Checks that the types of the module's parameters comply to the interface,
     * and calls convertToConst() on the parameters declared as const in the
     * interface.
     */
    void checkParametersOf(cModule *module);
    //@}
};

//==========================================================================

/**
 * Class for creating a module of a specific type.
 *
 * A cModuleType object exist for each module type (simple or compound).
 * A cModuleType object 'knows' how to create a module of a given type,
 * thus a module can be created without having to include the .h file
 * with the C++ declaration of the module class ("class FddiMAC...").
 * A cModuleType object is created through a Define_Module macro. Thus,
 * each module type must have a Define_Module() line, e.g:
 *
 * Define_Module( MySimpleModule );
 *
 * nedc automatically generates Define_Module for compound modules, but the
 * user is responsible for writing it for each simple module type.
 *
 * @ingroup Internals
 */
class SIM_API cModuleType : public cObject
{
    friend class cModule;
  private:
    char *interface_name;
    cModuleInterface *iface;
    ModuleCreateFunc create_func;

  public:
    /** @name Constructors, destructor, assignment */
    //@{

    /**
     * Constructor.
     */
    cModuleType(const char *classname, const char *interf_name, ModuleCreateFunc cf);

    /**
     * Copy constructor.
     */
    cModuleType(const cModuleType& mi);

    /**
     * Destructor.
     */
    virtual ~cModuleType();

    /**
     * Assignment operator. The name member doesn't get copied; see cObject's operator=() for more details.
     */
    cModuleType& operator=(const cModuleType& mi);
    //@}

    /** @name Redefined cObject member functions. */
    //@{

    /**
     * Returns pointer to a string containing the class name, "cModuleType".
     */
    virtual const char *className() const {return "cModuleType";}

    /**
     * Creates and returns an exact copy of this object.
     * See cObject for more details.
     */
    virtual cObject *dup() const     {return new cModuleType(*this);}
    //@}

    /** @name FIXME */
    //@{

    /**
     * Creates a module. In addition to creating an object of the correct type,
     * this function inserts it into cSimulation's module vector and adds the
     * parameters and gates specified in the interface description.
     */
    cModule *create(const char *name, cModule *parentmod, bool local=true);

    /**
     * Builds adds submodules and internal connections to the empty compound
     * module passed.
     */
    void buildInside(cModule *mod);

    /**
     * This is a convenience function to get a module up and running in one step.
     *
     * First, the module is created using create() and buildInside(), then
     * starter messages are created (using mod->scheduleStart(simulation.simTime())),
     * then initialize() is called (mod->callInitialize()). It is important that
     * scheduleStart() be called before initialize(), because initialize()
     * functions might contain scheduleAt() calls which could otherwise insert
     * a message BEFORE the starter messages for module.
     *
     * This method works for simple and compound modules alike. Not applicable
     * if the module:
     *  - has parameters to be set
     *  - gate vector sizes to be set
     *  - gates to be connected before initialize()
     */
    cModule *createScheduleInit(char *name, cModule *parentmod);
    //@}
};


//==========================================================================

/**
 * Represents a connection type: name, delay, bit error rate, data rate.
 * An instance knows how to create delay, bit error rate and data rate
 * objects (cPars) for a given channel.
 *
 * Objects of this class are usually created via the Define_Channel() macro.
 *
 * @ingroup Internals
 */
class SIM_API cLinkType : public cObject
{
  private:
    cPar *(*delayfunc)();     // delay
    cPar *(*errorfunc)();     // bit error rate
    cPar *(*dataratefunc)();  // data rate

  public:
    /** @name Constructors, destructor, assignment */
    //@{

    /**
     * Constructor. It takes three function pointers; the corresponding
     * functions should be 'factory' functions that create the delay,
     * bit error rate and data rate objects (cPars) for this channel type.
     */
    cLinkType(const char *name, cPar *(*d)(), cPar *(*e)(), cPar *(*dr)() );

    /**
     * Copy constructor.
     */
    cLinkType(const cLinkType& li);

    /**
     * Destructor.
     */
    virtual ~cLinkType()    {}

    /**
     * Assignment operator. The name member doesn't get copied; see cObject's operator=() for more details.
     */
    cLinkType& operator=(const cLinkType& o);
    //@}

    /** @name Redefined cObject member functions. */
    //@{

    /**
     * Returns pointer to a string containing the class name, "cLinkType".
     */
    virtual const char *className() const {return "cLinkType";}

    /**
     * Creates and returns an exact copy of this object.
     * See cObject for more details.
     */
    virtual cObject *dup() const     {return new cLinkType(*this);}
    //@}

    /** @name Channel properties. */
    //@{

    /**
     * Creates a cPar object, representing the delay of this channel.
     * Returns NULL if the channel has no associated delay.
     */
    cPar *createDelay() const;

    /**
     * Creates a cPar object, representing the bit error rate of this channel.
     * Returns NULL if the channel has no associated bit error rate.
     */
    cPar *createError() const;

    /**
     * Creates a cPar object, representing the data rate of this channel.
     * Returns NULL if the channel has no associated data rate.
     */
    cPar *createDataRate() const;
    //@}
};

//==========================================================================

/**
 * Registration class. An instance knows how to build a network of specific type.
 *
 * Objects of this class are usually created via the Define_Network() macro.
 *
 * @ingroup Internals
 */
class SIM_API cNetworkType : public cObject
{
  public:  //FIXME: ????
    void (*setupfunc)();

  public:
    /** @name Constructors, destructor, assignment */
    //@{

    /**
     * Copy constructor.
     */
    cNetworkType(const cNetworkType& n)  {setName(n.name());operator=(n);}

    /**
     * Constructor. It takes pointer to a function that can build up a network.
     */
    cNetworkType(const char *name, void (*f)());

    /**
     * Destructor.
     */
    virtual ~cNetworkType() {}

    /**
     * Assignment is not supported for this class. This function raises an error when called.
     */
    cNetworkType& operator=(const cNetworkType&)  {copyNotSupported();return *this;}
    //@}

    /** @name Redefined cObject member functions. */
    //@{

    /**
     * Returns pointer to a string containing the class name, "cNetworkType".
     */
    virtual const char *className() const {return "cNetworkType";}

    /**
     * Creates and returns an exact copy of this object.
     * See cObject for more details.
     */
    virtual cObject *dup() const     {return new cNetworkType(*this);}
    //@}
};

//==========================================================================

/**
 * Registration class. Stores a function pointer (returning a double).
 *
 * Objects of this class are usually created via the Define_Function() macro.
 *
 * @ingroup Internals
 */
class SIM_API cFunctionType : public cObject
{
  public:
    MathFunc f;   //FIXME: add getter funcs!!!
    int argcount;
  public:
    /** @name Constructors, destructor, assignment */
    //@{

    /**
     * Copy constructor.
     */
    cFunctionType(const cFunctionType& ft)  {setName(ft.name());operator=(ft);}

    /**
     * Constructor.
     */
    cFunctionType(const char *name, MathFunc f0, int argc);

    /**
     * Destructor.
     */
    virtual ~cFunctionType() {}

    /**
     * Assignment is not supported for this class. This function raises an error when called.
     */
    cFunctionType& operator=(const cFunctionType&)  {copyNotSupported();return *this;}
    //@}

    /** @name Redefined cObject member functions. */
    //@{

    /**
     * Returns pointer to a string containing the class name, "cFunctionType".
     */
    virtual const char *className() const {return "cFunctionType";}

    /**
     * Creates and returns an exact copy of this object.
     * See cObject for more details.
     */
    virtual cObject *dup() const  {return new cFunctionType(*this);}
    //@}
};

cFunctionType *findfunctionbyptr(MathFunc f);

//==========================================================================

/**
 * The class behind the createOne() function and the Register_Class() macro.
 * Each instance is a factory for a particular class: it knows how to create
 * an object of that class.
 *
 * @see ::createOne() function
 * @see Register_Class() macro
 * @ingroup Internals
 */
class SIM_API cClassRegister : public cObject
{
    void *(*creatorfunc)();

  public:
    /** @name Constructors, destructor, assignment. */
    //@{

    /**
     * Copy constructor.
     */
    cClassRegister(const cClassRegister& c)  {setName(c.name());operator=(c);}

    /**
     * Constructor.
     */
    cClassRegister(const char *name, void *(*f)());

    /**
     * Destructor.
     */
    virtual ~cClassRegister() {}

    /**
     * Assignment is not supported for this class. This function raises an error when called.
     */
    cClassRegister& operator=(const cClassRegister&)  {copyNotSupported();return *this;}
    //@}

    /** @name Redefined cObject member functions. */
    //@{

    /**
     * Returns pointer to a string containing the class name, "cClassRegister".
     */
    virtual const char *className() const {return "cClassRegister";}

    /**
     * Creates and returns an exact copy of this object.
     * See cObject for more details.
     */
    virtual cObject *dup() const  {return new cClassRegister(*this);}
    //@}

    /** @name Factory function. */
    //@{

    /**
     * Creates an instance of a particular class by calling the creator
     * function. The result has to be cast to the appropriate type by hand.
     */
    void *createOne() const  {return creatorfunc();}
    //@}
};

/**
 * @name Miscellaneous functions.
 * @ingroup Functions
 */
//@{

/**
 * Creates an instance of a particular class; the result has to be cast
 * to the appropriate type by hand. The class must have been registered
 * previously with the Register_Class() macro. This function internally
 * relies on the cClassRegister class.
 * 
 * Example: 
 *
 * <code>cObject *param = createOne( "cPar" );</code>
 *
 * createOne() is used e.g. in parallel simulation when an object is received
 * from another segment and it has to be demashalled.
 *
 * @see Register_Class() macro
 * @see cClassRegister class
 */
// FIXME into some class, as static member!!!
SIM_API void *createOne(const char *classname);
//@}

//==========================================================================

/**
 * Internal class. Serves as a base class for inspector factories of
 * specific classes. Inspector factories are implemented as part of
 * user interface libraries, and really belong there.
 *
 * @ingroup Internals
 */
class SIM_API cInspectorFactory : public cObject
{
    TInspector *(*inspFactoryFunc)(cObject *,int,void *);

  public:
    /** @name Constructors, destructor, assignment. */
    //@{

    /**
     * Copy constructor.
     */
    cInspectorFactory(const cInspectorFactory& ifc)  {setName(ifc.name());operator=(ifc);}

    /**
     * Constructor.
     */
    cInspectorFactory(const char *name, TInspector *(*f)(cObject *,int,void *));

    /**
     * Destructor.
     */
    virtual ~cInspectorFactory() {}

    /**
     * Assignment is not supported for this class. This function raises an error when called.
     */
    cInspectorFactory& operator=(const cInspectorFactory&)  {copyNotSupported();return *this;}
    //@}

    /** @name Redefined cObject member functions. */
    //@{

    /**
     * Returns pointer to a string containing the class name, "cInspectorFactory".
     */
    virtual const char *className() const {return "cInspectorFactory";}

    /**
     * Creates and returns an exact copy of this object.
     * See cObject for more details.
     */
    virtual cObject *dup() const  {return new cInspectorFactory(*this);}
    //@}

    /** @name Inspector creation. */
    //@{

    /**
     * Creates an inspector for the object passed. The type and data
     * arguments influence the type of inspector created. These parameters
     * as well as the created inspector object only make sense in the
     * context of the user interface library (e.g.Tkenv)
     */
    TInspector *createInspectorFor(cObject *object,int type,void *data);
    //@}
};


#endif


