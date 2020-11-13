#ifndef _TEXTEDITOR_H_
#define _TEXTEDITOR_H_

/*** includes ***/
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

/*** defines ***/
#define CTRL_KEY(k) ((k) & 0x1f)

/*** data ***/
struct editorConfig{
	int cx, cy;
	int screenrows;
	int screencols;
	struct termios orig_termios;
};


/*** terminal ***/
void die(const char *s);

void disableRawMode();

void enableRawMode();

char editorReadKey();

int getCursorPosition(int *rows, int *cols);

int getWindowSize(int *rows, int *cols);

/*** append buffer ***/
#define ABUF_INIT {NULL, 0}

struct abuf{
	char *b;
	int len;
};

void abAppend(struct abuf *b, const char *s, int len);

void abFree(struct abuf *ab);

/*** output ***/
void editorDrawRows();

void editorRefreshScreen();

/*** input ***/
void editorProcessKeypress();

/** init **/
void initEditor();

#endif  //_TEXTEDITOR_H_
