package org.omnetpp.inifile.editor.model;

import java.io.IOException;
import java.io.Reader;
import java.io.StringReader;
import java.util.ArrayList;
import java.util.LinkedHashMap;

import org.eclipse.core.resources.IFile;
import org.eclipse.jface.text.BadLocationException;
import org.eclipse.jface.text.DocumentEvent;
import org.eclipse.jface.text.IDocument;
import org.eclipse.jface.text.IDocumentListener;
import org.omnetpp.common.util.StringUtils;

/**
 * Standard implementation of IInifileDocument.
 * Setters change the underlying IDocument.
 * @author Andras
 */
//XXX renameSection() missing
public class InifileDocument implements IInifileDocument {
	private IDocument document; // the document we are manipulating
	private IFile documentFile; // the file of the document
	private boolean changed; // whether changed since last parsed

	class Line {
		IFile file;
		int lineNumber;
		int numLines;  // ==1 unless line continues on other lines (trailing backslash)
		String comment;
	};
	class SectionHeadingLine extends Line {
		String sectionName;
	}
	class KeyValueLine extends Line {
		String key;
		String value;
	}
	class IncludeLine extends Line {
		String includedFile;
	}

	class Section {
		SectionHeadingLine sectionHeading; // the first if there's more than one; XXX store all?
		LinkedHashMap<String,KeyValueLine> entries = new LinkedHashMap<String, KeyValueLine>();
	}

	private LinkedHashMap<String,Section> sections = new LinkedHashMap<String,Section>();
	private ArrayList<IncludeLine> topIncludes = new ArrayList<IncludeLine>();
	private ArrayList<IncludeLine> bottomIncludes = new ArrayList<IncludeLine>();
	private IDocumentListener listener;
	private InifileChangeListenerList listeners = new InifileChangeListenerList();

	public InifileDocument(IDocument document, IFile documentFile) {
		this.document = document;
		this.documentFile = documentFile;
		this.changed = true;

		// listen on changes so we know when we need to re-parse
		listener = new IDocumentListener() {
			public void documentAboutToBeChanged(DocumentEvent event) {}
			public void documentChanged(DocumentEvent event) {
				changed = true;
			}
		};
		document.addDocumentListener(listener);
	}

	//FIXME to be called from the editor!
	public void dispose() {
		document.removeDocumentListener(listener);
	}

	public void parseIfChanged() {
		if (changed)
			parse();
	}

	public void parse() {
		sections.clear();
		topIncludes.clear();
		bottomIncludes.clear();
		long startTime = System.currentTimeMillis();
		Reader streamReader = new StringReader(document.get());
		try {
			new InifileParser().parse(streamReader, new InifileParser.ParserCallback() {
				Section currentSection = null;
				IFile currentFile = documentFile; 

				public void blankOrCommentLine(int lineNumber, String rawLine, String comment) {
					// ignore
				}

				public void directiveLine(int lineNumber, String rawLine, String directive, String args, String comment) {
					if (directive.equals("include")) {
						IncludeLine line = new IncludeLine();
						line.file = currentFile;
						line.lineNumber = lineNumber;
						line.numLines = 1; //XXX
						line.comment = comment;
						line.includedFile = args;
						// TODO: at this point, we should recursively parse that file as well
					}
				}

				public void incompleteLine(int lineNumber, String rawLine) {
					//XXX eliminate
				}

				public void keyValueLine(int lineNumber, String rawLine, String key, String value, String comment) {
					if (currentSection==null)
						throw new ParseException("entry occurs before first section heading", lineNumber);
					if (!currentSection.entries.containsKey(key)) {
						KeyValueLine line = new KeyValueLine();
						line.file = currentFile;
						line.lineNumber = lineNumber;
						line.numLines = 1; //XXX
						line.comment = comment;
						line.key = key;
						line.value = value;
						currentSection.entries.put(key, line);
					}
				}

				public void sectionHeadingLine(int lineNumber, String rawLine, String sectionName, String comment) {
					if (!sections.containsKey(sectionName)) {
						// add if such section not yet exists
						SectionHeadingLine line = new SectionHeadingLine();
						line.file = currentFile;
						line.lineNumber = lineNumber;
						line.numLines = 1; //XXX
						line.comment = comment;
						line.sectionName = sectionName;
						Section section = new Section(); //XXX fill it in
						sections.put(sectionName, section);
					}
					currentSection = sections.get(sectionName);
				}
			});
		} 
		catch (IOException e) {
			// cannot happen with string input
		} 
		catch (ParseException e) {
			System.err.println(e.getClass()+": "+e.getMessage()); //XXX convert to marker?
		}
		changed = false; // even if there was an error, we don't try again until text changes
		fireModelChanged();
		System.out.println("Inifile parsing: "+(System.currentTimeMillis()-startTime)+"ms");
	}

	public String getValue(String section, String key) {
		KeyValueLine line = lookupEntry(section, key);
		return line == null ? null : line.value;
	}

	protected KeyValueLine lookupEntry(String sectionName, String key) {
		parseIfChanged();
		Section section = sections.get(sectionName);
		return section == null ? null : section.entries.get(key);
	}

	protected boolean isEditable(Line line) {
		return line.file == documentFile;
	}
	
