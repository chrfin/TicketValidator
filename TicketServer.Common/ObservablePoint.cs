using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Windows;

namespace TicketServer.Common
{
	/// <summary>
	/// Implementation of <see cref="P:System.Windows.Point"/> which implements <see cref="P:System.ComponentModel.INotifyPropertyChanged"/>.
	/// </summary>
	public class ObservablePoint<Tx, Ty> : INotifyPropertyChanged
	{
		private Tx x;
		private Ty y;

		/// <summary>
		/// Gets or sets the X value.
		/// </summary>
		/// <value>
		/// The X.
		/// </value>
		public Tx X
		{
			get { return x; }
			set
			{
				x = value;
				if (PropertyChanged != null)
					PropertyChanged(this, new PropertyChangedEventArgs("X"));
			}
		}

		/// <summary>
		/// Gets or sets the Y value.
		/// </summary>
		/// <value>
		/// The Y.
		/// </value>
		public Ty Y
		{
			get { return y; }
			set
			{
				y = value;
				if (PropertyChanged != null)
					PropertyChanged(this, new PropertyChangedEventArgs("Y"));
			}
		}

		/// <summary>
		/// Initializes a new instance of the <see cref="ObservablePoint"/> class.
		/// </summary>
		public ObservablePoint() { }

		/// <summary>
		/// Initializes a new instance of the <see cref="ObservablePoint"/> class.
		/// </summary>
		/// <param name="x">The x value.</param>
		/// <param name="y">The y value.</param>
		public ObservablePoint(Tx x, Ty y)
		{
			X = x;
			Y = y;
		}

		#region INotifyPropertyChanged Members

		public event PropertyChangedEventHandler PropertyChanged;

		#endregion
	}
}
