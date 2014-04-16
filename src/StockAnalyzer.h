//******************************************************************************
//
// File Name:     StockAnalyzer.h
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

#ifndef StockAnalyzer_h
#define StockAnalyzer_h

#include "Stock.h"

//******************************************************************************
//
// Class:    StockAnalyzer
//
// Overview: Represents a StockAnalyzer
//             Contains a stock data file which parses price data to a stock
//             Calculates SMA, EMA, and MACD for a fast and slow period
//             The default periods are 12 and 26
//             Use setPeriodsFast and setPeriodsSlow to changes these values
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added class
//
//******************************************************************************
class StockAnalyzer
{
public:   

   //***************************************************************************
   // Function    : constructor                                   
   // Description : Calls initPeriodsToDefaults
   //                Need to set the stock data file name and stock afterwards
   // Constraints : None
   //***************************************************************************
   StockAnalyzer();

   //***************************************************************************
   // Function    : constructor                                   
   // Description : Calls initPeriodsToDefaults
   //                Sets the stock data file name and stock
   // Constraints : None
   //***************************************************************************
   StockAnalyzer(
      char* stockDataFileName,
      const Stock& stock);

   //***************************************************************************
   // Function    : destructor                                   
   // Description : Performs cleanup tasks              
   // Constraints : None
   //***************************************************************************
   virtual ~StockAnalyzer();   

   // Member functions in alphabetical order
   
   //***************************************************************************
   // Function    : analyzeStock                                   
   // Description : Analyzes the stock, calculates the SMA, EMA, and MACD
   // Constraints : None
   //***************************************************************************
   void analyzeStock();
          
   //***************************************************************************
   // Function    : getCurrentEMAFast                                   
   // Description : Accessor for currentEMAFast            
   // Constraints : None
   //***************************************************************************  
   inline double getCurrentEMAFast() const;
      
   //***************************************************************************
   // Function    : getYesterdayEMAFast                                   
   // Description : Accessor for yesterdayEMAFast            
   // Constraints : None
   //***************************************************************************
   inline double getYesterdayEMAFast() const; 
      
   //***************************************************************************
   // Function    : getCurrentEMASlow                                   
   // Description : Accessor for currentEMASlow            
   // Constraints : None
   //***************************************************************************
   inline double getCurrentEMASlow() const;
      
   //***************************************************************************
   // Function    : getYesterdayEMASlow                                   
   // Description : Accessor for yesterdayEMASlow            
   // Constraints : None
   //***************************************************************************
   inline double getYesterdayEMASlow() const;
      
   //***************************************************************************
   // Function    : getCurrentMACD                                   
   // Description : Accessor for currentMACD            
   // Constraints : None
   //***************************************************************************
   inline double getCurrentMACD() const;  
      
   //***************************************************************************
   // Function    : getFirstPeriodSMAFast                                   
   // Description : Accessor for firstPeriodSMAFast            
   // Constraints : None
   //***************************************************************************
   inline double getFirstPeriodSMAFast() const;
      
   //***************************************************************************
   // Function    : getFirstPeriodSMASlow                                   
   // Description : Accessor for firstPeriodSMASlow            
   // Constraints : None
   //***************************************************************************
   inline double getFirstPeriodSMASlow() const; 
      
   //***************************************************************************
   // Function    : getMultEMAFast                                   
   // Description : Accessor for multEMAFast            
   // Constraints : None
   //***************************************************************************
   inline double getMultEMAFast() const;
      
   //***************************************************************************
   // Function    : getMultEMASlow                                   
   // Description : Accessor for multEMASlow            
   // Constraints : None
   //***************************************************************************
   inline double getMultEMASlow() const;
      
   //***************************************************************************
   // Function    : getNumStockPrices                                   
   // Description : Utility for stock.getNumPrices()            
   // Constraints : None
   //***************************************************************************
   inline int getNumStockPrices() const;
      
   //***************************************************************************
   // Function    : getPeriodsFast                                   
   // Description : Accessor for periodsFast            
   // Constraints : None
   //***************************************************************************
   inline int getPeriodsFast() const;
      
   //***************************************************************************
   // Function    : getPeriodsSlow                                   
   // Description : Accessor for periodsSlow            
   // Constraints : None
   //***************************************************************************
   inline int getPeriodsSlow() const;
      
