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
        GMarkerGoogle IhaMarker = new GMarkerGoogle(new PointLatLng(0, 0), GMarkerGoogleType.red);


        GMarkerGoogle IkaMarker = new GMarkerGoogle(new PointLatLng(0, 0), GMarkerGoogleType.blue);


        public Map(String port)
        {
            InitializeComponent();
            LoadMap();


            // IHA
            BackgroundWorker updateWorker = new BackgroundWorker();
            updateWorker.WorkerSupportsCancellation = true;
            updateWorker.DoWork += UpdateWorker_DoWork;
            updateWorker.RunWorkerAsync();

            // IKA
            BackgroundWorker IkaWorker = new BackgroundWorker();
            IkaWorker.WorkerSupportsCancellation = true;
            IkaWorker.DoWork += IkaWorker_DoWork;
            //IkaWorker.RunWorkerAsync();


        }



        private void UpdateWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            BackgroundWorker worker = sender as BackgroundWorker;

            while (true)
            {

                GPSInfo IhaGpsInfo = api.IHAGps();
                GPSInfo IkaGpsInfo = api.IKAGps();


                double IhaLat = Convert.ToDouble(IhaGpsInfo.Latitude );
                double IhaLng = Convert.ToDouble(IhaGpsInfo.Longitude);

                double IkaLat = Convert.ToDouble(IkaGpsInfo.Latitude);
                double IkaLng = Convert.ToDouble(IkaGpsInfo.Longitude);
                Invoke((MethodInvoker)delegate
                {

                    labelLat.Text = Convert.ToString(IhaLat);
                    labelLng.Text = Convert.ToString(IhaLng);
                    if (IhaLat == -1.0 && IhaLng == -1.0)
                    {
                        
                        removeMarker(IhaMarker);
                    }
                    else
                    {
                        //removeMarker(IhaMarker)
                        //removeIHA();
                        removeMarker(IhaMarker);
                        addMarker(IhaMarker, IhaLat, IhaLng, GMarkerGoogleType.red, "IHA");
                        //addIHA(lat, lng, GMarkerGoogleType.red, "IHA");
                    
                    }
                    if (IkaLat ==  -1.0 && IkaLng == -1.0)
                    {
                        removeMarker(IkaMarker);
                    }else
                    {
                        removeMarker(IkaMarker);
                        addMarker(IkaMarker, IkaLat, IkaLng, GMarkerGoogleType.red, "IKA");

                    }
                });

            }
        }

        private void IkaWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            BackgroundWorker worker = sender as BackgroundWorker;

            while (true)
            {

                GPSInfo gpsInfo = api.IKAGps();


                double lat = Convert.ToDouble(gpsInfo.Latitude);
                double lng = Convert.ToDouble(gpsInfo.Longitude);
                Invoke((MethodInvoker)delegate
                {

                    labelLat.Text = Convert.ToString(lat);
                    labelLng.Text = Convert.ToString(lng);
                    if (lat == -1.0 || lng == -1.0)
                    {

                        removeMarker(IkaMarker);
                    }
                    else
                    {
                        removeMarker(IkaMarker);
                        addMarker(IkaMarker, lat, lng, GMarkerGoogleType.blue, "IKA");
                    }
                });

            }
        }


        private void LoadMap()
        {
            GMap.NET.GMaps.Instance.Mode = GMap.NET.AccessMode.ServerOnly;
            map.SetPositionByKeywords("kayseri, Turkey");
            map.ShowCenter = false;



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
        private void addMarker(GMarkerGoogle marker, double x, double y, GMarkerGoogleType color, String title)
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
