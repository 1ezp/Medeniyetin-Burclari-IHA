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

namespace MedeniyetinApp.UI
{
    public partial class Map : Form
    {

        private IHAGps gpsData;


        private Point mouseLocation;
        bool isMax = false;

        GMapOverlay markerOverlay;
        GMapControl map = new GMapControl();

        // points
        GMarkerGoogle IhaMarker;
        int counter=0;

        public Map(String port)
        {
            InitializeComponent();
            LoadMap();
            gpsData = new IHAGps(port);
            //System.Windows.Forms.Timer updateTimer = new System.Windows.Forms.Timer();
            //updateTimer.Interval = 1000;
            //updateTimer.Tick += UpdateTimer_Target;
            //updateTimer.Start();

            BackgroundWorker updateWorker = new BackgroundWorker();
            //updateWorker.WorkerReportsProgress = false; // No progress reporting
            updateWorker.WorkerSupportsCancellation = true;
            updateWorker.DoWork += UpdateWorker_DoWork;
            updateWorker.RunWorkerAsync();

        }

        //object sender, EventArgs e
        private void UpdateTimer_Target(object sender, DoWorkEventArgs e)
        {
                double lat = gpsData.TargetLat();
                double lng = gpsData.TargetLng();
            Invoke((MethodInvoker)delegate
            {
                labelLat.Text = Convert.ToString(lat);
                labelLng.Text = Convert.ToString(lng);
                if (lat == -1.0 && lng == -1.0)
                {
                    removeIHA();
                }
                else
                {
                        
                    removeIHA();
                    addIHA(lat, lng, GMarkerGoogleType.red, "IHA");
                }

            });
            Thread.Sleep(500);
        }

        private void UpdateWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            BackgroundWorker worker = sender as BackgroundWorker;

            while (true)
            {
                double lat = gpsData.TargetLat();
                double lng = gpsData.TargetLng();
                this.Invoke((MethodInvoker)delegate
                {
                    counter += 1;
                    labelCounter.Text = Convert.ToString(counter);
                    labelLat.Text = Convert.ToString(lat);
                    labelLng.Text = Convert.ToString(lng);
                    if (lat == -1.0 && lng == -1.0)
                    {
                        removeIHA();
                    }
                    else
                    {
                        removeIHA();
                        addIHA(lat, lng, GMarkerGoogleType.red, "IHA");
                    }
                });

                //Thread.Sleep(1000); // Adjust the delay as needed

            }
        }


        private void LoadMap()
        {
            GMap.NET.GMaps.Instance.Mode = GMap.NET.AccessMode.ServerOnly;
            map.SetPositionByKeywords("Talas, Turkey");
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
