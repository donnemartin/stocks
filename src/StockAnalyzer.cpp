// COPYRIGHT © 2011, Donne Martin
// All Rights Reserved.
//
//******************************************************************************
//
// File Name:     StockAnalyzer.cpp
//
// File Overview: Represents a StockAnalyzer
//
//******************************************************************************
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added class
//******************************************************************************

#include "stdafx.h"
#include <exception>
#include <iostream>
#include <fstream>

#include "StockAnalyzer.h"

//******************************************************************************
// File scope (static) variable definitions
//******************************************************************************

// None

//******************************************************************************
// Function : constructor                                   
// Process  : Call initPeriodsToDefaults
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************                    
StockAnalyzer::StockAnalyzer() 
{
   this->initPeriodsToDefaults();
} // end StockAnalyzer::StockAnalyzer

//******************************************************************************  
// Function : constructor                                   
// Process  : Call initPeriodsToDefaults
//             Set the stock data file name
//             Set the stock
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************  
StockAnalyzer::StockAnalyzer(
   char* stockDataFileName,
   const Stock& stock) 
{  
   this->initPeriodsToDefaults();
   this->setStockDataFileName(stockDataFileName);     
   this->setStock(stock);      
}

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
StockAnalyzer::~StockAnalyzer()
{
} // end StockAnalyzer::~StockAnalyzer

//******************************************************************************
// Function : analyzeStock                                   
// Process  : Call parsePricesFromDataFile to parse the data from the stock file
//             Perform the stock analysis with the fast period
//                Calculate first period SMA
//                Calculate EMA multiplier
//                Calculate EMA
//             Perform the stock analysis with the slow period
//                Calculate first period SMA
//                Calculate EMA multiplier
//                Calculate EMA
//             Calculate the MACD
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
void StockAnalyzer::analyzeStock()
{
   // Parse the data from the stock file
   this->parsePricesFromDataFile();

   cout << "Performing stock analyzis..." << endl << endl;
   cout << "Period " << this->getPeriodsFast() << endl;
   
   // Perform the stock analysis with the fast period
   // Formatted to fit 80 chars
   // Calculate first period SMA
   this->calculateFirstPeriodSMA(
      this->getPeriodsFast(), 
      StockAnalyzer::CALCFASTPERIOD);
   
   // Calculate EMA multiplier
   this->calculateMultEMA(
      this->getPeriodsFast(), 
      StockAnalyzer::CALCFASTPERIOD);
   
   // Calculate EMA
   this->calculateEMA(
      this->getFirstPeriodSMAFast(), 
      this->getMultEMAFast(), 
      this->getPeriodsFast(), 
      StockAnalyzer::CALCFASTPERIOD);

   cout << endl;
   cout << "Period " << this->getPeriodsSlow() << endl;
   
   // Perform the stock analysis with the fast period
   // Formatted to fit 80 chars
   // Calculate first period SMA
   this->calculateFirstPeriodSMA(
      this->getPeriodsSlow(), 
      StockAnalyzer::CALCSLOWPERIOD);
   
   // Calculate EMA multiplier
   this->calculateMultEMA(
      this->getPeriodsSlow(), 
      StockAnalyzer::CALCSLOWPERIOD);
   
   // Calculate EMA
   this->calculateEMA(
      this->getFirstPeriodSMASlow(), 
      this->getMultEMASlow(), 
      this->getPeriodsSlow(), 
      StockAnalyzer::CALCSLOWPERIOD);

   cout << endl;

   // Calculate the MACD
   this->calculateMACDs();

   cout << endl;
}