	public void setValue(String section, String key, String value) {
		KeyValueLine line = lookupEntry(section, key);
		if (line == null)
			throw new IllegalArgumentException("no such entry: ["+section+"] "+key);
		if (!isEditable(line))
			throw new IllegalArgumentException("cannot change entry in an included file: ["+section+"] "+key);

		// change IDocument
		line.value = value; 
		String text = line.key + " = " + line.value + (line.comment == null ? "" : " "+line.comment);
		replaceLine(line, text);
		//changed = true; //XXX just to trigger the "tru/fals" bug
	}

	/**
	 * Replaces line content in IDocument.
s	 * @return true if line numbers have changed, false if not
	 */
	protected boolean replaceLine(Line line, String text) {
		try {
			int offset = document.getLineOffset(line.lineNumber-1);
			int length = document.getLineOffset(line.lineNumber-1+line.numLines) - 1 - offset;
			document.replace(offset, length, text);

			boolean lineNumberChange = (line.numLines != StringUtils.countNewLines(text)+1);
			if (lineNumberChange)
				changed = true; // force re-parsing because line numbers have shifted
			return lineNumberChange;
		} 
		catch (BadLocationException e) {
			throw new RuntimeException("cannot set value: bad location: "+e.getMessage());
		}
	}

	public void addEntry(String section, String key, String value, String comment, String beforeKey) {
		KeyValueLine line = lookupEntry(section, key);
		if (line != null)
			throw new IllegalArgumentException("entry already exists: ["+section+"] "+key);
		KeyValueLine beforeLine = lookupEntry(section, key);
		if (beforeLine == null)
			throw new IllegalArgumentException("no such entry: ["+section+"] "+beforeKey);
		if (!isEditable(beforeLine))
			throw new IllegalArgumentException("cannot insert entry into included file, before entry ["+section+"] "+beforeKey);
		//TODO change IDocument
	}

	public LineInfo getEntryLineDetails(String section, String key) {
		KeyValueLine line = lookupEntry(section, key);
		return line==null ? null : new LineInfo(line.file, line.lineNumber, !isEditable(line));
	} 

	public String getComment(String section, String key) {
		KeyValueLine line = lookupEntry(section, key);
		if (line == null)
			throw new IllegalArgumentException("no such entry: ["+section+"] "+key);
		return line.comment;
	}

	public void setComment(String section, String key, String comment) {
		KeyValueLine line = lookupEntry(section, key);
		if (line == null)
			throw new IllegalArgumentException("no such entry: ["+section+"] "+key);

		// modify IDocument
		line.comment = comment; 
		String text = line.key + " = " + line.value + (line.comment == null ? "" : " "+line.comment);
		replaceLine(line, text);
		//TODO
	}

	public void removeKey(String section, String key) {
		KeyValueLine line = lookupEntry(section, key);
		if (line != null) {
			//TODO remove
		}
	}

	public String[] getKeys(String sectionName) {
		parseIfChanged();
		Section section = sections.get(sectionName);
		return section == null ? null : section.entries.keySet().toArray(new String[0]);
	}

	public String[] getSectionNames() {
		parseIfChanged();
		return sections.keySet().toArray(new String[0]);
	}

	public void removeSection(String sectionName) {
		parseIfChanged();
		Section section = sections.get(sectionName);
		if (section != null) {
			//TODO remove from IDocument
		}
	}

	public void addSection(String sectionName, String beforeSectionName) {
		parseIfChanged();
		Section section = sections.get(sectionName);
		if (section != null)
			throw new IllegalArgumentException("section already exists: ["+sectionName+"]");
		Section beforeSection = sections.get(beforeSectionName);
		if (beforeSection == null)
			throw new IllegalArgumentException("section does not exist: ["+beforeSectionName+"]");
		//TODO add
	}

	public LineInfo getSectionLineDetails(String sectionName) {
		parseIfChanged();
		Section section = sections.get(sectionName);
		return section==null ? null : new LineInfo(section.sectionHeading.file, section.sectionHeading.lineNumber, !isEditable(section.sectionHeading));
	} 

	public String getSectionComment(String sectionName) {
		parseIfChanged();
		Section section = sections.get(sectionName);
		if (section == null)
			throw new IllegalArgumentException("section does not exist: ["+sectionName+"]");
		return section.sectionHeading.comment;
	}

	public void setSectionComment(String sectionName, String comment) {
		parseIfChanged();
		Section section = sections.get(sectionName);
		if (section == null)
			throw new IllegalArgumentException("section does not exist: ["+sectionName+"]");

		SectionHeadingLine line = section.sectionHeading;
		line.comment = comment; 
		String text = "[" + line.sectionName + "]" + (line.comment == null ? "" : " "+line.comment);
		replaceLine(line, text);
	}

	public String[] getTopIncludes() {
		parseIfChanged();
		return null; //TODO
	}

	public void addTopInclude(String include, String before) {
		parseIfChanged();
		//TODO
	}

	public void removeTopInclude(String include) {
		parseIfChanged();
		//TODO
	}

	public String[] getBottomIncludes() {
		parseIfChanged();
		return null; //TODO
	}

	public void addBottomInclude(String include, String before) {
		parseIfChanged();
		//TODO
	}

	public void removeBottomInclude(String include) {
		parseIfChanged();
		//TODO
	}

    /**
     * @return The listener list attached to this element 
     */
    public InifileChangeListenerList getListeners() {
        return listeners;
    }
	
	/**
     * Fires a model change event by notifying listeners.
     */
    public void fireModelChanged() {
        if (listeners != null && getListeners().isEnabled())
        	listeners.fireModelChanged();
    }
}
