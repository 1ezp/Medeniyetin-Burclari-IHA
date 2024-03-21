using System;
using System.ComponentModel;
using System.Windows.Forms;
using MedeniyetinApp.Core;

namespace MedeniyetinApp.UI
{
    public partial class Test : Form
    {
        private IHAGps gpsData;

        public Test(String port)
        {
            InitializeComponent();
            gpsData = new IHAGps(port);
            //Timer updateTimer = new Timer();
            //updateTimer.Interval = 100;
            //updateTimer.Tick += UpdateTimer_Tick1;
            //updateTimer.Start();

            BackgroundWorker updateWorker = new BackgroundWorker();
            updateWorker.WorkerSupportsCancellation = true;
            updateWorker.DoWork += UpdateTimer_Tick1;
            updateWorker.RunWorkerAsync();

        }
        private void UpdateTimer_Tick(object sender, EventArgs e)
        {
            Invoke((MethodInvoker)delegate
            {
                String data = gpsData.ReadData();
                richTextBox.SelectedText = data;
            });
        }

        private void UpdateTimer_Tick1(object sender, DoWorkEventArgs e)
        {
                    double lng = gpsData.TargetLng();
                    double lat = gpsData.TargetLat();
            while (true)
            {

                Invoke((MethodInvoker)delegate
                {


                    lbTargetLat.Text = Convert.ToString(lat);
                    lbTargetLng.Text = Convert.ToString(lng);

                });
            }
        }

        private void serialPort1_ErrorReceived(object sender, System.IO.Ports.SerialErrorReceivedEventArgs e)
        {

        }

        private void serialPort1_PinChanged(object sender, System.IO.Ports.SerialPinChangedEventArgs e)
        {

        }
    }
}
