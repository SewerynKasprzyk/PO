/**  
* @file ObiektSISO.h  
* @brief SISO (Single Input Single Output) system interface  
*/  
#pragma once  

/**  
* @brief Abstract SISO system  
*/  
class ObiektSISO {  
public: // Change access specifier to public  
  /**  
   * @brief Simulate system output for given input  
   * @param u Input value  
   * @return double Output value  
   */  
  virtual double symuluj(double u) = 0;  

  virtual ~ObiektSISO() = default;  
};