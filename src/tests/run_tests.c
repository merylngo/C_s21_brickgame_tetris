#include "run_tests.h"

int main(void) {
  int failed = 0;
  int total = 0;

  Suite* list[] = {create_remove_test(), NULL};

  for (int i = 0; list[i]; i++) {
    SRunner* sr = srunner_create(list[i]);

    srunner_set_fork_status(sr, CK_NOFORK);

    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    total += srunner_ntests_run(sr);

    srunner_free(sr);
  }

  printf(RED_BCGR WHITE_FONT " >>> FAILED : %-3d <<< " RESET_COLORS "\n",
         failed);
  printf(GREEN_BCGR WHITE_FONT " >>> SUCCESS: %-3d <<< " RESET_COLORS "\n",
         total - failed);
  printf(GREEN_BCGR WHITE_FONT " >>> TOTAL: %-3d <<<  " RESET_COLORS "\n",
         total);

  return 0;
}
