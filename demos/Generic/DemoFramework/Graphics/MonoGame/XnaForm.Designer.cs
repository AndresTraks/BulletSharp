namespace DemoFramework.MonoGame
{
    partial class XnaForm
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
            this.graphicsDeviceControl1 = new DemoFramework.MonoGame.GraphicsDeviceControl();
            this.SuspendLayout();
            // 
            // graphicsDeviceControl1
            // 
            this.graphicsDeviceControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.graphicsDeviceControl1.Location = new System.Drawing.Point(0, 0);
            this.graphicsDeviceControl1.Name = "graphicsDeviceControl1";
            this.graphicsDeviceControl1.Size = new System.Drawing.Size(1024, 768);
            this.graphicsDeviceControl1.TabIndex = 0;
            this.graphicsDeviceControl1.Text = "graphicsDeviceControl1";
            // 
            // XnaForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1024, 768);
            this.Controls.Add(this.graphicsDeviceControl1);
            this.Name = "XnaForm";
            this.Text = "XnaForm";
            this.ResumeLayout(false);

        }

        #endregion

        private GraphicsDeviceControl graphicsDeviceControl1;

    }
}