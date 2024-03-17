using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using MedeniyetinApp.Core;

using GMap.NET;
using GMap.NET.MapProviders;
using GMap.NET.WindowsForms;
using GMap.NET.WindowsForms.Markers;

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

        public Map(String port)
        {
            InitializeComponent();
            
            gpsData = new IHAGps(port);
            LoadMap();
            Timer updateTimer = new Timer();
            updateTimer.Interval = 1000;
            updateTimer.Tick += UpdateTimer_Target;
            updateTimer.Start();

        }

        private void UpdateTimer_Target(object sender, EventArgs e)
        {
            string lat = gpsData.TargetLat();
            string lng = gpsData.TargetLng();

            if (lat != "error" && lng != "error" && lat != "0" && lng != "0")
            {
                Invoke((MethodInvoker)delegate
                {
                    removeIHA();
                    addIHA(Convert.ToDouble(lat), Convert.ToDouble(lng), GMarkerGoogleType.red, "IHA");
                });
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

        private void addIHA(double x,double y, GMarkerGoogleType color,String title)
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


        public void removeIHA()
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
