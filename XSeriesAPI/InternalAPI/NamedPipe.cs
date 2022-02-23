#region Imports

using System;
using System.IO;
using System.Text;
using System.IO.Pipes;
using System.Threading.Tasks;
using System.Collections.Generic;
using System.Runtime.InteropServices;

#endregion

namespace XSeriesAPI.InternalAPI
{
    internal class NamedPipe
    {
        #region DLLImports

        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool WaitNamedPipe(string name, int timeout);

        #endregion

        public static bool PipeExists(string pn)
        {
            bool output = false;

            try
            {
                bool skip = false;
                if (!WaitNamedPipe($"\\\\.\\pipe\\{pn}", 0 ))
                {
                    int err = Marshal.GetLastWin32Error();
                    if (err == 0 || err == 2)
                        skip = true;
                }
                if (!skip)
                    output = true;
            }
            catch { } // ignore

            return output;
        }

        private static List<String> pipeData = new List<String>(); // String looks better here ngl
        public static bool SendPacket(string pipeName, string command, string data)
        {
            bool output = false;

            pipeData.Clear();
            if (PipeExists(pipeName))
            {
                Task.Factory.StartNew(() =>
                {
                    try
                    {
                        using (NamedPipeClientStream pipe = new NamedPipeClientStream(".", pipeName, PipeDirection.Out))
                        {
                            pipe.Connect();
                            using (StreamWriter sw = new StreamWriter(pipe, Encoding.Default, 0xF4240)) // 1 megabyte
                            {
                                uint id = 0;
                                switch (command)
                                {
                                    case "Script":
                                        id = 1;
                                        break;
                                    default:
                                        id = uint.MaxValue; // -1
                                        break;
                                }
                                sw.Write(id + "█" + data);

                                output = true;
                            }
                        }
                    }
                    catch { } //TODO: Send error to pipeserver
                }).Start();
            }

            return output;
        }
    }
}
