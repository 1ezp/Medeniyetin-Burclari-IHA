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

        public VehicleInfo IHAGps()
        {
            VehicleInfo VehicleInfo = null;
            HttpResponseMessage response = client.GetAsync(Base+"IHA").Result;

            if (response.IsSuccessStatusCode)
            {
                string json = response.Content.ReadAsStringAsync().Result;
                VehicleInfo = JsonConvert.DeserializeObject<VehicleInfo>(json);
            }

            return VehicleInfo;
        }

        public VehicleInfo IKAGps()
        {
            VehicleInfo VehicleInfo = null;
            HttpResponseMessage response = client.GetAsync(Base + "IKA").Result;

            if (response.IsSuccessStatusCode)
            {
                string json = response.Content.ReadAsStringAsync().Result;
                VehicleInfo = JsonConvert.DeserializeObject<VehicleInfo>(json);
            }

            return VehicleInfo;
        }

        public VehicleInfo YERGps()
        {
            VehicleInfo VehicleInfo = null;
            HttpResponseMessage response = client.GetAsync(Base + "YER").Result;

            if (response.IsSuccessStatusCode)
            {
                string json = response.Content.ReadAsStringAsync().Result;
                VehicleInfo = JsonConvert.DeserializeObject<VehicleInfo>(json);
            }

            return VehicleInfo;
        }
    }
}
