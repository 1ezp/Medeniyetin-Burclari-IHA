using MedeniyetinApp.Core;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
//using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;
using System.Windows.Media;



namespace MedeniyetinApp.UI
{
    public partial class Main : Form
    {
        private System.Drawing.Point mouseLocation;
        bool isMax = false;
        Server server = new Server();

        public Main()
        {
            InitializeComponent();

            //attitudeIndicator1.display_layer["Background"] = false;
            BackgroundWorker updateWorker = new BackgroundWorker();
            updateWorker.WorkerSupportsCancellation = true;
            updateWorker.DoWork += UpdateWorker_DoWork;
            updateWorker.RunWorkerAsync();

        }

        private void UpdateWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            BackgroundWorker worker = sender as BackgroundWorker;
            
            while (true)
            {
                VehicleInfo IHAInfo = server.IHA();
                try
                {
                    Invoke((MethodInvoker)delegate
                    {
                        GmotorSpeed.Value = (float)IHAInfo.motorSpeed;
                        LmotorSpeed.Text = Convert.ToString(IHAInfo.motorSpeed);

                        GgroundSpeed.Value = (float)IHAInfo.groundSpeed;
                        LgroundSpeed.Text = Convert.ToString(IHAInfo.groundSpeed);

                        GrelativeAlt.Value = (float)IHAInfo.relative_alt;
                        LrelativeAlt.Text = Convert.ToString(IHAInfo.relative_alt);
                        attitudeIndicatorInstrumentControl1.SetAttitudeIndicatorParameters(IHAInfo.pitch, IHAInfo.roll);

                        GbatteryVoltage.Value = (float)IHAInfo.batteryVoltage;
                        LBatteryVoltage.Text = Convert.ToString(IHAInfo.batteryVoltage);
                        
                        UpdateIHAMode((int)IHAInfo.MODE);
                        UpdateIHAGPS(IHAInfo.Latitude, IHAInfo.Longitude);
                    });
                }
                catch { }
            }   
        }

        private void UpdateIHAMode(int Mode)
        {
            switch (Mode)
            {
                case 1:
                    ModePixhawk.ForeColor = System.Drawing.Color.Lime;
                    ModePixhawk.Font = new Font(ModePixhawk.Font, FontStyle.Bold);
                    ModePID.ForeColor = System.Drawing.Color.Silver;
                    ModeOFF.ForeColor = System.Drawing.Color.Silver;
                    break;
                case 2:
                    ModePID.ForeColor = System.Drawing.Color.Lime;
                    ModePID.Font = new Font(ModePID.Font, FontStyle.Bold);
                    ModePixhawk.ForeColor= System.Drawing.Color.Silver;
                    ModeOFF.ForeColor= System.Drawing.Color.Silver;
                    break;
                case 3:
                    ModeOFF.ForeColor = System.Drawing.Color.Red;
                    ModeOFF.Font = new Font(ModeOFF.Font, FontStyle.Bold);
                    ModePixhawk.ForeColor = System.Drawing.Color.Silver;
                    ModePID.ForeColor = System.Drawing.Color.Silver;
                    break;
            }
        }

        private void UpdateIHAGPS(double Lat,Double Long)
        {
            LIhaLat.Text = Lat.ToString();
            LIhaLong.Text = Long.ToString();
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
                if (WindowState == FormWindowState.Maximized)
                {
                    WindowState = FormWindowState.Normal;
                    isMax = false;
                }
                System.Drawing.Point mousePose = Control.MousePosition;
                mousePose.Offset(mouseLocation.X, mouseLocation.Y);
                Location = mousePose;
            }
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            server.sendArmming("1:0");
        }


        private void button1_Click(object sender, EventArgs e)
        {
            server.sendArmming("1:1");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            server.sendArmming("0:0");
        }

        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                mouseLocation = new System.Drawing.Point(-e.X, -e.Y);
            }
        }

        private void gaugePanel_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                mouseLocation = e.Location;
            }
        }

        private void gaugePanel_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                var dx = e.X - mouseLocation.X;
                var dy = e.Y - mouseLocation.Y;

                gaugePanel.Size = new Size(gaugePanel.Width + dx, gaugePanel.Height + dy);
                mouseLocation = e.Location;
                this.Cursor = Cursors.SizeWE;
            }
        }

        private void gaugePanel_MouseUp(object sender, MouseEventArgs e)
        {
            this.Cursor = Cursors.Default;
        }

        private void gaugePanel_Paint(object sender, PaintEventArgs e)
        {

        }

        
    }
}
