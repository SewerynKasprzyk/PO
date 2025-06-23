/**
 * @file TestyKonfiguracji.h
 * @brief Declaration of test functions for the control system components
 */
#pragma once

/**
* @brief Tests serialization and deserialization of configuration
*/
void testZapisuIOdczytu();
/**
 * @brief Tests parameter modification in the configuration
 */
void testZmianyParametrow();

/**
 * @brief Runs a complete simulation to verify functionality
 */
void testPelnejSymulacji();

/**
 * @brief Executes all test cases
 */
void uruchomTesty();
