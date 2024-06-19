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
        // 315, 207
        private const float AspectRatio = 315f / 207f;
        String host;
        MJPEGStream stream;
        private Server server;
        private Point mouseLocation;
        bool isMax = false;
        public Camera(string host)
        {
            InitializeComponent();
            this.Resize +=  AdjustCameraBoxSize;
            this.host = host;
            server = new Server();
            changeRes();
            String url = $"http://{host}:81/stream";
            stream = new MJPEGStream(url);
            stream.NewFrame += GetNewFrame;
        }

        void GetNewFrame(object sender, NewFrameEventArgs e)
        {
            Invoke((MethodInvoker)delegate
            {
                TargetInfo targetInfo = server.TargetData();

                Bitmap bmp = (Bitmap)e.Frame.Clone();
                Bitmap resizedBmp = new Bitmap(bmp, panel2.Width, panel2.Height);

                double xScale = (double)panel2.Width / 315.0;
                double yScale = (double)panel2.Height / 207.0;

                double x = xScale * targetInfo.x - 25;
                double y = yScale * targetInfo.y - 25;

                bmpX.Text = Convert.ToString(x);
                bmpY.Text = Convert.ToString(y);

                DrawRedDot(resizedBmp, Convert.ToInt32(x), Convert.ToInt32(y), 50);
                cameraBox.Image = resizedBmp;
            });
        }
        void DrawRedDot(Bitmap bmp, int x, int y, int size)
        {
            if (x >= 0 && y >= 0 && x + size < bmp.Width && y + size < bmp.Height)
            {
                using (Graphics g = Graphics.FromImage(bmp))
                {
                    Pen borderPen = new Pen(Color.Red, 2);
                    g.DrawRectangle(borderPen, x, y, size, size);
                }
            }
        }

        private void AdjustCameraBoxSize(object sender, EventArgs e)
        {
            int newWidth, newHeight;
            if (this.ClientSize.Width / (float)this.ClientSize.Height > AspectRatio)
            {
                    
                newHeight = this.ClientSize.Height;
                newWidth = (int)(newHeight * AspectRatio);
            }
            else
            {
                newWidth = this.ClientSize.Width;
                newHeight = (int)(newWidth / AspectRatio);
            }
            cameraBox.Size = new Size(newWidth, newHeight);
            cameraBox.Location = new Point((this.ClientSize.Width - newWidth) / 2, (this.ClientSize.Height - newHeight) / 2);
        }

        void changeRes()
        {

            using (HttpClient client = new HttpClient())
            {
                try
                {
                    client.DefaultRequestHeaders.Add("Accept", "*/*");
                    client.DefaultRequestHeaders.Add("Accept-Language", "en-US,en;q=0.9,ar-AE;q=0.8,ar;q=0.7");
                    client.DefaultRequestHeaders.Add("Connection", "keep-alive");
                    client.DefaultRequestHeaders.Add("DNT", "1");
                    client.DefaultRequestHeaders.Add("Referer", $"http://{host}/");
                    client.DefaultRequestHeaders.Add("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/122.0.0.0 Safari/537.36");
                    string url = $"http://{host}/control?var=framesize&val=13";
                    HttpResponseMessage response = client.GetAsync(url).Result;
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Error: " + ex.Message);
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
