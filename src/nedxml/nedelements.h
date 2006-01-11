//==========================================================================
// Part of the OMNeT++/OMNEST Discrete Event Simulation System
//
// Generated from ned.dtd by dtdclassgen.pl
//
//==========================================================================

/*--------------------------------------------------------------*
  Copyright (C) 2002-2004 Andras Varga

  This file is distributed WITHOUT ANY WARRANTY. See the file
  `license' for details on this and other legal matters.
*--------------------------------------------------------------*/

//
// THIS IS A GENERATED FILE, DO NOT EDIT!
//


#ifndef __NEDELEMENTS_H
#define __NEDELEMENTS_H

#include "nedelement.h"

class FilesNode;
class NedFileNode;
class ImportNode;
class PropertydefNode;
class SimpleNode;
class InterfaceNode;
class ModuleNode;
class ParametersNode;
class ParametersBlockNode;
class ParamNode;
class PropertyNode;
class KeyValueNode;
class GatesNode;
class GateBlockNode;
class GateNode;
class SubmodulesNode;
class SubmoduleNode;
class ConnectionsNode;
class ConnectionNode;
class ChannelInterfaceNode;
class ChannelNode;
class ConnectionBlockNode;
class LoopNode;
class ConditionNode;
class ExpressionNode;
class OperatorNode;
class FunctionNode;
class ParamRefNode;
class IdentNode;
class ConstNode;
class MsgFileNode;
class CplusplusNode;
class StructDeclNode;
class ClassDeclNode;
class MessageDeclNode;
class EnumDeclNode;
class EnumNode;
class EnumFieldsNode;
class EnumFieldNode;
class MessageNode;
class ClassNode;
class StructNode;
class FieldsNode;
class FieldNode;
class PropertiesNode;
class PropertyNode;
class UnknownNode;


/**
 * Tag codes
 * 
 * @ingroup Data
 */
enum NEDElementCode {
    NED_FILES,
    NED_NED_FILE,
    NED_IMPORT,
    NED_PROPERTYDEF,
    NED_SIMPLE,
    NED_INTERFACE,
    NED_MODULE,
    NED_PARAMETERS,
    NED_PARAMETERS_BLOCK,
    NED_PARAM,
    NED_PROPERTY,
    NED_KEY_VALUE,
    NED_GATES,
    NED_GATE_BLOCK,
    NED_GATE,
    NED_SUBMODULES,
    NED_SUBMODULE,
    NED_CONNECTIONS,
    NED_CONNECTION,
    NED_CHANNEL_INTERFACE,
    NED_CHANNEL,
    NED_CONNECTION_BLOCK,
    NED_LOOP,
    NED_CONDITION,
    NED_EXPRESSION,
    NED_OPERATOR,
    NED_FUNCTION,
    NED_PARAM_REF,
    NED_IDENT,
    NED_CONST,
    NED_MSG_FILE,
    NED_CPLUSPLUS,
    NED_STRUCT_DECL,
    NED_CLASS_DECL,
    NED_MESSAGE_DECL,
    NED_ENUM_DECL,
    NED_ENUM,
    NED_ENUM_FIELDS,
    NED_ENUM_FIELD,
    NED_MESSAGE,
    NED_CLASS,
    NED_STRUCT,
    NED_FIELDS,
    NED_FIELD,
    NED_PROPERTIES,
    NED_PROPERTY,
    NED_UNKNOWN
};

enum {NED_GATEDIR_INPUT, NED_GATEDIR_OUTPUT};
enum {NED_ARROWDIR_LEFT, NED_ARROWDIR_RIGHT};
enum {NED_CONST_BOOL, NED_CONST_INT, NED_CONST_REAL, NED_CONST_STRING, NED_CONST_TIME};

/**
 * GENERATED CLASS. Represents the &lt;files&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT files ((ned-file|msg-file)*)>
 * 
 * </pre>
 * 
 * @ingroup Data
 */
