/**
 * <copyright>
 * </copyright>
 *
 * $Id$
 */
package org.omnetpp.ned2.provider.tree;

import java.util.Collection;
import java.util.List;

import org.eclipse.emf.common.notify.AdapterFactory;
import org.eclipse.emf.common.notify.Notification;

import org.eclipse.emf.common.util.ResourceLocator;

import org.eclipse.emf.ecore.EStructuralFeature;

import org.eclipse.emf.ecore.util.FeatureMapUtil;

import org.eclipse.emf.edit.provider.ComposeableAdapterFactory;
import org.eclipse.emf.edit.provider.IEditingDomainItemProvider;
import org.eclipse.emf.edit.provider.IItemLabelProvider;
import org.eclipse.emf.edit.provider.IItemPropertySource;
import org.eclipse.emf.edit.provider.IStructuredItemContentProvider;
import org.eclipse.emf.edit.provider.ITreeItemContentProvider;
import org.eclipse.emf.edit.provider.ItemPropertyDescriptor;
import org.eclipse.emf.edit.provider.ItemProviderAdapter;
import org.eclipse.emf.edit.provider.ViewerNotification;

import org.omnetpp.ned2.model.NedFile;

import org.omnetpp.ned2.model.meta.Ned2Factory;
import org.omnetpp.ned2.model.meta.Ned2Package;

/**
 * This is the item provider adapter for a {@link org.omnetpp.ned2.model.NedFile} object.
 * <!-- begin-user-doc -->
 * <!-- end-user-doc -->
 * @generated
 */
