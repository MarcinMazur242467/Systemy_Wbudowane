#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifdef  DEBUG
/*******************************************************************************
* @brief		The CHECK_PARAM macro is used for function's parameters check.
* 				It is used only if the library is compiled in DEBUG mode.
* @param[in]	expr - If expr is false, it calls check_failed() function
*                    	which reports the name of the source file and the source
*                    	line number of the call that failed.
*                    - If expr is true, it returns no value.
* @return		None
*******************************************************************************/
#define CHECK_PARAM(expr) ((expr) ? (void)0 : blad_krytyczny(__FILE__, __LINE__))
#else
#define CHECK_PARAM(expr)
#endif /* DEBUG */



/************************** GLOBAL/PUBLIC FUNCTION DECLARATION *********************************/

#ifdef  DEBUG
/*************************************************************
 * @brief: Obsługa błędów krytycznych
 * @param file[in]: komunikat, typowo nazwa pliku: makro __FILE__, choć niekoniecznie
 * @param line[in]: nr linii typowo uzyskiwany makrem __LINE__
 * @side effects: program ugrzęźnie w tej procedurze (nigdy z niej nie wyjdzie)
 */
void blad_krytyczny (char *file, uint32_t line);
#endif

#endif //__DEBUG_H__
