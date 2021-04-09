
namespace crypto
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
            SaveConfig();

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
            this.InputFileTextBox = new System.Windows.Forms.TextBox();
            this.InputFileButton = new System.Windows.Forms.Button();
            this.KeyButton = new System.Windows.Forms.Button();
            this.KeyFileTextBox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.openKeyFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.InfoTextBox = new System.Windows.Forms.TextBox();
            this.EncodeButton = new System.Windows.Forms.Button();
            this.DecodeButton = new System.Windows.Forms.Button();
            this.OutputFileButton = new System.Windows.Forms.Button();
            this.OutputFileTextBox = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.saveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 43);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(56, 15);
            this.label1.TabIndex = 0;
            this.label1.Text = "Input File";
            // 
            // InputFileTextBox
            // 
            this.InputFileTextBox.Location = new System.Drawing.Point(86, 40);
            this.InputFileTextBox.Name = "InputFileTextBox";
            this.InputFileTextBox.Size = new System.Drawing.Size(251, 23);
            this.InputFileTextBox.TabIndex = 3;
            // 
            // InputFileButton
            // 
            this.InputFileButton.Location = new System.Drawing.Point(343, 40);
            this.InputFileButton.Name = "InputFileButton";
            this.InputFileButton.Size = new System.Drawing.Size(37, 24);
            this.InputFileButton.TabIndex = 4;
            this.InputFileButton.Text = "...";
            this.InputFileButton.UseVisualStyleBackColor = true;
            this.InputFileButton.Click += new System.EventHandler(this.InputFileButton_Click);
            // 
            // KeyButton
            // 
            this.KeyButton.Location = new System.Drawing.Point(343, 11);
            this.KeyButton.Name = "KeyButton";
            this.KeyButton.Size = new System.Drawing.Size(37, 24);
            this.KeyButton.TabIndex = 2;
            this.KeyButton.Text = "...";
            this.KeyButton.UseVisualStyleBackColor = true;
            this.KeyButton.Click += new System.EventHandler(this.KeyButton_Click);
            // 
            // KeyFileTextBox
            // 
            this.KeyFileTextBox.Location = new System.Drawing.Point(86, 11);
            this.KeyFileTextBox.Name = "KeyFileTextBox";
            this.KeyFileTextBox.Size = new System.Drawing.Size(251, 23);
            this.KeyFileTextBox.TabIndex = 1;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(13, 14);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(47, 15);
            this.label2.TabIndex = 3;
            this.label2.Text = "Key File";
            // 
            // openKeyFileDialog
            // 
            this.openKeyFileDialog.AddExtension = false;
            this.openKeyFileDialog.DefaultExt = "key";
            this.openKeyFileDialog.Filter = "\"key files (*.key)|*.key|All files (*.*)|*.*\";";
            // 
            // InfoTextBox
            // 
            this.InfoTextBox.BackColor = System.Drawing.SystemColors.InfoText;
            this.InfoTextBox.ForeColor = System.Drawing.SystemColors.ButtonFace;
            this.InfoTextBox.Location = new System.Drawing.Point(13, 139);
            this.InfoTextBox.Name = "InfoTextBox";
            this.InfoTextBox.Size = new System.Drawing.Size(367, 23);
            this.InfoTextBox.TabIndex = 9;
            this.InfoTextBox.Text = "Info";
            this.InfoTextBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // EncodeButton
            // 
            this.EncodeButton.Location = new System.Drawing.Point(86, 101);
            this.EncodeButton.Name = "EncodeButton";
            this.EncodeButton.Size = new System.Drawing.Size(119, 23);
            this.EncodeButton.TabIndex = 7;
            this.EncodeButton.Text = "Encode";
            this.EncodeButton.UseVisualStyleBackColor = true;
            this.EncodeButton.Click += new System.EventHandler(this.EncodeButton_Click);
            // 
            // DecodeButton
            // 
            this.DecodeButton.Location = new System.Drawing.Point(218, 101);
            this.DecodeButton.Name = "DecodeButton";
            this.DecodeButton.Size = new System.Drawing.Size(119, 23);
            this.DecodeButton.TabIndex = 8;
            this.DecodeButton.Text = "Decode";
            this.DecodeButton.UseVisualStyleBackColor = true;
            this.DecodeButton.Click += new System.EventHandler(this.DecodeButton_Click);
            // 
            // OutputFileButton
            // 
            this.OutputFileButton.Location = new System.Drawing.Point(343, 69);
            this.OutputFileButton.Name = "OutputFileButton";
            this.OutputFileButton.Size = new System.Drawing.Size(37, 24);
            this.OutputFileButton.TabIndex = 6;
            this.OutputFileButton.Text = "...";
            this.OutputFileButton.UseVisualStyleBackColor = true;
            this.OutputFileButton.Click += new System.EventHandler(this.OutputFileButton_Click);
            // 
            // OutputFileTextBox
            // 
            this.OutputFileTextBox.Location = new System.Drawing.Point(86, 69);
            this.OutputFileTextBox.Name = "OutputFileTextBox";
            this.OutputFileTextBox.Size = new System.Drawing.Size(251, 23);
            this.OutputFileTextBox.TabIndex = 5;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(13, 72);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(66, 15);
            this.label3.TabIndex = 11;
            this.label3.Text = "Output File";
            // 
            // saveFileDialog
            // 
            this.saveFileDialog.AddExtension = false;
            // 
            // openFileDialog
            // 
            this.openFileDialog.AddExtension = false;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(398, 172);
            this.Controls.Add(this.OutputFileButton);
            this.Controls.Add(this.OutputFileTextBox);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.DecodeButton);
            this.Controls.Add(this.EncodeButton);
            this.Controls.Add(this.InfoTextBox);
            this.Controls.Add(this.KeyButton);
            this.Controls.Add(this.KeyFileTextBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.InputFileButton);
            this.Controls.Add(this.InputFileTextBox);
            this.Controls.Add(this.label1);
            this.Name = "MainForm";
            this.Text = "Crypto";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox InputFileTextBox;
        private System.Windows.Forms.Button InputFileButton;
        private System.Windows.Forms.Button KeyButton;
        private System.Windows.Forms.TextBox KeyFileTextBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.OpenFileDialog openKeyFileDialog;
        private System.Windows.Forms.TextBox InfoTextBox;
        private System.Windows.Forms.Button EncodeButton;
        private System.Windows.Forms.Button DecodeButton;
        private System.Windows.Forms.Button OutputFileButton;
        private System.Windows.Forms.TextBox OutputFileTextBox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.SaveFileDialog saveFileDialog;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
    }
}

