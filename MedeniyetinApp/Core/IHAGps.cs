using System;
using System.ComponentModel;
using System.IO.Ports;
using System.Runtime.CompilerServices;
using System.Threading;
using System.Windows.Forms;

namespace MedeniyetinApp.Core
{
    public class IHAGps
    {
        private SerialPort serialPort;
        float _IHALat;
        float _IHALong;

        public float IHALat
        {
            get { return _IHALat; }
            set { _IHALat = value; }
        }
        public float IHALong
        {
            get { return _IHALong; }
            set { _IHALong = value; }
        }

        public IHAGps(string port)
        {
            try
            {
                serialPort = new SerialPort(port, 115200);
                serialPort.Open();
                serialPort.DataReceived += SerialPort_DataReceived;

            }
            catch (Exception ex)
            {
                MessageBox.Show("Error initializing serial port: " + ex.Message);
                Application.Exit();
            }
        }
        private void SerialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort serialPort = (SerialPort)sender;
            string data = serialPort.ReadLine();
            string[] values = data.Split(',');

            _IHALat = float.Parse(values[0]);
            _IHALat = float.Parse(values[1]);

        }


    }
}
