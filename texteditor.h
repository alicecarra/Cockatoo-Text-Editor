#ifndef _TEXTEDITOR_H_
#define _TEXTEDITOR_H_

#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE 

#define _VERSION "0.0.2"
#define _TAB_STOP 8
#define _QUIT_TIMES 3

/*** includes ***/
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

/*** defines ***/
#define CTRL_KEY(k) ((k) & 0x1f)

enum editorKey{
	BACKSPACE = 127,
	ARROW_LEFT = 1000,
	ARROW_RIGHT,
	ARROW_UP,
	ARROW_DOWN,
	DEL_KEY,
	HOME_KEY,
	END_KEY,
	PAGE_UP,
	PAGE_DOWN
};

/*** data ***/
typedef struct erow{
	int size;
	int rsize;
	char *chars;
	char *render;
} erow;

struct editorConfig{
	int cx, cy;
	int rx;
	int rowoff;
	int coloff;
	int screenrows;
	int screencols;
	int numrows;
	erow *row;
	int dirty;
	char *filename;
	char statusmsg[80];
	time_t statusmsg_time;
	struct termios orig_termios;
};


/*** terminal ***/
void die(const char *s);
void disableRawMode();
void enableRawMode();
int editorReadKey();
int getCursorPosition(int *rows, int *cols);
int getWindowSize(int *rows, int *cols);

/*** row operations ***/
int editorRowCxToRx(erow *row, int cx);
void editorUpdateRow(erow *row);
void editorInsertRow(int at, char *s, size_t len);
void editorFreeRow(erow *row);
void editorFreeRow(erow *row);
void editorDelRow(int at);
void editorRowAppendString(erow *row, char *s, size_t len);
void editorRowDelChar(erow *row, int at);

/*** editor operations ***/
void editorInsertChar(int c);
void editorInserNewline();
void editorDelChar();

/*** file I/O ***/
void editorOpen();

/*** append buffer ***/
#define ABUF_INIT {NULL, 0}

struct abuf{
	char *b;
	int len;
};

void abAppend(struct abuf *b, const char *s, int len);
void abFree(struct abuf *ab);

/*** output ***/
void editorDrawStatusBat(struct abuf *ab);
void editorDrawRows();
void editorDrawMessageBar(struct abuf *ab);
void editorRefreshScreen();
void editorScroll();
void editorSetStatusMessage(const char *fmt, ...);

/*** input ***/
void editorProcessKeypress();
void editorMoveCursor(int key);

/** init **/
void initEditor();

#endif  //_TEXTEDITOR_H_
