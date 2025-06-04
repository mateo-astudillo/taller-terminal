#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  unsigned short value; // puntaje 1 a 5
  char message[255];    // mensaje
  char user[255];       // mensaje
} SCORE;

int print_version() {
  printf("Score V1.0");
  return EXIT_SUCCESS;
}

int print_help() {
  printf("Usage:\n  score COMMAND [OPTIONS]...\n");
  printf("Commands:\n  help\n  insert\n  get\n");
  printf("insert options:\n  --message string\tAdd a comment to the score\n");
  printf("  --user string\t\tmakes the score not anonymous\n");
  return EXIT_SUCCESS;
}

int insert_score(SCORE *score) {
  FILE *score_file = fopen("./score.csv", "a");
  if (score_file == NULL)
    return EXIT_FAILURE;
  fprintf(score_file, "%d,%s,%s\n", score->value, score->message, score->user);
  fclose(score_file);
  return EXIT_SUCCESS;
}

int get_all() {
  FILE *score_file = fopen("./score.csv", "r");
  char linea[1000];
  if (score_file == NULL)
    return EXIT_FAILURE;
  while (fgets(linea, sizeof(linea), score_file) != NULL) {
    printf("%s", linea);
  }
  fclose(score_file);
  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  if (argc < 2)
    return print_version();
  char *arg = argv[1];
  if (!strcmp("help", arg))
    return print_help();
  if (!strcmp("insert", arg)) {
    SCORE score = {(unsigned short)atoi(argv[2]), "", ""};
    for (int i = 3; i < argc - 1; i++) {
      if (!strcmp("--message", argv[i]))
        strcpy(score.message, argv[i + 1]);
      if (!strcmp("--user", argv[i]))
        strcpy(score.user, argv[i + 1]);
    }
    return insert_score(&score);
  }
  if (!strcmp("get", arg))
    return get_all();
  return EXIT_FAILURE;
}
