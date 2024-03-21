using System;
using System.ComponentModel;
using System.IO.Ports;
using System.Threading;
using System.Windows.Forms;

namespace MedeniyetinApp.Core
{
    public class IHAGps
    {
        private SerialPort serialPort;

        public IHAGps(string port)
        {
            try
            {
                serialPort = new SerialPort(port, 115200);
                serialPort.Open();


                BackgroundWorker updateWorker = new BackgroundWorker();
                updateWorker.WorkerSupportsCancellation = true;
                updateWorker.DoWork += UpdateWorker_DoWork;
                //updateWorker.RunWorkerAsync();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error initializing serial port: " + ex.Message);
                Application.Exit();
            }
        }

        private void UpdateWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            BackgroundWorker worker = sender as BackgroundWorker;

            while (true)
            {
                try
                {
                    if (serialPort.IsOpen)
                    {
                        serialPort.Close();
                    }
                    serialPort.Open();
                }catch (Exception) { }
                
                Thread.Sleep(5000);
            }
        }

        public void Reload(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                serialPort.Close();
            }
            serialPort.Open();

        }

        public double TargetLat()
        {
            try
            {
                string data = serialPort.ReadLine();
                serialPort.DiscardInBuffer();

                if (data == "-1")
                {
                    return -1.0;
                }
                string[] parts = data.Split(':');
                return Convert.ToDouble(parts[0]);
            }
            catch
            {
                return -1.0;
            }
        }

        public double TargetLng()
        {
            try
            {
                string data = serialPort.ReadLine();
                serialPort.DiscardInBuffer();
                if (data == "-1")
                {
                    return -1.0;
                }
                string[] parts = data.Split(':');
                return Convert.ToDouble(parts[1]);
            }
            catch
            {
                return -1.0;
            }
        }

        public string ReadData()
        {

            try
            {
                return serialPort.ReadLine();
            }
            catch
            {
                return "-1";
            }
        }
    }
}
