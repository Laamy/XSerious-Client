#region Imports

using System;
using System.Drawing;
using System.Windows.Forms;

using XSeriesAPI;

#endregion

namespace XSeriesUI
{
    public partial class Form1 : Form
    {
        ExploitAPI api = new ExploitAPI();
        public Form1()
        {
            InitializeComponent();
        }

        private void guna2Button2_Click_1(object sender, EventArgs e)
        {
            api.ExecuteScript(guna2TextBox1.Text);
        }

        private void guna2Button1_Click_1(object sender, EventArgs e)
        {
            api.ExitRoblox();
        }

        private void guna2Button3_Click_1(object sender, EventArgs e)
        {
            guna2TextBox1.Clear();
        }

        private void guna2Button5_Click_1(object sender, EventArgs e)
        {
            bool injected = api.Attach();
            if (injected)
                InfoBox.Text = "Injected into process!";
            else InfoBox.Text = "Fatal error";
        }

        private void guna2Button4_Click_1(object sender, EventArgs e)
        {
            bool injected = api.Attach();
            if (injected)
                InfoBox.Text = "Injected into process!";
            else InfoBox.Text = "Fatal error";
        }

        Point pos;
        private void guna2Panel1_MouseDown(object sender, MouseEventArgs e)
        {
            switch (e.Button)
            {
                case MouseButtons.Left:
                    pos = e.Location;
                    break;
            }
        }

        private void guna2Panel1_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Left) return;
            Left = e.X + Left - pos.X;
            Top = e.Y + Top - pos.Y;
        }

        private void guna2Button6_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void guna2Button7_Click(object sender, EventArgs e)
        {
            switch (WindowState)
            {
                case FormWindowState.Maximized:
                    WindowState = FormWindowState.Normal;
                    guna2Button7.Text = "[ ]";
                    break;
                case FormWindowState.Normal:
                    WindowState = FormWindowState.Maximized;
                    guna2Button7.Text = "[]";
                    break;
            }
        }

        private void guna2Button8_Click(object sender, EventArgs e)
        {
            WindowState = FormWindowState.Minimized;
        }
    }
}