   //***************************************************************************
   // Function    : getSlopeMACD                                   
   // Description : Accessor for slopeMACD            
   // Constraints : None
   //***************************************************************************
   inline double getSlopeMACD() const;  
      
   //***************************************************************************
   // Function    : getStockDataFileName                                   
   // Description : Accessor for stockDataFileName            
   // Constraints : None
   //***************************************************************************
   inline char* getStockDataFileName() const;
      
   //***************************************************************************
   // Function    : getStockPriceAtIndex                                   
   // Description : Utility for stock.getPriceAt(index)    
   // Constraints : Throws an out_of_range exception for invalid index
   //***************************************************************************
   inline double getStockPriceAtIndex(int index) const;
      
   //***************************************************************************
   // Function    : getYesterdayMACD                                   
   // Description : Accessor for yesterdayMACD            
   // Constraints : None
   //***************************************************************************
   inline double getYesterdayMACD() const;  
      
   //***************************************************************************
   // Function    : parsePricesFromDataFile                                   
   // Description : Parses the data file and            
   // Constraints : None
   //***************************************************************************
   void parsePricesFromDataFile();
      
   //***************************************************************************
   // Function    : setPeriodsFast                                   
   // Description : Mutator for periodsFast            
   // Constraints : None
   //***************************************************************************
   inline void setPeriodsFast(const int periodsFast);
      
   //***************************************************************************
   // Function    : setPeriodsSlow                                   
   // Description : Mutator for periodsSlow            
   // Constraints : None
   //***************************************************************************
   inline void setPeriodsSlow(const int periodsSlow);
      
   //***************************************************************************
   // Function    : setStock                                   
   // Description : Mutator for stock            
   // Constraints : None
   //***************************************************************************
   inline void setStock(const Stock& stock);
      
   //***************************************************************************
   // Function    : setStockDataFileName                                   
   // Description : Mutator for stockDataFileName            
   // Constraints : None
   //***************************************************************************
   inline void setStockDataFileName(char* stockDataFileName);
   
   static const int DEFAULTFASTPERIODS = 12; // 12 periods default for fast
   static const int DEFAULTSLOWPERIODS = 26; // 26 periods default for slow

   // Determines whether to calculate fast or slow period
   enum PeriodToCalc
   {
      CALCFASTPERIOD,
      CALCSLOWPERIOD
   };

private:      
   //***************************************************************************
   // Function    : addEMAFast                                   
   // Description : Adds the EMA to our list of emas (fast period)            
   //                Private, for internal calculations, 
   //                   call analyzeStock instead
   // Constraints : None
   //***************************************************************************
   inline void addEMAFast(double newEMA);
      
   //***************************************************************************
   // Function    : addEMASlow                                   
   // Description : Adds the EMA to our list of emas (slow period)          
   //                Private, for internal calculations, 
   //                   call analyzeStock instead         
   // Constraints : None
   //***************************************************************************
   inline void addEMASlow(double newEMA);
      
   //***************************************************************************
   // Function    : addStockPrice                                   
   // Description : Adds the stock price to our list of prices       
   //                Private, for internal calculations, 
   //                   call analyzeStock instead          
   // Constraints : None
   //***************************************************************************
   inline void addStockPrice(const double stockPrice);
      
   //***************************************************************************
   // Function    : calculateEMA                                   
   // Description : Calculates the EMA of either the fast or slow period           
   //                Private, for internal calculations, 
   //                   call analyzeStock instead      
   // Constraints : None
   //***************************************************************************
   void calculateEMA(
      const double firstPeriodSMA, 
      const double multEMA, 
      const int period, 
      StockAnalyzer::PeriodToCalc periodToCalc);
      
   //***************************************************************************
   // Function    : calculateFirstPeriodSMA                                   
   // Description : Calculates the first period SMA of either 
   //                the fast or slow period                    
   //                Private, for internal calculations, 
   //                   call analyzeStock instead
   // Constraints : None
   //***************************************************************************
   void calculateFirstPeriodSMA(
      const int period, 
      StockAnalyzer::PeriodToCalc periodToCalc);
      
