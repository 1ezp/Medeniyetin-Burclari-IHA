﻿namespace MedeniyetinApp.UI
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
            System.Windows.Forms.AGaugeRange aGaugeRange13 = new System.Windows.Forms.AGaugeRange();
            System.Windows.Forms.AGaugeRange aGaugeRange14 = new System.Windows.Forms.AGaugeRange();
            System.Windows.Forms.AGaugeRange aGaugeRange15 = new System.Windows.Forms.AGaugeRange();
            System.Windows.Forms.AGaugeRange aGaugeRange16 = new System.Windows.Forms.AGaugeRange();
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.panel5 = new System.Windows.Forms.Panel();
            this.panel6 = new System.Windows.Forms.Panel();
            this.Piha = new System.Windows.Forms.PictureBox();
            this.LIhaLong = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.LIhaLat = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.ModeOFF = new System.Windows.Forms.Label();
            this.ModePID = new System.Windows.Forms.Label();
            this.ModePixhawk = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.panel4 = new System.Windows.Forms.Panel();
            this.button2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.btnStart = new System.Windows.Forms.Button();
            this.attitudeIndicatorInstrumentControl1 = new MedeniyetinApp.Controllers.AttitudeIndicatorInstrumentControl();
            this.gaugePanel = new System.Windows.Forms.Panel();
            this.LBatteryVoltage = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.GbatteryVoltage = new System.Windows.Forms.AGauge();
            this.LmotorSpeed = new System.Windows.Forms.Label();
            this.LgroundSpeed = new System.Windows.Forms.Label();
            this.LrelativeAlt = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.GrelativeAlt = new System.Windows.Forms.AGauge();
            this.label2 = new System.Windows.Forms.Label();
            this.GgroundSpeed = new System.Windows.Forms.AGauge();
            this.label1 = new System.Windows.Forms.Label();
            this.GmotorSpeed = new System.Windows.Forms.AGauge();
            this.rollRight = new System.Windows.Forms.Panel();
            this.rollLeft = new System.Windows.Forms.Panel();
            this.pitchLeft = new System.Windows.Forms.Panel();
            this.pitchRight = new System.Windows.Forms.Panel();
            this.panel2.SuspendLayout();
            this.panel3.SuspendLayout();
            this.panel5.SuspendLayout();
            this.panel6.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Piha)).BeginInit();
            this.panel4.SuspendLayout();
            this.gaugePanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(988, 16);
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
            this.panel2.Location = new System.Drawing.Point(0, 16);
            this.panel2.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(988, 1072);
            this.panel2.TabIndex = 3;
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.panel5);
            this.panel3.Controls.Add(this.panel4);
            this.panel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel3.Location = new System.Drawing.Point(453, 0);
            this.panel3.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(535, 1072);
            this.panel3.TabIndex = 2;
            // 
            // panel5
            // 
            this.panel5.Controls.Add(this.panel6);
            this.panel5.Controls.Add(this.LIhaLong);
            this.panel5.Controls.Add(this.label9);
            this.panel5.Controls.Add(this.LIhaLat);
            this.panel5.Controls.Add(this.label6);
            this.panel5.Controls.Add(this.label4);
            this.panel5.Controls.Add(this.ModeOFF);
            this.panel5.Controls.Add(this.ModePID);
            this.panel5.Controls.Add(this.ModePixhawk);
            this.panel5.Controls.Add(this.label5);
            this.panel5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel5.Location = new System.Drawing.Point(0, 647);
            this.panel5.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.panel5.Name = "panel5";
            this.panel5.Size = new System.Drawing.Size(535, 425);
            this.panel5.TabIndex = 20;
            // 
            // panel6
            // 
            this.panel6.Controls.Add(this.pitchRight);
            this.panel6.Controls.Add(this.pitchLeft);
            this.panel6.Controls.Add(this.rollLeft);
            this.panel6.Controls.Add(this.rollRight);
            this.panel6.Controls.Add(this.Piha);
            this.panel6.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel6.Location = new System.Drawing.Point(0, 0);
            this.panel6.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.panel6.Name = "panel6";
            this.panel6.Size = new System.Drawing.Size(535, 409);
            this.panel6.TabIndex = 10;
            // 
            // Piha
            // 
            this.Piha.Image = global::MedeniyetinApp.Properties.Resources.iha;
            this.Piha.Location = new System.Drawing.Point(0, 0);
            this.Piha.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Piha.Name = "Piha";
            this.Piha.Size = new System.Drawing.Size(535, 409);
            this.Piha.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.Piha.TabIndex = 0;
            this.Piha.TabStop = false;
            // 
            // LIhaLong
            // 
            this.LIhaLong.AutoSize = true;
            this.LIhaLong.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LIhaLong.ForeColor = System.Drawing.Color.Silver;
            this.LIhaLong.Location = new System.Drawing.Point(404, 662);
            this.LIhaLong.Name = "LIhaLong";
            this.LIhaLong.Size = new System.Drawing.Size(23, 25);
            this.LIhaLong.TabIndex = 9;
            this.LIhaLong.Text = "0";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.ForeColor = System.Drawing.Color.Silver;
            this.label9.Location = new System.Drawing.Point(341, 662);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(62, 25);
            this.label9.TabIndex = 8;
            this.label9.Text = "Long:";
            // 
            // LIhaLat
            // 
            this.LIhaLat.AutoSize = true;
            this.LIhaLat.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LIhaLat.ForeColor = System.Drawing.Color.Silver;
            this.LIhaLat.Location = new System.Drawing.Point(117, 662);
            this.LIhaLat.Name = "LIhaLat";
            this.LIhaLat.Size = new System.Drawing.Size(23, 25);
            this.LIhaLat.TabIndex = 7;
            this.LIhaLat.Text = "0";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.ForeColor = System.Drawing.Color.Silver;
            this.label6.Location = new System.Drawing.Point(67, 662);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(45, 25);
            this.label6.TabIndex = 5;
            this.label6.Text = "Lat:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.ForeColor = System.Drawing.Color.White;
            this.label4.Location = new System.Drawing.Point(27, 592);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(129, 29);
            this.label4.TabIndex = 4;
            this.label4.Text = "IHA GPS:";
            // 
            // ModeOFF
            // 
            this.ModeOFF.AutoSize = true;
            this.ModeOFF.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ModeOFF.ForeColor = System.Drawing.Color.Silver;
            this.ModeOFF.Location = new System.Drawing.Point(415, 514);
            this.ModeOFF.Name = "ModeOFF";
            this.ModeOFF.Size = new System.Drawing.Size(52, 25);
            this.ModeOFF.TabIndex = 3;
            this.ModeOFF.Text = "OFF";
            // 
            // ModePID
            // 
            this.ModePID.AutoSize = true;
            this.ModePID.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ModePID.ForeColor = System.Drawing.Color.Silver;
            this.ModePID.Location = new System.Drawing.Point(261, 514);
            this.ModePID.Name = "ModePID";
            this.ModePID.Size = new System.Drawing.Size(44, 25);
            this.ModePID.TabIndex = 2;
            this.ModePID.Text = "PID";
            // 
            // ModePixhawk
            // 
            this.ModePixhawk.AutoSize = true;
            this.ModePixhawk.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ModePixhawk.ForeColor = System.Drawing.Color.Silver;
            this.ModePixhawk.Location = new System.Drawing.Point(67, 514);
            this.ModePixhawk.Name = "ModePixhawk";
            this.ModePixhawk.Size = new System.Drawing.Size(85, 25);
            this.ModePixhawk.TabIndex = 1;
            this.ModePixhawk.Text = "Pixhawk";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.ForeColor = System.Drawing.Color.White;
            this.label5.Location = new System.Drawing.Point(27, 458);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(140, 29);
            this.label5.TabIndex = 0;
            this.label5.Text = "IHA Mode:";
            // 
            // panel4
            // 
            this.panel4.Controls.Add(this.button2);
            this.panel4.Controls.Add(this.button1);
            this.panel4.Controls.Add(this.btnStart);
            this.panel4.Controls.Add(this.attitudeIndicatorInstrumentControl1);
            this.panel4.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel4.Location = new System.Drawing.Point(0, 0);
            this.panel4.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(535, 647);
            this.panel4.TabIndex = 19;
            // 
            // button2
            // 
            this.button2.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button2.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button2.ForeColor = System.Drawing.Color.White;
            this.button2.Location = new System.Drawing.Point(371, 560);
            this.button2.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(131, 55);
            this.button2.TabIndex = 21;
            this.button2.Text = "Disarm";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button1
            // 
            this.button1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button1.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button1.ForeColor = System.Drawing.Color.White;
            this.button1.Location = new System.Drawing.Point(172, 560);
            this.button1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(192, 55);
            this.button1.TabIndex = 20;
            this.button1.Text = "Force Arm";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // btnStart
            // 
            this.btnStart.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnStart.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnStart.ForeColor = System.Drawing.Color.White;
            this.btnStart.Location = new System.Drawing.Point(31, 560);
            this.btnStart.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(135, 55);
            this.btnStart.TabIndex = 19;
            this.btnStart.Text = "Arm";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // attitudeIndicatorInstrumentControl1
            // 
            this.attitudeIndicatorInstrumentControl1.Location = new System.Drawing.Point(31, 18);
            this.attitudeIndicatorInstrumentControl1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.attitudeIndicatorInstrumentControl1.Name = "attitudeIndicatorInstrumentControl1";
            this.attitudeIndicatorInstrumentControl1.Size = new System.Drawing.Size(434, 434);
            this.attitudeIndicatorInstrumentControl1.TabIndex = 18;
            // 
            // gaugePanel
            // 
            this.gaugePanel.Controls.Add(this.LBatteryVoltage);
            this.gaugePanel.Controls.Add(this.label8);
            this.gaugePanel.Controls.Add(this.GbatteryVoltage);
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
            this.gaugePanel.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.gaugePanel.Name = "gaugePanel";
            this.gaugePanel.Size = new System.Drawing.Size(453, 1072);
            this.gaugePanel.TabIndex = 1;
            this.gaugePanel.Paint += new System.Windows.Forms.PaintEventHandler(this.gaugePanel_Paint);
            this.gaugePanel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.gaugePanel_MouseDown);
            this.gaugePanel.MouseMove += new System.Windows.Forms.MouseEventHandler(this.gaugePanel_MouseMove);
            this.gaugePanel.MouseUp += new System.Windows.Forms.MouseEventHandler(this.gaugePanel_MouseUp);
            // 
            // LBatteryVoltage
            // 
            this.LBatteryVoltage.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LBatteryVoltage.ForeColor = System.Drawing.Color.Lime;
            this.LBatteryVoltage.Location = new System.Drawing.Point(173, 1221);
            this.LBatteryVoltage.Name = "LBatteryVoltage";
            this.LBatteryVoltage.Size = new System.Drawing.Size(67, 21);
            this.LBatteryVoltage.TabIndex = 25;
            this.LBatteryVoltage.Text = "0";
            this.LBatteryVoltage.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.ForeColor = System.Drawing.Color.Lime;
            this.label8.Location = new System.Drawing.Point(128, 1257);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(139, 20);
            this.label8.TabIndex = 24;
            this.label8.Text = "Battery Voltage";
            // 
            // GbatteryVoltage
            // 
            this.GbatteryVoltage.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.GbatteryVoltage.BaseArcColor = System.Drawing.Color.Gray;
            this.GbatteryVoltage.BaseArcRadius = 80;
            this.GbatteryVoltage.BaseArcStart = 135;
            this.GbatteryVoltage.BaseArcSweep = 270;
            this.GbatteryVoltage.BaseArcWidth = 2;
            this.GbatteryVoltage.Center = new System.Drawing.Point(110, 110);
            aGaugeRange13.Color = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            aGaugeRange13.EndValue = 5F;
            aGaugeRange13.InnerRadius = 1;
            aGaugeRange13.InRange = false;
            aGaugeRange13.Name = "GaugeRange1";
            aGaugeRange13.OuterRadius = 2;
            aGaugeRange13.StartValue = 0F;
            this.GbatteryVoltage.GaugeRanges.Add(aGaugeRange13);
            this.GbatteryVoltage.Location = new System.Drawing.Point(68, 1030);
            this.GbatteryVoltage.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.GbatteryVoltage.MaximumSize = new System.Drawing.Size(289, 228);
            this.GbatteryVoltage.MaxValue = 20F;
            this.GbatteryVoltage.MinimumSize = new System.Drawing.Size(289, 228);
            this.GbatteryVoltage.MinValue = 0F;
            this.GbatteryVoltage.Name = "GbatteryVoltage";
            this.GbatteryVoltage.NeedleColor1 = System.Windows.Forms.AGaugeNeedleColor.Gray;
            this.GbatteryVoltage.NeedleColor2 = System.Drawing.Color.DimGray;
            this.GbatteryVoltage.NeedleRadius = 65;
            this.GbatteryVoltage.NeedleType = System.Windows.Forms.NeedleType.Simple;
            this.GbatteryVoltage.NeedleWidth = 2;
            this.GbatteryVoltage.ScaleLinesInterColor = System.Drawing.Color.Lime;
            this.GbatteryVoltage.ScaleLinesInterInnerRadius = 73;
            this.GbatteryVoltage.ScaleLinesInterOuterRadius = 80;
            this.GbatteryVoltage.ScaleLinesInterWidth = 1;
            this.GbatteryVoltage.ScaleLinesMajorColor = System.Drawing.Color.Lime;
            this.GbatteryVoltage.ScaleLinesMajorInnerRadius = 70;
            this.GbatteryVoltage.ScaleLinesMajorOuterRadius = 80;
            this.GbatteryVoltage.ScaleLinesMajorStepValue = 1F;
            this.GbatteryVoltage.ScaleLinesMajorWidth = 2;
            this.GbatteryVoltage.ScaleLinesMinorColor = System.Drawing.Color.Gray;
            this.GbatteryVoltage.ScaleLinesMinorInnerRadius = 75;
            this.GbatteryVoltage.ScaleLinesMinorOuterRadius = 80;
            this.GbatteryVoltage.ScaleLinesMinorTicks = 9;
            this.GbatteryVoltage.ScaleLinesMinorWidth = 1;
            this.GbatteryVoltage.ScaleNumbersColor = System.Drawing.Color.Lime;
            this.GbatteryVoltage.ScaleNumbersFormat = "";
            this.GbatteryVoltage.ScaleNumbersRadius = 95;
            this.GbatteryVoltage.ScaleNumbersRotation = 0;
            this.GbatteryVoltage.ScaleNumbersStartScaleLine = 1;
            this.GbatteryVoltage.ScaleNumbersStepScaleLines = 1;
            this.GbatteryVoltage.Size = new System.Drawing.Size(289, 228);
            this.GbatteryVoltage.TabIndex = 23;
            this.GbatteryVoltage.Text = "aGauge1";
            this.GbatteryVoltage.Value = 0F;
            // 
            // LmotorSpeed
            // 
            this.LmotorSpeed.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LmotorSpeed.ForeColor = System.Drawing.Color.Lime;
            this.LmotorSpeed.Location = new System.Drawing.Point(176, 260);
            this.LmotorSpeed.Name = "LmotorSpeed";
            this.LmotorSpeed.Size = new System.Drawing.Size(67, 21);
            this.LmotorSpeed.TabIndex = 22;
            this.LmotorSpeed.Text = "0";
            this.LmotorSpeed.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // LgroundSpeed
            // 
            this.LgroundSpeed.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LgroundSpeed.ForeColor = System.Drawing.Color.Lime;
            this.LgroundSpeed.Location = new System.Drawing.Point(177, 588);
            this.LgroundSpeed.Name = "LgroundSpeed";
            this.LgroundSpeed.Size = new System.Drawing.Size(67, 21);
            this.LgroundSpeed.TabIndex = 21;
            this.LgroundSpeed.Text = "0";
            this.LgroundSpeed.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // LrelativeAlt
            // 
            this.LrelativeAlt.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LrelativeAlt.ForeColor = System.Drawing.Color.Lime;
            this.LrelativeAlt.Location = new System.Drawing.Point(173, 903);
            this.LrelativeAlt.Name = "LrelativeAlt";
            this.LrelativeAlt.Size = new System.Drawing.Size(67, 21);
            this.LrelativeAlt.TabIndex = 20;
            this.LrelativeAlt.Text = "0";
            this.LrelativeAlt.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.ForeColor = System.Drawing.Color.Lime;
            this.label3.Location = new System.Drawing.Point(145, 939);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(106, 20);
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
            aGaugeRange14.Color = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            aGaugeRange14.EndValue = 5F;
            aGaugeRange14.InnerRadius = 1;
            aGaugeRange14.InRange = false;
            aGaugeRange14.Name = "GaugeRange1";
            aGaugeRange14.OuterRadius = 2;
            aGaugeRange14.StartValue = 0F;
            this.GrelativeAlt.GaugeRanges.Add(aGaugeRange14);
            this.GrelativeAlt.Location = new System.Drawing.Point(68, 711);
            this.GrelativeAlt.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.GrelativeAlt.MaximumSize = new System.Drawing.Size(289, 228);
            this.GrelativeAlt.MaxValue = 400F;
            this.GrelativeAlt.MinimumSize = new System.Drawing.Size(289, 228);
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
            this.GrelativeAlt.Size = new System.Drawing.Size(289, 228);
            this.GrelativeAlt.TabIndex = 18;
            this.GrelativeAlt.Text = "aGauge1";
            this.GrelativeAlt.Value = 0F;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.Lime;
            this.label2.Location = new System.Drawing.Point(115, 615);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(179, 20);
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
            aGaugeRange15.Color = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            aGaugeRange15.EndValue = 5F;
            aGaugeRange15.InnerRadius = 1;
            aGaugeRange15.InRange = false;
            aGaugeRange15.Name = "GaugeRange1";
            aGaugeRange15.OuterRadius = 2;
            aGaugeRange15.StartValue = 0F;
            this.GgroundSpeed.GaugeRanges.Add(aGaugeRange15);
            this.GgroundSpeed.Location = new System.Drawing.Point(68, 382);
            this.GgroundSpeed.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.GgroundSpeed.MaximumSize = new System.Drawing.Size(289, 228);
            this.GgroundSpeed.MaxValue = 300F;
            this.GgroundSpeed.MinimumSize = new System.Drawing.Size(289, 228);
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
            this.GgroundSpeed.Size = new System.Drawing.Size(289, 228);
            this.GgroundSpeed.TabIndex = 15;
            this.GgroundSpeed.Text = "aGauge1";
            this.GgroundSpeed.Value = 0F;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.Lime;
            this.label1.Location = new System.Drawing.Point(145, 290);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(121, 20);
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
            aGaugeRange16.Color = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            aGaugeRange16.EndValue = 5F;
            aGaugeRange16.InnerRadius = 1;
            aGaugeRange16.InRange = false;
            aGaugeRange16.Name = "GaugeRange1";
            aGaugeRange16.OuterRadius = 2;
            aGaugeRange16.StartValue = 0F;
            this.GmotorSpeed.GaugeRanges.Add(aGaugeRange16);
            this.GmotorSpeed.Location = new System.Drawing.Point(68, 65);
            this.GmotorSpeed.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.GmotorSpeed.MaximumSize = new System.Drawing.Size(289, 228);
            this.GmotorSpeed.MaxValue = 1000F;
            this.GmotorSpeed.MinimumSize = new System.Drawing.Size(289, 228);
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
            this.GmotorSpeed.Size = new System.Drawing.Size(289, 228);
            this.GmotorSpeed.TabIndex = 13;
            this.GmotorSpeed.Text = "aGauge1";
            this.GmotorSpeed.Value = 0F;
            // 
            // rollRight
            // 
            this.rollRight.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(0)))));
            this.rollRight.Location = new System.Drawing.Point(300, 212);
            this.rollRight.Name = "rollRight";
            this.rollRight.Size = new System.Drawing.Size(132, 19);
            this.rollRight.TabIndex = 1;
            // 
            // rollLeft
            // 
            this.rollLeft.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))));
            this.rollLeft.Location = new System.Drawing.Point(73, 212);
            this.rollLeft.Name = "rollLeft";
            this.rollLeft.Size = new System.Drawing.Size(138, 19);
            this.rollLeft.TabIndex = 2;
            // 
            // pitchLeft
            // 
            this.pitchLeft.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(224)))), ((int)(((byte)(192)))));
            this.pitchLeft.Location = new System.Drawing.Point(171, 338);
            this.pitchLeft.Name = "pitchLeft";
            this.pitchLeft.Size = new System.Drawing.Size(54, 15);
            this.pitchLeft.TabIndex = 3;
            // 
            // pitchRight
            // 
            this.pitchRight.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(224)))), ((int)(((byte)(192)))));
            this.pitchRight.Location = new System.Drawing.Point(292, 338);
            this.pitchRight.Name = "pitchRight";
            this.pitchRight.Size = new System.Drawing.Size(54, 15);
            this.pitchRight.TabIndex = 4;
            // 
            // Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.ClientSize = new System.Drawing.Size(988, 1088);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "Main";
            this.Text = "s";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.Load += new System.EventHandler(this.Main_Load);
            this.panel2.ResumeLayout(false);
            this.panel3.ResumeLayout(false);
            this.panel5.ResumeLayout(false);
            this.panel5.PerformLayout();
            this.panel6.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.Piha)).EndInit();
            this.panel4.ResumeLayout(false);
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
        private System.Windows.Forms.Panel panel5;
        private System.Windows.Forms.Panel panel4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label ModeOFF;
        private System.Windows.Forms.Label ModePID;
        private System.Windows.Forms.Label ModePixhawk;
        private System.Windows.Forms.Label LIhaLong;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label LIhaLat;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label LBatteryVoltage;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.AGauge GbatteryVoltage;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.Panel panel6;
        private System.Windows.Forms.PictureBox Piha;
        private System.Windows.Forms.Panel rollRight;
        private System.Windows.Forms.Panel rollLeft;
        private System.Windows.Forms.Panel pitchRight;
        private System.Windows.Forms.Panel pitchLeft;
    }
}