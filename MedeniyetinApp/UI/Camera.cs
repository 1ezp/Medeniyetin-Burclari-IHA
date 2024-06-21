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
using System.Net.Http;
using MedeniyetinApp.Core;


namespace MedeniyetinApp.UI
{
    public partial class Camera : Form
    {
        
        private const float AspectRatio = 315f / 207f;

        int cam1Width = 1280;
        int cam1Height = 720;
        int cam2Width = 315;
        int cam2Height = 207;

        // Scaling factors
        private double scaleX;
        private double scaleY;

        String host;
        MJPEGStream stream;
        private Server server;
        private Point mouseLocation;
        bool isMax = false;
        
        public Camera(string host)
        {
            InitializeComponent();
            
            scaleX = (double)cam1Width / cam2Width;
            scaleY = (double)cam1Height / cam2Height;

            changeRes(host);
            this.host = host;
            server = new Server();
            String url = $"http://{host}:81/stream";
            stream = new MJPEGStream(url);
            stream.NewFrame += GetNewFrame;
        }

        void GetNewFrame(object sender, NewFrameEventArgs e)
        {
            Invoke((MethodInvoker)delegate
            {
                // Get the target data
                TargetInfo targetInfo = server.TargetData();

                // video data
                // HD
                Bitmap resizedBmp = new Bitmap((Bitmap)e.Frame.Clone(), panel2.Width, panel2.Height);

                double xScale = (double)resizedBmp.Width / cam2Width;
                double yScale = (double)resizedBmp.Height / cam2Height;

                double x = (xScale * targetInfo.x);
                double y = (yScale * targetInfo.y);

                // Target
                bmpX.Text = Convert.ToString(x);
                bmpY.Text = Convert.ToString(y);
                // bmp reslution
                pnlX.Text = Convert.ToString(resizedBmp.Width);
                pnlY.Text = Convert.ToString(resizedBmp.Height);


                DrawRedDot(resizedBmp, Convert.ToInt32(x), Convert.ToInt32(y), 80);
                cameraBox.Image = resizedBmp;
            });
        }
        void DrawRedDot(Bitmap bmp, int x, int y, int size)
        {
            if (x >= 0 && y >= 0 && x + size < bmp.Width && y + size < bmp.Height)
            {
                using (Graphics g = Graphics.FromImage(bmp))
                {
                    Pen borderPen = new Pen(Color.Blue, 2);
                    int topLeftX = x - (size / 2);
                    int topLeftY = y - (size / 2);
                    g.DrawRectangle(borderPen, topLeftX, topLeftY, size, size);
                }
            }
        }



        async void changeRes(string host)
        {

            string url = $"http://{host}/control?var=framesize&val=11";

            using (HttpClient client = new HttpClient())
            {
                try
                {
                    HttpResponseMessage response = await client.GetAsync(url);
                    response.EnsureSuccessStatusCode();

                }
                catch (HttpRequestException e)
                {   
                    Console.WriteLine("Request error: " + e.Message);
                }
            }
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
            if (e.Button == MouseButtons.Left)
            {
                Point mousePose = Control.MousePosition;
                mousePose.Offset(mouseLocation.X, mouseLocation.Y);
                Location = mousePose;
            }
        }

        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                mouseLocation = new Point(-e.X, -e.Y);
            }
        }
    }
}
