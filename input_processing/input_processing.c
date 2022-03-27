#include "input_processing.h"

int process_data(int argc, char * argv[]) {
  int opt, n;
  /*
  '-' - обработка non-option-аргументов вместо их перемещения в конец argv. Если выставляется, то первым
  ':' - отключение печати ошибок и обработка ошибки отсутствия аргумента :. Если выставляется, то перед параметрами
  'n::' - опциональный параметр n. Валидно -n или -nvalue без пробела. -n value - это -n и non-option value
  'c:' - параметр c с обязательным аргументом
  'h' - параметр-флаг
  */
  char *opts = "-:n::c:h", c;

  printf("Got %d args\n", argc);

  // opterr = 0; // отключает печать ошибок от getopt при отсутствии : в начале

  while ((opt = getopt(argc, argv, opts)) != -1) {
    printf("optopt=%c, opt=%c, optarg=%s\n", optopt, opt, optarg);
    switch (opt) {
      case 'n': n = optarg ? atoi(optarg) : 0; break;
      case 'c': c = optarg[0]; break;
      case 'h': printf("Usage: %s [-h|-n10|-c 'a'] <args>\n", argv[0]); break;
      case '?': printf("Unknown option: %c\n", optopt); break;
      case ':': printf("Missing arg for %c\n", optopt); break; // ':' in opts
      case  1 : printf("Non-option arg: %s\n", optarg); break; // '-' in opts
      default: break;
    }
  }

  return n;

}


