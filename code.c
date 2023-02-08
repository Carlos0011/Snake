#include <ncurses.h>
#include <unistd.h>

#define DELAY 200000

// Representação da cobra como uma lista de coordenadas (x, y)
struct Snake {
  int x;
  int y;
  struct Snake *next;
};

// Função para adicionar um segmento à cobra
void add_segment(struct Snake *snake) {
  struct Snake *new_segment = malloc(sizeof(struct Snake));
  new_segment->x = snake->x;
  new_segment->y = snake->y;
  new_segment->next = snake->next;
  snake->next = new_segment;
}

// Função para mover a cobra em uma direção específica
void move_snake(struct Snake *snake, int dx, int dy) {
  add_segment(snake);
  snake->x += dx;
  snake->y += dy;
  struct Snake *segment = snake->next;
  while (segment->next != NULL) {
    segment->x = segment->next->x;
    segment->y = segment->next->y;
    segment = segment->next;
  }
  struct Snake *last_segment = segment;
  last_segment->x = snake->x;
  last_segment->y = snake->y;
}

int main(void) {
  // Inicialização da tela
  initscr();
  noecho();
  curs_set(FALSE);
  nodelay(stdscr, TRUE);

  // Inicialização da cobra
  struct Snake snake;
  snake.x = COLS / 2;
  snake.y = LINES / 2;
  snake.next = NULL;
  add_segment(&snake);

  int dx = 1;
  int dy = 0;
  while (1) {
    // Atualização da tela
    clear();
    struct Snake *segment = &snake;
    while (segment != NULL) {
      mvprintw(segment->y, segment->x, "*");
      segment = segment->next;
    }
    refresh();

    // Verificação de colisão
    if (snake.x <= 0 || snake.x >= COLS - 1 || snake.y <= 0 || snake.y >= LINES - 1) {
      break;
    }

    // Captura de entrada do usuário
    int c = getch();
    switch (c) {
      case 'a':
        dx = -1;
        dy = 0;
        break;
      case 'd':
        dx = 1;
        dy = 0;
        break;
      case 'w':
        dx = 0;
        dy = -1;
        break;
      case 's':
        dx = 0;
        dy = 1;
