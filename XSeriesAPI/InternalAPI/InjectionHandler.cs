#region Imports

using System;
using System.Text;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.IO;
using System.Security.AccessControl;
using System.Security.Principal;
using System.Windows.Forms;

#endregion

namespace XSeriesAPI.InternalAPI
{
    internal class InjectionHandler
    {
        #region DllImport

        [DllImport("kernel32.dll")]
        static extern IntPtr OpenProcess(int dwDesiredAccess, bool bInheritHandle, int dwProcessId);

        [DllImport("kernel32.dll", CharSet = CharSet.Auto)]
        static extern IntPtr GetModuleHandle(string lpModuleName);

        [DllImport("kernel32", CharSet = CharSet.Ansi, ExactSpelling = true, SetLastError = true)]
        static extern IntPtr GetProcAddress(IntPtr hModule, string procName);

        [DllImport("kernel32.dll", SetLastError = true, ExactSpelling = true)]
        static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress, uint dwSize, uint flAllocationType, uint flProtect);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, uint nSize, out UIntPtr lpNumberOfBytesWritten);

        [DllImport("kernel32.dll")]
        static extern IntPtr CreateRemoteThread(IntPtr hProcess, IntPtr lpThreadAttributes, uint dwStackSize, IntPtr lpStartAddress, IntPtr lpParameter, uint dwCreationFlags, IntPtr lpThreadId);

        #endregion

        #region Access

        const int PROCESS_CREATE_THREAD = 0x2;
        const int PROCESS_QUERY_INFORMATION = 0x400;
        const int PROCESS_VM_OPERATION = 0x8;
        const int PROCESS_VM_WRITE = 0x20;
        const int PROCESS_VM_READ = 0x10;

        const uint MEM_COMMIT = 0x1000;
        const uint MEM_RESERVE = 0x2000;
        const uint PAGE_READWRITE = 4;

        #endregion

        public static void InjectDLL(string path)
        {
            string robloxC = "RobloxPlayerBeta";
            Process[] targetProcessIndex = Process.GetProcessesByName(robloxC);
            if (targetProcessIndex.Length > 0)
            {
                string pathv2 = Application.StartupPath + "\\" + path;
                applyAllApplicationPackages(pathv2);

                Process targetProcess = targetProcessIndex[0];
                IntPtr procHandle = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, false, targetProcess.Id);

                IntPtr loadLibraryAddr = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");

                IntPtr allocMemAddress = VirtualAllocEx(procHandle, IntPtr.Zero, (uint)((pathv2.Length + 1) * Marshal.SizeOf(typeof(char))), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

                UIntPtr bytesWritten; // ignore
                WriteProcessMemory(procHandle, allocMemAddress, Encoding.Default.GetBytes(pathv2), (uint)((pathv2.Length + 1) * Marshal.SizeOf(typeof(char))), out bytesWritten);
                CreateRemoteThread(procHandle, IntPtr.Zero, 0, loadLibraryAddr, allocMemAddress, 0, IntPtr.Zero);
            }
            else throw new Exception("Please check that roblox before attempting to inject DLL!");
        }

        public static void applyAllApplicationPackages(string path) // Dont think I need this for roblox due to its not UWP
        {
            FileInfo InfoFile = new FileInfo(path);
            FileSecurity fSecurity = InfoFile.GetAccessControl();
            fSecurity.AddAccessRule(new FileSystemAccessRule(new SecurityIdentifier("S-1-15-2-1"), FileSystemRights.FullControl, InheritanceFlags.None, PropagationFlags.NoPropagateInherit, AccessControlType.Allow));
            InfoFile.SetAccessControl(fSecurity);
        }
    }
}
