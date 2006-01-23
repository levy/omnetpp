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

import org.eclipse.emf.edit.provider.ComposeableAdapterFactory;
import org.eclipse.emf.edit.provider.IEditingDomainItemProvider;
import org.eclipse.emf.edit.provider.IItemLabelProvider;
import org.eclipse.emf.edit.provider.IItemPropertySource;
import org.eclipse.emf.edit.provider.IStructuredItemContentProvider;
import org.eclipse.emf.edit.provider.ITreeItemContentProvider;
import org.eclipse.emf.edit.provider.ItemPropertyDescriptor;
import org.eclipse.emf.edit.provider.ItemProviderAdapter;
import org.eclipse.emf.edit.provider.ViewerNotification;

import org.omnetpp.ned2.model.Submodule;

import org.omnetpp.ned2.model.meta.Ned2Factory;
import org.omnetpp.ned2.model.meta.Ned2Package;

/**
 * This is the item provider adapter for a {@link org.omnetpp.ned2.model.Submodule} object.
 * <!-- begin-user-doc -->
 * <!-- end-user-doc -->
 * @generated
 */
public class SubmoduleItemProvider extends ItemProviderAdapter implements
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
	public SubmoduleItemProvider(AdapterFactory adapterFactory) {
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

			addLikeParamPropertyDescriptor(object);
			addLikeTypePropertyDescriptor(object);
			addNamePropertyDescriptor(object);
			addTypePropertyDescriptor(object);
			addVectorSizePropertyDescriptor(object);
		}
		return itemPropertyDescriptors;
	}

	/**
	 * This adds a property descriptor for the Like Param feature.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected void addLikeParamPropertyDescriptor(Object object) {
		itemPropertyDescriptors
				.add(createItemPropertyDescriptor(
						((ComposeableAdapterFactory) adapterFactory)
								.getRootAdapterFactory(), getResourceLocator(),
						getString("_UI_Submodule_likeParam_feature"),
						getString("_UI_PropertyDescriptor_description",
								"_UI_Submodule_likeParam_feature",
								"_UI_Submodule_type"),
						Ned2Package.Literals.SUBMODULE__LIKE_PARAM, true,
						ItemPropertyDescriptor.GENERIC_VALUE_IMAGE, null, null));
	}

	/**
	 * This adds a property descriptor for the Like Type feature.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected void addLikeTypePropertyDescriptor(Object object) {
		itemPropertyDescriptors
				.add(createItemPropertyDescriptor(
						((ComposeableAdapterFactory) adapterFactory)
								.getRootAdapterFactory(), getResourceLocator(),
						getString("_UI_Submodule_likeType_feature"), getString(
								"_UI_PropertyDescriptor_description",
								"_UI_Submodule_likeType_feature",
								"_UI_Submodule_type"),
						Ned2Package.Literals.SUBMODULE__LIKE_TYPE, true,
						ItemPropertyDescriptor.GENERIC_VALUE_IMAGE, null, null));
	}

	/**
	 * This adds a property descriptor for the Name feature.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected void addNamePropertyDescriptor(Object object) {
		itemPropertyDescriptors.add(createItemPropertyDescriptor(
				((ComposeableAdapterFactory) adapterFactory)
						.getRootAdapterFactory(), getResourceLocator(),
				getString("_UI_Submodule_name_feature"), getString(
						"_UI_PropertyDescriptor_description",
						"_UI_Submodule_name_feature", "_UI_Submodule_type"),
				Ned2Package.Literals.SUBMODULE__NAME, true,
				ItemPropertyDescriptor.GENERIC_VALUE_IMAGE, null, null));
	}

	/**
	 * This adds a property descriptor for the Type feature.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected void addTypePropertyDescriptor(Object object) {
		itemPropertyDescriptors.add(createItemPropertyDescriptor(
				((ComposeableAdapterFactory) adapterFactory)
						.getRootAdapterFactory(), getResourceLocator(),
				getString("_UI_Submodule_type_feature"), getString(
						"_UI_PropertyDescriptor_description",
						"_UI_Submodule_type_feature", "_UI_Submodule_type"),
				Ned2Package.Literals.SUBMODULE__TYPE, true,
				ItemPropertyDescriptor.GENERIC_VALUE_IMAGE, null, null));
	}

	/**
	 * This adds a property descriptor for the Vector Size feature.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected void addVectorSizePropertyDescriptor(Object object) {
		itemPropertyDescriptors.add(createItemPropertyDescriptor(
				((ComposeableAdapterFactory) adapterFactory)
						.getRootAdapterFactory(), getResourceLocator(),
				getString("_UI_Submodule_vectorSize_feature"), getString(
						"_UI_PropertyDescriptor_description",
						"_UI_Submodule_vectorSize_feature",
						"_UI_Submodule_type"),
				Ned2Package.Literals.SUBMODULE__VECTOR_SIZE, true,
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
			childrenFeatures.add(Ned2Package.Literals.SUBMODULE__WHITESPACE);
			childrenFeatures.add(Ned2Package.Literals.SUBMODULE__EXPRESSION);
			childrenFeatures.add(Ned2Package.Literals.SUBMODULE__PARAMETERS);
			childrenFeatures.add(Ned2Package.Literals.SUBMODULE__GATES);
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
	 * This returns Submodule.gif.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Object getImage(Object object) {
		return getResourceLocator().getImage("full/obj16/Submodule");
	}

	/**
	 * This returns the label text for the adapted class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public String getText(Object object) {
		String label = ((Submodule) object).getName();
		return label == null || label.length() == 0 ? getString("_UI_Submodule_type")
				: getString("_UI_Submodule_type") + " " + label;
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

		switch (notification.getFeatureID(Submodule.class)) {
		case Ned2Package.SUBMODULE__LIKE_PARAM:
		case Ned2Package.SUBMODULE__LIKE_TYPE:
		case Ned2Package.SUBMODULE__NAME:
		case Ned2Package.SUBMODULE__TYPE:
		case Ned2Package.SUBMODULE__VECTOR_SIZE:
			fireNotifyChanged(new ViewerNotification(notification, notification
					.getNotifier(), false, true));
			return;
		case Ned2Package.SUBMODULE__WHITESPACE:
		case Ned2Package.SUBMODULE__EXPRESSION:
		case Ned2Package.SUBMODULE__PARAMETERS:
		case Ned2Package.SUBMODULE__GATES:
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
				Ned2Package.Literals.SUBMODULE__WHITESPACE,
				Ned2Factory.eINSTANCE.createWhitespace()));

		newChildDescriptors.add(createChildParameter(
				Ned2Package.Literals.SUBMODULE__EXPRESSION,
				Ned2Factory.eINSTANCE.createExpression()));

		newChildDescriptors.add(createChildParameter(
				Ned2Package.Literals.SUBMODULE__PARAMETERS,
				Ned2Factory.eINSTANCE.createParameters()));

		newChildDescriptors.add(createChildParameter(
				Ned2Package.Literals.SUBMODULE__GATES, Ned2Factory.eINSTANCE
						.createGates()));
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
