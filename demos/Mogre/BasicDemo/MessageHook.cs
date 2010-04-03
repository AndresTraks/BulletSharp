using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace BasicDemo
{
    class MessageHook : IDisposable
    {
        public event EventHandler MessageReceived;

        public Message LastMessage
        {
            get;
            private set;
        }

        IntPtr HookHandle;
        GetMsgProc getMsgProc;


        // The messages we're interested in
        const int WM_KEYDOWN = 0x100;
        const int WM_KEYUP = 0x101;
        const int WM_CHAR = 0x102;

        const int WH_GETMESSAGE = 3;


        delegate int GetMsgProc(int nCode, int wParam, ref Message msg);

        [DllImport("user32.dll", EntryPoint = "SetWindowsHookExA")]
        static extern IntPtr SetWindowsHookEx(int idHook, GetMsgProc lpfn, IntPtr hmod, int dwThreadId);
        [DllImport("user32.dll")]
        public static extern int UnhookWindowsHookEx(IntPtr hHook);
        [DllImport("user32.dll")]
        public static extern int CallNextHookEx(int hHook, int ncode, int wParam, ref Message lParam);
        [DllImport("kernel32.dll")]
        public static extern int GetCurrentThreadId();


        public MessageHook(IntPtr whnd)
        {
            // Need to keep this reference to avoid crashing
            getMsgProc = new GetMsgProc(ProcessMessages);

            // Create the keyboard hook
            HookHandle = SetWindowsHookEx(WH_GETMESSAGE, getMsgProc, IntPtr.Zero, GetCurrentThreadId());
        }

        public void Dispose()
        {
            // Remove the hook
            if (HookHandle != IntPtr.Zero)
                UnhookWindowsHookEx(this.HookHandle);
        }

        private int ProcessMessages(int nCode, int wParam, ref Message msg)
        {
            // Check if we must process this message (and whether it has been retrieved via GetMessage)
            if (nCode == 0 && wParam == 1)
            {
                // If it's one of the keyboard-related messages, raise an event for it
                switch (msg.Msg)
                {
                    case WM_CHAR:
                    case WM_KEYDOWN:
                    case WM_KEYUP:
                        LastMessage = msg;
                        if (MessageReceived != null)
                            MessageReceived(this, EventArgs.Empty);
                        break;
                }
            }

            // Call next hook in chain:
            return CallNextHookEx(0, nCode, wParam, ref msg);
        }
    }
}
