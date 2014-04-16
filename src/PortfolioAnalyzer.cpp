// COPYRIGHT © 2011, Donne Martin
// All Rights Reserved.
//
//******************************************************************************
//
// File Name:     PortfolioAnalyzer.cpp
//
// File Overview: Represents a PortfolioAnalyzer
//
//******************************************************************************
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added class
//******************************************************************************

#include "stdafx.h"
#include <iostream>
#include "PortfolioAnalyzer.h"

//******************************************************************************
// File scope (static) variable definitions
//******************************************************************************

// None

//******************************************************************************
// Function : main                                   
// Process  : Runs PortfolioAnalyzer            
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
int _tmain(int argc, _TCHAR* argv[])
{
   try
   {
      PortfolioAnalyzer portfolioAnalyzer; // Analyzes the list of stocks
      portfolioAnalyzer.addDefaultStocksToPortfolio();
      portfolioAnalyzer.analyzePortfolio();
   }
   catch (const exception& exception)
   {
      cout << exception.what() << endl;
      cout << "Terminating program" << endl;
   }
      
   char pauseBeforeTerminate = ' '; // Don't let the program terminate by itself
   cin >> pauseBeforeTerminate;

   return 0;
}

//******************************************************************************
// Function : constructor                                   
// Process  : None
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************                    
PortfolioAnalyzer::PortfolioAnalyzer() 
{
} // end PortfolioAnalyzer::PortfolioAnalyzer

//******************************************************************************
// Function : destructor                                   
// Process  : None           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
PortfolioAnalyzer::~PortfolioAnalyzer()
{
} // end PortfolioAnalyzer::~PortfolioAnalyzer

//******************************************************************************
// Function : addDefaultStocksToPortfolio                                   
// Process  : Adds the list of default stocks
//             Data taken on 6/25 from the homework instructions:
//                Set the screener criteria as follows:
//                   P/E Ratio min 1 max 15
//                   52w Price Change min 6 max 1000
//                   Last Price min 5 max 100
//                Click the top of the 52w Price Change column 
//                until the column is sorted highest to lowest
// Notes    : For next iteration, consider looking for all csv files
//             In a specific folder in case the list of stocks changes
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
void PortfolioAnalyzer::addDefaultStocksToPortfolio()
{
   vector<char*> stockDataFileNames;   // List of stock data file names
                                       // Could be more efficient by setting
                                       // the size beforehand to an expected
                                       // value, consider for next iteration
   stockDataFileNames.push_back("StockDataOME.csv");
   stockDataFileNames.push_back("StockDataSHS.csv");
   stockDataFileNames.push_back("StockDataIOSP.csv");
   stockDataFileNames.push_back("StockDataAPL.csv");
   stockDataFileNames.push_back("StockDataBSQR.csv");
   stockDataFileNames.push_back("StockDataHS.csv");
   stockDataFileNames.push_back("StockDataWLK.csv");
   stockDataFileNames.push_back("StockDataDEPO.csv");
   stockDataFileNames.push_back("StockDataNL.csv");
   stockDataFileNames.push_back("StockDataATML.csv");

   this->setStockDataFiles(stockDataFileNames);
}

//******************************************************************************
// Function : analyzePortfolio                                   
// Process  : Loop through all of the stock data analyzers
//             Analyze the stock
//             Determine the highest MACD of all stocks analyzed
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
void PortfolioAnalyzer::analyzePortfolio()
{
   int numFiles = this->getNumStockDataFiles(); // Number of stock data files

   // Loop through all of the stock data analyzers
   for (int analyzerIndex = 0; analyzerIndex < numFiles; ++analyzerIndex)
   {
      // Analyze the stock
      this->stockAnalyzers[analyzerIndex].analyzeStock();
   }

   cout << "---Calculating highest MACD from all stock data---" << endl << endl;

   // Determine the highest MACD of all stocks analyzed
   this->outputStockWithHighestMACDSlope();
}

//******************************************************************************
// Function : outputStockWithHighestMACDSlope                                   
// Process  : Loop through all of the stock data analyzers
//             If this is not the first analyzer
//                Retrieve the current analyzer's MACD
//                if the current MACD is higher than the previous max
//                   Set highMACD to the current analyzer's MACD and
//                   stockDataFileName to current analyzer's stock data file
//             Else
//                   Set highMACD to the first analyzer's MACD and
//                   stockDataFileName to first analyzer's stock data file
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
char* PortfolioAnalyzer::outputStockWithHighestMACDSlope()
{
   double currMACDSlope = 0.0;                          // Current MACD slope 
                                                        // from past two days
   double highMACDSlope = 0.0;                          // Highest MACD slope 
                                                        // from past two days
   int    numAnalyzers  = this->getNumStockAnalyzers(); // Number of analyzers 
                                                        // to look through
   char*  dataFileName  = "";                           // Current data file

   // Loop through all of the stock data analyzers
   for (int analyzerIndex = 0; analyzerIndex < numAnalyzers; ++analyzerIndex)
   {
      // If this is not the first analyzer
      if (analyzerIndex != 0)
      {
         // Retrieve the current analyzer's MACD
         currMACDSlope = this->stockAnalyzers[analyzerIndex].getSlopeMACD();

         // if the current MACD is higher than the previously highest value
         if (highMACDSlope < currMACDSlope)
         {
            // Set highMACD to the current analyzer's MACD and
            // stockDataFileName to the current analyzer's stock data file name
            highMACDSlope = currMACDSlope;
            dataFileName  = 
               this->stockAnalyzers[analyzerIndex].getStockDataFileName();
         }
      }
      // If this is the first analyzer
      else {
         // Set highMACD to the first analyzer's MACD and
         // stockDataFileName to the first analyzer's stock data file name
         highMACDSlope = this->stockAnalyzers[analyzerIndex].getSlopeMACD();
         dataFileName  = 
            this->stockAnalyzers[analyzerIndex].getStockDataFileName();
      }
   }

   // Output the results
   cout << "Highest MACD two day slope found calculating: " << dataFileName;
   cout << endl;
   cout << "Highest MACD two day slope value: " << highMACDSlope << endl;

   return dataFileName;
}

//******************************************************************************
// Function : setStockDataFiles                                   
// Process  : Mutator for stockDataFileNames
//             Set our data files to the input files           
//             Set the size of our stock and stock analyzer lists based 
//             on the number of stock data files provided.
//             Loop through all of the stock data analyzers
//                Ensure our analyzer has the proper data file and stock set
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
void PortfolioAnalyzer::setStockDataFiles(
   const vector<char*>& stockDataFileNames)
{
   // Set our data files to the input files
   this->stockDataFileNames = stockDataFileNames;
   
   // Set the size of our stock and stock analyzer lists based 
   // on the number of stock data files provided.
   int numDataFiles = this->getNumStockDataFiles();
   this->stocks.resize(numDataFiles);
   this->stockAnalyzers.resize(numDataFiles);

   // Loop through all of the stock data analyzers
   for (int analyzerIndex = 0; analyzerIndex < numDataFiles; ++analyzerIndex)
   {
      // Ensure our analyzer has the proper data file and stock set
      this->stockAnalyzers[analyzerIndex].
         setStockDataFileName(this->stockDataFileNames[analyzerIndex]);

      this->stockAnalyzers[analyzerIndex].setStock(this->stocks[analyzerIndex]);
   }
}