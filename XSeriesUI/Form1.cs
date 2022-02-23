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

        private void button4_Click(object sender, EventArgs e) //attach
        {
            bool injected = api.Attach();
            if (injected)
                InfoBox.Text = "Injected into process!";
            else InfoBox.Text = "Fatal error";
        }

        private void button5_Click(object sender, EventArgs e) //reattach
        {
             // fuck this
        }

        private void button2_Click(object sender, EventArgs e) //clear
        {
            textBox1.Clear();
        }

        private void button3_Click(object sender, EventArgs e) // restart
        {
            api.ExitRoblox();
        }

        private void button1_Click(object sender, EventArgs e) // execute
        {
            api.ExecuteScript(textBox1.Text);
        }
    }
}
