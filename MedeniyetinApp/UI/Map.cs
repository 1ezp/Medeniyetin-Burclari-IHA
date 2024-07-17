using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
//using System.Threading.Tasks;

using MedeniyetinApp.Core;

using GMap.NET;
using GMap.NET.MapProviders;
using GMap.NET.WindowsForms;
using GMap.NET.WindowsForms.Markers;
using System.Threading;
using System.Linq.Expressions;
using System.Security.Cryptography;


namespace MedeniyetinApp.UI
{
    public partial class Map : Form
    {


        API api = new API();

        private Point mouseLocation;
        bool isMax = false;

        GMapOverlay markerOverlay;
        GMapControl map = new GMapControl();
        

        // points
        GMarkerGoogle IhaMarker = new GMarkerGoogle(new PointLatLng(-1, -1), GMarkerGoogleType.red);
        GMarkerGoogle IkaMarker = new GMarkerGoogle(new PointLatLng(-1, -1), GMarkerGoogleType.blue);
        GMarkerGoogle YerMarker = new GMarkerGoogle(new PointLatLng(-1, -1), GMarkerGoogleType.orange);

        public Map(String port)
        {
            InitializeComponent();
            LoadMap();


            BackgroundWorker updateWorker = new BackgroundWorker();
            updateWorker.WorkerSupportsCancellation = true;
            updateWorker.DoWork += UpdateWorker_DoWork;
            updateWorker.RunWorkerAsync();


        }



        private void UpdateWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            BackgroundWorker worker = sender as BackgroundWorker;
            Server server = new Server();
            while (true)
            {

                //VehicleInfo IhaVehicleInfo = api.IHAGps();
                VehicleInfo IhaVehicleInfo = server.IHA();

                VehicleInfo IkaVehicleInfo = server.IKAGps();
                VehicleInfo YerVehicleInfo = server.YERGps();


                double IhaLat = Convert.ToDouble(IhaVehicleInfo.Latitude );
                double IhaLng = Convert.ToDouble(IhaVehicleInfo.Longitude);

                double IkaLat = Convert.ToDouble(IkaVehicleInfo.Latitude);
                double IkaLng = Convert.ToDouble(IkaVehicleInfo.Longitude);

                double YerLat = Convert.ToDouble(YerVehicleInfo.Latitude);
                    double YerLng = Convert.ToDouble(YerVehicleInfo.Longitude);

                Invoke((MethodInvoker)delegate
                {

                    labelLat.Text = Convert.ToString(IhaLat);
                    labelLng.Text = Convert.ToString(IhaLng);
                    if (IhaLat == 0 && IhaLng == 0)
                    {
                        
                        removeMarker(IhaMarker);
                    }
                    else
                    {
                        removeMarker(IhaMarker);
                        addMarker(IhaMarker, IhaLat, IhaLng, "IHA");
                    
                    }
                    if (IkaLat == 0 && IkaLng == 0)
                    {
                        removeMarker(IkaMarker);
                    }else
                    {
                        removeMarker(IkaMarker);
                        addMarker(IkaMarker, IkaLat, IkaLng, "IKA");

                    }

                    if (YerLat == 0 && YerLng == 0)
                    {
                        removeMarker(YerMarker);
                    }
                    else
                    {
                        removeMarker(YerMarker);
                        addMarker(YerMarker, YerLat, YerLng, "YER");

                    }
                });

            }
        }

       


        private void LoadMap()
        {
            GMap.NET.GMaps.Instance.Mode = GMap.NET.AccessMode.ServerAndCache;
            map.SetPositionByKeywords("kayseri, Turkey");
            map.Position = new PointLatLng(38.7225, 35.4875);
            map.ShowCenter = false;
            map.CacheLocation = @"C:\Users\hekmt\Desktop\Medeniyetin-Burclari-IHA\MedeniyetinApp\cache";


            map.MouseWheelZoomEnabled = true;
            map.MouseWheelZoomType = MouseWheelZoomType.MousePositionWithoutCenter;
            map.DragButton = MouseButtons.Left;
            map.MinZoom = 2;
            map.MaxZoom = 18;
            map.Zoom = 12;


            //map.MapProvider = GoogleHybridMapProvider.Instance;
            map.MapProvider = GoogleKoreaHybridMapProvider.Instance;


            //points
            markerOverlay = new GMapOverlay("markers");
            map.Overlays.Add(markerOverlay);


            GMapProviders.GoogleMap.ApiKey = "AIzaSyA9k7og3eKp8ni-Wv-xHYE5Vq5Js4jJ0yI";
            map.Dock = DockStyle.Fill;
            pnlMap.Controls.Add(map);


        }
        private void addIHA(double x, double y, GMarkerGoogleType color, String title)
        {
            // position
            PointLatLng initialPosition = new PointLatLng(x, y);

            IhaMarker = new GMarkerGoogle(initialPosition, color);
            IhaMarker.ToolTipText = title;
            IhaMarker.ToolTip.Font = new Font("Arial", 15, FontStyle.Bold);
            IhaMarker.ToolTipMode = MarkerTooltipMode.Always;
            IhaMarker.IsVisible = true;
            markerOverlay.Markers.Add(IhaMarker);


        }
        private void addMarker(GMarkerGoogle marker, double x, double y, String title)
        {

            
            marker.Position = new PointLatLng(x, y);
            marker.ToolTipText = title;
            marker.ToolTip.Font = new Font("Arial", 15, FontStyle.Bold);
            marker.ToolTipMode = MarkerTooltipMode.Always;
            marker.IsVisible = true;
            
            markerOverlay.Markers.Add(marker);
            

        }


        void removeMarker(GMarkerGoogle Marker)
        {
            try

            {
        
                if (markerOverlay.Markers.Contains(Marker))
                {
                    markerOverlay.Markers.Remove(Marker);
                }
                
            }
            catch { }

        }
        void removeIHA()
        {
            if (markerOverlay.Markers.Contains(IhaMarker))
            {
                markerOverlay.Markers.Remove(IhaMarker);
            }


        }
        


        private void panel1_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                Point mousePose = Control.MousePosition;
                mousePose.Offset(mouseLocation.X, mouseLocation.Y);
                Location = mousePose;
            }
        }

        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                mouseLocation = new Point(-e.X, -e.Y);
            }
        }

        private void panel1_DoubleClick(object sender, EventArgs e)
        {
            if (isMax)
            {
                WindowState = FormWindowState.Normal;
                isMax = false;
            }
            else
            {
                WindowState = FormWindowState.Maximized;
                isMax = true;
            }

        }


    }
}
