namespace MedeniyetinApp.UI
{
    partial class Main
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.AGaugeRange aGaugeRange1 = new System.Windows.Forms.AGaugeRange();
            System.Windows.Forms.AGaugeRange aGaugeRange2 = new System.Windows.Forms.AGaugeRange();
            System.Windows.Forms.AGaugeRange aGaugeRange3 = new System.Windows.Forms.AGaugeRange();
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.gaugePanel = new System.Windows.Forms.Panel();
            this.LmotorSpeed = new System.Windows.Forms.Label();
            this.LgroundSpeed = new System.Windows.Forms.Label();
            this.LrelativeAlt = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.GrelativeAlt = new System.Windows.Forms.AGauge();
            this.label2 = new System.Windows.Forms.Label();
            this.GgroundSpeed = new System.Windows.Forms.AGauge();
            this.label1 = new System.Windows.Forms.Label();
            this.GmotorSpeed = new System.Windows.Forms.AGauge();
            this.attitudeIndicatorInstrumentControl1 = new MedeniyetinApp.Controllers.AttitudeIndicatorInstrumentControl();
            this.panel2.SuspendLayout();
            this.panel3.SuspendLayout();
            this.gaugePanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(741, 13);
            this.panel1.TabIndex = 2;
            this.panel1.DoubleClick += new System.EventHandler(this.panel1_DoubleClick);
            this.panel1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.panel1_MouseDown);
            this.panel1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.panel1_MouseMove);
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.panel2.Controls.Add(this.panel3);
            this.panel2.Controls.Add(this.gaugePanel);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(0, 13);
            this.panel2.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(741, 1204);
            this.panel2.TabIndex = 3;
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.attitudeIndicatorInstrumentControl1);
            this.panel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel3.Location = new System.Drawing.Point(297, 0);
            this.panel3.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(444, 1204);
            this.panel3.TabIndex = 2;
            // 
            // gaugePanel
            // 
            this.gaugePanel.Controls.Add(this.LmotorSpeed);
            this.gaugePanel.Controls.Add(this.LgroundSpeed);
            this.gaugePanel.Controls.Add(this.LrelativeAlt);
            this.gaugePanel.Controls.Add(this.label3);
            this.gaugePanel.Controls.Add(this.GrelativeAlt);
            this.gaugePanel.Controls.Add(this.label2);
            this.gaugePanel.Controls.Add(this.GgroundSpeed);
            this.gaugePanel.Controls.Add(this.label1);
            this.gaugePanel.Controls.Add(this.GmotorSpeed);
            this.gaugePanel.Dock = System.Windows.Forms.DockStyle.Left;
            this.gaugePanel.Location = new System.Drawing.Point(0, 0);
            this.gaugePanel.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.gaugePanel.Name = "gaugePanel";
            this.gaugePanel.Size = new System.Drawing.Size(297, 1204);
            this.gaugePanel.TabIndex = 1;
            this.gaugePanel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.gaugePanel_MouseDown);
            this.gaugePanel.MouseMove += new System.Windows.Forms.MouseEventHandler(this.gaugePanel_MouseMove);
            this.gaugePanel.MouseUp += new System.Windows.Forms.MouseEventHandler(this.gaugePanel_MouseUp);
            // 
            // LmotorSpeed
            // 
            this.LmotorSpeed.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LmotorSpeed.ForeColor = System.Drawing.Color.Lime;
            this.LmotorSpeed.Location = new System.Drawing.Point(125, 255);
            this.LmotorSpeed.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.LmotorSpeed.Name = "LmotorSpeed";
            this.LmotorSpeed.Size = new System.Drawing.Size(50, 17);
            this.LmotorSpeed.TabIndex = 22;
            this.LmotorSpeed.Text = "0";
            this.LmotorSpeed.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // LgroundSpeed
            // 
            this.LgroundSpeed.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LgroundSpeed.ForeColor = System.Drawing.Color.Lime;
            this.LgroundSpeed.Location = new System.Drawing.Point(126, 666);
            this.LgroundSpeed.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.LgroundSpeed.Name = "LgroundSpeed";
            this.LgroundSpeed.Size = new System.Drawing.Size(50, 17);
            this.LgroundSpeed.TabIndex = 21;
            this.LgroundSpeed.Text = "0";
            this.LgroundSpeed.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // LrelativeAlt
            // 
            this.LrelativeAlt.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LrelativeAlt.ForeColor = System.Drawing.Color.Lime;
            this.LrelativeAlt.Location = new System.Drawing.Point(123, 1084);
            this.LrelativeAlt.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.LrelativeAlt.Name = "LrelativeAlt";
            this.LrelativeAlt.Size = new System.Drawing.Size(50, 17);
            this.LrelativeAlt.TabIndex = 20;
            this.LrelativeAlt.Text = "0";
            this.LrelativeAlt.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.ForeColor = System.Drawing.Color.Lime;
            this.label3.Location = new System.Drawing.Point(102, 1113);
            this.label3.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(91, 17);
            this.label3.TabIndex = 19;
            this.label3.Text = "Relative Alt";
            // 
            // GrelativeAlt
            // 
            this.GrelativeAlt.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.GrelativeAlt.BaseArcColor = System.Drawing.Color.Gray;
            this.GrelativeAlt.BaseArcRadius = 80;
            this.GrelativeAlt.BaseArcStart = 135;
            this.GrelativeAlt.BaseArcSweep = 270;
            this.GrelativeAlt.BaseArcWidth = 2;
            this.GrelativeAlt.Center = new System.Drawing.Point(110, 110);
            aGaugeRange1.Color = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            aGaugeRange1.EndValue = 5F;
            aGaugeRange1.InnerRadius = 1;
            aGaugeRange1.InRange = false;
            aGaugeRange1.Name = "GaugeRange1";
            aGaugeRange1.OuterRadius = 2;
            aGaugeRange1.StartValue = 0F;
            this.GrelativeAlt.GaugeRanges.Add(aGaugeRange1);
            this.GrelativeAlt.Location = new System.Drawing.Point(44, 929);
            this.GrelativeAlt.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.GrelativeAlt.MaximumSize = new System.Drawing.Size(217, 185);
            this.GrelativeAlt.MaxValue = 400F;
            this.GrelativeAlt.MinimumSize = new System.Drawing.Size(217, 185);
            this.GrelativeAlt.MinValue = 0F;
            this.GrelativeAlt.Name = "GrelativeAlt";
            this.GrelativeAlt.NeedleColor1 = System.Windows.Forms.AGaugeNeedleColor.Gray;
            this.GrelativeAlt.NeedleColor2 = System.Drawing.Color.DimGray;
            this.GrelativeAlt.NeedleRadius = 65;
            this.GrelativeAlt.NeedleType = System.Windows.Forms.NeedleType.Simple;
            this.GrelativeAlt.NeedleWidth = 2;
            this.GrelativeAlt.ScaleLinesInterColor = System.Drawing.Color.Lime;
            this.GrelativeAlt.ScaleLinesInterInnerRadius = 73;
            this.GrelativeAlt.ScaleLinesInterOuterRadius = 80;
            this.GrelativeAlt.ScaleLinesInterWidth = 1;
            this.GrelativeAlt.ScaleLinesMajorColor = System.Drawing.Color.Lime;
            this.GrelativeAlt.ScaleLinesMajorInnerRadius = 70;
            this.GrelativeAlt.ScaleLinesMajorOuterRadius = 80;
            this.GrelativeAlt.ScaleLinesMajorStepValue = 50F;
            this.GrelativeAlt.ScaleLinesMajorWidth = 2;
            this.GrelativeAlt.ScaleLinesMinorColor = System.Drawing.Color.Gray;
            this.GrelativeAlt.ScaleLinesMinorInnerRadius = 75;
            this.GrelativeAlt.ScaleLinesMinorOuterRadius = 80;
            this.GrelativeAlt.ScaleLinesMinorTicks = 9;
            this.GrelativeAlt.ScaleLinesMinorWidth = 1;
            this.GrelativeAlt.ScaleNumbersColor = System.Drawing.Color.Lime;
            this.GrelativeAlt.ScaleNumbersFormat = "";
            this.GrelativeAlt.ScaleNumbersRadius = 95;
            this.GrelativeAlt.ScaleNumbersRotation = 0;
            this.GrelativeAlt.ScaleNumbersStartScaleLine = 1;
            this.GrelativeAlt.ScaleNumbersStepScaleLines = 1;
            this.GrelativeAlt.Size = new System.Drawing.Size(217, 185);
            this.GrelativeAlt.TabIndex = 18;
            this.GrelativeAlt.Text = "aGauge1";
            this.GrelativeAlt.Value = 0F;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.Lime;
            this.label2.Location = new System.Drawing.Point(79, 688);
            this.label2.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(155, 17);
            this.label2.TabIndex = 16;
            this.label2.Text = "Ground Speed (m/s)";
            // 
            // GgroundSpeed
            // 
            this.GgroundSpeed.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.GgroundSpeed.BaseArcColor = System.Drawing.Color.Gray;
            this.GgroundSpeed.BaseArcRadius = 80;
            this.GgroundSpeed.BaseArcStart = 135;
            this.GgroundSpeed.BaseArcSweep = 270;
            this.GgroundSpeed.BaseArcWidth = 2;
            this.GgroundSpeed.Center = new System.Drawing.Point(110, 110);
            aGaugeRange2.Color = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            aGaugeRange2.EndValue = 5F;
            aGaugeRange2.InnerRadius = 1;
            aGaugeRange2.InRange = false;
            aGaugeRange2.Name = "GaugeRange1";
            aGaugeRange2.OuterRadius = 2;
            aGaugeRange2.StartValue = 0F;
            this.GgroundSpeed.GaugeRanges.Add(aGaugeRange2);
            this.GgroundSpeed.Location = new System.Drawing.Point(44, 498);
            this.GgroundSpeed.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.GgroundSpeed.MaximumSize = new System.Drawing.Size(217, 185);
            this.GgroundSpeed.MaxValue = 300F;
            this.GgroundSpeed.MinimumSize = new System.Drawing.Size(217, 185);
            this.GgroundSpeed.MinValue = 0F;
            this.GgroundSpeed.Name = "GgroundSpeed";
            this.GgroundSpeed.NeedleColor1 = System.Windows.Forms.AGaugeNeedleColor.Gray;
            this.GgroundSpeed.NeedleColor2 = System.Drawing.Color.DimGray;
            this.GgroundSpeed.NeedleRadius = 65;
            this.GgroundSpeed.NeedleType = System.Windows.Forms.NeedleType.Simple;
            this.GgroundSpeed.NeedleWidth = 2;
            this.GgroundSpeed.ScaleLinesInterColor = System.Drawing.Color.Lime;
            this.GgroundSpeed.ScaleLinesInterInnerRadius = 73;
            this.GgroundSpeed.ScaleLinesInterOuterRadius = 80;
            this.GgroundSpeed.ScaleLinesInterWidth = 1;
            this.GgroundSpeed.ScaleLinesMajorColor = System.Drawing.Color.Lime;
            this.GgroundSpeed.ScaleLinesMajorInnerRadius = 70;
            this.GgroundSpeed.ScaleLinesMajorOuterRadius = 80;
            this.GgroundSpeed.ScaleLinesMajorStepValue = 30F;
            this.GgroundSpeed.ScaleLinesMajorWidth = 2;
            this.GgroundSpeed.ScaleLinesMinorColor = System.Drawing.Color.Gray;
            this.GgroundSpeed.ScaleLinesMinorInnerRadius = 75;
            this.GgroundSpeed.ScaleLinesMinorOuterRadius = 80;
            this.GgroundSpeed.ScaleLinesMinorTicks = 9;
            this.GgroundSpeed.ScaleLinesMinorWidth = 1;
            this.GgroundSpeed.ScaleNumbersColor = System.Drawing.Color.Lime;
            this.GgroundSpeed.ScaleNumbersFormat = "";
            this.GgroundSpeed.ScaleNumbersRadius = 95;
            this.GgroundSpeed.ScaleNumbersRotation = 0;
            this.GgroundSpeed.ScaleNumbersStartScaleLine = 1;
            this.GgroundSpeed.ScaleNumbersStepScaleLines = 1;
            this.GgroundSpeed.Size = new System.Drawing.Size(217, 185);
            this.GgroundSpeed.TabIndex = 15;
            this.GgroundSpeed.Text = "aGauge1";
            this.GgroundSpeed.Value = 0F;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.Lime;
            this.label1.Location = new System.Drawing.Point(102, 280);
            this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(105, 17);
            this.label1.TabIndex = 14;
            this.label1.Text = "Motor Speed ";
            // 
            // GmotorSpeed
            // 
            this.GmotorSpeed.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.GmotorSpeed.BaseArcColor = System.Drawing.Color.Gray;
            this.GmotorSpeed.BaseArcRadius = 80;
            this.GmotorSpeed.BaseArcStart = 135;
            this.GmotorSpeed.BaseArcSweep = 270;
            this.GmotorSpeed.BaseArcWidth = 2;
            this.GmotorSpeed.Center = new System.Drawing.Point(110, 110);
            aGaugeRange3.Color = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            aGaugeRange3.EndValue = 5F;
            aGaugeRange3.InnerRadius = 1;
            aGaugeRange3.InRange = false;
            aGaugeRange3.Name = "GaugeRange1";
            aGaugeRange3.OuterRadius = 2;
            aGaugeRange3.StartValue = 0F;
            this.GmotorSpeed.GaugeRanges.Add(aGaugeRange3);
            this.GmotorSpeed.Location = new System.Drawing.Point(44, 97);
            this.GmotorSpeed.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.GmotorSpeed.MaximumSize = new System.Drawing.Size(217, 185);
            this.GmotorSpeed.MaxValue = 1000F;
            this.GmotorSpeed.MinimumSize = new System.Drawing.Size(217, 185);
            this.GmotorSpeed.MinValue = 0F;
            this.GmotorSpeed.Name = "GmotorSpeed";
            this.GmotorSpeed.NeedleColor1 = System.Windows.Forms.AGaugeNeedleColor.Gray;
            this.GmotorSpeed.NeedleColor2 = System.Drawing.Color.DimGray;
            this.GmotorSpeed.NeedleRadius = 65;
            this.GmotorSpeed.NeedleType = System.Windows.Forms.NeedleType.Simple;
            this.GmotorSpeed.NeedleWidth = 2;
            this.GmotorSpeed.ScaleLinesInterColor = System.Drawing.Color.Lime;
            this.GmotorSpeed.ScaleLinesInterInnerRadius = 73;
            this.GmotorSpeed.ScaleLinesInterOuterRadius = 80;
            this.GmotorSpeed.ScaleLinesInterWidth = 1;
            this.GmotorSpeed.ScaleLinesMajorColor = System.Drawing.Color.Lime;
            this.GmotorSpeed.ScaleLinesMajorInnerRadius = 70;
            this.GmotorSpeed.ScaleLinesMajorOuterRadius = 80;
            this.GmotorSpeed.ScaleLinesMajorStepValue = 100F;
            this.GmotorSpeed.ScaleLinesMajorWidth = 2;
            this.GmotorSpeed.ScaleLinesMinorColor = System.Drawing.Color.Gray;
            this.GmotorSpeed.ScaleLinesMinorInnerRadius = 75;
            this.GmotorSpeed.ScaleLinesMinorOuterRadius = 80;
            this.GmotorSpeed.ScaleLinesMinorTicks = 9;
            this.GmotorSpeed.ScaleLinesMinorWidth = 1;
            this.GmotorSpeed.ScaleNumbersColor = System.Drawing.Color.Lime;
            this.GmotorSpeed.ScaleNumbersFormat = "";
            this.GmotorSpeed.ScaleNumbersRadius = 95;
            this.GmotorSpeed.ScaleNumbersRotation = 0;
            this.GmotorSpeed.ScaleNumbersStartScaleLine = 1;
            this.GmotorSpeed.ScaleNumbersStepScaleLines = 1;
            this.GmotorSpeed.Size = new System.Drawing.Size(217, 185);
            this.GmotorSpeed.TabIndex = 13;
            this.GmotorSpeed.Text = "aGauge1";
            this.GmotorSpeed.Value = 0F;
            // 
            // attitudeIndicatorInstrumentControl1
            // 
            this.attitudeIndicatorInstrumentControl1.Location = new System.Drawing.Point(-5, 4);
            this.attitudeIndicatorInstrumentControl1.Margin = new System.Windows.Forms.Padding(2);
            this.attitudeIndicatorInstrumentControl1.Name = "attitudeIndicatorInstrumentControl1";
            this.attitudeIndicatorInstrumentControl1.Size = new System.Drawing.Size(383, 383);
            this.attitudeIndicatorInstrumentControl1.TabIndex = 18;
            // 
            // Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.ClientSize = new System.Drawing.Size(741, 1217);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.Name = "Main";
            this.Text = "s";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.panel2.ResumeLayout(false);
            this.panel3.ResumeLayout(false);
            this.gaugePanel.ResumeLayout(false);
            this.gaugePanel.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Panel gaugePanel;
        private System.Windows.Forms.Label LmotorSpeed;
        private System.Windows.Forms.Label LgroundSpeed;
        private System.Windows.Forms.Label LrelativeAlt;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.AGauge GrelativeAlt;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.AGauge GgroundSpeed;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.AGauge GmotorSpeed;
        private System.Windows.Forms.Panel panel3;
        private Controllers.AttitudeIndicatorInstrumentControl attitudeIndicatorInstrumentControl1;
    }
}