   //***************************************************************************
   // Function    : calculateMultEMA                                   
   // Description : Calculates EMA multiplier of either the fast or slow period          
   //                Private, for internal calculations, 
   //                   call analyzeStock instead        
   // Constraints : None
   //***************************************************************************
   void calculateMultEMA(
      const int period, 
      StockAnalyzer::PeriodToCalc periodToCalc);
      
   //***************************************************************************
   // Function    : calculateMACDs                                   
   // Description : Calculates the MACDs       
   //                Private, for internal calculations, 
   //                   call analyzeStock instead
   // Constraints : None
   //***************************************************************************
   void calculateMACDs();
      
   //***************************************************************************
   // Function    : initPeriodsToDefaults                                   
   // Description : Initialize the periods to 12, 26   
   //                Private, for internal calculations, 
   //                   call analyzeStock instead       
   // Constraints : None
   //***************************************************************************
   void initPeriodsToDefaults();
      
   //***************************************************************************
   // Function    : reversePriceOrder                                   
   // Description : stock.reversePriceOrder()           
   //                Private, for internal calculations, 
   //                   call analyzeStock instead
   // Constraints : [first, last) must be a valid range
   //***************************************************************************
   inline void reversePriceOrder();
      
   //***************************************************************************
   // Function    : setCurrentMACD                                   
   // Description : Mutator for currentMACD      
   //                Private, for internal calculations, 
   //                   call analyzeStock instead     
   // Constraints : None
   //***************************************************************************
   inline void setCurrentMACD(const double currentMACD);
      
   //***************************************************************************
   // Function    : setFirstPeriodSMAFast                                   
   // Description : Mutator for firstPeriodSMAFast     
   //                Private, for internal calculations, 
   //                   call analyzeStock instead      
   // Constraints : None
   //***************************************************************************
   inline void setFirstPeriodSMAFast(const double firstPeriodSMAFast);
      
   //***************************************************************************
   // Function    : setFirstPeriodSMASlow                                   
   // Description : Mutator for firstPeriodSMASlow   
   //                Private, for internal calculations, 
   //                   call analyzeStock instead        
   // Constraints : None
   //***************************************************************************
   inline void setFirstPeriodSMASlow(const double firstPeriodSMASlow);
      
   //***************************************************************************
   // Function    : setMultEMAFast                                   
   // Description : Mutator for multEMAFast      
   //                Private, for internal calculations, 
   //                   call analyzeStock instead     
   // Constraints : None
   //***************************************************************************
   inline void setMultEMAFast(const double multEMAFast);
      
   //***************************************************************************
   // Function    : setMultEMASlow                                   
   // Description : Mutator for multEMASlow     
   //                Private, for internal calculations, 
   //                   call analyzeStock instead      
   // Constraints : None
   //***************************************************************************
   inline void setMultEMASlow(const double multEMASlow);
      
   //***************************************************************************
   // Function    : setSlopeMACD                                   
   // Description : Mutator for slopeMACD         
   //                Private, for internal calculations, 
   //                   call analyzeStock instead  
   // Constraints : None
   //***************************************************************************
   inline void setSlopeMACD(const double slopeMACD);
      
   //***************************************************************************
   // Function    : setYesterdayMACD                                   
   // Description : Mutator for yesterdayMACD    
   //                Private, for internal calculations, 
   //                   call analyzeStock instead       
   // Constraints : None
   //***************************************************************************
   inline void setYesterdayMACD(const double yesterdayMACD);
   
   double currentMACD;           // MACD calculated over one year from today

   double firstPeriodSMAFast;    // First fast SMA period for the SMA (average of price)
   double firstPeriodSMASlow;    // First slow SMA period for the SMA (average of price)

   vector<double> listEMAFast;   // List of EMAs for the fast period
   vector<double> listEMASlow;   // List of EMAs for the slow period

   double multEMAFast;           // Multiplier to determine the EMA for the fast period
   double multEMASlow;           // Multiplier to determine the EMA for the slow period

   int periodsFast;              // Number of days for the fast period
   int periodsSlow;              // Number of days for the slow period

   double slopeMACD;             // MACD slope is calculated with currentMACD and yesterdayMACD
   
   Stock stock;                  // Represents the stock
   char* stockDataFileName;      // Contains the stock data over one year
   double yesterdayMACD;         // MACD calculated over one year from yesterday
}; // end class StockAnalyzer