//******************************************************************************
// Function : calculateEMA                                   
// Process  : EMA: {Close - EMA(previous day)} x multiplier + EMA(previous day)    
//             Loop through all prices
//                If this is not our first rep
//                   calculate the EMA for the current period using the 
//                   EMA equation listed above
//                   Increment our loop counter
//                   Add the EMA to ouor list of EMAs
//                Else
//                   In the first pass, EMA is the input SMA
//                   Add the EMA to ouor list of EMAs
//             Output the current EMA (EMA for the last day calculated)
// Notes    : Throws an exception if periodToCalc is invalid
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
void StockAnalyzer::calculateEMA(
   const double firstPeriodSMA, 
   const double multEMA, 
   const int period, 
   StockAnalyzer::PeriodToCalc periodToCalc)
{
   double    currentEMA    = 0.0;         // Today's EMA
   int       currRep       = 0;           // currRep, used to process all prices
   bool      isFirstPass   = true;        // First pass of while loop?
   double    tempEMA       = 0.0;         // Holds temp EMA
   double    yesterdadyEMA = 0.0;         // Yesterday's EMA

   const int NUMPRICES = this->getNumStockPrices(); // Number of prices
   const int MAXREPS   = NUMPRICES - period - 1;    // First EMA for the period 
                                                    // is input SMA so no need
                                                    // to take first [period]
                                                    // indices into account
                                                    // when looping for 
                                                    // successive EMAs
   
   // EMA: {Close - EMA(previous day)} x multiplier + EMA(previous day). 
   // Loop through all prices
   while (currRep <= MAXREPS)
   {
      // If this is not our first rep, calculate the EMA for the current period
      // using the EMA equation listed above
      if (!isFirstPass)
      {
         tempEMA = (this->getStockPriceAtIndex(period + currRep) - currentEMA) * multEMA + currentEMA;
         currentEMA = tempEMA;

         // Increment our loop counter
         currRep++;
      }
      // If this is our first pass, EMA is the input SMA
      else
      {
         currentEMA = firstPeriodSMA;
         isFirstPass = false;
      }

      // Add the EMA to ouor list of EMAs
      if (StockAnalyzer::CALCFASTPERIOD == periodToCalc)
      {
         this->addEMAFast(currentEMA);
      }
      else if (StockAnalyzer::CALCSLOWPERIOD == periodToCalc)
      {
         this->addEMASlow(currentEMA);
      }
      else
      {
         throw exception("Unexpected StockAnalyzer::PeriodToCalc value"); 
      }
   }

   // Output the current EMA (EMA for the last day calculated)
   if (StockAnalyzer::CALCFASTPERIOD == periodToCalc)
   {
      cout << "   currentEMA:     " << this->getCurrentEMAFast() << endl;
   }
   else if (StockAnalyzer::CALCSLOWPERIOD == periodToCalc)
   {
      cout << "   currentEMA:     " << this->getCurrentEMASlow() << endl;
   }
   else
   {
      throw exception("Unexpected StockAnalyzer::PeriodToCalc value"); 
   }   
}

//******************************************************************************
// Function : calculateFirstPeriodSMA                                   
// Process  : SMA: period sum / number of periods
//             Calculate the sum of prices based on the number of periods
//             Take the average of the sum to determine the SMA
//             Update the SMA data member
//             Output the SMA
// Notes    : Throws an exception if periodToCalc is invalid
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
void StockAnalyzer::calculateFirstPeriodSMA(
   const int period, 
   StockAnalyzer::PeriodToCalc periodToCalc)
{
   double    firstPeriodSMA = 0.0;                         // Avg of last period 
                                                           // number of prices
   const int NUMPRICES      = this->getNumStockPrices();   // Number of prices
   double    sumSMA         = 0.0;                         // Sum of last period 
                                                           // number of prices
   
   // SMA: period sum / number of periods 
   for (int priceIndex = 0; priceIndex < period; ++priceIndex)
   {
      // Calculate the sum of prices based on the number of periods
      sumSMA += this->getStockPriceAtIndex(priceIndex);
   }
      
   // Take the average of the sum to determine the SMA
   firstPeriodSMA = sumSMA / period;

   cout << "   firstPeriodSMA: " << firstPeriodSMA << endl;

   // Output the SMA
   if (StockAnalyzer::CALCFASTPERIOD == periodToCalc)
   {
      this->setFirstPeriodSMAFast(firstPeriodSMA);
   }
   else if (StockAnalyzer::CALCSLOWPERIOD == periodToCalc)
   {
      this->setFirstPeriodSMASlow(firstPeriodSMA);
   }
   else
   {
      throw exception("Unexpected StockAnalyzer::PeriodToCalc value"); 
   }
}

