using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab1SGBD
{
    public partial class Form1 : Form
    {

        SqlDataAdapter daSuppliers;
        SqlDataAdapter daAnimals;
        SqlConnection connection;

        DataSet dataSet;
        BindingSource bsSuppliers;
        BindingSource bsAnimals;

        string connectionString = @"Data Source=DELL\SQLEXPRESS;Initial Catalog = PetShopDB; Integrated Security = True; TrustServerCertificate=True";

        public Form1()
        {
            InitializeComponent();
            FillData();
            allSuppliers.SelectionChanged += allSuppliers_selectionChanged;
        }


        string getConnectionString()
        { return connectionString; }


        private void Form1_Load(object sender, EventArgs e)
        {

        }

        void FillData()
        {

            using (this.connection = new SqlConnection(getConnectionString()))
            {
                this.connection.Open();
                daSuppliers = new SqlDataAdapter("Select * from Suppliers", this.connection);
                daAnimals = new SqlDataAdapter("Select * from Animals", this.connection);

                this.dataSet = new DataSet();
                this.daSuppliers.Fill(dataSet, "Suppliers");
                this.daAnimals.Fill(dataSet, "Animals");


                bsSuppliers = new BindingSource();
                bsSuppliers.DataSource = dataSet;
                bsSuppliers.DataMember = "Suppliers";
                allSuppliers.DataSource = bsSuppliers;


                bsAnimals = new BindingSource();
                bsAnimals.DataSource = dataSet;
                bsAnimals.DataMember = "Animals";
                animalsGrid.DataSource = bsAnimals;

                connection.Close();


            }





        }

        private void Form1_Load_1(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            try
            {
                SqlConnection cn = new SqlConnection(connectionString);
                if (cn.State == System.Data.ConnectionState.Closed)
                    cn.Open();
                MessageBox.Show("Test connection succeded", "Message", MessageBoxButtons.OK, MessageBoxIcon.Information);

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Message", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void dataGridView3_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void allSuppliers_selectionChanged(object sender, EventArgs e)
        {
            using (SqlConnection conn = new SqlConnection(getConnectionString()))  
            {
                conn.Open();

                if (allSuppliers.CurrentRow != null)
                {
                    int supID = Convert.ToInt32(allSuppliers.CurrentRow.Cells["supplierID"].Value);

                    SqlCommand cmd = new SqlCommand("SELECT * FROM Animals WHERE supplierID = @supplierID", conn);
                    cmd.Parameters.AddWithValue("@supplierID", supID);

                    DataView dv = new DataView(dataSet.Tables["Animals"]);
                    dv.RowFilter = $"supplierID = {supID}";
                    bsAnimals.DataSource = dv;
                }
            }



        }

        private void button1_Click(object sender, EventArgs e)
        {

            try
            {
                bsSuppliers.EndEdit();
                bsAnimals.EndEdit();
                allSuppliers.EndEdit();
                animalsGrid.EndEdit();

                if (dataSet.HasChanges())
                {
                    using (SqlConnection conn = new SqlConnection(getConnectionString()))
                    {
                        conn.Open();

                        daSuppliers.SelectCommand = new SqlCommand("SELECT * FROM Suppliers", conn);
                        daAnimals.SelectCommand = new SqlCommand("SELECT * FROM Animals", conn);

                        SqlCommandBuilder cmdBuilderSuppliers = new SqlCommandBuilder(daSuppliers);
                        SqlCommandBuilder cmdBuilderAnimals = new SqlCommandBuilder(daAnimals);

                        daSuppliers.Update(dataSet, "Suppliers");
                        daAnimals.Update(dataSet, "Animals");

                        dataSet.Tables["Animals"].Clear();
                        daAnimals.Fill(dataSet, "Animals");

                        MessageBox.Show("Updated successfully!");
                    }
                }
                else
                {
                    MessageBox.Show("No observed updates.");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }


        private void button2_Click(object sender, EventArgs e)
        {

            try
            {

                if (animalsGrid.CurrentRow != null)
                {
                    int rowIndex = animalsGrid.CurrentRow.Index;
                    DialogResult result = MessageBox.Show("Are you sure you want to delete this entry?", "Confirm Deletion", MessageBoxButtons.YesNo, MessageBoxIcon.Warning);

                    if (result == DialogResult.Yes)
                    {
                        using (SqlConnection conn = new SqlConnection(getConnectionString()))
                        {
                            conn.Open();

                            int animalID = Convert.ToInt32(animalsGrid.Rows[rowIndex].Cells["animalID"].Value);

                            DataRow[] animalRow = dataSet.Tables["Animals"].Select($"animalID = {animalID}");
                            if (animalRow.Length > 0)
                            {
                                animalRow[0].Delete();
                            }

                            daAnimals.DeleteCommand = new SqlCommand("delete from Animals where animalID = @animalID", conn);
                            daAnimals.DeleteCommand.Parameters.AddWithValue("@animalID", animalID);


                            daAnimals.Update(dataSet, "Animals");

                            MessageBox.Show("Deleted successfully!");
                            animalsGrid.Refresh();
                        }
                    }
                }
                else
                {
                    MessageBox.Show("No row selected for deletion.");
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show("Error while deleting: " + ex.Message);
            }
                
            
          
        }

    }
}