//******************************************************************************
// Function : addEMAFast                                   
// Process  : Adds the EMA to our list of emas (fast period)            
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline void StockAnalyzer::addEMAFast(double newEMA) 
{ 
   listEMAFast.push_back(newEMA); 
}

//******************************************************************************
// Function : addEMASlow                                   
// Process  : Adds the EMA to our list of emas (slow period)            
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline void StockAnalyzer::addEMASlow(double newEMA) 
{ 
   listEMASlow.push_back(newEMA); 
}

//******************************************************************************
// Function : addStockPrice                                   
// Process  : Adds the stock price to our list of prices           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline void StockAnalyzer::addStockPrice(const double stockPrice) 
{ 
   this->stock.addPrice(stockPrice); 
}

//******************************************************************************
// Function : getCurrentEMAFast                                   
// Process  : Accessor for last index of listEMAFast           
// Notes    : Throws an out_of_range exception for invalid index to at()
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline double StockAnalyzer::getCurrentEMAFast() const 
{ 
   static const int OFFSETLASTELEMENT = 1;
   return listEMAFast.at(listEMAFast.size() - OFFSETLASTELEMENT); 
}

//******************************************************************************
// Function : getYesterdayEMAFast                                   
// Process  : Accessor for second last index of listEMAFast               
// Notes    : Throws an out_of_range exception for invalid index to at()
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline double StockAnalyzer::getYesterdayEMAFast() const 
{ 
   static const int OFFSETSECONDLASTELEMENT = 2;
   return listEMAFast.at(listEMAFast.size() - OFFSETSECONDLASTELEMENT); 
}  

//******************************************************************************
// Function : getCurrentEMASlow                                   
// Process  : Accessor for last index of listEMASlow            
// Notes    : Throws an out_of_range exception for invalid index to at()
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline double StockAnalyzer::getCurrentEMASlow() const 
{ 
   static const int OFFSETLASTELEMENT = 1;
   return listEMASlow.at(listEMASlow.size() - OFFSETLASTELEMENT); 
}

//******************************************************************************
// Function : getYesterdayEMASlow                                   
// Process  : Accessor for second last index of listEMASlow       
// Notes    : Throws an out_of_range exception for invalid index to at()
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline double StockAnalyzer::getYesterdayEMASlow() const 
{ 
   static const int OFFSETSECONDLASTELEMENT = 2;
   return listEMASlow.at(listEMASlow.size() - OFFSETSECONDLASTELEMENT); 
}

//******************************************************************************
// Function : getCurrentMACD                                   
// Process  : Accessor for currentMACD           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline double StockAnalyzer::getCurrentMACD() const 
{ 
   return this->currentMACD; 
}  

//******************************************************************************
// Function : getFirstPeriodSMAFast                                   
// Process  : Accessor for firstPeriodSMAFast           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline double StockAnalyzer::getFirstPeriodSMAFast() const 
{ 
   return this->firstPeriodSMAFast; 
}

//******************************************************************************
// Function : getFirstPeriodSMASlow                                   
// Process  : Accessor for firstPeriodSMASlow           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline double StockAnalyzer::getFirstPeriodSMASlow() const 
{ 
   return this->firstPeriodSMASlow; 
} 
   
//******************************************************************************
// Function : getMultEMAFast                                   
// Process  : Accessor for multEMAFast           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline double StockAnalyzer::getMultEMAFast() const 
{ 
   return this->multEMAFast; 
}

//******************************************************************************
// Function : getMultEMASlow                                   
// Process  : Accessor for multEMASlow           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline double StockAnalyzer::getMultEMASlow() const 
{ 
   return this->multEMASlow; 
}
   
//******************************************************************************
// Function : getNumStockPrices                                   
// Process  : Utility for stock.getNumPrices()           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline int StockAnalyzer::getNumStockPrices() const 
{ 
   return this->stock.getNumPrices(); 
}
   
//******************************************************************************
// Function : getPeriodsFast                                   
// Process  : Accessor for periodsFast           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline int StockAnalyzer::getPeriodsFast() const 
{ 
   return this->periodsFast; 
}

//******************************************************************************
// Function : getPeriodsSlow                                   
// Process  : Accessor for periodsSlow           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline int StockAnalyzer::getPeriodsSlow() const 
{ 
   return this->periodsSlow; 
}
   
