﻿namespace MedeniyetinApp.UI
{
    partial class Camera
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
            this.panel1 = new System.Windows.Forms.Panel();
            this.pnlY = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.pnlX = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.bmpY = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.bmpX = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.panel2 = new System.Windows.Forms.Panel();
            this.cameraBox = new System.Windows.Forms.PictureBox();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.cameraBox)).BeginInit();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.pnlY);
            this.panel1.Controls.Add(this.label4);
            this.panel1.Controls.Add(this.pnlX);
            this.panel1.Controls.Add(this.label6);
            this.panel1.Controls.Add(this.bmpY);
            this.panel1.Controls.Add(this.label3);
            this.panel1.Controls.Add(this.bmpX);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(1252, 16);
            this.panel1.TabIndex = 1;
            this.panel1.DoubleClick += new System.EventHandler(this.panel1_DoubleClick);
            this.panel1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.panel1_MouseDown);
            this.panel1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.panel1_MouseMove);
            // 
            // pnlY
            // 
            this.pnlY.AutoSize = true;
            this.pnlY.Font = new System.Drawing.Font("Microsoft Sans Serif", 5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.pnlY.Location = new System.Drawing.Point(726, 2);
            this.pnlY.Name = "pnlY";
            this.pnlY.Size = new System.Drawing.Size(10, 12);
            this.pnlY.TabIndex = 7;
            this.pnlY.Text = "0";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(674, 2);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(27, 12);
            this.label4.TabIndex = 6;
            this.label4.Text = "pnl y:";
            // 
            // pnlX
            // 
            this.pnlX.AutoSize = true;
            this.pnlX.Font = new System.Drawing.Font("Microsoft Sans Serif", 5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.pnlX.Location = new System.Drawing.Point(598, 2);
            this.pnlX.Name = "pnlX";
            this.pnlX.Size = new System.Drawing.Size(10, 12);
            this.pnlX.TabIndex = 5;
            this.pnlX.Text = "0";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(546, 2);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(27, 12);
            this.label6.TabIndex = 4;
            this.label6.Text = "pnl x:";
            // 
            // bmpY
            // 
            this.bmpY.Font = new System.Drawing.Font("Microsoft Sans Serif", 5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bmpY.Location = new System.Drawing.Point(248, 2);
            this.bmpY.Name = "bmpY";
            this.bmpY.Size = new System.Drawing.Size(90, 16);
            this.bmpY.TabIndex = 3;
            this.bmpY.Text = "0";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(182, 2);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 2;
            this.label3.Text = "Target y:";
            // 
            // bmpX
            // 
            this.bmpX.Font = new System.Drawing.Font("Microsoft Sans Serif", 5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bmpX.Location = new System.Drawing.Point(79, 2);
            this.bmpX.Name = "bmpX";
            this.bmpX.Size = new System.Drawing.Size(97, 15);
            this.bmpX.TabIndex = 1;
            this.bmpX.Text = "0";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(12, 2);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "Target x:";
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.cameraBox);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(0, 16);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(1252, 719);
            this.panel2.TabIndex = 2;
            // 
            // cameraBox
            // 
            this.cameraBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.cameraBox.Location = new System.Drawing.Point(0, 0);
            this.cameraBox.Name = "cameraBox";
            this.cameraBox.Size = new System.Drawing.Size(1252, 719);
            this.cameraBox.TabIndex = 0;
            this.cameraBox.TabStop = false;
            // 
            // Camera
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.ClientSize = new System.Drawing.Size(1252, 735);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel1);
            this.ForeColor = System.Drawing.Color.White;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "Camera";
            this.Text = "Camera";
            this.Load += new System.EventHandler(this.Camera_Load);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.cameraBox)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Label pnlY;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label pnlX;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label bmpY;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label bmpX;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.PictureBox cameraBox;
    }
}