class FilesNode : public NEDElement
{
  private:
  public:
    /** @name Constructors, destructor */
    //@{
    FilesNode() {applyDefaults();}
    FilesNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~FilesNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "files";}
    virtual int getTagCode() const {return NED_FILES;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{

    virtual FilesNode *getNextFilesNodeSibling() const;
    virtual NedFileNode *getFirstNedFileChild() const;
    virtual MsgFileNode *getFirstMsgFileChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;ned-file&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT ned-file ((import|propertydef|property|channel|
 *                      channel-interface|simple|module|interface)*)>
 * <!ATTLIST ned-file
 *      filename           CDATA     #REQUIRED
 *      package            CDATA     #IMPLIED
 * >
 * </pre>
 * 
 * @ingroup Data
 */
class NedFileNode : public NEDElement
{
  private:
    std::string filename;
    std::string package;
  public:
    /** @name Constructors, destructor */
    //@{
    NedFileNode() {applyDefaults();}
    NedFileNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~NedFileNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "ned-file";}
    virtual int getTagCode() const {return NED_NED_FILE;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getFilename() const  {return filename.c_str();}
    void setFilename(const char * val)  {filename = val;}
    const char * getPackage() const  {return package.c_str();}
    void setPackage(const char * val)  {package = val;}

    virtual NedFileNode *getNextNedFileNodeSibling() const;
    virtual ImportNode *getFirstImportChild() const;
    virtual PropertydefNode *getFirstPropertydefChild() const;
    virtual PropertyNode *getFirstPropertyChild() const;
    virtual ChannelNode *getFirstChannelChild() const;
    virtual ChannelInterfaceNode *getFirstChannelInterfaceChild() const;
    virtual SimpleNode *getFirstSimpleChild() const;
    virtual ModuleNode *getFirstModuleChild() const;
    virtual InterfaceNode *getFirstInterfaceChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;import&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT import EMPTY>
 * <!ATTLIST import
 *      filename           CDATA     #REQUIRED
 * >
 * </pre>
 * 
 * @ingroup Data
 */
class ImportNode : public NEDElement
{
  private:
    std::string filename;
  public:
    /** @name Constructors, destructor */
    //@{
    ImportNode() {applyDefaults();}
    ImportNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~ImportNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "import";}
    virtual int getTagCode() const {return NED_IMPORT;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getFilename() const  {return filename.c_str();}
    void setFilename(const char * val)  {filename = val;}

    virtual ImportNode *getNextImportNodeSibling() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;propertydef&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT propertydef (key-value*)>
 * <!ATTLIST propertydef
 *      name               NMTOKEN   #REQUIRED
 * >
 * </pre>
 * 
 * @ingroup Data
 */
class PropertydefNode : public NEDElement
{
  private:
    std::string name;
  public:
    /** @name Constructors, destructor */
    //@{
    PropertydefNode() {applyDefaults();}
    PropertydefNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~PropertydefNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "propertydef";}
    virtual int getTagCode() const {return NED_PROPERTYDEF;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getName() const  {return name.c_str();}
    void setName(const char * val)  {name = val;}

    virtual PropertydefNode *getNextPropertydefNodeSibling() const;
    virtual KeyValueNode *getFirstKeyValueChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;simple&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT simple (extends?, interface-name*, parameters?, gates?)>
 * <!ATTLIST simple
 *      name               NMTOKEN   #REQUIRED
 * >
 * </pre>
 * 
 * @ingroup Data
 */
class SimpleNode : public NEDElement
{
  private:
    std::string name;
  public:
    /** @name Constructors, destructor */
    //@{
    SimpleNode() {applyDefaults();}
    SimpleNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~SimpleNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "simple";}
    virtual int getTagCode() const {return NED_SIMPLE;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getName() const  {return name.c_str();}
    void setName(const char * val)  {name = val;}

    virtual SimpleNode *getNextSimpleNodeSibling() const;
    virtual  *getFirstExtendsChild() const;
    virtual  *getFirstInterfaceNameChild() const;
    virtual ParametersNode *getFirstParametersChild() const;
    virtual GatesNode *getFirstGatesChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;interface&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT interface (extends*, parameters?, gates?)>
 * <!ATTLIST interface
 *      name               NMTOKEN   #REQUIRED
 * >
 * </pre>
 * 
 * @ingroup Data
 */
class InterfaceNode : public NEDElement
{
  private:
    std::string name;
  public:
    /** @name Constructors, destructor */
    //@{
    InterfaceNode() {applyDefaults();}
    InterfaceNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~InterfaceNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "interface";}
    virtual int getTagCode() const {return NED_INTERFACE;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getName() const  {return name.c_str();}
    void setName(const char * val)  {name = val;}

    virtual InterfaceNode *getNextInterfaceNodeSibling() const;
    virtual  *getFirstExtendsChild() const;
    virtual ParametersNode *getFirstParametersChild() const;
    virtual GatesNode *getFirstGatesChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;module&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT module (extends?, interface-name*, parameters?, gates?,
 *                   submodules?, connections?)>
 * <!ATTLIST module
 *      name               NMTOKEN   #REQUIRED
 *  >
 * </pre>
 * 
 * @ingroup Data
 */
class ModuleNode : public NEDElement
{
  private:
    std::string name;
  public:
    /** @name Constructors, destructor */
    //@{
    ModuleNode() {applyDefaults();}
    ModuleNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~ModuleNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "module";}
    virtual int getTagCode() const {return NED_MODULE;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getName() const  {return name.c_str();}
    void setName(const char * val)  {name = val;}

    virtual ModuleNode *getNextModuleNodeSibling() const;
    virtual  *getFirstExtendsChild() const;
    virtual  *getFirstInterfaceNameChild() const;
    virtual ParametersNode *getFirstParametersChild() const;
    virtual GatesNode *getFirstGatesChild() const;
    virtual SubmodulesNode *getFirstSubmodulesChild() const;
    virtual ConnectionsNode *getFirstConnectionsChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;parameters&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT parameters ((property|param|parameters-block)*)>
 * <!ATTLIST parameters
 *     is-implicit         (true|false)    "true"
 * >
 * </pre>
 * 
 * @ingroup Data
 */
class ParametersNode : public NEDElement
{
  private:
    bool isImplicit;
  public:
    /** @name Constructors, destructor */
    //@{
    ParametersNode() {applyDefaults();}
    ParametersNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~ParametersNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "parameters";}
    virtual int getTagCode() const {return NED_PARAMETERS;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    bool getIsImplicit() const  {return isImplicit;}
    void setIsImplicit(bool val)  {isImplicit = val;}

    virtual ParametersNode *getNextParametersNodeSibling() const;
    virtual PropertyNode *getFirstPropertyChild() const;
    virtual ParamNode *getFirstParamChild() const;
    virtual ParametersBlockNode *getFirstParametersBlockChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;parameters-block&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT parameters-block (condition, (property|param)*)>
 * 
 * </pre>
 * 
 * @ingroup Data
 */
class ParametersBlockNode : public NEDElement
{
  private:
  public:
    /** @name Constructors, destructor */
    //@{
    ParametersBlockNode() {applyDefaults();}
    ParametersBlockNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~ParametersBlockNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "parameters-block";}
    virtual int getTagCode() const {return NED_PARAMETERS_BLOCK;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{

    virtual ParametersBlockNode *getNextParametersBlockNodeSibling() const;
    virtual ConditionNode *getFirstConditionChild() const;
    virtual PropertyNode *getFirstPropertyChild() const;
    virtual ParamNode *getFirstParamChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;param&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT param (expression?)>
 * <!ATTLIST param
 *      name               NMTOKEN   #REQUIRED
 *      type               (double|int|string|bool|xml) #REQUIRED
 *      is-function        (true|false)    "false"
 *      value               CDATA     #IMPLIED
 *  >
 * </pre>
 * 
 * @ingroup Data
 */
class ParamNode : public NEDElement
{
  private:
    std::string name;
    int type;
    bool isFunction;
    std::string value;
  public:
    /** @name Constructors, destructor */
    //@{
    ParamNode() {applyDefaults();}
    ParamNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~ParamNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "param";}
    virtual int getTagCode() const {return NED_PARAM;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getName() const  {return name.c_str();}
    void setName(const char * val)  {name = val;}
    int getType() const  {return type;}
    void setType(int val)  {type = val;}
    bool getIsFunction() const  {return isFunction;}
    void setIsFunction(bool val)  {isFunction = val;}
    const char * getValue() const  {return value.c_str();}
    void setValue(const char * val)  {value = val;}

    virtual ParamNode *getNextParamNodeSibling() const;
    virtual ExpressionNode *getFirstExpressionChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;property&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT property EMPTY>
 * <!ATTLIST property
 *      name                NMTOKEN   #REQUIRED
 *      value               CDATA     #IMPLIED
 *      banner-comment      CDATA     #IMPLIED
 *      right-comment       CDATA     "&#10;" >
 * </pre>
 * 
 * @ingroup Data
 */
class PropertyNode : public NEDElement
{
  private:
    std::string name;
    std::string value;
    std::string bannerComment;
    std::string rightComment;
  public:
    /** @name Constructors, destructor */
    //@{
    PropertyNode() {applyDefaults();}
    PropertyNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~PropertyNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "property";}
    virtual int getTagCode() const {return NED_PROPERTY;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getName() const  {return name.c_str();}
    void setName(const char * val)  {name = val;}
    const char * getValue() const  {return value.c_str();}
    void setValue(const char * val)  {value = val;}
    const char * getBannerComment() const  {return bannerComment.c_str();}
    void setBannerComment(const char * val)  {bannerComment = val;}
    const char * getRightComment() const  {return rightComment.c_str();}
    void setRightComment(const char * val)  {rightComment = val;}

    virtual PropertyNode *getNextPropertyNodeSibling() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;key-value&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT key-value EMPTY>
 * <!ATTLIST key-value
 *      key                CDATA   #IMPLIED
 *      value              CDATA   #IMPLIED
 * >
 * </pre>
 * 
 * @ingroup Data
 */
class KeyValueNode : public NEDElement
{
  private:
    std::string key;
    std::string value;
  public:
    /** @name Constructors, destructor */
    //@{
    KeyValueNode() {applyDefaults();}
    KeyValueNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~KeyValueNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "key-value";}
    virtual int getTagCode() const {return NED_KEY_VALUE;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getKey() const  {return key.c_str();}
    void setKey(const char * val)  {key = val;}
    const char * getValue() const  {return value.c_str();}
    void setValue(const char * val)  {value = val;}

    virtual KeyValueNode *getNextKeyValueNodeSibling() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;gates&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT gates ((gate|gate-block)*)>
 * 
 * </pre>
 * 
 * @ingroup Data
 */
class GatesNode : public NEDElement
{
  private:
  public:
    /** @name Constructors, destructor */
    //@{
    GatesNode() {applyDefaults();}
    GatesNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~GatesNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "gates";}
    virtual int getTagCode() const {return NED_GATES;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{

    virtual GatesNode *getNextGatesNodeSibling() const;
    virtual GateNode *getFirstGateChild() const;
    virtual GateBlockNode *getFirstGateBlockChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;gate-block&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT gate-block (condition, gate*)>
 * 
 * </pre>
 * 
 * @ingroup Data
 */
class GateBlockNode : public NEDElement
{
  private:
  public:
    /** @name Constructors, destructor */
    //@{
    GateBlockNode() {applyDefaults();}
    GateBlockNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~GateBlockNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "gate-block";}
    virtual int getTagCode() const {return NED_GATE_BLOCK;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{

    virtual GateBlockNode *getNextGateBlockNodeSibling() const;
    virtual ConditionNode *getFirstConditionChild() const;
    virtual GateNode *getFirstGateChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;gate&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT gate (expression?)>
 * <!ATTLIST gate
 *      name               NMTOKEN   #REQUIRED
 *      type               (input|output|inout) #REQUIRED
 *      vector-size        CDATA     #IMPLIED
 * >
 * </pre>
 * 
 * @ingroup Data
 */
class GateNode : public NEDElement
{
  private:
    std::string name;
    int type;
    std::string vectorSize;
  public:
    /** @name Constructors, destructor */
    //@{
    GateNode() {applyDefaults();}
    GateNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~GateNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "gate";}
    virtual int getTagCode() const {return NED_GATE;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getName() const  {return name.c_str();}
    void setName(const char * val)  {name = val;}
    int getType() const  {return type;}
    void setType(int val)  {type = val;}
    const char * getVectorSize() const  {return vectorSize.c_str();}
    void setVectorSize(const char * val)  {vectorSize = val;}

    virtual GateNode *getNextGateNodeSibling() const;
    virtual ExpressionNode *getFirstExpressionChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;submodules&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT submodules (submodule*)>
 * 
 * </pre>
 * 
 * @ingroup Data
 */
class SubmodulesNode : public NEDElement
{
  private:
  public:
    /** @name Constructors, destructor */
    //@{
    SubmodulesNode() {applyDefaults();}
    SubmodulesNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~SubmodulesNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "submodules";}
    virtual int getTagCode() const {return NED_SUBMODULES;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{

    virtual SubmodulesNode *getNextSubmodulesNodeSibling() const;
    virtual SubmoduleNode *getFirstSubmoduleChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;submodule&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT submodule (expression*, parameters?, gates?)>
 * <!ATTLIST submodule
 *      name               NMTOKEN   #REQUIRED
 *      type               NMTOKEN   #IMPLIED
 *      like-type          NMTOKEN   #IMPLIED
 *      like-param         CDATA     #IMPLIED
 *      vector-size        CDATA     #IMPLIED
 * >
 * </pre>
 * 
 * @ingroup Data
 */
class SubmoduleNode : public NEDElement
{
  private:
    std::string name;
    std::string type;
    std::string likeType;
    std::string likeParam;
    std::string vectorSize;
  public:
    /** @name Constructors, destructor */
    //@{
    SubmoduleNode() {applyDefaults();}
    SubmoduleNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~SubmoduleNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "submodule";}
    virtual int getTagCode() const {return NED_SUBMODULE;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getName() const  {return name.c_str();}
    void setName(const char * val)  {name = val;}
    const char * getType() const  {return type.c_str();}
    void setType(const char * val)  {type = val;}
    const char * getLikeType() const  {return likeType.c_str();}
    void setLikeType(const char * val)  {likeType = val;}
    const char * getLikeParam() const  {return likeParam.c_str();}
    void setLikeParam(const char * val)  {likeParam = val;}
    const char * getVectorSize() const  {return vectorSize.c_str();}
    void setVectorSize(const char * val)  {vectorSize = val;}

    virtual SubmoduleNode *getNextSubmoduleNodeSibling() const;
    virtual ExpressionNode *getFirstExpressionChild() const;
    virtual ParametersNode *getFirstParametersChild() const;
    virtual GatesNode *getFirstGatesChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;connections&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT connections ((connection|connection-block)*)>
 * <!ATTLIST connections
 *      check-unconnected (true|false) "true">
 * </pre>
 * 
 * @ingroup Data
 */
class ConnectionsNode : public NEDElement
{
  private:
    bool checkUnconnected;
  public:
    /** @name Constructors, destructor */
    //@{
    ConnectionsNode() {applyDefaults();}
    ConnectionsNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~ConnectionsNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "connections";}
    virtual int getTagCode() const {return NED_CONNECTIONS;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    bool getCheckUnconnected() const  {return checkUnconnected;}
    void setCheckUnconnected(bool val)  {checkUnconnected = val;}

    virtual ConnectionsNode *getNextConnectionsNodeSibling() const;
    virtual ConnectionNode *getFirstConnectionChild() const;
    virtual ConnectionBlockNode *getFirstConnectionBlockChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;connection&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT connection (expression*, parameters?)>
 * <!ATTLIST connection
 *      channel-name        NMTOKEN   #IMPLIED
 *      src-module          NMTOKEN   #IMPLIED
 *      src-module-index    CDATA     #IMPLIED
 *      src-gate            NMTOKEN   #REQUIRED
 *      src-gate-plusplus (true|false) "false"
 *      src-gate-index      CDATA     #IMPLIED
 *      dest-module         NMTOKEN   #IMPLIED
 *      dest-module-index   CDATA     #IMPLIED
 *      dest-gate           NMTOKEN   #REQUIRED
 *      dest-gate-plusplus (true|false) "false"
 *      dest-gate-index     CDATA     #IMPLIED
 *      is-left-to-right   (true|false) #REQUIRED
 * >
 * </pre>
 * 
 * @ingroup Data
 */
class ConnectionNode : public NEDElement
{
  private:
    std::string channelName;
    std::string srcModule;
    std::string srcModuleIndex;
    std::string srcGate;
    bool srcGatePlusplus;
    std::string srcGateIndex;
    std::string destModule;
    std::string destModuleIndex;
    std::string destGate;
    bool destGatePlusplus;
    std::string destGateIndex;
    bool isLeftToRight;
  public:
    /** @name Constructors, destructor */
    //@{
    ConnectionNode() {applyDefaults();}
    ConnectionNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~ConnectionNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "connection";}
    virtual int getTagCode() const {return NED_CONNECTION;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getChannelName() const  {return channelName.c_str();}
    void setChannelName(const char * val)  {channelName = val;}
    const char * getSrcModule() const  {return srcModule.c_str();}
    void setSrcModule(const char * val)  {srcModule = val;}
    const char * getSrcModuleIndex() const  {return srcModuleIndex.c_str();}
    void setSrcModuleIndex(const char * val)  {srcModuleIndex = val;}
    const char * getSrcGate() const  {return srcGate.c_str();}
    void setSrcGate(const char * val)  {srcGate = val;}
    bool getSrcGatePlusplus() const  {return srcGatePlusplus;}
    void setSrcGatePlusplus(bool val)  {srcGatePlusplus = val;}
    const char * getSrcGateIndex() const  {return srcGateIndex.c_str();}
    void setSrcGateIndex(const char * val)  {srcGateIndex = val;}
    const char * getDestModule() const  {return destModule.c_str();}
    void setDestModule(const char * val)  {destModule = val;}
    const char * getDestModuleIndex() const  {return destModuleIndex.c_str();}
    void setDestModuleIndex(const char * val)  {destModuleIndex = val;}
    const char * getDestGate() const  {return destGate.c_str();}
    void setDestGate(const char * val)  {destGate = val;}
    bool getDestGatePlusplus() const  {return destGatePlusplus;}
    void setDestGatePlusplus(bool val)  {destGatePlusplus = val;}
    const char * getDestGateIndex() const  {return destGateIndex.c_str();}
    void setDestGateIndex(const char * val)  {destGateIndex = val;}
    bool getIsLeftToRight() const  {return isLeftToRight;}
    void setIsLeftToRight(bool val)  {isLeftToRight = val;}

    virtual ConnectionNode *getNextConnectionNodeSibling() const;
    virtual ExpressionNode *getFirstExpressionChild() const;
    virtual ParametersNode *getFirstParametersChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;channel-interface&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT channel-interface (extends*, parameters?)>
 * <!ATTLIST channel-interface
 *      name               NMTOKEN   #REQUIRED
 * >
 * </pre>
 * 
 * @ingroup Data
 */
class ChannelInterfaceNode : public NEDElement
{
  private:
    std::string name;
  public:
    /** @name Constructors, destructor */
    //@{
    ChannelInterfaceNode() {applyDefaults();}
    ChannelInterfaceNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~ChannelInterfaceNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "channel-interface";}
    virtual int getTagCode() const {return NED_CHANNEL_INTERFACE;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getName() const  {return name.c_str();}
    void setName(const char * val)  {name = val;}

    virtual ChannelInterfaceNode *getNextChannelInterfaceNodeSibling() const;
    virtual  *getFirstExtendsChild() const;
    virtual ParametersNode *getFirstParametersChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;channel&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT channel (extends?, channel-interface-name*, parameters?)>
 * <!ATTLIST channel
 *      name                NMTOKEN   #REQUIRED
 * >
 * </pre>
 * 
 * @ingroup Data
 */
class ChannelNode : public NEDElement
{
  private:
    std::string name;
  public:
    /** @name Constructors, destructor */
    //@{
    ChannelNode() {applyDefaults();}
    ChannelNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~ChannelNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "channel";}
    virtual int getTagCode() const {return NED_CHANNEL;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getName() const  {return name.c_str();}
    void setName(const char * val)  {name = val;}

    virtual ChannelNode *getNextChannelNodeSibling() const;
    virtual  *getFirstExtendsChild() const;
    virtual  *getFirstChannelInterfaceNameChild() const;
    virtual ParametersNode *getFirstParametersChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;connection-block&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT connection-block ((loop|condition)*,connection*)>
 * 
 * </pre>
 * 
 * @ingroup Data
 */
class ConnectionBlockNode : public NEDElement
{
  private:
  public:
    /** @name Constructors, destructor */
    //@{
    ConnectionBlockNode() {applyDefaults();}
    ConnectionBlockNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~ConnectionBlockNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "connection-block";}
    virtual int getTagCode() const {return NED_CONNECTION_BLOCK;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{

    virtual ConnectionBlockNode *getNextConnectionBlockNodeSibling() const;
    virtual LoopNode *getFirstLoopChild() const;
    virtual ConditionNode *getFirstConditionChild() const;
    virtual ConnectionNode *getFirstConnectionChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;loop&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT loop (expression*)>
 * <!ATTLIST loop
 *      param-name          NMTOKEN   #REQUIRED
 *      from-value          CDATA     #IMPLIED
 *      to-value            CDATA     #IMPLIED>
 * </pre>
 * 
 * @ingroup Data
 */
class LoopNode : public NEDElement
{
  private:
    std::string paramName;
    std::string fromValue;
    std::string toValue;
  public:
    /** @name Constructors, destructor */
    //@{
    LoopNode() {applyDefaults();}
    LoopNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~LoopNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "loop";}
    virtual int getTagCode() const {return NED_LOOP;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getParamName() const  {return paramName.c_str();}
    void setParamName(const char * val)  {paramName = val;}
    const char * getFromValue() const  {return fromValue.c_str();}
    void setFromValue(const char * val)  {fromValue = val;}
    const char * getToValue() const  {return toValue.c_str();}
    void setToValue(const char * val)  {toValue = val;}

    virtual LoopNode *getNextLoopNodeSibling() const;
    virtual ExpressionNode *getFirstExpressionChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;condition&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT condition (expression?)>
 * <!ATTLIST condition
 *      condition          CDATA     #IMPLIED
 * >
 * </pre>
 * 
 * @ingroup Data
 */
class ConditionNode : public NEDElement
{
  private:
    std::string condition;
  public:
    /** @name Constructors, destructor */
    //@{
    ConditionNode() {applyDefaults();}
    ConditionNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~ConditionNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "condition";}
    virtual int getTagCode() const {return NED_CONDITION;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getCondition() const  {return condition.c_str();}
    void setCondition(const char * val)  {condition = val;}

    virtual ConditionNode *getNextConditionNodeSibling() const;
    virtual ExpressionNode *getFirstExpressionChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;expression&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT expression ((operator|function|param-ref|ident|const))>
 * <!ATTLIST expression
 *      target              CDATA     #IMPLIED >
 * </pre>
 * 
 * @ingroup Data
 */
class ExpressionNode : public NEDElement
{
  private:
    std::string target;
  public:
    /** @name Constructors, destructor */
    //@{
    ExpressionNode() {applyDefaults();}
    ExpressionNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~ExpressionNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "expression";}
    virtual int getTagCode() const {return NED_EXPRESSION;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getTarget() const  {return target.c_str();}
    void setTarget(const char * val)  {target = val;}

    virtual ExpressionNode *getNextExpressionNodeSibling() const;
    virtual OperatorNode *getFirstOperatorChild() const;
    virtual FunctionNode *getFirstFunctionChild() const;
    virtual ParamRefNode *getFirstParamRefChild() const;
    virtual IdentNode *getFirstIdentChild() const;
    virtual ConstNode *getFirstConstChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;operator&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT operator ((operator|function|param-ref|ident|const)+)>
 * <!ATTLIST operator
 *      name                CDATA     #REQUIRED >
 * </pre>
 * 
 * @ingroup Data
 */
class OperatorNode : public NEDElement
{
  private:
    std::string name;
  public:
    /** @name Constructors, destructor */
    //@{
    OperatorNode() {applyDefaults();}
    OperatorNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~OperatorNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "operator";}
    virtual int getTagCode() const {return NED_OPERATOR;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getName() const  {return name.c_str();}
    void setName(const char * val)  {name = val;}

    virtual OperatorNode *getNextOperatorNodeSibling() const;
    virtual OperatorNode *getFirstOperatorChild() const;
    virtual FunctionNode *getFirstFunctionChild() const;
    virtual ParamRefNode *getFirstParamRefChild() const;
    virtual IdentNode *getFirstIdentChild() const;
    virtual ConstNode *getFirstConstChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;function&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT function ((operator|function|param-ref|ident|const)*)>
 * <!ATTLIST function
 *      name                NMTOKEN   #REQUIRED >
 * </pre>
 * 
 * @ingroup Data
 */
class FunctionNode : public NEDElement
{
  private:
    std::string name;
  public:
    /** @name Constructors, destructor */
    //@{
    FunctionNode() {applyDefaults();}
    FunctionNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~FunctionNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "function";}
    virtual int getTagCode() const {return NED_FUNCTION;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getName() const  {return name.c_str();}
    void setName(const char * val)  {name = val;}

    virtual FunctionNode *getNextFunctionNodeSibling() const;
    virtual OperatorNode *getFirstOperatorChild() const;
    virtual FunctionNode *getFirstFunctionChild() const;
    virtual ParamRefNode *getFirstParamRefChild() const;
    virtual IdentNode *getFirstIdentChild() const;
    virtual ConstNode *getFirstConstChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;param-ref&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT param-ref (expression*)>
 * <!ATTLIST param-ref
 *      module              CDATA     #IMPLIED
 *      module-index        CDATA     #IMPLIED
 *      param-name          NMTOKEN   #REQUIRED
 *      param-index         CDATA     #IMPLIED
 *      is-ref           (true|false) "false"
 *      is-ancestor      (true|false) "false" >
 * </pre>
 * 
 * @ingroup Data
 */
class ParamRefNode : public NEDElement
{
  private:
    std::string module;
    std::string moduleIndex;
    std::string paramName;
    std::string paramIndex;
    bool isRef;
    bool isAncestor;
  public:
    /** @name Constructors, destructor */
    //@{
    ParamRefNode() {applyDefaults();}
    ParamRefNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~ParamRefNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "param-ref";}
    virtual int getTagCode() const {return NED_PARAM_REF;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getModule() const  {return module.c_str();}
    void setModule(const char * val)  {module = val;}
    const char * getModuleIndex() const  {return moduleIndex.c_str();}
    void setModuleIndex(const char * val)  {moduleIndex = val;}
    const char * getParamName() const  {return paramName.c_str();}
    void setParamName(const char * val)  {paramName = val;}
    const char * getParamIndex() const  {return paramIndex.c_str();}
    void setParamIndex(const char * val)  {paramIndex = val;}
    bool getIsRef() const  {return isRef;}
    void setIsRef(bool val)  {isRef = val;}
    bool getIsAncestor() const  {return isAncestor;}
    void setIsAncestor(bool val)  {isAncestor = val;}

    virtual ParamRefNode *getNextParamRefNodeSibling() const;
    virtual ExpressionNode *getFirstExpressionChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;ident&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT ident EMPTY>
 * <!ATTLIST ident
 *      name                NMTOKEN   #REQUIRED >
 * </pre>
 * 
 * @ingroup Data
 */
class IdentNode : public NEDElement
{
  private:
    std::string name;
  public:
    /** @name Constructors, destructor */
    //@{
    IdentNode() {applyDefaults();}
    IdentNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~IdentNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "ident";}
    virtual int getTagCode() const {return NED_IDENT;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getName() const  {return name.c_str();}
    void setName(const char * val)  {name = val;}

    virtual IdentNode *getNextIdentNodeSibling() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;const&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT const EMPTY>
 * <!ATTLIST const
 *      type  (bool|int|real|string|time)  #REQUIRED
 *      text                CDATA     #IMPLIED
 *      value               CDATA     #IMPLIED>
 * </pre>
 * 
 * @ingroup Data
 */
class ConstNode : public NEDElement
{
  private:
    int type;
    std::string text;
    std::string value;
  public:
    /** @name Constructors, destructor */
    //@{
    ConstNode() {applyDefaults();}
    ConstNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~ConstNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "const";}
    virtual int getTagCode() const {return NED_CONST;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    int getType() const  {return type;}
    void setType(int val)  {type = val;}
    const char * getText() const  {return text.c_str();}
    void setText(const char * val)  {text = val;}
    const char * getValue() const  {return value.c_str();}
    void setValue(const char * val)  {value = val;}

    virtual ConstNode *getNextConstNodeSibling() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;msg-file&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT msg-file ((cplusplus|struct-decl|class-decl|message-decl|enum-decl|
 *                      enum|message|class|struct)*)>
 * <!ATTLIST msg-file
 *      filename            CDATA     #IMPLIED
 *      package             CDATA     #IMPLIED >
 * </pre>
 * 
 * @ingroup Data
 */
class MsgFileNode : public NEDElement
{
  private:
    std::string filename;
    std::string package;
  public:
    /** @name Constructors, destructor */
    //@{
    MsgFileNode() {applyDefaults();}
    MsgFileNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~MsgFileNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "msg-file";}
    virtual int getTagCode() const {return NED_MSG_FILE;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getFilename() const  {return filename.c_str();}
    void setFilename(const char * val)  {filename = val;}
    const char * getPackage() const  {return package.c_str();}
    void setPackage(const char * val)  {package = val;}

    virtual MsgFileNode *getNextMsgFileNodeSibling() const;
    virtual CplusplusNode *getFirstCplusplusChild() const;
    virtual StructDeclNode *getFirstStructDeclChild() const;
    virtual ClassDeclNode *getFirstClassDeclChild() const;
    virtual MessageDeclNode *getFirstMessageDeclChild() const;
    virtual EnumDeclNode *getFirstEnumDeclChild() const;
    virtual EnumNode *getFirstEnumChild() const;
    virtual MessageNode *getFirstMessageChild() const;
    virtual ClassNode *getFirstClassChild() const;
    virtual StructNode *getFirstStructChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;cplusplus&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT cplusplus EMPTY>
 * <!ATTLIST cplusplus
 *      body                CDATA     #REQUIRED
 *      banner-comment      CDATA     #IMPLIED
 *      right-comment       CDATA     "&#10;"
 *      trailing-comment    CDATA     "&#10;" >
 * </pre>
 * 
 * @ingroup Data
 */
class CplusplusNode : public NEDElement
{
  private:
    std::string body;
    std::string bannerComment;
    std::string rightComment;
    std::string trailingComment;
  public:
    /** @name Constructors, destructor */
    //@{
    CplusplusNode() {applyDefaults();}
    CplusplusNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~CplusplusNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "cplusplus";}
    virtual int getTagCode() const {return NED_CPLUSPLUS;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getBody() const  {return body.c_str();}
    void setBody(const char * val)  {body = val;}
    const char * getBannerComment() const  {return bannerComment.c_str();}
    void setBannerComment(const char * val)  {bannerComment = val;}
    const char * getRightComment() const  {return rightComment.c_str();}
    void setRightComment(const char * val)  {rightComment = val;}
    const char * getTrailingComment() const  {return trailingComment.c_str();}
    void setTrailingComment(const char * val)  {trailingComment = val;}

    virtual CplusplusNode *getNextCplusplusNodeSibling() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;struct-decl&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT struct-decl EMPTY>
 * <!ATTLIST struct-decl
 *      name                NMTOKEN   #REQUIRED
 *      banner-comment      CDATA     #IMPLIED
 *      right-comment       CDATA     "&#10;"
 *      trailing-comment    CDATA     "&#10;" >
 * </pre>
 * 
 * @ingroup Data
 */
class StructDeclNode : public NEDElement
{
  private:
    std::string name;
    std::string bannerComment;
    std::string rightComment;
    std::string trailingComment;
  public:
    /** @name Constructors, destructor */
    //@{
    StructDeclNode() {applyDefaults();}
    StructDeclNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~StructDeclNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "struct-decl";}
    virtual int getTagCode() const {return NED_STRUCT_DECL;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getName() const  {return name.c_str();}
    void setName(const char * val)  {name = val;}
    const char * getBannerComment() const  {return bannerComment.c_str();}
    void setBannerComment(const char * val)  {bannerComment = val;}
    const char * getRightComment() const  {return rightComment.c_str();}
    void setRightComment(const char * val)  {rightComment = val;}
    const char * getTrailingComment() const  {return trailingComment.c_str();}
    void setTrailingComment(const char * val)  {trailingComment = val;}

    virtual StructDeclNode *getNextStructDeclNodeSibling() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;class-decl&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT class-decl EMPTY>
 * <!ATTLIST class-decl
 *      name                NMTOKEN   #REQUIRED
 *      is-cobject      (true|false)  "false"
 *      banner-comment      CDATA     #IMPLIED
 *      right-comment       CDATA     "&#10;"
 *      trailing-comment    CDATA     "&#10;" >
 * </pre>
 * 
 * @ingroup Data
 */
class ClassDeclNode : public NEDElement
{
  private:
    std::string name;
    bool isCobject;
    std::string bannerComment;
    std::string rightComment;
    std::string trailingComment;
  public:
    /** @name Constructors, destructor */
    //@{
    ClassDeclNode() {applyDefaults();}
    ClassDeclNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~ClassDeclNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "class-decl";}
    virtual int getTagCode() const {return NED_CLASS_DECL;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getName() const  {return name.c_str();}
    void setName(const char * val)  {name = val;}
    bool getIsCobject() const  {return isCobject;}
    void setIsCobject(bool val)  {isCobject = val;}
    const char * getBannerComment() const  {return bannerComment.c_str();}
    void setBannerComment(const char * val)  {bannerComment = val;}
    const char * getRightComment() const  {return rightComment.c_str();}
    void setRightComment(const char * val)  {rightComment = val;}
    const char * getTrailingComment() const  {return trailingComment.c_str();}
    void setTrailingComment(const char * val)  {trailingComment = val;}

    virtual ClassDeclNode *getNextClassDeclNodeSibling() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;message-decl&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT message-decl EMPTY>
 * <!ATTLIST message-decl
 *      name                NMTOKEN   #REQUIRED
 *      banner-comment      CDATA     #IMPLIED
 *      right-comment       CDATA     "&#10;"
 *      trailing-comment    CDATA     "&#10;" >
 * </pre>
 * 
 * @ingroup Data
 */
class MessageDeclNode : public NEDElement
{
  private:
    std::string name;
    std::string bannerComment;
    std::string rightComment;
    std::string trailingComment;
  public:
    /** @name Constructors, destructor */
    //@{
    MessageDeclNode() {applyDefaults();}
    MessageDeclNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~MessageDeclNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "message-decl";}
    virtual int getTagCode() const {return NED_MESSAGE_DECL;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getName() const  {return name.c_str();}
    void setName(const char * val)  {name = val;}
    const char * getBannerComment() const  {return bannerComment.c_str();}
    void setBannerComment(const char * val)  {bannerComment = val;}
    const char * getRightComment() const  {return rightComment.c_str();}
    void setRightComment(const char * val)  {rightComment = val;}
    const char * getTrailingComment() const  {return trailingComment.c_str();}
    void setTrailingComment(const char * val)  {trailingComment = val;}

    virtual MessageDeclNode *getNextMessageDeclNodeSibling() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;enum-decl&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT enum-decl EMPTY>
 * <!ATTLIST enum-decl
 *      name                NMTOKEN   #REQUIRED
 *      banner-comment      CDATA     #IMPLIED
 *      right-comment       CDATA     "&#10;"
 *      trailing-comment    CDATA     "&#10;" >
 * </pre>
 * 
 * @ingroup Data
 */
class EnumDeclNode : public NEDElement
{
  private:
    std::string name;
    std::string bannerComment;
    std::string rightComment;
    std::string trailingComment;
  public:
    /** @name Constructors, destructor */
    //@{
    EnumDeclNode() {applyDefaults();}
    EnumDeclNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~EnumDeclNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "enum-decl";}
    virtual int getTagCode() const {return NED_ENUM_DECL;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getName() const  {return name.c_str();}
    void setName(const char * val)  {name = val;}
    const char * getBannerComment() const  {return bannerComment.c_str();}
    void setBannerComment(const char * val)  {bannerComment = val;}
    const char * getRightComment() const  {return rightComment.c_str();}
    void setRightComment(const char * val)  {rightComment = val;}
    const char * getTrailingComment() const  {return trailingComment.c_str();}
    void setTrailingComment(const char * val)  {trailingComment = val;}

    virtual EnumDeclNode *getNextEnumDeclNodeSibling() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;enum&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT enum (enum-fields?)>
 * <!ATTLIST enum
 *      name                NMTOKEN   #REQUIRED
 *      extends-name        NMTOKEN   #IMPLIED
 *      source-code         CDATA     #IMPLIED
 *      banner-comment      CDATA     #IMPLIED
 *      right-comment       CDATA     "&#10;"
 *      trailing-comment    CDATA     "&#10;" >
 * </pre>
 * 
 * @ingroup Data
 */
class EnumNode : public NEDElement
{
  private:
    std::string name;
    std::string extendsName;
    std::string sourceCode;
    std::string bannerComment;
    std::string rightComment;
    std::string trailingComment;
  public:
    /** @name Constructors, destructor */
    //@{
    EnumNode() {applyDefaults();}
    EnumNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~EnumNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "enum";}
    virtual int getTagCode() const {return NED_ENUM;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getName() const  {return name.c_str();}
    void setName(const char * val)  {name = val;}
    const char * getExtendsName() const  {return extendsName.c_str();}
    void setExtendsName(const char * val)  {extendsName = val;}
    const char * getSourceCode() const  {return sourceCode.c_str();}
    void setSourceCode(const char * val)  {sourceCode = val;}
    const char * getBannerComment() const  {return bannerComment.c_str();}
    void setBannerComment(const char * val)  {bannerComment = val;}
    const char * getRightComment() const  {return rightComment.c_str();}
    void setRightComment(const char * val)  {rightComment = val;}
    const char * getTrailingComment() const  {return trailingComment.c_str();}
    void setTrailingComment(const char * val)  {trailingComment = val;}

    virtual EnumNode *getNextEnumNodeSibling() const;
    virtual EnumFieldsNode *getFirstEnumFieldsChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;enum-fields&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT enum-fields (enum-field*)>
 * <!ATTLIST enum-fields
 *      banner-comment      CDATA     #IMPLIED
 *      right-comment       CDATA     "&#10;" >
 * </pre>
 * 
 * @ingroup Data
 */
class EnumFieldsNode : public NEDElement
{
  private:
    std::string bannerComment;
    std::string rightComment;
  public:
    /** @name Constructors, destructor */
    //@{
    EnumFieldsNode() {applyDefaults();}
    EnumFieldsNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~EnumFieldsNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "enum-fields";}
    virtual int getTagCode() const {return NED_ENUM_FIELDS;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getBannerComment() const  {return bannerComment.c_str();}
    void setBannerComment(const char * val)  {bannerComment = val;}
    const char * getRightComment() const  {return rightComment.c_str();}
    void setRightComment(const char * val)  {rightComment = val;}

    virtual EnumFieldsNode *getNextEnumFieldsNodeSibling() const;
    virtual EnumFieldNode *getFirstEnumFieldChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;enum-field&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT enum-field EMPTY>
 * <!ATTLIST enum-field
 *      name                NMTOKEN   #REQUIRED
 *      value               CDATA     #IMPLIED
 *      banner-comment      CDATA     #IMPLIED
 *      right-comment       CDATA     "&#10;" >
 * </pre>
 * 
 * @ingroup Data
 */
class EnumFieldNode : public NEDElement
{
  private:
    std::string name;
    std::string value;
    std::string bannerComment;
    std::string rightComment;
  public:
    /** @name Constructors, destructor */
    //@{
    EnumFieldNode() {applyDefaults();}
    EnumFieldNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~EnumFieldNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "enum-field";}
    virtual int getTagCode() const {return NED_ENUM_FIELD;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getName() const  {return name.c_str();}
    void setName(const char * val)  {name = val;}
    const char * getValue() const  {return value.c_str();}
    void setValue(const char * val)  {value = val;}
    const char * getBannerComment() const  {return bannerComment.c_str();}
    void setBannerComment(const char * val)  {bannerComment = val;}
    const char * getRightComment() const  {return rightComment.c_str();}
    void setRightComment(const char * val)  {rightComment = val;}

    virtual EnumFieldNode *getNextEnumFieldNodeSibling() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;message&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT message (properties?,fields?)>
 * <!ATTLIST message
 *      name                NMTOKEN   #REQUIRED
 *      extends-name        NMTOKEN   #IMPLIED
 *      source-code         CDATA     #IMPLIED
 *      banner-comment      CDATA     #IMPLIED
 *      right-comment       CDATA     "&#10;"
 *      trailing-comment    CDATA     "&#10;" >
 * </pre>
 * 
 * @ingroup Data
 */
class MessageNode : public NEDElement
{
  private:
    std::string name;
    std::string extendsName;
    std::string sourceCode;
    std::string bannerComment;
    std::string rightComment;
    std::string trailingComment;
  public:
    /** @name Constructors, destructor */
    //@{
    MessageNode() {applyDefaults();}
    MessageNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~MessageNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "message";}
    virtual int getTagCode() const {return NED_MESSAGE;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getName() const  {return name.c_str();}
    void setName(const char * val)  {name = val;}
    const char * getExtendsName() const  {return extendsName.c_str();}
    void setExtendsName(const char * val)  {extendsName = val;}
    const char * getSourceCode() const  {return sourceCode.c_str();}
    void setSourceCode(const char * val)  {sourceCode = val;}
    const char * getBannerComment() const  {return bannerComment.c_str();}
    void setBannerComment(const char * val)  {bannerComment = val;}
    const char * getRightComment() const  {return rightComment.c_str();}
    void setRightComment(const char * val)  {rightComment = val;}
    const char * getTrailingComment() const  {return trailingComment.c_str();}
    void setTrailingComment(const char * val)  {trailingComment = val;}

    virtual MessageNode *getNextMessageNodeSibling() const;
    virtual PropertiesNode *getFirstPropertiesChild() const;
    virtual FieldsNode *getFirstFieldsChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;class&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT class (properties?,fields?)>
 * <!ATTLIST class
 *      name                NMTOKEN   #REQUIRED
 *      extends-name        NMTOKEN   #IMPLIED
 *      source-code         CDATA     #IMPLIED
 *      banner-comment      CDATA     #IMPLIED
 *      right-comment       CDATA     "&#10;"
 *      trailing-comment    CDATA     "&#10;" >
 * </pre>
 * 
 * @ingroup Data
 */
class ClassNode : public NEDElement
{
  private:
    std::string name;
    std::string extendsName;
    std::string sourceCode;
    std::string bannerComment;
    std::string rightComment;
    std::string trailingComment;
  public:
    /** @name Constructors, destructor */
    //@{
    ClassNode() {applyDefaults();}
    ClassNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~ClassNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "class";}
    virtual int getTagCode() const {return NED_CLASS;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getName() const  {return name.c_str();}
    void setName(const char * val)  {name = val;}
    const char * getExtendsName() const  {return extendsName.c_str();}
    void setExtendsName(const char * val)  {extendsName = val;}
    const char * getSourceCode() const  {return sourceCode.c_str();}
    void setSourceCode(const char * val)  {sourceCode = val;}
    const char * getBannerComment() const  {return bannerComment.c_str();}
    void setBannerComment(const char * val)  {bannerComment = val;}
    const char * getRightComment() const  {return rightComment.c_str();}
    void setRightComment(const char * val)  {rightComment = val;}
    const char * getTrailingComment() const  {return trailingComment.c_str();}
    void setTrailingComment(const char * val)  {trailingComment = val;}

    virtual ClassNode *getNextClassNodeSibling() const;
    virtual PropertiesNode *getFirstPropertiesChild() const;
    virtual FieldsNode *getFirstFieldsChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;struct&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT struct (properties?,fields?)>
 * <!ATTLIST struct
 *      name                NMTOKEN   #REQUIRED
 *      extends-name        NMTOKEN   #IMPLIED
 *      source-code         CDATA     #IMPLIED
 *      banner-comment      CDATA     #IMPLIED
 *      right-comment       CDATA     "&#10;"
 *      trailing-comment    CDATA     "&#10;" >
 * </pre>
 * 
 * @ingroup Data
 */
class StructNode : public NEDElement
{
  private:
    std::string name;
    std::string extendsName;
    std::string sourceCode;
    std::string bannerComment;
    std::string rightComment;
    std::string trailingComment;
  public:
    /** @name Constructors, destructor */
    //@{
    StructNode() {applyDefaults();}
    StructNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~StructNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "struct";}
    virtual int getTagCode() const {return NED_STRUCT;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getName() const  {return name.c_str();}
    void setName(const char * val)  {name = val;}
    const char * getExtendsName() const  {return extendsName.c_str();}
    void setExtendsName(const char * val)  {extendsName = val;}
    const char * getSourceCode() const  {return sourceCode.c_str();}
    void setSourceCode(const char * val)  {sourceCode = val;}
    const char * getBannerComment() const  {return bannerComment.c_str();}
    void setBannerComment(const char * val)  {bannerComment = val;}
    const char * getRightComment() const  {return rightComment.c_str();}
    void setRightComment(const char * val)  {rightComment = val;}
    const char * getTrailingComment() const  {return trailingComment.c_str();}
    void setTrailingComment(const char * val)  {trailingComment = val;}

    virtual StructNode *getNextStructNodeSibling() const;
    virtual PropertiesNode *getFirstPropertiesChild() const;
    virtual FieldsNode *getFirstFieldsChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;fields&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT fields (field*)>
 * <!ATTLIST fields
 *      banner-comment      CDATA     #IMPLIED
 *      right-comment       CDATA     "&#10;" >
 * </pre>
 * 
 * @ingroup Data
 */
class FieldsNode : public NEDElement
{
  private:
    std::string bannerComment;
    std::string rightComment;
  public:
    /** @name Constructors, destructor */
    //@{
    FieldsNode() {applyDefaults();}
    FieldsNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~FieldsNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "fields";}
    virtual int getTagCode() const {return NED_FIELDS;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getBannerComment() const  {return bannerComment.c_str();}
    void setBannerComment(const char * val)  {bannerComment = val;}
    const char * getRightComment() const  {return rightComment.c_str();}
    void setRightComment(const char * val)  {rightComment = val;}

    virtual FieldsNode *getNextFieldsNodeSibling() const;
    virtual FieldNode *getFirstFieldChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;field&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT field EMPTY>
 * <!ATTLIST field
 *      name                NMTOKEN   #REQUIRED
 *      data-type           CDATA     #IMPLIED
 *      is-abstract     (true|false)  "false"
 *      is-readonly     (true|false)  "false"
 *      is-vector       (true|false)  "false"
 *      vector-size         CDATA     #IMPLIED
 *      enum-name           NMTOKEN   #IMPLIED
 *      default-value       CDATA     #IMPLIED
 *      banner-comment      CDATA     #IMPLIED
 *      right-comment       CDATA     "&#10;" >
 * </pre>
 * 
 * @ingroup Data
 */
class FieldNode : public NEDElement
{
  private:
    std::string name;
    std::string dataType;
    bool isAbstract;
    bool isReadonly;
    bool isVector;
    std::string vectorSize;
    std::string enumName;
    std::string defaultValue;
    std::string bannerComment;
    std::string rightComment;
  public:
    /** @name Constructors, destructor */
    //@{
    FieldNode() {applyDefaults();}
    FieldNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~FieldNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "field";}
    virtual int getTagCode() const {return NED_FIELD;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getName() const  {return name.c_str();}
    void setName(const char * val)  {name = val;}
    const char * getDataType() const  {return dataType.c_str();}
    void setDataType(const char * val)  {dataType = val;}
    bool getIsAbstract() const  {return isAbstract;}
    void setIsAbstract(bool val)  {isAbstract = val;}
    bool getIsReadonly() const  {return isReadonly;}
    void setIsReadonly(bool val)  {isReadonly = val;}
    bool getIsVector() const  {return isVector;}
    void setIsVector(bool val)  {isVector = val;}
    const char * getVectorSize() const  {return vectorSize.c_str();}
    void setVectorSize(const char * val)  {vectorSize = val;}
    const char * getEnumName() const  {return enumName.c_str();}
    void setEnumName(const char * val)  {enumName = val;}
    const char * getDefaultValue() const  {return defaultValue.c_str();}
    void setDefaultValue(const char * val)  {defaultValue = val;}
    const char * getBannerComment() const  {return bannerComment.c_str();}
    void setBannerComment(const char * val)  {bannerComment = val;}
    const char * getRightComment() const  {return rightComment.c_str();}
    void setRightComment(const char * val)  {rightComment = val;}

    virtual FieldNode *getNextFieldNodeSibling() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;properties&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT properties (property*)>
 * <!ATTLIST properties
 *      banner-comment      CDATA     #IMPLIED
 *      right-comment       CDATA     "&#10;" >
 * </pre>
 * 
 * @ingroup Data
 */
class PropertiesNode : public NEDElement
{
  private:
    std::string bannerComment;
    std::string rightComment;
  public:
    /** @name Constructors, destructor */
    //@{
    PropertiesNode() {applyDefaults();}
    PropertiesNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~PropertiesNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "properties";}
    virtual int getTagCode() const {return NED_PROPERTIES;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getBannerComment() const  {return bannerComment.c_str();}
    void setBannerComment(const char * val)  {bannerComment = val;}
    const char * getRightComment() const  {return rightComment.c_str();}
    void setRightComment(const char * val)  {rightComment = val;}

    virtual PropertiesNode *getNextPropertiesNodeSibling() const;
    virtual PropertyNode *getFirstPropertyChild() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;property&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT property EMPTY>
 * <!ATTLIST property
 *      name                NMTOKEN   #REQUIRED
 *      value               CDATA     #IMPLIED
 *      banner-comment      CDATA     #IMPLIED
 *      right-comment       CDATA     "&#10;" >
 * </pre>
 * 
 * @ingroup Data
 */
class PropertyNode : public NEDElement
{
  private:
    std::string name;
    std::string value;
    std::string bannerComment;
    std::string rightComment;
  public:
    /** @name Constructors, destructor */
    //@{
    PropertyNode() {applyDefaults();}
    PropertyNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~PropertyNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "property";}
    virtual int getTagCode() const {return NED_PROPERTY;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getName() const  {return name.c_str();}
    void setName(const char * val)  {name = val;}
    const char * getValue() const  {return value.c_str();}
    void setValue(const char * val)  {value = val;}
    const char * getBannerComment() const  {return bannerComment.c_str();}
    void setBannerComment(const char * val)  {bannerComment = val;}
    const char * getRightComment() const  {return rightComment.c_str();}
    void setRightComment(const char * val)  {rightComment = val;}

    virtual PropertyNode *getNextPropertyNodeSibling() const;
    //@}
};

/**
 * GENERATED CLASS. Represents the &lt;unknown&gt; XML element in memory. DTD declaration:
 * 
 * <pre>
 * <!ELEMENT unknown        ANY>
 * <!ATTLIST unknown
 *      element             NMTOKEN   #REQUIRED>
 * </pre>
 * 
 * @ingroup Data
 */
class UnknownNode : public NEDElement
{
  private:
    std::string element;
  public:
    /** @name Constructors, destructor */
    //@{
    UnknownNode() {applyDefaults();}
    UnknownNode(NEDElement *parent) : NEDElement(parent) {applyDefaults();}
    virtual ~UnknownNode() {}
    //@}

    /** @name Redefined NEDElement methods, incl. generic access to attributes */
    //@{
    virtual const char *getTagName() const {return "unknown";}
    virtual int getTagCode() const {return NED_UNKNOWN;}
    virtual int getNumAttributes() const;
    virtual const char *getAttributeName(int k) const;
    virtual const char *getAttribute(int k) const;
    virtual void setAttribute(int k, const char *val);
    virtual const char *getAttributeDefault(int k) const;
    //@}

    /** @name Typed access to attributes, children and siblings */
    //@{
    const char * getElement() const  {return element.c_str();}
    void setElement(const char * val)  {element = val;}

    virtual UnknownNode *getNextUnknownNodeSibling() const;
    //@}
};

/**
 * GENERATED CLASS. Factory for NEDElement subclasses.
 * 
 * @ingroup Data
 */
class NEDElementFactory
{
  private:
    static NEDElementFactory *f;
    // ctor is private, because only one instance is allowed
    NEDElementFactory() {}
  public:
    /** Destructor */
    virtual ~NEDElementFactory() {}
    /** Returns factory instance */
    static NEDElementFactory *getInstance();
    /** Creates NEDElement subclass which corresponds to tagname */
    virtual NEDElement *createNodeWithTag(const char *tagname);
    /** Creates NEDElement subclass which corresponds to tagcode */
    virtual NEDElement *createNodeWithTag(int tagcode);
};

#endif

