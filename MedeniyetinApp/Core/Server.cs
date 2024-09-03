using System;
using System.Collections.Specialized;
using System.Net.Sockets;
using System.Text;
using Newtonsoft.Json;

namespace MedeniyetinApp.Core
{

    public class VehicleInfo
    {
        [JsonProperty("MODE")]
        public double MODE { get; set; }

        [JsonProperty("Lat")]
        public double Latitude { get; set; }

        [JsonProperty("Long")]
        public double Longitude { get; set; }

        [JsonProperty("motorSpeed")]
        public double motorSpeed { get; set; }

        [JsonProperty("groundSpeed")]
        public double groundSpeed { get; set; }

        [JsonProperty("roll")]
        public double roll { get; set; }

        [JsonProperty("pitch")]
        public double pitch { get; set; }

        [JsonProperty("relative_alt")]
        public double relative_alt { get; set; }

        [JsonProperty("batteryVoltage")]
        public double batteryVoltage { get; set; }
    }

    public class TargetInfo
    {
        [JsonProperty("x")]
        public double x { get; set; }

        [JsonProperty("y")]
        public double y { get; set; }
    }

    public class Motor
    {
        [JsonProperty("value")]
        public double value { get; set; }

    }

    public class Server 
    {
        private readonly TcpClient client;
        private readonly NetworkStream stream;
        private static readonly string ip = "127.0.0.1";
        private static readonly int port = 12345;

        public Server()
        {
            client = new TcpClient(ip, port);
            stream = client.GetStream();
        }

        public VehicleInfo IHA()
        {
            try
            {
                string request = "IHA";
                byte[] requestData = Encoding.UTF8.GetBytes(request);
                stream.Write(requestData, 0, requestData.Length);

                byte[] buffer = new byte[1024];
                int bytesRead = stream.Read(buffer, 0, buffer.Length);
                string message = Encoding.UTF8.GetString(buffer, 0, bytesRead);
                VehicleInfo VehicleInfo = JsonConvert.DeserializeObject<VehicleInfo>(message);
                return VehicleInfo;
            }
            catch (SocketException se)
            {
                Console.WriteLine($"SocketException: {se.Message}");
                return null;
            }
            catch (Exception e)
            {
                Console.WriteLine($"An error occurred: {e.Message}");
                return null;
            }
        }
        public VehicleInfo IKAGps()
        {
            try
            {
                string request = "IKA";
                byte[] requestData = Encoding.UTF8.GetBytes(request);
                stream.Write(requestData, 0, requestData.Length);

                byte[] buffer = new byte[1024];
                int bytesRead = stream.Read(buffer, 0, buffer.Length);
                string message = Encoding.UTF8.GetString(buffer, 0, bytesRead);
                VehicleInfo VehicleInfo = JsonConvert.DeserializeObject<VehicleInfo>(message);
                return VehicleInfo;
            }
            catch (SocketException se)
            {
                Console.WriteLine($"SocketException: {se.Message}");
                return null;
            }
            catch (Exception e)
            {
                Console.WriteLine($"An error occurred: {e.Message}");
                return null;
            }
        }
        public VehicleInfo YERGps()
        {
            try
            {
                string request = "YER";
                byte[] requestData = Encoding.UTF8.GetBytes(request);
                stream.Write(requestData, 0, requestData.Length);

                byte[] buffer = new byte[1024];
                int bytesRead = stream.Read(buffer, 0, buffer.Length);
                string message = Encoding.UTF8.GetString(buffer, 0, bytesRead);
                VehicleInfo VehicleInfo = JsonConvert.DeserializeObject<VehicleInfo>(message);
                return VehicleInfo;
            }
            catch (SocketException se)
            {
                Console.WriteLine($"SocketException: {se.Message}");
                return null;
            }
            catch (Exception e)
            {
                Console.WriteLine($"An error occurred: {e.Message}");
                return null;
            }
        }
        public TargetInfo TargetData()
        {
            try
            {
                string request = "Target";
                byte[] requestData = Encoding.UTF8.GetBytes(request);
                stream.Write(requestData, 0, requestData.Length);

                byte[] buffer = new byte[1024];
                int bytesRead = stream.Read(buffer, 0, buffer.Length);
                string message = Encoding.UTF8.GetString(buffer, 0, bytesRead);
                TargetInfo Info = JsonConvert.DeserializeObject<TargetInfo>(message);
                return Info;
            }
            catch (SocketException se)
            {
                Console.WriteLine($"SocketException: {se.Message}");
                return null;
            }
            catch (Exception e)
            {
                Console.WriteLine($"An error occurred: {e.Message}");
                return null;
            }
        }


        public Motor motorSpeed()
        {
            try
            {
                string request = "motorSpeed";
                byte[] requestData = Encoding.UTF8.GetBytes(request);
                stream.Write(requestData, 0, requestData.Length);

                byte[] buffer = new byte[1024];
                int bytesRead = stream.Read(buffer, 0, buffer.Length);
                string message = Encoding.UTF8.GetString(buffer, 0, bytesRead);
                Motor motorInfo = JsonConvert.DeserializeObject<Motor>(message);
                return motorInfo;
            }
            catch (SocketException se)
            {
                Console.WriteLine($"SocketException: {se.Message}");
                return null;
            }
            catch (Exception e)
            {
                Console.WriteLine($"An error occurred: {e.Message}");
                return null;
            }
        }

        public void sendCameraRes(double weight, double height)
        {
            string request = "Camera:"+weight+":"+height;
            byte[] requestData = Encoding.UTF8.GetBytes(request);
            stream.Write(requestData, 0, requestData.Length);
        }

        public void sendArmming(string arm) 
        {
            try
            {
                string request = "arm:"+arm;
                byte[] requestData = Encoding.UTF8.GetBytes(request);
                stream.Write(requestData, 0, requestData.Length);

            }
            catch (SocketException se)
            {
                Console.WriteLine($"SocketException: {se.Message}");
            }
            catch (Exception e)
            {
                Console.WriteLine($"An error occurred: {e.Message}");
            }
        }


    }
}
