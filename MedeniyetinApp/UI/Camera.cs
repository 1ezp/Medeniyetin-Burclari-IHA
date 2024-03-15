using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MedeniyetinApp.UI;
using AForge.Video;
using AForge.Video.DirectShow;


namespace MedeniyetinApp.UI
{
    public partial class Camera : Form
    {

        Login loginfrm;
        MJPEGStream stream;

        private Point mouseLocation;
        bool isMax = false;

        public Camera(Login loginfrm)
        {
            InitializeComponent();
            this.loginfrm = loginfrm;

            String url = $"http://{loginfrm.cameraIP.Text}:81/stream";
            stream = new MJPEGStream(url);
            stream.NewFrame += GetNewFrame;
        }

        void GetNewFrame(object sender, NewFrameEventArgs e)
        {
            Bitmap bmp = (Bitmap)e.Frame.Clone();
            cameraBox.Image = bmp;
        }

        private void Camera_Load(object sender, EventArgs e)
        {
            stream.Start();
        }

        private void panel1_DoubleClick(object sender, EventArgs e)
        {
            if (isMax)
            {
                WindowState = FormWindowState.Normal;
                isMax = false;
            }
            else
            {
                WindowState = FormWindowState.Maximized;
                isMax = true;
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

        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                mouseLocation = new Point(-e.X, -e.Y);
            }
        }
    }
}
