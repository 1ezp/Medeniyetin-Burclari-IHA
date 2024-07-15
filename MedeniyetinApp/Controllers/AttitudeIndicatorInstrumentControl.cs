using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MedeniyetinApp.Controllers
{
    public class AttitudeIndicatorInstrumentControl : InstrumentControl
    {
        #region Fields

        // Parameters
        double PitchAngle = 0; // Phi
        double RollAngle = 0; // Theta



        // Images
        Bitmap bmpCadran = new Bitmap(MedeniyetinApp.Properties.Resources.Horizon_Background);
        Bitmap bmpBoule = new Bitmap(MedeniyetinApp.Properties.Resources.Horizon_GroundSky);
        Bitmap bmpAvion = new Bitmap(MedeniyetinApp.Properties.Resources.Maquette_Avion);

        #endregion

        #region Contructor

        /// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

        public AttitudeIndicatorInstrumentControl()
        {
            this.Size = new Size(370, 360);
            // Double bufferisation
            SetStyle(ControlStyles.DoubleBuffer | ControlStyles.UserPaint |
                ControlStyles.AllPaintingInWmPaint, true);
        }

        #endregion

        #region Component Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
        }
        #endregion

        #region Paint

        protected override void OnPaint(PaintEventArgs pe)
        {
            // Calling the base class OnPaint
            base.OnPaint(pe);

            // Get the background color of the form
            Color backgroundColor = this.BackColor;


            for (int x = 0; x < bmpCadran.Width; x++)
            {
                for (int y = 0; y < bmpCadran.Height; y++)
                {
                    // Get the color of the current pixel
                    Color pixelColor = bmpCadran.GetPixel(x, y);

                    // Check if the pixel color matches the target color (#FF002AFF)
                    if (pixelColor.ToArgb() == Color.FromArgb(255, 0, 42, 255).ToArgb()) // #FF002AFF
                    {
                        // Replace the pixel with the form's background color
                        bmpCadran.SetPixel(x, y, backgroundColor);
                    }
                }
            }


            // Pre Display computings

            Point ptBoule = new Point(25, -210);
            Point ptRotation = new Point(150, 150);

            float scale = (float)this.Width / bmpCadran.Width;

            // Affichages - - - - - - - - - - - - - - - - - - - - - - 

            bmpCadran.MakeTransparent(Color.Yellow);
            bmpAvion.MakeTransparent(Color.Yellow);

            // display Horizon
            RotateAndTranslate(pe, bmpBoule, RollAngle, 0, ptBoule, (int)(4 * PitchAngle), ptRotation, scale);

            // diplay mask
            Pen maskPen = new Pen(this.BackColor, 30 * scale);
            pe.Graphics.DrawRectangle(maskPen, 0, 0, bmpCadran.Width * scale, bmpCadran.Height * scale);

            // display cadran
            pe.Graphics.DrawImage(bmpCadran, 0, 0, (float)(bmpCadran.Width * scale), (float)(bmpCadran.Height * scale));

            // display aircraft symbol
            pe.Graphics.DrawImage(bmpAvion, (float)((0.5 * bmpCadran.Width - 0.5 * bmpAvion.Width) * scale), (float)((0.5 * bmpCadran.Height - 0.5 * bmpAvion.Height) * scale), (float)(bmpAvion.Width * scale), (float)(bmpAvion.Height * scale));


        }

        #endregion

        #region Rezize

        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);

            // Ensure equal width and height
            int newSize = Math.Min(this.Width, this.Height);
            this.Size = new Size(newSize, newSize);

            // Redraw the control when resized
            this.Invalidate();
        }


        #endregion

        #region Methods

        /// <summary>
        /// Define the physical value to be displayed on the indicator
        /// </summary>
        /// <param name="aircraftPitchAngle">The aircraft pitch angle in °deg</param>
        /// <param name="aircraftRollAngle">The aircraft roll angle in °deg</param
        public void SetAttitudeIndicatorParameters(double aircraftPitchAngle, double aircraftRollAngle)
        {
            PitchAngle = aircraftPitchAngle;
            RollAngle = aircraftRollAngle * Math.PI / 180;

            this.Refresh();
        }

        #endregion

    }
}
