package org.omnetpp.simulation.actions;

import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.swt.widgets.Display;
import org.omnetpp.simulation.SimulationPlugin;
import org.omnetpp.simulation.SimulationUIConstants;
import org.omnetpp.simulation.controller.SimulationController;
import org.omnetpp.simulation.controller.SimulationController.SimState;

/**
 * The Rebuild Network action.
 *  
 * @author Andras
 */
public class RebuildNetworkAction extends AbstractSimulationAction {
    public RebuildNetworkAction(SimulationController controller) {
        super(controller);
        setText("Rebuild Network");
        setToolTipText("Rebuild Network");
        setImageDescriptor(SimulationPlugin.getImageDescriptor(SimulationUIConstants.IMG_TOOL_RESTART));
    }

    @Override
    public void run() {
        try {
            SimulationController controller = getSimulationController();
            if (!ensureNotRunning(controller))
                return;
            if (!controller.isNetworkPresent()) {
                MessageDialog.openInformation(getShell(), "Error", "No network has been set up yet.");
                return;
            }
            
            controller.rebuildNetwork();
        }
        catch (Exception e) {
            MessageDialog.openError(Display.getCurrent().getActiveShell(), "Error", "Internal error: " + e.toString());
            SimulationPlugin.logError(e);
        }
    }

    @Override
    public void updateState() {
        SimState state = getSimulationController().getState();
        setEnabled(state != SimState.DISCONNECTED && state != SimState.NONETWORK && state != SimState.RUNNING);
    }
}