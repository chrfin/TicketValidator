using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media;
using System.Security;

namespace TicketServer.Common
{
	/// <summary>
	/// Container for several helper methods
	/// </summary>
	public static class Helper
	{
		/// <summary>
		/// Got from http://weblogs.asp.net/jgalloway/archive/2008/04/13/encrypting-passwords-in-a-net-app-config-file.aspx
		/// </summary>
		static byte[] entropy = System.Text.Encoding.Unicode.GetBytes("butzvarruckt");

		/// <summary>
		/// Encrypts the string.
		/// </summary>
		/// <param name="input">The input.</param>
		/// <returns></returns>
		public static string EncryptString(System.Security.SecureString input)
		{
			byte[] encryptedData = System.Security.Cryptography.ProtectedData.Protect(
				System.Text.Encoding.Unicode.GetBytes(ToInsecureString(input)),
				entropy,
				System.Security.Cryptography.DataProtectionScope.CurrentUser);
			return Convert.ToBase64String(encryptedData);
		}

		/// <summary>
		/// Decrypts the string.
		/// </summary>
		/// <param name="encryptedData">The encrypted data.</param>
		/// <returns></returns>
		public static SecureString DecryptString(string encryptedData)
		{
			try
			{
				byte[] decryptedData = System.Security.Cryptography.ProtectedData.Unprotect(
					Convert.FromBase64String(encryptedData),
					entropy,
					System.Security.Cryptography.DataProtectionScope.CurrentUser);
				return ToSecureString(System.Text.Encoding.Unicode.GetString(decryptedData));
			}
			catch
			{
				return new SecureString();
			}
		}

		/// <summary>
		/// Toes the secure string.
		/// </summary>
		/// <param name="input">The input.</param>
		/// <returns></returns>
		public static SecureString ToSecureString(string input)
		{
			SecureString secure = new SecureString();
			foreach (char c in input)
			{
				secure.AppendChar(c);
			}
			secure.MakeReadOnly();
			return secure;
		}

		/// <summary>
		/// Toes the insecure string.
		/// </summary>
		/// <param name="input">The input.</param>
		/// <returns></returns>
		public static string ToInsecureString(SecureString input)
		{
			string returnValue = string.Empty;
			IntPtr ptr = System.Runtime.InteropServices.Marshal.SecureStringToBSTR(input);
			try
			{
				returnValue = System.Runtime.InteropServices.Marshal.PtrToStringBSTR(ptr);
			}
			finally
			{
				System.Runtime.InteropServices.Marshal.ZeroFreeBSTR(ptr);
			}
			return returnValue;
		}
	}
}