//******************************************************************************
// Function : getSlopeMACD                                   
// Process  : Accessor for slopeMACD           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline double StockAnalyzer::getSlopeMACD() const 
{
   return this->slopeMACD; 
}  
   
//******************************************************************************
// Function : getStockDataFileName                                   
// Process  : Accessor for stockDataFileName           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline char* StockAnalyzer::getStockDataFileName() const 
{ 
   return stockDataFileName; 
}

//******************************************************************************
// Function : getStockPriceAtIndex                                   
// Process  : Utility for stock.getPriceAt(index)           
// Notes    : Throws an out_of_range exception for invalid index
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline double StockAnalyzer::getStockPriceAtIndex(int index) const 
{ 
   return this->stock.getPriceAt(index); 
}

//******************************************************************************
// Function : getYesterdayMACD                                   
// Process  : Accessor for yesterdayMACD           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline double StockAnalyzer::getYesterdayMACD() const 
{ 
   return this->yesterdayMACD; 
}  

//******************************************************************************
// Function : reversePriceOrder                                   
// Process  : Utility for stock.reversePriceOrder()           
// Notes    : [first, last) must be a valid range
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline void StockAnalyzer::reversePriceOrder() 
{ 
   this->stock.reversePriceOrder(); 
}
   
//******************************************************************************
// Function : setCurrentMACD                                   
// Process  : Mutator for currentMACD           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline void StockAnalyzer::setCurrentMACD(const double currentMACD) 
{ 
   this->currentMACD = currentMACD; 
}

//******************************************************************************
// Function : setFirstPeriodSMAFast                                   
// Process  : Mutator for firstPeriodSMAFast           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline void StockAnalyzer::setFirstPeriodSMAFast(const double firstPeriodSMAFast) 
{ 
   this->firstPeriodSMAFast = firstPeriodSMAFast; 
}

//******************************************************************************
// Function : setFirstPeriodSMASlow                                   
// Process  : Mutator for firstPeriodSMASlow           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline void StockAnalyzer::setFirstPeriodSMASlow(const double firstPeriodSMASlow) 
{ 
   this->firstPeriodSMASlow = firstPeriodSMASlow; 
}

//******************************************************************************
// Function : setMultEMAFast                                   
// Process  : Mutator for multEMAFast           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline void StockAnalyzer::setMultEMAFast(const double multEMAFast) 
{ 
   this->multEMAFast = multEMAFast; 
}

//******************************************************************************
// Function : setMultEMASlow                                   
// Process  : Mutator for multEMASlow           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline void StockAnalyzer::setMultEMASlow(const double multEMASlow) 
{ 
   this->multEMASlow = multEMASlow; 
}

//******************************************************************************
// Function : setPeriodsFast                                   
// Process  : Mutator for periodsFast           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline void StockAnalyzer::setPeriodsFast(const int periodsFast) 
{ 
   this->periodsFast = periodsFast; 
}

//******************************************************************************
// Function : setPeriodsSlow                                   
// Process  : Mutator for periodsSlow           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline void StockAnalyzer::setPeriodsSlow(const int periodsSlow) 
{ 
   this->periodsSlow = periodsSlow; 
}

//******************************************************************************
// Function : setSlopeMACD                                   
// Process  : Mutator for slopeMACD           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline void StockAnalyzer::setSlopeMACD(const double slopeMACD) 
{ 
   this->slopeMACD = slopeMACD; 
}

//******************************************************************************
// Function : setStock                                   
// Process  : Mutator for stock           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline void StockAnalyzer::setStock(const Stock& stock) 
{ 
   this->stock = stock; 
}

//******************************************************************************
// Function : setStockDataFileName                                   
// Process  : Mutator for stockDataFileName           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline void StockAnalyzer::setStockDataFileName(char* stockDataFileName) 
{ 
   this->stockDataFileName = stockDataFileName; 
}

//******************************************************************************
// Function : setYesterdayMACD                                   
// Process  : Mutator for yesterdayMACD           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline void StockAnalyzer::setYesterdayMACD(const double yesterdayMACD) 
{ 
   this->yesterdayMACD = yesterdayMACD; 
}

#endif // StockAnalyzer_h