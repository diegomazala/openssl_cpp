using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace crypto
{
    public partial class MainForm : Form
    {
        private class crypto_dll
        {
            [DllImport("openssl_cpp_crypto")]
            public static extern bool aes_cbc_create_key(string out_filename);

            [DllImport("openssl_cpp_crypto")]
            public static extern bool aes_cbc_encode_to_file(string in_filename_data, string in_filename_key, string out_filename_data);

            [DllImport("openssl_cpp_crypto")]
            public static extern bool aes_cbc_decode_to_file(string in_filename_data, string in_filename_key, string out_filename_data);

            [DllImport("openssl_cpp_crypto")]
            public static extern int aes_cbc_decode_to_str(string in_filename_data, string in_filename_key, StringBuilder out_decoded_data);
        }

        public MainForm()
        {
            InitializeComponent();

            LoadConfig();
        }

        private void KeyButton_Click(object sender, EventArgs e)
        {
            openKeyFileDialog.ShowDialog();
            KeyFileTextBox.Text = openKeyFileDialog.FileName;
        }

        private void InputFileButton_Click(object sender, EventArgs e)
        {
            openFileDialog.ShowDialog();
            InputFileTextBox.Text = openFileDialog.FileName;
        }

        private void OutputFileButton_Click(object sender, EventArgs e)
        {
            saveFileDialog.ShowDialog();
            OutputFileTextBox.Text = saveFileDialog.FileName;
        }

        private void EncodeButton_Click(object sender, EventArgs e)
        {
            if (crypto_dll.aes_cbc_encode_to_file(InputFileTextBox.Text, KeyFileTextBox.Text, OutputFileTextBox.Text))
                InfoTextBox.Text = "File encoded successfully";
            else
                InfoTextBox.Text = "Encode failed";
        }

        private void DecodeButton_Click(object sender, EventArgs e)
        {
            if (crypto_dll.aes_cbc_decode_to_file(InputFileTextBox.Text, KeyFileTextBox.Text, OutputFileTextBox.Text))
                InfoTextBox.Text = "File decoded successfully";
            else
                InfoTextBox.Text = "Decode failed";

            StringBuilder str = new StringBuilder(1024);
            int str_size = crypto_dll.aes_cbc_decode_to_str(InputFileTextBox.Text, KeyFileTextBox.Text, str);
            if (str_size > 0)
            {
                System.IO.File.WriteAllText(System.IO.Path.ChangeExtension(OutputFileTextBox.Text, ".json"), str.ToString());
            }
            else
            {
                MessageBox.Show("Decode failed", this.Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        protected void LoadConfig()
        {
            try
            {
                using (System.IO.StreamReader sr = new System.IO.StreamReader("config.cfg"))
                {
                    KeyFileTextBox.Text = sr.ReadLine();
                    InputFileTextBox.Text = sr.ReadLine();
                    OutputFileTextBox.Text = sr.ReadLine();
                }
            }
            catch(Exception e)
            {
            }
        }

        protected void SaveConfig()
        {
            using (System.IO.StreamWriter sw = new System.IO.StreamWriter("config.cfg"))
            {
                sw.WriteLine(KeyFileTextBox.Text);
                sw.WriteLine(InputFileTextBox.Text);
                sw.WriteLine(OutputFileTextBox.Text);
            }
        }

        private void keyGenerateButton_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("Are you sure you want to generate a new key", 
                this.Text, MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation) 
                != DialogResult.Yes)
                return;

            if (saveKeyFileDialog.ShowDialog() != DialogResult.OK)
                return;

            if (!crypto_dll.aes_cbc_create_key(saveKeyFileDialog.FileName))
            {
                MessageBox.Show("Key generation failed", this.Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            KeyFileTextBox.Text = saveKeyFileDialog.FileName;
        }
    }
}
