namespace MedeniyetinApp.UI
{
    partial class Test
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
            this.label1 = new System.Windows.Forms.Label();
            this.lbTargetLat = new System.Windows.Forms.Label();
            this.lbTargetLng = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(106, 114);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(134, 29);
            this.label1.TabIndex = 0;
            this.label1.Text = "Target Lat:";
            // 
            // lbTargetLat
            // 
            this.lbTargetLat.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbTargetLat.Location = new System.Drawing.Point(20, 154);
            this.lbTargetLat.Name = "lbTargetLat";
            this.lbTargetLat.Size = new System.Drawing.Size(321, 29);
            this.lbTargetLat.TabIndex = 1;
            this.lbTargetLat.Text = "0";
            this.lbTargetLat.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lbTargetLng
            // 
            this.lbTargetLng.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbTargetLng.Location = new System.Drawing.Point(25, 239);
            this.lbTargetLng.Name = "lbTargetLng";
            this.lbTargetLng.Size = new System.Drawing.Size(316, 29);
            this.lbTargetLng.TabIndex = 3;
            this.lbTargetLng.Text = "0";
            this.lbTargetLng.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(106, 201);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(141, 29);
            this.label3.TabIndex = 2;
            this.label3.Text = "Target Lng:";
            // 
            // Test
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(372, 450);
            this.Controls.Add(this.lbTargetLng);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.lbTargetLat);
            this.Controls.Add(this.label1);
            this.Name = "Test";
            this.Text = "Test";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label3;
        public System.Windows.Forms.Label lbTargetLat;
        public System.Windows.Forms.Label lbTargetLng;
    }
}