//******************************************************************************
// Function : calculateMACDs                                   
// Process  : MACD = EMA[fast] – EMA[slow]
//             Calculate current and yesterday's MACDs
//             Calculate slope of MACDs over today and yesterday
//             Set up slope equation vars (y1 - y2) / (x1 - x2)
//                y1 = yesterdayMACD
//                y2 = currentMACD
//                x1 = previousDay
//                x2 = currentDay
//             Update the MACD data members
//             Output the MACDs
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
void StockAnalyzer::calculateMACDs()
{
   double currentMACD      = 0.0;  // Moving Avg Converge/Diverge for today
   double yesterdayMACD    = 0.0;  // Moving Avg Converge/Diverge for yesterday
   double slopeMACD        = 0.0;  // MACD slope of today and yesterday

   double currentEMAFast   = this->getCurrentEMAFast();     // Current EMA for 
                                                            // the fast period
   double currentEMASlow   = this->getCurrentEMASlow();     // Current EMA for 
                                                            // the slow period
   double yesterdayEMAFast = this->getYesterdayEMAFast();   // Yesterday's EMA 
                                                            // for fast period
   double yesterdayEMASlow = this->getYesterdayEMASlow();   // Yesterday's EMA 
                                                            // for slow period
   cout << "MACD" << endl;

   // MACD = EMA[fast] – EMA[slow]
   // Calculate current and yesterday's MACDs
   currentMACD   = currentEMAFast - currentEMASlow;
   yesterdayMACD = yesterdayEMAFast - yesterdayEMASlow;

   double previousDay = 0.0;               // Previous day, 
                                           // set to a 0.0 value as start
   double currentDay  = previousDay + 1.0; // Current day, 
                                           // set to 1 plus prev day

   // Calculate the slope using the equation (y1 - y2) / (x1 - x2)
   // where the y's are the days and the x's are the MACDs
   // y1 = yesterdayMACD
   // y2 = currentMACD
   // x1 = previousDay
   // x2 = currentDay
   slopeMACD = (yesterdayMACD - currentMACD) / (previousDay - currentDay);

   // Update the MACD data members
   this->setCurrentMACD(currentMACD);
   this->setYesterdayMACD(yesterdayMACD);
   this->setSlopeMACD(slopeMACD);
   
   // Output the MACDs
   cout << "   yesterdayMACD:     " << yesterdayMACD << endl;
   cout << "   currentMACD:       " << currentMACD << endl;
   cout << "   slopeMACD (2 day): " << slopeMACD << endl;
}

//******************************************************************************
// Function : calculateMultEMA                                   
// Process  : Multiplier: (2 / (Time periods + 1))     
//             Calculate the EMA multiplier
//             Update the EMA multiplier data member
//             Output the EMA multiplier
// Notes    : Throws an exception if periodToCalc is invalid
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
void StockAnalyzer::calculateMultEMA(
   const int period, 
   StockAnalyzer::PeriodToCalc periodToCalc)
{
   double multEMA                              = 0.0; // EMA multiplier
   static const double MULTNUMERATOR           = 2.0; // Numerator from equation
   static const double MULTDENOMADDITIONFACTOR = 1.0; // Denominator add factor 
                                                      // from equation

   // Multiplier: (2 / (Time periods + 1))  
   // Calculate the EMA multiplier
   multEMA = (MULTNUMERATOR / (period + (double(MULTDENOMADDITIONFACTOR))));

   cout << "   multEMA:        " << multEMA << endl;

   // Output the EMA multiplier
   if (StockAnalyzer::CALCFASTPERIOD == periodToCalc)
   {
      this->setMultEMAFast(multEMA);
   }
   else if (StockAnalyzer::CALCSLOWPERIOD == periodToCalc)
   {
      this->setMultEMASlow(multEMA);
   }
   else
   {
      throw exception("Unexpected StockAnalyzer::PeriodToCalc value"); 
   }
}
   
