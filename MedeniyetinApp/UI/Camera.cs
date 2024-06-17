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


namespace MedeniyetinApp.UI
{
    public partial class Camera : Form
    {

        
        String host;
        MJPEGStream stream;

        private Point mouseLocation;
        bool isMax = false;

        public Camera(string host)
        {
            InitializeComponent();
            this.host = host;
            changeRes();
            String url = $"http://{host}:81/stream";
            stream = new MJPEGStream(url);
            stream.NewFrame += GetNewFrame;
        }

        void GetNewFrame(object sender, NewFrameEventArgs e)
        {
            
            Invoke((MethodInvoker)delegate
            {
            
                pnlX.Text = panel2.Height.ToString();
                pnlY.Text = panel2.Width.ToString();
                Bitmap bmp = (Bitmap)e.Frame.Clone();



                double x =  (Convert.ToDouble(panel2.Height) / 360.0 * 180.0) - 25;
                double y = (Convert.ToDouble(panel2.Width) / 240.0 * 120.0) - 25;

                bmpX.Text = Convert.ToString(x);
                bmpY.Text = Convert.ToString(y);

                DrawRedDot(bmp, Convert.ToInt32(y), Convert.ToInt32(x), 50);
                cameraBox.Image = bmp;
            
            
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
