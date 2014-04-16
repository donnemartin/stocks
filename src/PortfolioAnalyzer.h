//******************************************************************************
//
// File Name:     PortfolioAnalyzer.h
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

#ifndef PortfolioAnalyzer_h
#define PortfolioAnalyzer_h

#include "StockAnalyzer.h"

//******************************************************************************
//
// Class:    PortfolioAnalyzer
//
// Overview: Represents a PortfolioAnalyzer
//             Contains a list of stocks
//             Contains a list of stock analyzers to load data to stocks
//                and analyze each stock
//             Contains a list of stock data files, used to setup each
//                stock analyzer
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added class
//
//******************************************************************************
class PortfolioAnalyzer
{
public:
   
   //***************************************************************************
   // Function    : constructor                                   
   // Description : None
   // Constraints : None
   //***************************************************************************
   PortfolioAnalyzer();

   //***************************************************************************
   // Function    : destructor                                   
   // Description : Performs cleanup tasks              
   // Constraints : None
   //***************************************************************************
   virtual ~PortfolioAnalyzer();   

   // Member functions in alphabetical order   
      
   //***************************************************************************
   // Function    : addDefaultStocksToPortfolio                                   
   // Description : Adds the default stocks to the portfolio
   //                The default stocks are those taken from the hw instructions
   // Constraints : None
   //***************************************************************************
   void addDefaultStocksToPortfolio();
      
   //***************************************************************************
   // Function    : analyzePortfolio                                   
   // Description : Calls analyzeStock on all stocks then findHighestMACDStock            
   // Constraints : None
   //***************************************************************************
   void analyzePortfolio();

   //***************************************************************************
   // Function    : getNumStockAnalyzers                                   
   // Description : Retrieves the number of stock analyzers
   // Constraints : None
   //***************************************************************************
   inline int getNumStockAnalyzers() const;

   //***************************************************************************
   // Function    : getNumStockDataFiles                                   
   // Description : Retrieves the number of stock data files
   // Constraints : None
   //***************************************************************************
   inline int getNumStockDataFiles() const;

   //***************************************************************************
   // Function    : getNumStocks                                   
   // Description : Retrieves the number of stocks
   // Constraints : None
   //***************************************************************************
   inline int getNumStocks() const;
      
   //***************************************************************************
   // Function    : getStockAnalyzerAtIndex                                   
   // Description : Retrieves the stock analyzer at the specified index            
   // Constraints : Throws an out_of_range exception for invalid index
   //***************************************************************************
   inline void getStockAnalyzerAtIndex(
      const int index, 
      StockAnalyzer& stockAnalyzer) const;
      
   //***************************************************************************
   // Function    : getStockAtIndex                                   
   // Description : Retrieves the stock at the specified index            
   // Constraints : Throws an out_of_range exception for invalid index
   //***************************************************************************
   inline void getStockAtIndex(
      const int index, 
      Stock& stock) const;
      
   //***************************************************************************
   // Function    : getStockDataFileNameAtIndex                                   
   // Description : Retrieves the stock data file name at the specified index            
   // Constraints : Throws an out_of_range exception for invalid index
   //***************************************************************************
   inline void getStockDataFileNameAtIndex(
      const int index, 
      char* stockDataFileName) const;
      
   //***************************************************************************
   // Function    : outputStockWithHighestMACDSlope                                  
   // Description : Outputs the stock with the highest MACD slope
   //                based on the most recent two days of MACD values
   // Constraints : None
   //***************************************************************************
   char* outputStockWithHighestMACDSlope();
      
   //***************************************************************************
   // Function    : setStockDataFiles                                   
   // Description : Mutator for stockDataFileNames
   //                Sets the stock data files used for analysis            
   // Constraints : None
   //***************************************************************************
   void setStockDataFiles(const vector<char*>& stockDataFileNames);

private:   
   vector<char*>           stockDataFileNames;  // List of stock data file names
   vector<Stock>           stocks;              // List of stocks
   vector<StockAnalyzer>   stockAnalyzers;      // List of stock analyzers
}; // end class PortfolioAnalyzer

//******************************************************************************
// Function : getNumStockAnalyzers                                   
// Process  : Retrieve the number of stock analyzers          
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline int PortfolioAnalyzer::getNumStockAnalyzers() const
{
   return this->stockAnalyzers.size();
}

//******************************************************************************
// Function : getNumStockDataFiles                                   
// Process  : Retrieve the number of stock data files     
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline int PortfolioAnalyzer::getNumStockDataFiles() const
{
   return this->stockDataFileNames.size();
}

//******************************************************************************
// Function : getNumStocks                                   
// Process  : Retrieve the number of stocks          
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline int PortfolioAnalyzer::getNumStocks() const
{
   return this->stocks.size();
}

//******************************************************************************
// Function : getStockAnalyzerAtIndex                                   
// Process  : Retrieve the stock analyzer at the specified index            
// Notes    : Throws an out_of_range exception for invalid index
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline void PortfolioAnalyzer::getStockAnalyzerAtIndex(
   const int index, 
   StockAnalyzer& stockAnalyzer) const
{ 
   stockAnalyzer = this->stockAnalyzers.at(index); 
}

//******************************************************************************
// Function : getStockAtIndex                                   
// Process  : Retrieve the stock at the specified index            
// Notes    : Throws an out_of_range exception for invalid index
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline void PortfolioAnalyzer::getStockAtIndex(
   const int index, 
   Stock& stock) const
{ 
   stock = this->stocks.at(index); 
}

//******************************************************************************
// Function : getStockDataFileNameAtIndex                                   
// Process  : Retrieve the stock data file name at the specified index          
// Notes    : Throws an out_of_range exception for invalid index
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline void PortfolioAnalyzer::getStockDataFileNameAtIndex(
   const int index, 
   char* stockDataFileName) const
{ 
   stockDataFileName = this->stockDataFileNames.at(index); 
}
      
#endif // PortfolioAnalyzer_h