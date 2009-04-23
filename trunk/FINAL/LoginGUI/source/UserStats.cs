using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.IO;
using System.Diagnostics;

namespace LoginGUI
{
    /// <remarks>
    /// UserStats contains methods to parse user and module score XML files,
    /// as well as the structures to contain the data of these files.
    /// </remarks>
    /// <summary>
    /// UserStats contains methods to parse user and module score XML files,
    /// as well as the structures to contain the data of these files.
    /// </summary>
    public class UserStats
    {
        /// <summary>
        /// UserScoreNodes hold the date, time and score of a single user score.
        /// </summary>
        public struct UserScoreNode
        {
            /// <summary>
            /// date stores the date of a single user score.
            /// </summary>
            public string date;
            /// <summary>
            /// time stores the time of a single user score.
            /// </summary>
            public string time;
            /// <summary>
            /// score stores a single user score.
            /// </summary>
            public int score;
        }

        /// <summary>
        /// UserScoreData holds the username, module, last score, best score, first score, average score, list of UserScoreNodes, and the list size of the recent scores.
        /// </summary>
        public struct UserScoreData
        {
            /// <summary>
            /// username stores the username.
            /// </summary>
            public string username;
            /// <summary>
            /// module stores the name of the module.
            /// </summary>
            public string module;
            /// <summary>
            /// last stores the user's last score.
            /// </summary>
            public int last;
            /// <summary>
            /// best stores the user's best score.
            /// </summary>
            public int best;
            /// <summary>
            /// first stores the user's first score.
            /// </summary>
            public int first;
            /// <summary>
            /// average stores the user's average score.
            /// </summary>
            public int average;
            /// <summary>
            /// listsize stores the number of scores stored in <paramref>recent</paramref>.
            /// </summary>
            public int listsize;
            /// <summary>
            /// recent stores a list of UserScoreNodes representing all the scores of this user.
            /// </summary>
            public List<UserScoreNode> recent;
        }
        /// <summary>
        /// ModuleScoreNodes hold the username and score of an individual score.
        /// </summary>
        public struct ModuleScoreNode
        {
            /// <summary>
            /// username stores the username.
            /// </summary>
            public string username;
            /// <summary>
            /// score stores a single user score.
            /// </summary>
            public int score;
        }

        /// <summary>
        /// ModuleScoreData holds the module name, a list of ModuleScoreNodes, and the size of this list.
        /// </summary>
        public struct ModuleScoreData
        {
            /// <summary>
            /// module stores the name of the module.
            /// </summary>
            public string module;
            /// <summary>
            /// listsize stores the number of scores in <paramref>allData</paramref>.
            /// </summary>
            public int listsize;
            /// <summary>
            /// allData is a list of ModuleScoreNodes representing all the scores for the module.
            /// </summary>
            public List<ModuleScoreNode> allData;
        }

        /// <summary>
        /// parseUserScore parses a user's XML score file to extract significant data and store in a UserScoreNode structure.
        /// </summary>
        /// <param name="username">Defines the name of the user whose file to parse.</param>
        /// <param name="module">Defines the name of the game being parsed.</param>
        /// <returns>A UserScoreData structure that contains all the significant data from <paramref>username</paramref> in <paramref>module</paramref>.</returns>
        public UserScoreData parseUserScore(string username, string module)
        {
            UserScoreNode scores = new UserScoreNode();
            UserScoreData userData = new UserScoreData();
            List<UserScoreNode> templist = new List<UserScoreNode>();
            userData.username = username;
            userData.module = module;
            userData.listsize = 0;

            Trace.WriteLine(userData.username);

//************** FILENAME HERE ************************************
//****************************************************************************
//*******************************************
            XmlTextReader textParser = new XmlTextReader(Directory.GetCurrentDirectory() + "\\modules\\" + module + "\\users\\" + username + ".xml");
            textParser.Read();

            while (textParser.Read())
            {
                if (textParser.NodeType == XmlNodeType.Element)
                    switch (textParser.Name)
                    {
                        case "FIRSTSCORE":
                            userData.first = Int32.Parse(textParser.ReadString());
                            break;
                        case "LASTSCORE":
                            userData.last = Int32.Parse(textParser.ReadString());
                            break;
                        case "AVERAGESCORE":
                            userData.average = Int32.Parse(textParser.ReadString());
                            break;
                        case "BESTSCORE":
                            userData.best = Int32.Parse(textParser.ReadString());
                            break;
                        case "SCORE":
                            scores.date = textParser.GetAttribute("date").ToString();
                            scores.time = textParser.GetAttribute("time").ToString();
                            scores.score = Int32.Parse(textParser.ReadString());
                            templist.Add(scores);
                            userData.listsize++;
                            break;
                        default: break;
                    }
            }
            userData.recent = templist;
            return userData;
        }

        /// <summary>
        /// parseModuleScore parses a module's XML file to extract scores and their corresponding users.
        /// </summary>
        /// <param name="module">Defines the name of the module to be parsed.</param>
        /// <returns>A ModuleScoreData structure that contains all the significant data from <paramref>module</paramref>.</returns>
        public ModuleScoreData parseModuleScore(string module)
        {
            ModuleScoreNode scores = new ModuleScoreNode();
            ModuleScoreData moduleData = new ModuleScoreData();
            List<ModuleScoreNode> templist = new List<ModuleScoreNode>();
            moduleData.module = module;
            moduleData.listsize = 0;

//************** FILENAME HERE ************************************
//****************************************************************************
//*******************************************

            XmlTextReader textParser = new XmlTextReader(Directory.GetCurrentDirectory() + "\\modules\\" + module + "\\users\\scores.xml");
            textParser.Read();

            while (textParser.Read())
            {
                if (textParser.NodeType == XmlNodeType.Element && textParser.Name == "USER")
                {
                    scores.username = textParser.GetAttribute("name").ToString();
                    scores.score = Int32.Parse(textParser.ReadString());
                    templist.Add(scores);
                    moduleData.listsize++;
                }
            }

            moduleData.allData = templist;
            return moduleData;
        }
    }
}
