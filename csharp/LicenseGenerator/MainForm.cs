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
            public static extern bool aes_cbc_encode_to_file(string in_filename_data, string in_filename_key, string out_filename_data);

            [DllImport("openssl_cpp_crypto")]
            public static extern bool aes_cbc_decode_to_file(string in_filename_data, string in_filename_key, string out_filename_data);

            [DllImport("openssl_cpp_crypto")]
            public static extern int aes_cbc_decode_to_str(string in_filename_data, string in_filename_key, StringBuilder out_decoded_data);
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
            if (openKeyFileDialog.ShowDialog() != DialogResult.OK)
                return;
            keyFileTextBox.Text = openKeyFileDialog.FileName;
        }

        private void generateButton_Click(object sender, EventArgs e)
        {
            if (saveLicenseFileDialog.ShowDialog() != DialogResult.OK)
                return;

            license.Artist = artistNameTextBox.Text;
            license.Art = artTitleTextBox.Text;
            license.BeginDate = beginDateTimePicker.Value.ToString("d");
            license.EndDate = endDateTimePicker.Value.ToString("d"); ;

            var jsonFilename = Path.ChangeExtension(saveLicenseFileDialog.FileName, ".json");
            var jsonString = JsonSerializer.Serialize(license);
            File.WriteAllText(jsonFilename, jsonString);

            try
            {
                if (crypto_dll.aes_cbc_encode_to_file(jsonFilename, keyFileTextBox.Text, saveLicenseFileDialog.FileName))
                    MessageBox.Show("License file generated successfully", this.Text);
                else
                    MessageBox.Show("License file generated failed", this.Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch(Exception)
            {
                MessageBox.Show("Could not generate license file",
                    this.Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void loadButton_Click(object sender, EventArgs e)
        {
            try
            {
                if (!File.Exists(keyFileTextBox.Text))
                {
                    if (openKeyFileDialog.ShowDialog() != DialogResult.OK)
                        return;
                    keyFileTextBox.Text = openKeyFileDialog.FileName;
                }

                if (openLicenseFileDialog.ShowDialog() != DialogResult.OK)
                    return;

                string jsonStr = string.Empty;

                string fileExtension = Path.GetExtension(openLicenseFileDialog.FileName);
                if (fileExtension == ".aa")
                {
                    StringBuilder str = new StringBuilder(1024);
                    int str_size = crypto_dll.aes_cbc_decode_to_str(openLicenseFileDialog.FileName, keyFileTextBox.Text, str);
                    if (str_size > 0)
                    {
                        jsonStr = str.ToString();
                    }
                }
                else if (fileExtension == ".json")
                {
                    System.IO.File.ReadAllText(openLicenseFileDialog.FileName);
                }

                if (jsonStr.Length < 1)
                {
                    MessageBox.Show("Could not decode license file. Check if you are using the correct key file", 
                        this.Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                license = JsonSerializer.Deserialize<LicenseData>(jsonStr);

                artistNameTextBox.Text = license.Artist;
                artTitleTextBox.Text = license.Art;
                beginDateTimePicker.Value = DateTime.Parse(license.BeginDate);
                endDateTimePicker.Value = DateTime.Parse(license.EndDate);
            }
            catch(Exception)
            {
                MessageBox.Show("Could not decode license file",
                    this.Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void newKeyButton_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("Are you sure you want to generate a new key",
                this.Text, MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation)
                != DialogResult.Yes)
                return;

            if (saveKeyFileDialog.ShowDialog() != DialogResult.OK)
                return;

            try 
            { 
                if (!crypto_dll.aes_cbc_create_key(saveKeyFileDialog.FileName))
                {
                    MessageBox.Show("Key generation failed", this.Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                keyFileTextBox.Text = saveKeyFileDialog.FileName;
            }
            catch (Exception)
            {
                MessageBox.Show("Could not generate key file",
                    this.Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
