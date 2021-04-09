using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Runtime.InteropServices;

namespace License_Generator
{
    public partial class MainForm : Form
    {
        private class crypto_dll
        {
            [DllImport("openssl_cpp_crypto")]
            public static extern bool aes_cbc_create_key(string out_filename);

            [DllImport("openssl_cpp_crypto")]
            public static extern bool aes_cbc_encode(string in_filename_data, string in_filename_key, string out_filename_data);

            [DllImport("openssl_cpp_crypto")]
            public static extern bool aes_cbc_decode(string in_filename_data, string in_filename_key, string out_filename_data);
        }

        public class LicenseData
        {
            public string Artist { get; set; }
            public string Art { get; set; }
            public string BeginDate { get; set; }
            public string EndDate { get; set; }
        }

        LicenseData license = new LicenseData();

        public MainForm()
        {
            InitializeComponent();
        }

        private void openKeyFileButon_Click(object sender, EventArgs e)
        {
            openFileDialog.ShowDialog();
            keyFileTextBox.Text = openFileDialog.FileName;
        }

        private void generateButton_Click(object sender, EventArgs e)
        {
            if (saveFileDialog.ShowDialog() != DialogResult.OK)
                return;

            license.Artist = artistNameTextBox.Text;
            license.Art = artTitleTextBox.Text;
            license.BeginDate = beginDateTimePicker.Value.ToString("d");
            license.EndDate = endDateTimePicker.Value.ToString("d"); ;

            var jsonFilename = Path.ChangeExtension(saveFileDialog.FileName, ".json");
            var jsonString = JsonSerializer.Serialize(license);
            File.WriteAllText(jsonFilename, jsonString);

            if (crypto_dll.aes_cbc_encode(jsonFilename, keyFileTextBox.Text, saveFileDialog.FileName))
                MessageBox.Show("License file generated successfully", this.Text);
            else
                MessageBox.Show("License file generated failed", this.Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
