
void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);

bool is_complete(const char board[9][9]);

bool make_move(const char* position, char digit, char board[9][9]);

bool save_board(const char* filename , const char board[9][9]);

bool solve_board(char board[9][9]);

void move_to_blank_space(const char board[9][9], int &row_index, int &column_index, char *position);

bool row_check(int row_index, char digit, const char board[9][9]);

bool column_check(int column_index, char digit, const char board[9][9]);

bool box_check(int row_index, int column_index, char digit, const char board[9][9]);

bool coordinates_check(int row, int column);

bool is_blank(int row_index, int column_index, const char board[9][9]);

int letter_to_index(char character);

int number_to_index(char character);

char index_to_letter(int number);

char index_to_number(int number);


