using System;
using System.ComponentModel;
using System.Windows.Forms;
using MedeniyetinApp.Core;

namespace MedeniyetinApp.UI
{
    public partial class Test : Form
    {

        
        API api = new API();
        public Test(String port)
        {
            InitializeComponent();
            

            BackgroundWorker updateWorker = new BackgroundWorker();
            updateWorker.WorkerSupportsCancellation = true;
            updateWorker.DoWork += UpdateTimer_Tick1;
            updateWorker.RunWorkerAsync();

        }


        private void UpdateTimer_Tick1(object sender, DoWorkEventArgs e)
        {
            while (true)
            {
                GPSInfo gpsInfo = api.IHAGps();

                Invoke((MethodInvoker)delegate
                {


                    lbTargetLat.Text = Convert.ToString(gpsInfo.Latitude);
                    lbTargetLng.Text = Convert.ToString(gpsInfo.Longitude);

                });
            }
            
        }
    }


    
}
