#include "include/test_ai.h"
#include "include/test_gameboard.h"

#include <CUnit/Basic.h>
#include <CUnit/TestDB.h>

int main() {
  CU_initialize_registry();

  CU_pSuite ai_suite = CU_add_suite("AI Tests", NULL, NULL);
  CU_pSuite gameboard_suit = CU_add_suite("GameBoard Tests", NULL, NULL);

  CU_add_test(ai_suite, "initializeAi", test_initializeAi);
  CU_add_test(ai_suite, "copyBoard", test_copyBoard);

  CU_add_test(gameboard_suit, "initializeGameBoard", test_initializeGameBoard);
  CU_add_test(gameboard_suit, "playPlayer", test_playPlayer);
  CU_add_test(gameboard_suit, "checkWin", test_checkWin);

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();

  CU_cleanup_registry();
  return CU_get_error();
}
