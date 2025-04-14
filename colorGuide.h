/* Ansi color template for C
 * by Albert Tambwe Miñón Apr/2025
 *
 * based on the guide by JBlond
 * https://gist.github.com/JBlond/2fea43a3049b38287e5e9cefc87b2124
 */

// Reset color style
#define R_RESET   "\x1b[0m"

// Regular Colors
#define R_BLACK   "\x1b[30m"
#define R_RED     "\x1b[31m"
#define R_GREEN   "\x1b[32m"
#define R_YELLOW  "\x1b[33m"
#define R_BLUE    "\x1b[34m"
#define R_MAGENTA "\x1b[35m"
#define R_CYAN    "\x1b[36m"
#define R_WHITE   "\x1b[36m"

// Bold Colors
#define B_BLACK   "\x1b[1;30m"
#define B_RED     "\x1b[1;31m"
#define B_GREEN   "\x1b[1;32m"
#define B_YELLOW  "\x1b[1;33m"
#define B_BLUE    "\x1b[1;34m"
#define B_MAGENTA "\x1b[1;35m"
#define B_CYAN    "\x1b[1;36m"
#define B_WHITE   "\x1b[1;37m"

// Underline Colors
#define U_BLACK   "\x1b[4;30m"
#define U_RED     "\x1b[4;31m"
#define U_GREEN   "\x1b[4;32m"
#define U_YELLOW  "\x1b[4;33m"
#define U_BLUE    "\x1b[4;34m"
#define U_MAGENTA "\x1b[4;35m"
#define U_CYAN    "\x1b[4;36m"
#define U_WHITE   "\x1b[4;37m"

// Bold Underlines Colors
#define BU_BLACK   "\x1b[1;4;30m"
#define BU_RED     "\x1b[1;4;31m"
#define BU_GREEN   "\x1b[1;4;32m"
#define BU_YELLOW  "\x1b[1;4;33m"
#define BU_BLUE    "\x1b[1;4;34m"
#define BU_MAGENTA "\x1b[1;4;35m"
#define BU_CYAN    "\x1b[1;4;36m"
#define BU_WHITE   "\x1b[1;4;37m"

// Background Colors
#define BG_BLACK   "\x1b[40m"
#define BG_RED     "\x1b[41m"
#define BG_GREEN   "\x1b[42m"
#define BG_YELLOW  "\x1b[43m"
#define BG_BLUE    "\x1b[44m"
#define BG_MAGENTA "\x1b[45m"
#define BG_CYAN    "\x1b[46m"
#define BG_WHITE   "\x1b[47m"

// High Intensty Colors
#define HI_BLACK   "\x1b[0;90m"
#define HI_RED     "\x1b[0;91m"
#define HI_GREEN   "\x1b[0;92m"
#define HI_YELLOW  "\x1b[0;93m"
#define HI_BLUE    "\x1b[0;94m"
#define HI_MAGENTA "\x1b[0;95m"
#define HI_CYAN    "\x1b[0;96m"
#define HI_WHITE   "\x1b[0;97m"

// Bold High Intensty Colors
#define BHI_BLACK   "\x1b[1;90m"
#define BHI_RED     "\x1b[1;91m"
#define BHI_GREEN   "\x1b[1;92m"
#define BHI_YELLOW  "\x1b[1;93m"
#define BHI_BLUE    "\x1b[1;94m"
#define BHI_MAGENTA "\x1b[1;95m"
#define BHI_CYAN    "\x1b[1;96m"
#define BHI_WHITE   "\x1b[1;97m"

// High Intensty Background Colors
#define HIB_BLACK   "\x1b[0;100m"
#define HIB_RED     "\x1b[0;101m"
#define HIB_GREEN   "\x1b[0;102m"
#define HIB_YELLOW  "\x1b[0;103m"
#define HIB_BLUE    "\x1b[0;104m"
#define HIB_MAGENTA "\x1b[0;105m"
#define HIB_CYAN    "\x1b[0;106m"
#define HIB_WHITE   "\x1b[0;107m"