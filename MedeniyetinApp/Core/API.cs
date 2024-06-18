using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;

namespace MedeniyetinApp.Core
{

    
    public class API
    {

        String Base = "http://127.0.0.1/";
        private static readonly HttpClient client = new HttpClient();

        public GPSInfo IHAGps()
        {
            GPSInfo gpsInfo = null;
            HttpResponseMessage response = client.GetAsync(Base+"IHA").Result;

            if (response.IsSuccessStatusCode)
            {
                string json = response.Content.ReadAsStringAsync().Result;
                gpsInfo = JsonConvert.DeserializeObject<GPSInfo>(json);
            }

            return gpsInfo;
        }

        public GPSInfo IKAGps()
        {
            GPSInfo gpsInfo = null;
            HttpResponseMessage response = client.GetAsync(Base + "IKA").Result;

            if (response.IsSuccessStatusCode)
            {
                string json = response.Content.ReadAsStringAsync().Result;
                gpsInfo = JsonConvert.DeserializeObject<GPSInfo>(json);
            }

            return gpsInfo;
        }

        public GPSInfo YERGps()
        {
            GPSInfo gpsInfo = null;
            HttpResponseMessage response = client.GetAsync(Base + "YER").Result;

            if (response.IsSuccessStatusCode)
            {
                string json = response.Content.ReadAsStringAsync().Result;
                gpsInfo = JsonConvert.DeserializeObject<GPSInfo>(json);
            }

            return gpsInfo;
        }
    }
}
