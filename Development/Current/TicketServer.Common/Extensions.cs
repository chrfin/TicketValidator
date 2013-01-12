using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.ComponentModel;
using System.Windows.Markup;
using System.Windows;
using System.Windows.Data;
using System.Windows.Media;

namespace TicketServer.Common
{
	/// <summary>
	/// Markup extension that provides a list of the members of a given enum. 
	/// </summary>
	/// <remarks>
	/// Based on http://agsmith.wordpress.com/2008/09/19/accessing-enum-members-in-xaml/
	/// </remarks>
	public class EnumListExtension : MarkupExtension
	{
		#region Member Variables
 

		private Type _enumType;
		private bool _asString;
 

		#endregion //Member Variables
 

		#region Constructor
		/// <summary>
		/// Initializes a new <see cref=”EnumListExtension”/>
		/// </summary>
		public EnumListExtension()
		{
		}
 

		/// <summary>
		/// Initializes a new <see cref=”EnumListExtension”/>
		/// </summary>
		/// <param name=”enumType”>The type of enum whose members are to be returned.</param>
		public EnumListExtension(Type enumType)
		{
			this.EnumType = enumType;
		}
		#endregion //Constructor
 

		#region Properties
		/// <summary>
		/// Gets/sets the type of enumeration to return
		/// </summary>
		public Type EnumType
		{
			get { return this._enumType; }
			set
			{
				if (value != this._enumType)
				{
					if (null != value)
					{
						Type enumType = Nullable.GetUnderlyingType(value) ?? value;
 

						if (enumType.IsEnum == false)
							throw new ArgumentException("Type must be for an Enum.");
					}
 

					this._enumType = value;
				}
			}
		}
 

		/// <summary>
		/// Gets/sets a value indicating whether to display the enumeration members as strings using the Description on the member if available.
		/// </summary>
		public bool AsString
		{
			get { return this._asString; }
			set { this._asString = value; }
		}
		#endregion //Properties
 

		#region Base class overrides
		/// <summary>
		/// Returns a list of items for the specified <see cref=”EnumType”/>. Depending on the <see cref=”AsString”/> property, the
		/// items will be returned as the enum member value or as strings.
		/// </summary>
		/// <param name=”serviceProvider”>An object that provides services for the markup extension.</param>
		/// <returns></returns>
		public override object ProvideValue(IServiceProvider serviceProvider)
		{
			if (null == this._enumType)
				throw new InvalidOperationException("The EnumType must be specified.");
 

			Type actualEnumType = Nullable.GetUnderlyingType(this._enumType) ?? this._enumType;
			Array enumValues = Enum.GetValues(actualEnumType);
 

			// if the object itself is to be returned then just use GetValues
			//
			if (this._asString == false)
			{
				if (actualEnumType == this._enumType)
					return enumValues;
 

				Array tempArray = Array.CreateInstance(actualEnumType, enumValues.Length + 1);
				enumValues.CopyTo(tempArray, 1);
				return tempArray;
			}
 

			List<string> items = new List<string>();
 

			if (actualEnumType != this._enumType)
				items.Add(null);
 

			// otherwise we must process the list
			foreach (object item in Enum.GetValues(this._enumType))
			{
				string itemString = item.ToString();
				FieldInfo field = this._enumType.GetField(itemString);
				object[] attribs = field.GetCustomAttributes(typeof(DescriptionAttribute), false);
 

				if (null != attribs && attribs.Length > 0)
					itemString = ((DescriptionAttribute)attribs[0]).Description;
 

				items.Add(itemString);
			}
 

			return items.ToArray();
		}
		#endregion //Base class overrides
	}

	public static class CommonExtensions
	{
		/// <summary>
		/// Finds the visual child.
		/// </summary>
		/// <typeparam name="childItem">The type of the hild item.</typeparam>
		/// <param name="obj">The obj.</param>
		/// <returns></returns>
		/// <remarks>http://blogs.msdn.com/b/wpfsdk/archive/2007/04/16/how-do-i-programmatically-interact-with-template-generated-elements-part-ii.aspx</remarks>
		public static childItem FindVisualChild<childItem>(this DependencyObject obj) where childItem : DependencyObject
		{
			for (int i = 0; i < VisualTreeHelper.GetChildrenCount(obj); i++)
			{
				DependencyObject child = VisualTreeHelper.GetChild(obj, i);
				if (child != null && child is childItem)
					return (childItem)child;
				else
				{
					childItem childOfChild = FindVisualChild<childItem>(child);
					if (childOfChild != null)
						return childOfChild;
				}
			}
			return null;
		}

		/// <summary>
		/// Updates all binding targets.
		/// </summary>
		/// <param name="obj">The obj.</param>
		/// <remarks>http://stackoverflow.com/questions/5150983/how-to-invoke-updatesource-for-all-bindings-on-the-form</remarks>
		public static void UpdateAllBindingTargets(this DependencyObject obj)
		{
			foreach (var binding in obj.GetAllBindings().Where(b => b != null))
				binding.UpdateTarget();
		}

		/// <summary>
		/// Updates all binding sources.
		/// </summary>
		/// <param name="obj">The obj.</param>
		/// <remarks>http://stackoverflow.com/questions/5150983/how-to-invoke-updatesource-for-all-bindings-on-the-form</remarks>
		public static void UpdateAllBindingSources(this DependencyObject obj)
		{
			foreach (var binding in obj.GetAllBindings().Where(b => b != null))
				binding.UpdateSource();
		}

		/// <summary>
		/// Gets all bindings.
		/// </summary>
		/// <param name="obj">The obj.</param>
		/// <returns></returns>
		/// <remarks>http://stackoverflow.com/questions/5150983/how-to-invoke-updatesource-for-all-bindings-on-the-form</remarks>
		public static IEnumerable<BindingExpression> GetAllBindings(this DependencyObject obj)
		{
			var stack = new Stack<DependencyObject>();

			stack.Push(obj);

			while (stack.Count > 0)
			{
				var cur = stack.Pop();
				var lve = cur.GetLocalValueEnumerator();

				while (lve.MoveNext())
					if (BindingOperations.IsDataBound(cur, lve.Current.Property))
						yield return lve.Current.Value as BindingExpression;

				int count = VisualTreeHelper.GetChildrenCount(cur);
				for (int i = 0; i < count; ++i)
				{
					var child = VisualTreeHelper.GetChild(cur, i);
					if (child is FrameworkElement)
						stack.Push(child);
				}
			}
		}
	}
}
