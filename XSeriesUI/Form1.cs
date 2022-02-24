#region Imports

using System;
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

        private void guna2Button2_Click(object sender, EventArgs e)
        {
            api.ExecuteScript(guna2TextBox1.Text);
        }

        private void guna2Button1_Click(object sender, EventArgs e)
        {
            api.ExitRoblox();
        }

        private void guna2Button3_Click(object sender, EventArgs e)
        {
            guna2TextBox1.Clear();
        }

        private void guna2Button5_Click(object sender, EventArgs e)
        {
            bool injected = api.Attach();
            if (injected)
                InfoBox.Text = "Injected into process!";
            else InfoBox.Text = "Fatal error";
        }

        private void guna2Button4_Click(object sender, EventArgs e)
        {
            bool injected = api.Attach();
            if (injected)
                InfoBox.Text = "Injected into process!";
            else InfoBox.Text = "Fatal error";
        }
    }
}