//******************************************************************************
// Function : initPeriodsToDefaults                                   
// Process  : Initialize the periods to 12, 26             
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
void StockAnalyzer::initPeriodsToDefaults()
{
   this->setPeriodsFast(StockAnalyzer::DEFAULTFASTPERIODS);
   this->setPeriodsSlow(StockAnalyzer::DEFAULTSLOWPERIODS);
}

//******************************************************************************
// Function : parsePricesFromDataFile                                       
// Notes    : Throws an exception if atof fails
//             Throws an exception if fstream operation fails
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
void StockAnalyzer::parsePricesFromDataFile()
{
   static const int   MAX_CHARS_PER_LINE     = 512;   // Max chars per line
   static const int   MAX_TOKENS_PER_LINE    = 5;     // Max "," per line
   static const char* DELIMITER              = ",";   // CSV files
   static const int   CLOSINGPRICETOKENINDEX = 4;     // Closing price token index
   double             closingPrice           = 0.0;   // Closing price
   bool               firstPass              = false; // Skip labels
   int                numTokens              = 0;     // Num tokens in line
   ifstream           fin;                            // File reader
   char               buffer[MAX_CHARS_PER_LINE];     // Holds line

   // Read in the files and save the "Close" price
   // Create a file-reading object and open a file
   fin.open(this->getStockDataFileName());

   // Adapted from http://cs.dvc.edu/HowTo_Cparse.html
   // If there were no problems with the fstream operation
   if (fin.good()) 
   {  
      // While there are more lines to read
      while (!fin.eof())
      {
         // Read an entire line into memory
         fin.getline(buffer, MAX_CHARS_PER_LINE);

         // Skip the labels
         if (!firstPass)
         {  
            firstPass = true;
            continue;
         }
        
         // Array to store memory addresses of the tokens in buf
         vector<char*> token(MAX_TOKENS_PER_LINE);
    
         // Reset num tokens to prepare for the next iteration
         numTokens = 0;

         // dummy context required by strtok_s
         char* context	= NULL;

         for (int tokenIndex = 0; tokenIndex < MAX_TOKENS_PER_LINE; tokenIndex++)
         {
            // Not the first iteration, strtok expects a null pointer as the first param
            if (tokenIndex != 0)
            {
               // Get the next token
               token[tokenIndex] = strtok_s(0, DELIMITER, &context);

               // No more tokens
               if (!token[tokenIndex])
               {
                  break;
               }
            }
            // First iteration
            else
            {
               // Parse the line, get the first token
               token[0] = strtok_s(buffer, DELIMITER, &context);

               // Break if the line is blank
               if (!token[0])
               {
                  break;
               }
            }

            // Increment token count
            numTokens++;
         }

         if (CLOSINGPRICETOKENINDEX < numTokens) 
         {
            closingPrice = atof(token[CLOSINGPRICETOKENINDEX]);

            // Handle errors from atof:
            // On success, the function returns the converted floating point number as a double value.
            // If no valid conversion could be performed, or if the correct value would cause underflow, a zero value (0.0) is returned.
            // If the correct value is out of the range of representable values, a positive or negative HUGE_VAL is returned.
            if (abs(HUGE_VAL) == closingPrice || 0.0 == closingPrice)
            {
               throw exception("atof operation failed");
            }
            else
            {
               this->addStockPrice(closingPrice);
            }
         }
      } // end while (!fin.eof())

      // Simplifies the calculation so we can analyze stocks from oldest price (starting at 0 index)
      // to newest price (size - 1) instead of iterating through the price list backwards
      this->reversePriceOrder();

      cout << "---Loaded stock data from: " << this->getStockDataFileName() << "---" << endl << endl;
   } // end if (fin.good()) 
   else 
   {
      throw exception("fstream operation failed");
   }
}
