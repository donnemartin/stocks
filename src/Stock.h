//******************************************************************************
//
// File Name:     Stock.h
//
// File Overview: Represents a Stock
//
//******************************************************************************
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added class
//******************************************************************************

#ifndef Stock_h
#define Stock_h

#include <vector>
#include <exception>

using namespace std;

//******************************************************************************
//
// Class:    Stock
//
// Overview: Represents a Stock, which contains a list of closing prices
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added class
//
// Notes: Consider adding more data to stock, such as trading volume,
//          high/low price, etc in addition to just closing price
//
//******************************************************************************
class Stock
{
public:
   
   //***************************************************************************
   // Function    : constructor                                   
   // Description : None
   // Constraints : None
   //***************************************************************************
   Stock();

   //***************************************************************************
   // Function    : destructor                                   
   // Description : Performs cleanup tasks              
   // Constraints : None
   //***************************************************************************
   virtual ~Stock();   

   // Member functions in alphabetical order   

   //***************************************************************************
   // Function    : addPrice                                   
   // Description : Adds to our list of prices            
   // Constraints : None
   //***************************************************************************
   inline void addPrice(const double price);
   
   //***************************************************************************
   // Function    : getNumPrices                                   
   // Description : Retrieve the number of prices            
   // Constraints : None
   //***************************************************************************
   inline int getNumPrices() const;
      
   //***************************************************************************
   // Function    : getPriceAt                                   
   // Description : Retrieve the price at the specified index             
   // Constraints : Throws an out_of_range exception for invalid index
   //***************************************************************************
   inline double getPriceAt(const int index) const;
      
   //***************************************************************************
   // Function    : reversePriceOrder                                   
   // Description : Reverse the order of prices
   // Constraints : [first, last) must be a valid range
   //***************************************************************************
   inline void reversePriceOrder();

private:   
   vector<double> prices;   // Stock prices for the past year

}; // end class Stock

//******************************************************************************
// Function : addPrice                                   
// Process  : Add to our list of prices           
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline void Stock::addPrice(const double price) 
{ 
   this->prices.push_back(price); 
}

//******************************************************************************
// Function : getNumPrices                                   
// Process  : Retrieve the number of prices
// Notes    : None
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline int Stock::getNumPrices() const 
{ 
   return this->prices.size(); 
}

//******************************************************************************
// Function : getPriceAt                                   
// Process  : Retrieve the price at the specified index           
// Notes    : Throws an out_of_range exception for invalid index
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline double Stock::getPriceAt(const int index) const 
{ 
   return this->prices.at(index); 
}

//******************************************************************************
// Function : reversePriceOrder                                   
// Process  : Reverse the order of prices           
// Notes    : [first, last) must be a valid range
//
// Revision History:
//
// Date           Author               Description 
// 6.25.11        Donne Martin         Added function
//******************************************************************************
inline void Stock::reversePriceOrder() 
{ 
   std::reverse(prices.begin(), prices.end()); 
}

#endif // Stock_h