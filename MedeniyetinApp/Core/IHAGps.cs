using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using MedeniyetinApp.UI;
using System.Windows.Forms;
using System.Threading;

namespace MedeniyetinApp.Core
{
    public class IHAGps
    {
        public String Lat;
        public String Lng;
        static SerialPort serialPort;


        public IHAGps(String port)
        {
            try
            {
                serialPort = new SerialPort(port, 115200);
                serialPort.Open();
                //serialPort.DataReceived += SerialPortDataReceived;
                //new Thread(SerialPortDataReceived).Start();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error initializing serial port: " + ex.Message);
                return;
            }

        }
        private void SerialPortDataReceived()
        {
            string data = serialPort.ReadLine();
            if (!string.IsNullOrEmpty(data))
            {
                string[] parts = data.Split(':');
                if (parts.Length >= 2)
                {
                    Lat = parts[0];
                    Lng = parts[1];
                }
            }
        }

        public String TargetLat()
        {
            string data = serialPort.ReadLine();
            string[] parts = data.Split(':');
            if (parts.Length >= 2)
            {
                String latitude = parts[0];

                // Successfully parsed latitude as a double
                return latitude;
            }
            return "";
        }
        public String TargetLng()
        {
            string data = serialPort.ReadLine();
            string[] parts = data.Split(':');
            if (parts.Length >= 2)
            {
                String lng = parts[1];

                // Successfully parsed latitude as a double
                return lng;
            }
            return "";
        }
    }
}
