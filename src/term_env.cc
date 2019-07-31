#include <termios.h>
#include <unistd.h>

#include "term_env.hh"

term::env::env(termios *inner) {
	tcgetattr(STDIN_FILENO, &outer);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, inner);
}

term::env::~env() {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &outer);
}

term::env::builder::builder() {
	tcgetattr(STDIN_FILENO, &inner);
}

term::env term::env::builder::build() {
	term::env env(&inner);
	return env;
}

term::env::builder *term::env::builder::add_iflags(tcflag_t flags) {
	inner.c_iflag |= flags;
	return this;
}
term::env::builder *term::env::builder::add_oflags(tcflag_t flags) {
	inner.c_oflag |= flags;
	return this;
}
term::env::builder *term::env::builder::add_cflags(tcflag_t flags) {
	inner.c_cflag |= flags;
	return this;
}
term::env::builder *term::env::builder::add_lflags(tcflag_t flags) {
	inner.c_lflag |= flags;
	return this;
}
term::env::builder *term::env::builder::rem_iflags(tcflag_t flags) {
	inner.c_iflag &= ~flags;
	return this;
}
term::env::builder *term::env::builder::rem_oflags(tcflag_t flags) {
	inner.c_oflag &= ~flags;
	return this;
}
term::env::builder *term::env::builder::rem_cflags(tcflag_t flags) {
	inner.c_cflag &= ~flags;
	return this;
}
term::env::builder *term::env::builder::rem_lflags(tcflag_t flags) {
	inner.c_lflag &= ~flags;
	return this;
}

term::env::builder *term::env::builder::set_cc(int ind, cc_t ch) {
	inner.c_cc[ind] = ch;
	return this;
}

term::env term::env::raw() {
	term::env::builder b;

	return
	b.add_cflags(CS8)
	->rem_iflags(BRKINT | ICRNL | INPCK | ISTRIP | IXON)
	->rem_oflags(OPOST)
	->rem_lflags(ECHO | ICANON | IEXTEN | ISIG);
	->build();
}