public class NedFileItemProvider extends ItemProviderAdapter implements
		IEditingDomainItemProvider, IStructuredItemContentProvider,
		ITreeItemContentProvider, IItemLabelProvider, IItemPropertySource {
	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public static final String copyright = "";

	/**
	 * This constructs an instance from a factory and a notifier.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public NedFileItemProvider(AdapterFactory adapterFactory) {
		super(adapterFactory);
	}

	/**
	 * This returns the property descriptors for the adapted class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public List getPropertyDescriptors(Object object) {
		if (itemPropertyDescriptors == null) {
			super.getPropertyDescriptors(object);

			addFilenamePropertyDescriptor(object);
			addPackagePropertyDescriptor(object);
		}
		return itemPropertyDescriptors;
	}

	/**
	 * This adds a property descriptor for the Filename feature.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected void addFilenamePropertyDescriptor(Object object) {
		itemPropertyDescriptors.add(createItemPropertyDescriptor(
				((ComposeableAdapterFactory) adapterFactory)
						.getRootAdapterFactory(), getResourceLocator(),
				getString("_UI_NedFile_filename_feature"), getString(
						"_UI_PropertyDescriptor_description",
						"_UI_NedFile_filename_feature", "_UI_NedFile_type"),
				Ned2Package.Literals.NED_FILE__FILENAME, true,
				ItemPropertyDescriptor.GENERIC_VALUE_IMAGE, null, null));
	}

	/**
	 * This adds a property descriptor for the Package feature.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected void addPackagePropertyDescriptor(Object object) {
		itemPropertyDescriptors.add(createItemPropertyDescriptor(
				((ComposeableAdapterFactory) adapterFactory)
						.getRootAdapterFactory(), getResourceLocator(),
				getString("_UI_NedFile_package_feature"), getString(
						"_UI_PropertyDescriptor_description",
						"_UI_NedFile_package_feature", "_UI_NedFile_type"),
				Ned2Package.Literals.NED_FILE__PACKAGE, true,
				ItemPropertyDescriptor.GENERIC_VALUE_IMAGE, null, null));
	}

	/**
	 * This specifies how to implement {@link #getChildren} and is used to deduce an appropriate feature for an
	 * {@link org.eclipse.emf.edit.command.AddCommand}, {@link org.eclipse.emf.edit.command.RemoveCommand} or
	 * {@link org.eclipse.emf.edit.command.MoveCommand} in {@link #createCommand}.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Collection getChildrenFeatures(Object object) {
		if (childrenFeatures == null) {
			super.getChildrenFeatures(object);
			childrenFeatures.add(Ned2Package.Literals.NED_FILE__WHITESPACE);
			childrenFeatures.add(Ned2Package.Literals.NED_FILE__GROUP);
		}
		return childrenFeatures;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected EStructuralFeature getChildFeature(Object object, Object child) {
		// Check the type of the specified child object and return the proper feature to use for
		// adding (see {@link AddCommand}) it as a child.

		return super.getChildFeature(object, child);
	}

	/**
	 * This returns NedFile.gif.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Object getImage(Object object) {
		return getResourceLocator().getImage("full/obj16/NedFile");
	}

	/**
	 * This returns the label text for the adapted class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public String getText(Object object) {
		String label = ((NedFile) object).getFilename();
		return label == null || label.length() == 0 ? getString("_UI_NedFile_type")
				: getString("_UI_NedFile_type") + " " + label;
	}

	/**
	 * This handles model notifications by calling {@link #updateChildren} to update any cached
	 * children and by creating a viewer notification, which it passes to {@link #fireNotifyChanged}.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void notifyChanged(Notification notification) {
		updateChildren(notification);

		switch (notification.getFeatureID(NedFile.class)) {
		case Ned2Package.NED_FILE__FILENAME:
		case Ned2Package.NED_FILE__PACKAGE:
			fireNotifyChanged(new ViewerNotification(notification, notification
					.getNotifier(), false, true));
			return;
		case Ned2Package.NED_FILE__WHITESPACE:
		case Ned2Package.NED_FILE__GROUP:
			fireNotifyChanged(new ViewerNotification(notification, notification
					.getNotifier(), true, false));
			return;
		}
		super.notifyChanged(notification);
	}

	/**
	 * This adds to the collection of {@link org.eclipse.emf.edit.command.CommandParameter}s
	 * describing all of the children that can be created under this object.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected void collectNewChildDescriptors(Collection newChildDescriptors,
			Object object) {
		super.collectNewChildDescriptors(newChildDescriptors, object);

		newChildDescriptors.add(createChildParameter(
				Ned2Package.Literals.NED_FILE__WHITESPACE,
				Ned2Factory.eINSTANCE.createWhitespace()));

		newChildDescriptors.add(createChildParameter(
				Ned2Package.Literals.NED_FILE__GROUP, FeatureMapUtil
						.createEntry(Ned2Package.Literals.NED_FILE__IMPORT,
								Ned2Factory.eINSTANCE.createImport())));

		newChildDescriptors.add(createChildParameter(
				Ned2Package.Literals.NED_FILE__GROUP, FeatureMapUtil
						.createEntry(
								Ned2Package.Literals.NED_FILE__PROPERTYDEF,
								Ned2Factory.eINSTANCE.createPropertydef())));

		newChildDescriptors.add(createChildParameter(
				Ned2Package.Literals.NED_FILE__GROUP, FeatureMapUtil
						.createEntry(Ned2Package.Literals.NED_FILE__PROPERTY,
								Ned2Factory.eINSTANCE.createProperty())));

		newChildDescriptors.add(createChildParameter(
				Ned2Package.Literals.NED_FILE__GROUP, FeatureMapUtil
						.createEntry(Ned2Package.Literals.NED_FILE__CHANNEL,
								Ned2Factory.eINSTANCE.createChannel())));

		newChildDescriptors.add(createChildParameter(
				Ned2Package.Literals.NED_FILE__GROUP,
				FeatureMapUtil.createEntry(
						Ned2Package.Literals.NED_FILE__CHANNEL_INTERFACE,
						Ned2Factory.eINSTANCE.createChannelInterface())));

		newChildDescriptors.add(createChildParameter(
				Ned2Package.Literals.NED_FILE__GROUP, FeatureMapUtil
						.createEntry(
								Ned2Package.Literals.NED_FILE__SIMPLE_MODULE,
								Ned2Factory.eINSTANCE.createSimpleModule())));

		newChildDescriptors.add(createChildParameter(
				Ned2Package.Literals.NED_FILE__GROUP, FeatureMapUtil
						.createEntry(
								Ned2Package.Literals.NED_FILE__COMPOUND_MODULE,
								Ned2Factory.eINSTANCE.createCompoundModule())));

		newChildDescriptors.add(createChildParameter(
				Ned2Package.Literals.NED_FILE__GROUP,
				FeatureMapUtil.createEntry(
						Ned2Package.Literals.NED_FILE__MODULE_INTERFACE,
						Ned2Factory.eINSTANCE.createModuleInterface())));
	}

	/**
	 * Return the resource locator for this item provider's resources.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public ResourceLocator getResourceLocator() {
		return Ned2TreeProviderPlugin.INSTANCE;
	}

}
