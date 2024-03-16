using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MedeniyetinApp.UI
{
    public partial class Login : Form
    {
        private Point mouseLocation;
        public Login()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                mouseLocation = new Point(-e.X, -e.Y);
            }
        }

        private void panel1_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                Point mousePose = Control.MousePosition;
                mousePose.Offset(mouseLocation.X, mouseLocation.Y);
                Location = mousePose;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Camera cameraFrm = new Camera(cameraIP.Text);
            Map mapFrm = new Map();
            cameraFrm.Show();
            //mapFrm.Show();  
            this.Hide();
        }
    }
}
