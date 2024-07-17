using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using MedeniyetinApp.Core;
using System.Threading;

namespace MedeniyetinApp.UI
{
    public partial class Login : Form
    {
        private Point mouseLocation;
        public Login()
        {
            InitializeComponent();
            PopulateSerialPortComboBox();

            

        }


        private void PopulateSerialPortComboBox()
        {
            cmbPorts.Items.Clear();
            string[] portNames = SerialPort.GetPortNames();
            foreach (string portName in portNames)
            {
                cmbPorts.Items.Add(portName);
                
            }

            if (cmbPorts.Items.Count > 0)
            {
                cmbPorts.SelectedIndex = 0;
            }
        }
        private void btnRefresh_Click(object sender, EventArgs e)
        {
            cmbPorts.Items.Clear();
            string[] portNames = SerialPort.GetPortNames();
            foreach (string portName in portNames)
            {
                cmbPorts.Items.Add(portName);

            }

            if (cmbPorts.Items.Count > 0)
            {
                cmbPorts.SelectedIndex = 0;
            }

        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }


        private void btnStart_Click(object sender, EventArgs e)
        {

            //Camera cameraFrm = new Camera(cameraIP.Text);
            Camera cameraFrm = new Camera("172.0.0.1");
            Main mainFrm = new Main();
            Map mapFrm = new Map(cmbPorts.Text);

            Screen[] screens = Screen.AllScreens;
            if (screens.Length > 2)
            {
                mapFrm.StartPosition = FormStartPosition.Manual;
                mapFrm.Location = screens[1].WorkingArea.Location;
                mapFrm.WindowState = FormWindowState.Maximized;
                mapFrm.Show();


                mainFrm.StartPosition = FormStartPosition.Manual;
                mainFrm.Location = Screen.AllScreens[0].Bounds.Location;
                mainFrm.WindowState = FormWindowState.Maximized;
                mainFrm.Show();

                cameraFrm.StartPosition = FormStartPosition.Manual;
                cameraFrm.Location = Screen.AllScreens[2].Bounds.Location;
                cameraFrm.WindowState = FormWindowState.Maximized;
                cameraFrm.Show();



            }

            
            this.Hide();
        }
        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                mouseLocation = new Point(-e.X, -e.Y);
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

        
    }
}
