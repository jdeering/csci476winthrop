using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Printing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using ZedGraph;
using ZedGraph.Web;

namespace LoginGUI
{
    /// <remarks>
    /// ChartForm contains the user interface for displaying reports generated in the AdminForm.
    /// </remarks>
    /// <summary>
    /// ChartForm contains the user interface for displaying reports generated in the AdminForm.
    /// </summary>
    public partial class ChartForm : Form
    {
        [System.Runtime.InteropServices.DllImport("gdi32.dll")]
        
        public static extern long BitBlt(IntPtr hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, IntPtr hdcSrc, int nXSrc, int nYSrc, int dwRop); // overridden method.  Copies image into memory.
        /// <summary>
        /// memoryImage stores a bitmap of the chart to be printed. <
        /// </summary>
        private Bitmap memoryImage;
        /// <summary>
        /// CaptureScreen takes a screenshot of the ChartForm, so it can be printed.
        /// [1] Code taken from MSDN.com
        /// </summary>
        private void CaptureScreen()
        {
            Graphics mygraphics = this.CreateGraphics();
            Size s = this.Size;
            memoryImage = new Bitmap(s.Width + 200, (s.Height - 80), mygraphics);
            Graphics memoryGraphics = Graphics.FromImage(memoryImage);
            IntPtr dc1 = mygraphics.GetHdc();
            IntPtr dc2 = memoryGraphics.GetHdc();
            BitBlt(dc2, 0, 0, this.ClientRectangle.Width, (this.ClientRectangle.Height - 65), dc1, 0, 0, 13369376);
            mygraphics.ReleaseHdc(dc1);
            memoryGraphics.ReleaseHdc(dc2);
        }

        /// <summary>
        /// Constructor initializes the ChartForm and creates a user report chart specified by <paramref>usd</paramref>.
        /// </summary>
        /// <param name="usd">UserScoreData structure that holds user score information.</param>
        public ChartForm(UserStats.UserScoreData usd)
        {
            InitializeComponent();
            this.Text = "User Report for " + usd.username;
            CreateGraph(zedGraphControl1, usd);
            SetSize();
        }
        /// <summary>
        /// Constructor initializes the ChartForm and creates a game report chart specified by <paramref>msd</paramref>.
        /// </summary>
        /// <param name="msd">ModuleScoreData structure that holds game score information.</param>
        public ChartForm(UserStats.ModuleScoreData msd)
        {
            InitializeComponent();
            this.Text = "Game Report for " + msd.module;
            CreateGraph(zedGraphControl1, msd);
            SetSize();
        }

        /// <summary>
        /// SetSize sets the size of the chart area in the form.
        /// </summary>
        private void SetSize()
        {
            zedGraphControl1.Location = new Point(10, 10);
            zedGraphControl1.Size = new Size(ClientRectangle.Width - 20, ClientRectangle.Height - 80);
        }

        /// <summary>
        /// CreateGraph creates a graph from the user score data <paramref>usd</paramref>.
        /// </summary>
        /// <param name="zgc">Chart where user data is displayed.</param>
        /// <param name="usd">Contains user score information.</param>
        private void CreateGraph(ZedGraphControl zgc, UserStats.UserScoreData usd)
        {
            GraphPane userPane = zgc.GraphPane;

            userPane.Title.Text = usd.module + " statistics for \n" + usd.username;
            userPane.XAxis.Title.Text = "Date";
            userPane.YAxis.Title.Text = "Score";

            double x, y;
            PointPairList graphList = new PointPairList();
            for (int i = 0; i < usd.listsize; i++)
            {
                x = (double)new XDate(DateTime.ParseExact(usd.recent[i].date, "MM/dd/yy", null));
                y = (double)usd.recent[i].score;
                graphList.Add(x, y);
            }

            LineItem userCurve = userPane.AddCurve(usd.username, graphList, Color.Red, SymbolType.Circle);

            userPane.XAxis.Type = AxisType.Date;

            zgc.AxisChange();
        }

        /// <summary>
        /// CreateGraph creates a graph from the user score data <paramref>usd</paramref>.
        /// </summary>
        /// <param name="zgc">Chart where user data is displayed.</param>
        /// <param name="msd">Contains game score information.</param>
        private void CreateGraph(ZedGraphControl zgc, UserStats.ModuleScoreData msd)
        {
            GraphPane userPane = zgc.GraphPane;

            userPane.Title.Text = msd.module + " Statistics";
            userPane.XAxis.Title.Text = "User";
            userPane.YAxis.Title.Text = "Score";

            string[] labels = new string[msd.listsize];
            double[] y = new double[msd.listsize];

            for (int i = 0; i < msd.listsize; i++)
            {
                labels[i] = msd.allData[i].username;
                y[i] = msd.allData[i].score;
            }

            BarItem userBar = userPane.AddBar("Score", null, y, Color.Red);
            userBar.Bar.Fill = new Fill(Color.Red, Color.White, Color.Red);

            userPane.XAxis.MajorTic.IsBetweenLabels = true;
            userPane.XAxis.Scale.TextLabels = labels;
            userPane.XAxis.Type = AxisType.Text;

            zgc.AxisChange();


        }

        /// <summary>
        /// printDocument1_PrintPage adds the <paramref>memoryImage</paramref> to the print buffer.
        /// </summary>
        /// <param name="sender">.NET GUI parameter</param>
        /// <param name="e">.NET printer parameter</param>
        private void printDocument1_PrintPage(object sender, System.Drawing.Printing.PrintPageEventArgs e)
        {
            e.Graphics.DrawImage(memoryImage, 0, 0);
        }

        private void btn_Print_Click(object sender, EventArgs e)
        {
            // Capture screenshot in memory
            CaptureScreen();

            try
            {
                // add print event handlers to print control
                printDocument1.PrintPage += new PrintPageEventHandler(printDocument1_PrintPage);

                // set margins of document to be printed
                Margins margins = new Margins(100, 100, 100, 100);
                printDocument1.DefaultPageSettings.Margins = margins;
                // print document
                printDocument1.Print();
            }
            catch (Exception ex)
            {
                // Print page failed
                MessageBox.Show("An error occurred printing the chart - " + ex.Message);
            }
        }
    }
}