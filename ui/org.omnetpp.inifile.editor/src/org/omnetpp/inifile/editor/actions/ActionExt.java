package org.omnetpp.inifile.editor.actions;

import org.eclipse.jface.action.Action;
import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.jface.viewers.ISelectionChangedListener;
import org.eclipse.jface.viewers.SelectionChangedEvent;

/**
 * Small utility class: org.eclipse.jface.action.Action with an extra
 * convenience constructor, and implementing ISelectionChangedListener.
 * @author Andras
 */
public class ActionExt extends Action implements ISelectionChangedListener {
	public ActionExt() {
		super();
	}

	public ActionExt(String text, ImageDescriptor image) {
		super(text, image);
	}

	public ActionExt(String text, int style) {
		super(text, style);
	}

	public ActionExt(String text) {
		super(text);
	}

	public ActionExt(String text, int style, ImageDescriptor image) {
		super(text, style);
		setImageDescriptor(image);
	}

	public void selectionChanged(SelectionChangedEvent event) {
	}
}
