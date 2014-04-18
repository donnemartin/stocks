stockanalyzer
============

Stock analyzer written in C++.

Analyzes various stocks taken from Google Finance.

**Note: The CSV data files are provided as samples.  The program currently requires these files to be in the same directory as the executable.**

![alt tag](https://raw.githubusercontent.com/donnemartin/stockanalyzer/master/res/googlefinance.png)

Companies:

![alt tag](https://raw.githubusercontent.com/donnemartin/stockanalyzer/master/res/companies.png)

Data files:

![alt tag](https://raw.githubusercontent.com/donnemartin/stockanalyzer/master/res/data.png)

Stocks are ranked based on their current Moving Average Convergence Divergence, MACD,
based upon their past year of Closing Prices.

The equations for MACD are in wiki at http://en.wikipedia.org/wiki/MACD.

![alt tag](https://raw.githubusercontent.com/donnemartin/stockanalyzer/master/res/stockanalyzer.png)