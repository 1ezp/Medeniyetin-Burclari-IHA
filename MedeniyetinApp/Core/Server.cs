using System;
using System.Collections.Specialized;
using System.Net.Sockets;
using System.Text;
using Newtonsoft.Json;

namespace MedeniyetinApp.Core
{

    public class GPSInfo
    {
        [JsonProperty("Lat")]
        public double Latitude { get; set; }

        [JsonProperty("Long")]
        public double Longitude { get; set; }
    }

    public class TargetInfo
    {
        [JsonProperty("x")]
        public double x { get; set; }

        [JsonProperty("y")]
        public double y { get; set; }
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

        public GPSInfo IHAGps()
        {
            try
            {
                string request = "IHA";
                byte[] requestData = Encoding.UTF8.GetBytes(request);
                stream.Write(requestData, 0, requestData.Length);

                byte[] buffer = new byte[1024];
                int bytesRead = stream.Read(buffer, 0, buffer.Length);
                string message = Encoding.UTF8.GetString(buffer, 0, bytesRead);
                GPSInfo gpsInfo = JsonConvert.DeserializeObject<GPSInfo>(message);
                return gpsInfo;
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
        public GPSInfo IKAGps()
        {
            try
            {
                string request = "IKA";
                byte[] requestData = Encoding.UTF8.GetBytes(request);
                stream.Write(requestData, 0, requestData.Length);

                byte[] buffer = new byte[1024];
                int bytesRead = stream.Read(buffer, 0, buffer.Length);
                string message = Encoding.UTF8.GetString(buffer, 0, bytesRead);
                GPSInfo gpsInfo = JsonConvert.DeserializeObject<GPSInfo>(message);
                return gpsInfo;
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
        public GPSInfo YERGps()
        {
            try
            {
                string request = "YER";
                byte[] requestData = Encoding.UTF8.GetBytes(request);
                stream.Write(requestData, 0, requestData.Length);

                byte[] buffer = new byte[1024];
                int bytesRead = stream.Read(buffer, 0, buffer.Length);
                string message = Encoding.UTF8.GetString(buffer, 0, bytesRead);
                GPSInfo gpsInfo = JsonConvert.DeserializeObject<GPSInfo>(message);
                return gpsInfo;
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



    }
}
