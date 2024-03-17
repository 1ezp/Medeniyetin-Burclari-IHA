using System;
using System.Windows.Forms;
using MedeniyetinApp.Core;

namespace MedeniyetinApp.UI
{
    public partial class Test : Form
    {
        private IHAGps gpsData;

        public Test(String port)
        {
            gpsData = new IHAGps(port);
            InitializeComponent();
            Timer updateTimer = new Timer();
            updateTimer.Interval = 1000;
            updateTimer.Tick += UpdateTimer_Tick;
            updateTimer.Start();

        }
        private void UpdateTimer_Tick(object sender, EventArgs e)
        {
            string lat = gpsData.TargetLat();
            string lng = gpsData.TargetLng();

            if (lat != null && lng != null)
            {
                Invoke((MethodInvoker)delegate
                {
                    lbTargetLat.Text = Convert.ToString(lat) ;
                    lbTargetLng.Text = lng;
                });
            }
        }
    }
}
