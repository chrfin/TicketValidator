/** 
 * Got from http://www.assembla.com/code/AGB/subversion/nodes/AGB/AsyncHelper.cs
 * Based on AsyncHelper by Mike Woodring of http://staff.develop.com/woodring//
 * Use FireAndForget to execute a method in the thread pool without having to
 * call EndInvoke. Note that the delegate passed to FireAndForget can only have a
 * single Target.
 * 
 * AsyncHelper.FireAndForget(new MyHandler(MyMethod), methodArg1, methodArg2, etc);
 * 
 * To Fire an Event asynchronously (with each of the targets being called on its own thread
 * use FireAsync:
 * AsyncHelper.FireAsync(MyEvent, eventArg1, eventArg2, ...);
 * FireAsync is designed to be called on an event containing zero, one or more Targets.
 * Your FireEvent method does not need to check for null FireAsync will do it correctly even in a
 * multithreaded environment
 * */
using System;
using System.Threading;

namespace TicketServer.Common
{

	public class AsyncHelper
	{
		#region Private Types
		/// <summary>
		/// Private class holds data for a delegate to be run on the thread pool
		/// </summary>
		private class Target
		{
			#region Private Fields
			private readonly Delegate TargetDelegate;
			private readonly object[] Args;
			#endregion

			#region Constructor
			/// <summary>
			/// Creates a new <see cref="Target"/> instance this holds arguments and contains
			/// the method ExecuteDelegate to be called on the threadpool.
			/// </summary>
			/// <param name="d">The users delegate to fire</param>
			/// <param name="args">The users arguments to the delegate</param>
			public Target(Delegate d, object[] args)
			{
				TargetDelegate = d;
				Args = args;
			}
			#endregion

			#region Invoker
			/// <summary>
			/// Executes the delegate by calling DynamicInvoke.
			/// </summary>
			/// <param name="o">This parameter is required by the threadpool but is unused.</param>
			public void ExecuteDelegate(object o)
			{
				TargetDelegate.DynamicInvoke(Args);
			}
			#endregion
		}
		#endregion

		#region Public Static Methods
		/// <summary>
		/// Fires the delegate without any need to call EndInvoke.
		/// </summary>
		/// <param name="d">Target Delegate - must contain only one Target method</param>
		/// <param name="args">Users arguments.</param>
		private static void FireAndForget(Delegate d, params object[] args)
		{
			Target target = new Target(d, args);
			ThreadPool.QueueUserWorkItem(target.ExecuteDelegate);
		}

		/// <summary>
		/// Fires each of the members in the delegate asynchronously. All the members
		/// will be fired even if one of them fires an exception
		/// </summary>
		/// <param name="del">The delegate we want to fire</param>
		/// <param name="args">Each of the args we want to fire.</param>
		public static void FireAsync(Delegate del, params object[] args)
		{
			// copy the delegate to ensure that we can test for null in a thread
			// safe manner.
			Delegate temp = del;
			if (temp != null)
			{
				Delegate[] delegates = temp.GetInvocationList();
				foreach (Delegate receiver in delegates)
				{
					FireAndForget(receiver, args);
				}
			}
		}
		#endregion
	}
}