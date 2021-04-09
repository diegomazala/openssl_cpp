
namespace License_Generator
{
    partial class MainForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.artistNameTextBox = new System.Windows.Forms.TextBox();
            this.artTitleTextBox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.beginDateTimePicker = new System.Windows.Forms.DateTimePicker();
            this.keyFileTextBox = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.openKeyFileButon = new System.Windows.Forms.Button();
            this.generateButton = new System.Windows.Forms.Button();
            this.saveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.endDateTimePicker = new System.Windows.Forms.DateTimePicker();
            this.label5 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 16);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(70, 15);
            this.label1.TabIndex = 0;
            this.label1.Text = "Artist Name";
            // 
            // artistNameTextBox
            // 
            this.artistNameTextBox.Location = new System.Drawing.Point(105, 13);
            this.artistNameTextBox.Name = "artistNameTextBox";
            this.artistNameTextBox.Size = new System.Drawing.Size(172, 23);
            this.artistNameTextBox.TabIndex = 1;
            // 
            // artTitleTextBox
            // 
            this.artTitleTextBox.Location = new System.Drawing.Point(105, 44);
            this.artTitleTextBox.Name = "artTitleTextBox";
            this.artTitleTextBox.Size = new System.Drawing.Size(172, 23);
            this.artTitleTextBox.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 47);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(48, 15);
            this.label2.TabIndex = 2;
            this.label2.Text = "Art Title";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 82);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(64, 15);
            this.label3.TabIndex = 4;
            this.label3.Text = "Begin Date";
            // 
            // beginDateTimePicker
            // 
            this.beginDateTimePicker.Location = new System.Drawing.Point(105, 76);
            this.beginDateTimePicker.Name = "beginDateTimePicker";
            this.beginDateTimePicker.Size = new System.Drawing.Size(172, 23);
            this.beginDateTimePicker.TabIndex = 6;
            // 
            // keyFileTextBox
            // 
            this.keyFileTextBox.Location = new System.Drawing.Point(105, 144);
            this.keyFileTextBox.Name = "keyFileTextBox";
            this.keyFileTextBox.Size = new System.Drawing.Size(134, 23);
            this.keyFileTextBox.TabIndex = 8;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 147);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(47, 15);
            this.label4.TabIndex = 7;
            this.label4.Text = "Key File";
            // 
            // openFileDialog
            // 
            this.openFileDialog.DefaultExt = "key";
            // 
            // openKeyFileButon
            // 
            this.openKeyFileButon.Location = new System.Drawing.Point(245, 144);
            this.openKeyFileButon.Name = "openKeyFileButon";
            this.openKeyFileButon.Size = new System.Drawing.Size(31, 23);
            this.openKeyFileButon.TabIndex = 9;
            this.openKeyFileButon.Text = "...";
            this.openKeyFileButon.UseVisualStyleBackColor = true;
            this.openKeyFileButon.Click += new System.EventHandler(this.openKeyFileButon_Click);
            // 
            // generateButton
            // 
            this.generateButton.Location = new System.Drawing.Point(156, 185);
            this.generateButton.Name = "generateButton";
            this.generateButton.Size = new System.Drawing.Size(121, 23);
            this.generateButton.TabIndex = 10;
            this.generateButton.Text = "Generate";
            this.generateButton.UseVisualStyleBackColor = true;
            this.generateButton.Click += new System.EventHandler(this.generateButton_Click);
            // 
            // saveFileDialog
            // 
            this.saveFileDialog.DefaultExt = "aa";
            // 
            // endDateTimePicker
            // 
            this.endDateTimePicker.Location = new System.Drawing.Point(105, 109);
            this.endDateTimePicker.Name = "endDateTimePicker";
            this.endDateTimePicker.Size = new System.Drawing.Size(172, 23);
            this.endDateTimePicker.TabIndex = 12;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 115);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(54, 15);
            this.label5.TabIndex = 11;
            this.label5.Text = "End Date";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(293, 218);
            this.Controls.Add(this.endDateTimePicker);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.generateButton);
            this.Controls.Add(this.openKeyFileButon);
            this.Controls.Add(this.keyFileTextBox);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.beginDateTimePicker);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.artTitleTextBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.artistNameTextBox);
            this.Controls.Add(this.label1);
            this.Name = "MainForm";
            this.Text = "License Generator";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox artistNameTextBox;
        private System.Windows.Forms.TextBox artTitleTextBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.DateTimePicker beginDateTimePicker;
        private System.Windows.Forms.TextBox keyFileTextBox;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.Button openKeyFileButon;
        private System.Windows.Forms.Button generateButton;
        private System.Windows.Forms.SaveFileDialog saveFileDialog;
        private System.Windows.Forms.DateTimePicker endDateTimePicker;
        private System.Windows.Forms.Label label5;
    }
}

