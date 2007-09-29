package org.omnetpp.test.gui.access;

import org.omnetpp.inifile.editor.editors.InifileEditor;
import org.omnetpp.inifile.editor.form.InifileFormEditor;
import org.omnetpp.inifile.editor.text.InifileTextEditor;

import com.simulcraft.test.gui.access.CompositeAccess;
import com.simulcraft.test.gui.access.MultiPageEditorPartAccess;
import com.simulcraft.test.gui.access.TextEditorAccess;

public class InifileEditorAccess
    extends MultiPageEditorPartAccess
{

	public InifileEditorAccess(InifileEditor multiPageNedEditor) {
		super(multiPageNedEditor);
	}
	
	public InifileEditor getInifileEditor() {
	    return (InifileEditor)workbenchPart;
    }

    public InifileTextEditor getTextEditor() {
        return getInifileEditor().getTextEditor();
    }

    public InifileFormEditor getFormEditor() {
        return getInifileEditor().getFormEditor();
    }

    public TextEditorAccess activateTextEditor() {
        return (TextEditorAccess) activatePageEditor("Text");
    }

    public CompositeAccess activateFormEditor() {
        return (CompositeAccess) activatePageControl("Form");
    }

    public TextEditorAccess ensureActiveTextEditor() {
        return (TextEditorAccess)ensureActiveEditor("Text");
    }

    public CompositeAccess ensureActiveFormEditor() {
        return (CompositeAccess)ensureActivePage("Form");
    }
}
