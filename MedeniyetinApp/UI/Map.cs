using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using GMap.NET;
using GMap.NET.MapProviders;
using GMap.NET.WindowsForms;
using GMap.NET.WindowsForms.Markers;

namespace MedeniyetinApp.UI
{
    public partial class Map : Form
    {
        private Point mouseLocation;
        bool isMax = false;

        GMapOverlay markerOverlay;
        GMarkerGoogle IHA;
        GMapControl map = new GMapControl();

        public Map()
        {
            InitializeComponent();
            LoadMap();
            addPoint(38.7186606, 35.5252028);
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


            map.MapProvider = GoogleHybridMapProvider.Instance;
            GMapProviders.GoogleMap.ApiKey = "AIzaSyA9k7og3eKp8ni-Wv-xHYE5Vq5Js4jJ0yI";
            map.Dock = DockStyle.Fill;
            pnlMap.Controls.Add(map);


        }

        private void addPoint(double x,double y)
        {
            markerOverlay = new GMapOverlay("markers");
            map.Overlays.Add(markerOverlay);
            PointLatLng initialPosition = new PointLatLng(x, y);
            IHA = new GMarkerGoogle(initialPosition, GMarkerGoogleType.red);
            IHA.ToolTipText = "IHA";
            IHA.ToolTip.Font = new Font("Arial", 14, FontStyle.Bold);
            IHA.ToolTipMode = MarkerTooltipMode.Always;
            IHA.IsVisible = true;
            markerOverlay.Markers.Add(IHA);

        }


        private void panel1_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                Point mousePose = Control.MousePosition;
                mousePose.Offset(mouseLocation.X, mouseLocation.Y);
                Location = mousePose;
            }
        }

        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
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
